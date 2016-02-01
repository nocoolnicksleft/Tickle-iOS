/*---------------------------------------------------------------------------------




---------------------------------------------------------------------------------*/

#include "common.h"

#include "sprite.h"
#include "pinky.h"
#include "button.h"
#include "bubbles.h"
#include "menu.h"
#include "beach.h"
#include "screen.h"
#include "screenengine.h"
#include "screenframebuffer.h"
#include "background.h"
#include "rectangle.h"
#include "flipbook.h"
#include "wconsole.h"
#include "bitmap.h"
#include "font.h"
#include "controlbutton.h"

char debstr[80];

bool flag_vblank = false;
uint32 real_frames = 0;

void Interrupt_VBlank()
{
  flag_vblank = true;
  ++real_frames;
}


int LastPenX = 0;
int LastPenY = 0;

void Interrupt_MainTick()
{
	inactivity_counter++;
	TIMER0_DATA = TIMER_FREQ_1024(10);
}


// Global Status
#define STATUS_INTRO 0
#define STATUS_RUN 1

#define RUNSTATUS_MENU 0
#define RUNSTATUS_BUBBLES 1
#define RUNSTATUS_BEACH 2

// Pinky
int global_status = RUNSTATUS_MENU;
int run_status = STATUS_INTRO;
int global_frame = 0;

#define INTRO_STATUS_FADEIN 0
#define INTRO_STATUS_STAY 1
#define INTRO_STATUS_FADEOUT 2

int intro_status = INTRO_STATUS_FADEIN;

const int frame_delay = 1;
int frame_countdown = 0;

ScreenEngine * topscreen = 0;
ScreenFramebuffer * subscreen = 0;

Background * backdrop_top = 0;

Pinky * pinky = 0;

WConsole * textfenster = 0;

void FromBubblesToMenu()
{
	sprintf(debstr,"Bubbles Unloading: %8ld", gAllocatedMemory);  
	DebugPrint(debstr);

	InactivityAction = 0;

	Bubbles::Unload();

	Menu::Load();
	Menu::Run(subscreen);
	run_status = RUNSTATUS_MENU;
	
	sprintf(debstr,"mem %8ld", gAllocatedMemory);  
	DebugPrint(debstr);

}

void FromBeachToMenu()
{
	sprintf(debstr,"Beach Unloading: %8ld", gAllocatedMemory);  
	DebugPrint(debstr);

	InactivityAction = 0;
	Beach::Unload();

	sprintf(debstr,"Menu Loading: %8ld", gAllocatedMemory);  
	DebugPrint(debstr);

	Menu::Load();

	sprintf(debstr,"Menu Starting: %8ld", gAllocatedMemory);  
	DebugPrint(debstr);

	Menu::Run(subscreen);

	sprintf(debstr,"Menu Running: %8ld", gAllocatedMemory);  
	DebugPrint(debstr);
	run_status = RUNSTATUS_MENU;

	sprintf(debstr,"mem %8ld", gAllocatedMemory);  
	DebugPrint(debstr);
}

void Textfenster_MovedOut()
{
	textfenster->Invisible();
}

void ToggleTextfenster()
{
	if (textfenster->IsVisible()) 
	{
		textfenster->AnimatePosition(-256,0,20,AnimationCurveAccelerating);
		textfenster->OnAnimationCompleted = &Textfenster_MovedOut;
	}
	else 
	{
		textfenster->Visible();
		textfenster->OnAnimationCompleted = 0;
		textfenster->AnimatePosition(0,0,20,AnimationCurveSlowing);
	}
}

void FromMenuToBubbles()
{
	Menu::Unload();
	Bubbles::Load();
	Bubbles::Run(subscreen);
	run_status = RUNSTATUS_BUBBLES;
}

void FromMenuToBeach()
{
	sprintf(debstr,"Menu Unloading: %8ld", gAllocatedMemory);  
	DebugPrint(debstr);
	Menu::Unload();
	sprintf(debstr,"Beach Loading: %8ld", gAllocatedMemory);  
	DebugPrint(debstr);
	Beach::Load();
	sprintf(debstr,"Beach Starting: %8ld", gAllocatedMemory);  
	DebugPrint(debstr);
	Beach::Run(subscreen);
	sprintf(debstr,"Beach Running: %8ld", gAllocatedMemory);  
	DebugPrint(debstr);
	run_status = RUNSTATUS_BEACH;
}


