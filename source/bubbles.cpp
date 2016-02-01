
#include "bubbles.h"

#define BUTTON_ROW_1_Y 146
#define BUTTON_ROW_2_Y 165
#define BUTTON_COL_1_X 30
#define BUTTON_COL_2_X 100
#define BUTTON_COL_3_X 170

ScreenFramebuffer * Bubbles::screen = 0;

Flipbook * Bubbles::wasserhahn = 0;
Flipbook * Bubbles::schaum = 0;
Flipbook * Bubbles::handtuch = 0;
Flipbook * Bubbles::schaumA = 0;
Flipbook * Bubbles::schaumB = 0;
Flipbook * Bubbles::schaumC = 0;
Flipbook * Bubbles::planschen = 0;
ControlButton * Bubbles::buttonBack = 0;

uint16 Bubbles::bubbles_status = 0;
uint16 Bubbles::bubbles_temp = 0;
uint16 Bubbles::bubbles_wasserstand = 0;
uint16 Bubbles::bubbles_annoyance = 0;
uint16 Bubbles::bubbles_selfcontrol = 0;

uint16 Bubbles::handtuch_start_x = 0;
uint16 Bubbles::handtuch_start_y = 0;


Bubbles::Bubbles()
{

}

Bubbles::~Bubbles()
{

}

void Bubbles::Init()
{
	Unload();
}

void Bubbles::BackButton_OnAnimationCompleted(ControlButton * button, uint8 state)
{
	SendMessage(PM_STARTMENU);
}

