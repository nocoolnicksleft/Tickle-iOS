#pragma once

#include <nds.h>
#include <nds/arm9/image.h>
#include <stdio.h>
#include <string.h>

#include "binaries.h"

#include "memory_tracking.h"

#include <gbfs.h>
extern const GBFS_FILE  data_gbfs;

#include <vector>
#include <map>
#include <cstdarg>
#include <algorithm>
#include "FreePtr.h"

using namespace std;
using namespace FreePtr;


typedef void (*GenericEvent) (void);
typedef void (*PositionEvent) (int x, int y);


#define RGB_B(n) ((n & 0x7C00) >> 10 )
#define RGB_G(n) ((n & 0x03E0) >>  5 )
#define RGB_R(n) ((n & 0x001F)       )

#define RGB_B_NS(n) ((n & 0x7C00))
#define RGB_G_NS(n) ((n & 0x03E0))
#define RGB_R_NS(n) ((n & 0x001F))

void bitblt(u8 * target_img, u16 target_img_width, u16 target_x, u16 target_y, u8 * source_img, u16 source_img_width, u16 source_img_height);

void bitblt16(register u16 * target_img, u16 target_img_width, u16 target_img_height, int16 target_x, int16 target_y, register u16 * source_img, u16 source_img_width, u16 source_img_height);

void bitblt16alpha(register u16 * target_img, register u16 * source_img, register u8 * source_alpha, u16 target_img_width, u16 target_img_height, int16 target_x, int16 target_y, register u16 source_img_width, u16 source_img_height);

void bitblt16rle(u16 * target_img, u16 target_img_width, u16 target_x, u16 target_y, u16 * in);

void bitblt8rle(u8 * target_img, u16 target_img_width, u16 target_x, u16 target_y, u8 * in);

void DebugPrint(char * text);

u32 DecompressFileToMemory( const char *name, uint16 * target_address);

u16 * LoadFile(u16 id);
u16 * LoadFileCopy(u16 id);

u32 FileSize(u16 id);

void InitGBFS();

#define PM_STARTMENU 1
#define PM_STARTBUBBLES 2
#define PM_TOGGLETEXTFENSTER 3
#define PM_STARTBEACH 4
#define PM_STOPBUBBLES 5
#define PM_STOPBEACH 6


void SendMessage(int MsgId);
int ReadMessage();

extern uint32 inactivity_counter;
extern uint32 inactivity_threshold;
extern GenericEvent InactivityAction;

extern const uint8  x3table[];

enum AnimationCurve 
{
	AnimationCurveLinear,
	AnimationCurveSlowing,
	AnimationCurveAccelerating,
	AnimationCurveOvershoot
};