//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------

	gTrackAllocation = true;

	defaultExceptionHandler();

	

	debstr[0] = 0;
	

	WAIT_CR &= ~0x80;

	POWER_CR = POWER_LCD | POWER_2D_A | POWER_2D_B | POWER_SWAP_LCDS;

	POWER_CR &= ~POWER_SWAP_LCDS;

	vramSetMainBanks(	
		VRAM_A_LCD,
		VRAM_B_LCD,
		VRAM_C_SUB_BG_0x6200000,
		VRAM_D_SUB_SPRITE
		);

	setGenericSound(	11025,	/* sample rate */
		127,	/* volume */
		64,		/* panning */
		1 );	/* sound format (raw 8-bit signed) */

	
	TIMER0_CR = ( TIMER_IRQ_REQ | TIMER_ENABLE | 3);
	TIMER0_DATA = TIMER_FREQ_1024(10);

	irqInit();
	irqSet(IRQ_VBLANK, Interrupt_VBlank);
	irqSet(IRQ_TIMER0, Interrupt_MainTick);

	
	InitGBFS();



	/******************************************************************/
	/* PERFORMANCE TEST                                               */
	/******************************************************************/
	/*
	char testresult [120] = "x";
	
	Bitmap * test1 = new Bitmap(256,192);
	Bitmap * test2 = new Bitmap(256,192);

	Bitmap * testpinky = new Bitmap((int16)bigpinky_bubbles_drynaked_6_rle_bin,(int16)alphabigpinky_bubbles_drynaked_6_rle_bin,true);

	uint32 start_tick = real_frames;
	for (int i = 0; i < 1000; i++) test1->CopyBuffer(test2);
	uint32 ticks_test1 = real_frames - start_tick;
	
	start_tick = real_frames;
	for (int i = 0; i < 1000; i++) test2->DrawBitmapAlpha(testpinky,10,10);
	uint32 ticks_test2 = real_frames - start_tick;

	start_tick = real_frames;
	Rectangle * rect = new Rectangle(10,10,100,100);
	for (int i = 0; i < 1000; i++) test2->DrawRectangle(rect,0,1);
	uint32 ticks_test3 = real_frames - start_tick;
	delete rect;

	Font * font = new Font(FontTypeComicSans10);
	rect = new Rectangle(2,55,110,40);
	start_tick = real_frames;
	for (int i = 0; i < 1000; i++) test2->DrawText(font, rect, "Comic Sans MS 10pt auch sehr schön", 1 << 15);
	uint32 ticks_test4 = real_frames - start_tick;

	start_tick = real_frames;
//	for (int i = 0; i < 1000; i++) test2->FadeLow(128);
	uint32 ticks_test5 = real_frames - start_tick;

	sprintf(testresult,"plain %d\nalpha %d\nrect %d\nfont %d\nfade %d",ticks_test1,ticks_test2,ticks_test3,ticks_test4,ticks_test5);

	delete rect;
	delete font;
	delete test1;
	delete test2;
	delete testpinky;
	*/
	/******************************************************************/


	ControlButton::Init();  // intialize static sound data buffer

	topscreen = new ScreenEngine(1);
	subscreen = new ScreenFramebuffer(0,VRAM_A);
	subscreen->Visible();

	backdrop_top = new Background(1,3,0,0);

	pinky = new Pinky(ATTR1_SIZE_64);

	textfenster = new WConsole(new Rectangle(0,0,256,95),6,24,new Font(FontTypeLucidaConsole10) );
	textfenster->Print("Lucida Console 10pt\nfeste Laufweite\n");
	textfenster->Print("\nund total hübsch.\nHat auch Sternchen **** ");
	sprintf(debstr,"%c%c%c%c\n",NDSHeader.gameCode[0],NDSHeader.gameCode[1],NDSHeader.gameCode[2],NDSHeader.gameCode[3]);
	textfenster->Print(debstr);
	textfenster->Prepare();
	textfenster->Position(-256,00);
	textfenster->AlphaEnable();
	textfenster->SetAlpha(235);
	textfenster->Invisible();