void Bubbles::Load()
{
	Init();


	uint16 * file_inactive = LoadFile(button_inactive_rle_bin);
	uint16 * file_active = LoadFile(button_active_rle_bin);
	uint16 * file_pushed = LoadFile(button_pressed_rle_bin);
	
	buttonBack  = new ControlButton(new Rectangle(BUTTON_COL_3_X,BUTTON_ROW_2_Y,61,15),"Back",file_inactive,file_active,file_pushed,3);
	buttonBack->OnReset = &Bubbles::BackButton_OnAnimationCompleted;


	wasserhahn = new Flipbook(new Rectangle(30,25,32,32),"wasserhahn");
	wasserhahn->OnAnimationCompleted = &Bubbles_Wasserhahn_OnAnimationCompleted;
	wasserhahn->LoadAnimation(BUBBLES_WATER,extras_bubbles_tap_ani_bin,ar_extras_bubbles_tap);
	wasserhahn->LoadAnimation(BUBBLES_HOTWATER,extras_bubbles_taphot_ani_bin,ar_extras_bubbles_taphot);
	wasserhahn->AddSound(BUBBLES_HOTWATER,0,rausch_bin);
	wasserhahn->LoadAnimation(BUBBLES_COLDWATER,extras_bubbles_tapcold_ani_bin,ar_extras_bubbles_tapcold);
	wasserhahn->AddSound(BUBBLES_COLDWATER,0,rausch_bin);
	wasserhahn->AddAction(new Rectangle(0,0,15,15),0,BUBBLES_HOTWATER);
	wasserhahn->AddAction(new Rectangle(16,0,16,15),0,BUBBLES_COLDWATER);
	wasserhahn->Invisible();

	schaum = new Flipbook(new Rectangle(30,25,32,32),"schaum");
	schaum->OnAnimationCompleted = &Bubbles_Schaum_OnAnimationCompleted;
	schaum->LoadAnimation(BUBBLES_SCHAUM,extras_bubbles_foam_ani_bin,ar_extras_bubbles_foam);
	schaum->AddAction(new Rectangle(0,0,32,32),0,BUBBLES_SCHAUM);
	schaum->AddSound(BUBBLES_SCHAUM,7,blubb_bin);
	schaum->Invisible();

	schaumA = new Flipbook(new Rectangle(54,47,148,40),"schaumA");
	schaumA->LoadAnimationAlpha(0,bigpinky_bubbles_foamA_ani_bin,ar_bigpinky_bubbles_foamA,ar_	);
	schaumA->Invisible();
	schaumA->Disable();

	schaumB = new Flipbook(new Rectangle(54,47,148,40),"schaumB");
	schaumB->LoadAnimationAlpha(0,bigpinky_bubbles_foamB_ani_bin,ar_bigpinky_bubbles_foamB,ar_alphabigpinky_bubbles_foamB);
	schaumB->Invisible();
	schaumB->Disable();

	schaumC = new Flipbook(new Rectangle(54,47,148,40),"schaumC");
	schaumC->LoadAnimationAlpha(0,bigpinky_bubbles_foamC_ani_bin,ar_bigpinky_bubbles_foamC,ar_alphabigpinky_bubbles_foamC);
	schaumC->Invisible();
	schaumC->Disable();

	handtuch = new Flipbook(new Rectangle(30,25,120,120),"handtuch");
	handtuch->LoadAnimationAlpha(BUBBLES_TOWEL_DRY,bigpinky_bubbles_towel_ani_bin,ar_bigpinky_bubbles_towel,ar_alphabigpinky_bubbles_towel);
	handtuch->LoadAnimationAlpha(BUBBLES_TOWEL_BACK,bigpinky_bubbles_towelback_ani_bin,ar_bigpinky_bubbles_towelback,ar_alphabigpinky_bubbles_towelback);
	handtuch->AddAction(new Rectangle(95,10,25,100),&Handtuch_Click,-1);
	handtuch->Invisible();
	handtuch->Disable();

	planschen = new Flipbook(new Rectangle(30,25,120,120),"planschen");
	planschen->OnAnimationCompleted = &Bubbles_OnAnimationCompleted;

	planschen->LoadAnimationAlpha(BUBBLES_WALKRIGHT,bigpinky_allgemein_simpleright_ani_bin,ar_bigpinky_allgemein_simpleright,ar_alphabigpinky_allgemein_simpleright);
	planschen->LoadAnimationAlpha(BUBBLES_TURNRIGHTBACK,bigpinky_bubbles_turnrightback_ani_bin,ar_bigpinky_bubbles_turnrightback,ar_alphabigpinky_bubbles_turnrightback);
	planschen->LoadAnimationAlpha(BUBBLES_CHECKWATER,bigpinky_bubbles_checkwater_ani_bin,ar_bigpinky_bubbles_checkwater,ar_alphabigpinky_bubbles_checkwater);
	planschen->AddSound(BUBBLES_CHECKWATER,2,plitsch_bin);

	planschen->LoadAnimationAlpha(BUBBLES_COLDSTANDING,bigpinky_bubbles_coldstanding_ani_bin,ar_bigpinky_bubbles_coldstanding,ar_alphabigpinky_bubbles_coldstanding);
	planschen->LoadAnimationAlpha(BUBBLES_HOTSTANDING,bigpinky_bubbles_hotstanding_ani_bin,ar_bigpinky_bubbles_hotstanding,ar_alphabigpinky_bubbles_hotstanding);
	planschen->LoadAnimationAlpha(BUBBLES_SITDOWN,bigpinky_bubbles_sitdown_ani_bin,ar_bigpinky_bubbles_sitdown,ar_alphabigpinky_bubbles_sitdown);
	planschen->LoadAnimationAlpha(BUBBLES_COLDSITTING,bigpinky_bubbles_coldsitting_ani_bin,ar_bigpinky_bubbles_coldsitting,ar_alphabigpinky_bubbles_coldsitting);
	planschen->LoadAnimationAlpha(BUBBLES_HOTSITTING,bigpinky_bubbles_hotsitting_ani_bin,ar_bigpinky_bubbles_hotsitting,ar_alphabigpinky_bubbles_hotsitting);
	planschen->LoadAnimationAlpha(BUBBLES_STANDUP,bigpinky_bubbles_standup_ani_bin,ar_bigpinky_bubbles_standup,ar_alphabigpinky_bubbles_standup);
	planschen->LoadAnimationAlpha(BUBBLES_CLIMBIN,bigpinky_bubbles_climbin_ani_bin,ar_bigpinky_bubbles_climbin,ar_alphabigpinky_bubbles_climbin);
	planschen->AddSound(BUBBLES_CLIMBIN,20,sitdownsplosh_bin);
	planschen->LoadAnimationAlpha(BUBBLES_SPLASH,bigpinky_bubbles_splash_ani_bin,ar_bigpinky_bubbles_splash,ar_alphabigpinky_bubbles_splash);
	planschen->AddSound(BUBBLES_SPLASH,6,splash_bin);
	planschen->LoadAnimationAlpha(BUBBLES_DIVE,bigpinky_bubbles_dive_ani_bin,ar_bigpinky_bubbles_dive,ar_alphabigpinky_bubbles_dive);
	planschen->AddSound(BUBBLES_DIVE,10,splash_bin);
	planschen->LoadAnimationAlpha(BUBBLES_BLINKLEFT,bigpinky_bubbles_blinkleft_ani_bin,ar_bigpinky_bubbles_blinkleft,ar_alphabigpinky_bubbles_blinkleft);
	planschen->LoadAnimationAlpha(BUBBLES_TURNSITTINGFRONT,bigpinky_bubbles_turnsittingfront_ani_bin,ar_bigpinky_bubbles_turnsittingfront,ar_alphabigpinky_bubbles_turnsittingfront);
	planschen->LoadAnimationAlpha(BUBBLES_SPLASHFRONT,bigpinky_bubbles_splashfront_ani_bin,ar_bigpinky_bubbles_splashfront,ar_alphabigpinky_bubbles_splashfront);
	planschen->AddSound(BUBBLES_SPLASHFRONT,4,splash_bin);
	planschen->AddSound(BUBBLES_SPLASHFRONT,22,splash_bin);
	planschen->LoadAnimationAlpha(BUBBLES_BLINKFRONT,bigpinky_bubbles_blinkfront_ani_bin,ar_bigpinky_bubbles_blinkfront,ar_alphabigpinky_bubbles_blinkfront);

	planschen->LoadAnimationAlpha(BUBBLES_CLIMBOUT,bigpinky_bubbles_climbout_ani_bin,ar_bigpinky_bubbles_climbout,ar_alphabigpinky_bubbles_climbout);
	planschen->LoadAnimationAlpha(BUBBLES_DRYNAKED,bigpinky_bubbles_drynaked_ani_bin,ar_bigpinky_bubbles_drynaked,ar_alphabigpinky_bubbles_drynaked);
	planschen->LoadAnimationAlpha(BUBBLES_JOYJOY,bigpinky_bubbles_joyjoy_ani_bin,ar_bigpinky_bubbles_joyjoy,ar_alphabigpinky_bubbles_joyjoy);

	planschen->LoadAnimationAlpha(BUBBLES_JUMPOUT,bigpinky_bubbles_jumpout_ani_bin,ar_bigpinky_bubbles_jumpout,ar_alphabigpinky_bubbles_jumpout);
	planschen->LoadAnimationAlpha(BUBBLES_CONTROLCOLD,bigpinky_bubbles_controlcold_ani_bin,ar_bigpinky_bubbles_controlcold,ar_alphabigpinky_bubbles_controlcold);
	planschen->LoadAnimationAlpha(BUBBLES_CONTROLHOT,bigpinky_bubbles_controlhot_ani_bin,ar_bigpinky_bubbles_controlhot,ar_alphabigpinky_bubbles_controlhot);

	planschen->LoadAnimationAlpha(BUBBLES_WALKLEFT,bigpinky_allgemein_simpleleft_ani_bin,ar_bigpinky_allgemein_simpleleft,ar_alphabigpinky_allgemein_simpleleft);

	planschen->AddAction(new Rectangle(20,0,100,100),&OnBubblesPinkyClick,-1);	

}

void Bubbles::Unload()
{
	InactivityAction = 0;
	if (wasserhahn) screen->RemoveWindow(wasserhahn);
	if (schaum) screen->RemoveWindow(schaum);
	if (handtuch) screen->RemoveWindow(handtuch);
	if (schaumA) screen->RemoveWindow(schaumA);
	if (schaumB) screen->RemoveWindow(schaumB);
	if (schaumC) screen->RemoveWindow(schaumC);
	if (planschen) screen->RemoveWindow(planschen);
	if (buttonBack) screen->RemoveWindow(buttonBack);

	if (buttonBack) delete buttonBack;
	if (wasserhahn)	delete wasserhahn;
	if (schaum) delete schaum;
	if (handtuch) delete handtuch;
	if (schaumA) delete schaumA;
	if (schaumB) delete schaumB;
	if (schaumC) delete schaumC;

	if (planschen) delete planschen;

	planschen = 0;
	buttonBack = 0;

	wasserhahn = 0;
	schaum = 0;
	handtuch = 0;
	schaumA = 0;
	schaumB = 0;
	schaumC = 0;

	bubbles_status = 0;
	bubbles_temp = 0;
	bubbles_wasserstand = 0;
	bubbles_annoyance = 0;
	bubbles_selfcontrol = 0;
}