startover:
	topscreen->SetMode(MODE_5_2D |
		DISPLAY_SPR_ACTIVE |
		DISPLAY_SPR_1D |
		DISPLAY_BG3_ACTIVE);

	subscreen->SetMode(MODE_FB0);

	backdrop_top->Priority(3);
	backdrop_top->Wrap(0);
	backdrop_top->Type(BG_BMP8_256x256);
	backdrop_top->OffsetY();

	topscreen->ClearSprites();
	topscreen->FadeFromBlack(10);
	topscreen->Display();

	bitblt8rle((uint8 *)BG_BMP_RAM_SUB(0),256,0,0,(u8 *)LoadFile(banner_bg_rle_bin));

	topscreen->LoadBgPal(LoadFile(banner_bg_pal_bin));

	global_frame = 0;
    global_status = STATUS_INTRO;	
	run_status = RUNSTATUS_MENU;

	// VBLANK nochmal zurücksetzen, ist vielleicht schon etwas spät...
	flag_vblank = false;

	while(1) {

		/*************************************************************************/
		/* DISPLAY                                                               */
		/*************************************************************************/
		if (flag_vblank) {
			flag_vblank = false;

			/************************************/
			/* BUFFER TO SCREEN                 */
			/* Bei jedem VBLANK (60 frm/sec)    */
			/************************************/			

			/************************************/
			/* FRAME COUNTDOWN                  */
			/************************************/
			if (frame_countdown) {
				frame_countdown--;
			}
			else 
			/************************************/
			/* OBJEKTE ANZEIGEN                 */
			/* Schreiben in WRAM Buffer         */
			/* Bei jedem 2. VBLANK (30 frm/sec) */    
			/************************************/
			{
				subscreen->BufferToScreen();

				subscreen->Display();
				subscreen->Prepare();

				if (global_status == STATUS_RUN)
				{	
					if (pinky->X() > 150) {
						backdrop_top->OffsetXDelta(pinky->X()-150);
						pinky->X(150);
					}
					else {
						if (pinky->X() < 50) {
							backdrop_top->OffsetXDelta(-(50 - pinky->X()));
							pinky->X(50);
						}
					}
				}

				backdrop_top->Display();
				topscreen->Display();

				global_frame++;
				frame_countdown = frame_delay; // Delay to 29.9 frames/sec
			}

		} // if flag_vblank


		/*************************************************************************/
		/* MESSAGES VERARBEITEN                                                  */
		/*************************************************************************/
		
		while (int msg = ReadMessage())
		{
			if (msg == PM_STARTBUBBLES) FromMenuToBubbles();
			else if (msg == PM_TOGGLETEXTFENSTER) ToggleTextfenster();
			else if (msg == PM_STARTMENU) {
				if (run_status == RUNSTATUS_BEACH) FromBeachToMenu();
				else FromBubblesToMenu();
			}
			else if (msg == PM_STARTBEACH) FromMenuToBeach();
		}

		/*************************************************************************/
		/* INPUT VERARBEITEN                                                     */
		/*************************************************************************/

		if (global_status == STATUS_INTRO) {

			if (global_frame == 80) { 	
					intro_status = INTRO_STATUS_FADEOUT;
					topscreen->FadeToBlack(20);
			}
			// STARTUP RUN MODE
			if (global_frame == 100) { 
				DebugPrint("FRAME100");

				backdrop_top->Wrap(1);
				backdrop_top->Type(BG_BMP8_512x256);

				backdrop_top->OffsetX(0);
				backdrop_top->OffsetY(32);

				bitblt8rle((uint8 *)BG_BMP_RAM_SUB(0),512,0,0,(u8 *)LoadFile(desert_rle_bin));
				topscreen->LoadBgPal(LoadFile(desert_pal_bin));


				topscreen->LoadSpritePal(LoadFile(littlepinky_pal_bin));

				topscreen->addSprite(pinky);

				pinky->Move(120,120);
				pinky->Enable();
				
				subscreen->LoadCompressedBackground(LoadFile(banner_rle_bin));

				subscreen->AddWindow(textfenster,200);

				Menu::Load();
				Menu::Run(subscreen);

				topscreen->FadeFromBlack(25);
				subscreen->FadeFromBlack(25);
				
				global_status = STATUS_RUN;
			} 

		} else if (global_status == STATUS_RUN)
		{
			scanKeys();

			if (run_status == RUNSTATUS_MENU)
			{
				if ( (keysDown() & KEY_LEFT) || (keysHeld() & KEY_LEFT)) pinky->Left();
				if ( (keysDown() & KEY_RIGHT) || (keysHeld() & KEY_RIGHT)) pinky->Right();
				if (keysDown() & KEY_UP);
				if (keysDown() & KEY_DOWN) pinky->Turn(PinkyHeadingFront);
				if (keysDown() & KEY_A);

				if ((keysDown() & KEY_B) || (keysHeld() & KEY_B))  {
					if (pinky->Heading() != PinkyHeadingFront) pinky->Turn(PinkyHeadingFront);
					else pinky->Fly();
				}

				if ((keysDown() & KEY_X) || (keysHeld() & KEY_X)) pinky->Jump();
				if (keysDown() & KEY_Y) pinky->Fall();
			}
			
			if (run_status == RUNSTATUS_BEACH)
			{
				Beach::Keys(keysDown(), keysHeld());

			}

			if (keysDown() & KEY_SELECT) ToggleTextfenster();
			
			//if (keysDown() & KEY_START) {
			//	break;
			//}

			//if (keysDown() & KEY_L); 
			//if (keysDown() & KEY_R);

			touchPosition touchXY = touchReadXY();

			if (keysDown() & KEY_TOUCH) {
				subscreen->MsgPenDown(touchXY.px,touchXY.py);
				LastPenX = touchXY.px;
				LastPenY = touchXY.py;
				inactivity_counter = 0;
			}

			else if (keysUp() & KEY_TOUCH) {
				subscreen->MsgPenUp(touchXY.px,touchXY.py);
				inactivity_counter = 0;
			}

			else if (keysHeld() & KEY_TOUCH) {
				if (touchXY.px || touchXY.py)
				{
				if ( (touchXY.px != LastPenX) || (touchXY.py != LastPenY) )
				{
					subscreen->MsgPenMove(touchXY.px,touchXY.py);
					LastPenX = touchXY.px;
					LastPenY = touchXY.py;
				}
				}
				inactivity_counter = 0;
			}

		}

		if (inactivity_counter > inactivity_threshold)
		{
			if (InactivityAction) (*InactivityAction)();
			inactivity_counter = 0;
		}

	}

	goto startover;

	return 0;
}