void Bubbles::Run(ScreenFramebuffer * subscreen)
{
	screen = subscreen;

	subscreen->AddWindow(wasserhahn,10);
	subscreen->AddWindow(schaum,11);
	subscreen->AddWindow(schaumA,12);
	subscreen->AddWindow(schaumB,13);
	subscreen->AddWindow(planschen,20);
	subscreen->AddWindow(schaumC,25);
	subscreen->AddWindow(handtuch,26);
	subscreen->AddWindow(buttonBack,100);

	subscreen->LoadCompressedBackground(LoadFile(pommeswanne_rle_bin));

	handtuch->Visible();
	handtuch->Enable();
	handtuch->Set(0,0);

//	handtuch->OnDragStart = &Handtuch_DragStart;
//	handtuch->OnDragMove = &Handtuch_DragMove;
//	handtuch->OnDragEnd = &Handtuch_DragEnd;
//	handtuch->EnablePenCapture();
//	handtuch->Set(BUBBLES_TOWEL_BACK,0);


	schaum->Visible();
	schaum->Enable();
	schaum->Set(0,0);

	schaumA->Set(0,0);
	schaumA->Disable();
	schaumB->Set(0,0);
	schaumB->Disable();
	schaumC->Set(0,0);
	schaumC->Disable();

	wasserhahn->Visible();
	wasserhahn->Enable();
	wasserhahn->Set(0,0);

	planschen->Set(0,0);
	planschen->Position(-98,24);
	planschen->Visible();
	planschen->Enable();

	bubbles_wasserstand = 0;

	bubbles_temp = 10;
	bubbles_status = BUBBLES_STATUS_WAITING;

	subscreen->FadeFromBlack(25);
	subscreen->OnAnimationCompleted = &Bubbles_Start;

	InactivityAction = &OnBubblesInactivity;

}





void Bubbles::Handtuch_DragMove(Window * window, int dx, int dy)
{
	if (bubbles_status == BUBBLES_STATUS_OUT)
	{
		if (!planschen->IsRunning())
		{
			//			char debstr[60];
			//			sprintf(debstr,"Handtuch::Drag dx %d dy %d x %d y %d",dx,dy,handtuch->Position()->Left,handtuch->Position()->Top);
			//			DebugPrint(debstr);

			handtuch->PositionDelta(dx-handtuch_start_x,dy-handtuch_start_y);
			int16 newframe = 0;
			if (handtuch->Position()->Top > 131) handtuch->Position()->Top = 131;


			if (handtuch->Position()->Top > 63) 
			{
				newframe = 35 - ((handtuch->Position()->Top  - 63) / 2);
				handtuch->SetNoPosition(BUBBLES_TOWEL_BACK,newframe);
			}


			handtuch_start_x = dx;
			handtuch_start_y = dy;

		}
	}
}

void Bubbles::Handtuch_DragStart(Window * window, int dx, int dy)
{
	handtuch_start_x = dx;
	handtuch_start_y = dy;
	//			char debstr[60];
	//			sprintf(debstr,"Handtuch::Drag Start dx %d dy %d s_x %d s_y %d",dx,dy,handtuch_start_x,handtuch_start_y);
	//			DebugPrint(debstr);
}

void Bubbles::Handtuch_DragEnd(Window * window, int dx, int dy)
{
	if ( (window->Position()->Top < 100) && (window->Position()->Left > 170) )
	{
		bubbles_status = BUBBLES_STATUS_FINISHED;
		handtuch->AnimatePosition(176,36,handtuch->CurrentFrame(),AnimationCurveLinear);
		handtuch->OnDragStart = 0;
		handtuch->OnDragMove = 0;
		handtuch->OnDragEnd = 0;
		handtuch->DisablePenCapture();
	} else
	{
		//		char debstr[40];
		//		sprintf(debstr,"DragEnd dx %d dy %d left %d top %d",dx,dy,window->Position()->Left,window->Position()->Top);
		//		DebugPrint(debstr);
		handtuch->AnimatePosition(window->Position()->Left,131,handtuch->CurrentFrame(),AnimationCurveLinear);
		handtuch->RunReverse();
	}
}

void Bubbles::Bubbles_OnAnimationCompleted(Flipbook * flipbook, uint16 animationId)
{

	if (animationId == BUBBLES_CONTROLCOLD)
	{
		wasserhahn->Run(BUBBLES_COLDWATER);
	}

	if (animationId == BUBBLES_CONTROLHOT)
	{
		wasserhahn->Run(BUBBLES_HOTWATER);
	}

	if (animationId == BUBBLES_JUMPOUT)
	{
		bubbles_status = BUBBLES_STATUS_DRYING;
		planschen->Run(BUBBLES_WALKLEFT,3);
	}

	if (animationId == BUBBLES_WALKRIGHT) {
		planschen->Run(BUBBLES_JOYJOY);
	}

	if (animationId == BUBBLES_JOYJOY) {
	}

	if (animationId == BUBBLES_TURNRIGHTBACK) {
		planschen->Run(BUBBLES_CHECKWATER);
	}

	else if (animationId == BUBBLES_CHECKWATER)
	{
		if (bubbles_temp == 35) planschen->Run(BUBBLES_CLIMBIN);
		else if (bubbles_temp < 35) planschen->Run(BUBBLES_COLDSTANDING);
		else planschen->Run(BUBBLES_HOTSTANDING);
	}

	else if (animationId == BUBBLES_HOTSTANDING) planschen->Run(BUBBLES_SITDOWN);

	else if (animationId == BUBBLES_COLDSTANDING) planschen->Run(BUBBLES_SITDOWN);

	else if (animationId == BUBBLES_SITDOWN) {
		bubbles_status = BUBBLES_STATUS_SITTING;
	}

	else if (animationId == BUBBLES_CLIMBIN) {
		bubbles_status = BUBBLES_STATUS_BATHINGLEFT;
		planschen->Run(BUBBLES_BLINKLEFT);
	}

	else if (animationId == BUBBLES_STANDUP) {
		planschen->Run(BUBBLES_CHECKWATER);
	}

	else if (animationId == BUBBLES_SPLASH) {
		bubbles_status = BUBBLES_STATUS_BATHINGLEFT2;
		planschen->Run(BUBBLES_BLINKLEFT);
	}
	else if (animationId == BUBBLES_DIVE) {
		bubbles_status = BUBBLES_STATUS_BATHINGLEFT3;
		planschen->Run(BUBBLES_BLINKLEFT);
	}

	else if (animationId == BUBBLES_TURNSITTINGFRONT) 
	{
		bubbles_status = BUBBLES_STATUS_BATHINGFRONT;
		planschen->Run(BUBBLES_SPLASHFRONT);
		schaumC->Visible();
		schaumC->Run(0);
	}
	else if (animationId == BUBBLES_SPLASHFRONT) planschen->Run(BUBBLES_BLINKFRONT);

	else if (animationId == BUBBLES_CLIMBOUT) {
		bubbles_status = BUBBLES_STATUS_DRYING;
		handtuch->Enable();
		handtuch->Run(BUBBLES_TOWEL_DRY);
		planschen->Run(BUBBLES_DRYNAKED);
	}
	else if (animationId == BUBBLES_DRYNAKED) {
		bubbles_status = BUBBLES_STATUS_OUT;
		handtuch->OnDragStart = &Handtuch_DragStart;
		handtuch->OnDragMove = &Handtuch_DragMove;
		handtuch->OnDragEnd = &Handtuch_DragEnd;
		handtuch->EnablePenCapture();
		handtuch->Set(BUBBLES_TOWEL_BACK,0);
	}

}



void Bubbles::Bubbles_Wasserhahn_OnAnimationCompleted(Flipbook * flipbook, uint16 animationId)
{
	wasserhahn->Set(0,0);

	if (
		(bubbles_status == BUBBLES_STATUS_BATHINGLEFT) ||
		(bubbles_status == BUBBLES_STATUS_BATHINGLEFT2) ||
		(bubbles_status == BUBBLES_STATUS_BATHINGLEFT3)
		)
	{
		if (!bubbles_selfcontrol)
		{
			if (bubbles_annoyance > 3) {
				planschen->Run(BUBBLES_JUMPOUT);
			} else {
				if (animationId == BUBBLES_HOTWATER) {
					planschen->Run(BUBBLES_CONTROLCOLD);
				}
				else if (animationId == BUBBLES_COLDWATER) {
					planschen->Run(BUBBLES_CONTROLHOT);
				}
				bubbles_selfcontrol = 1;
				bubbles_annoyance++;
			}
		} else bubbles_selfcontrol = 0;

	}


	if (animationId == BUBBLES_HOTWATER) {
		bubbles_temp += 10;
		bubbles_wasserstand += 10;
	}
	else if (animationId == BUBBLES_COLDWATER) {
		bubbles_temp -= 5;
		bubbles_wasserstand += 10;
	}

	if (bubbles_wasserstand >= 20)
	{
		if (bubbles_status == BUBBLES_STATUS_SITTING) planschen->Run(BUBBLES_STANDUP);
		else if (bubbles_status == BUBBLES_STATUS_WAITING) planschen->Run(BUBBLES_TURNRIGHTBACK);
	}
}

void Bubbles::Bubbles_Schaum_OnAnimationCompleted(Flipbook * flipbook, uint16 animationId)
{
	schaum->Set(0,0);
	if (bubbles_status == BUBBLES_STATUS_BATHINGLEFT)
	{
		planschen->Run(BUBBLES_SPLASH,1);
		schaumA->Visible();
		schaumA->Run(0);
	}
}

void Bubbles::Schaum_OnClick()
{
	schaum->Run(0);
}

void Bubbles::Handtuch_Click()
{
	if (!planschen->IsRunning())
	{
		if (bubbles_status == BUBBLES_STATUS_BATHINGFRONT)
		{
			schaumA->RunReverse();
			schaumB->RunReverse();
			schaumC->RunReverse();
			planschen->Run(BUBBLES_CLIMBOUT);
		}
	}
}

void Bubbles::OnBubblesPinkyClick()
{
	if (!planschen->IsRunning())
	{
		if (bubbles_status == BUBBLES_STATUS_SITTING)
		{
			if (bubbles_temp == 35) planschen->Run(BUBBLES_STANDUP);
			else if (bubbles_temp < 35) planschen->Run(BUBBLES_COLDSITTING);
			else planschen->Run(BUBBLES_HOTSITTING);
		} 
		else if (bubbles_status == BUBBLES_STATUS_BATHINGLEFT2)
		{
			planschen->Run(BUBBLES_DIVE);
			schaumB->Visible();
			schaumB->Run(0);
		}
		else if (bubbles_status == BUBBLES_STATUS_BATHINGLEFT3)
		{
			planschen->Run(BUBBLES_TURNSITTINGFRONT);
		}
		else if (bubbles_status == BUBBLES_STATUS_BATHINGFRONT)
		{
			planschen->Run(BUBBLES_SPLASHFRONT);
		}
	}
}

void Bubbles::OnBubblesInactivity()
{
	if (!planschen->IsRunning())
	{
		if (
			(bubbles_status == BUBBLES_STATUS_BATHINGLEFT) ||
			(bubbles_status == BUBBLES_STATUS_BATHINGLEFT2) ||
			(bubbles_status == BUBBLES_STATUS_BATHINGLEFT3)
			) 
			planschen->Run(BUBBLES_BLINKLEFT);

		else if (bubbles_status == BUBBLES_STATUS_BATHINGFRONT)
			planschen->Run(BUBBLES_BLINKFRONT);
	}
}

void Bubbles::Bubbles_Start()
{
	planschen->Run(BUBBLES_WALKRIGHT,2);
	// TODO	InactivityAction = &OnBubblesInactivity;
}

