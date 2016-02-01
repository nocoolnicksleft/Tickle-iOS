#include "common.h"
#include "background.h"
#include <stdio.h>
#include <string.h>
#include <queue>
#include <gbfs.h>

using namespace std;

#define _DEBUGME

GBFS_FILE const* gbfs_file;
queue<int> MessageQueue;

uint32 inactivity_counter = 0;
uint32 inactivity_threshold = 50;
GenericEvent InactivityAction = 0;

void InitGBFS()
{
	gbfs_file = find_first_gbfs_file((void*)0x08000000);
}


u16 * LoadFile(u16 id)
{
	char filename[20];
	u16 * fileptr = 0;
	u32 size;
	sprintf(filename,"%u.bin",id);
	fileptr = (u16 *)gbfs_get_obj(gbfs_file, filename, &size);

	if (!fileptr)
	{
		sprintf(filename,"E %u.bin",id);
		DebugPrint(filename);
	}
//	else 
//	{
//		sprintf(filename,"L %u s %d",id,size);
//		DebugPrint(filename);
//	}
	return fileptr;
}

u16 * LoadFileCopy(u16 id)
{
	char filename[20];
	u8 * fileptr = 0;
	u8 * newfileptr = 0;
	u32 size;
	sprintf(filename,"%u.bin",id);
	fileptr = (u8 *)gbfs_get_obj(gbfs_file, filename, &size);

	if (!fileptr)
	{
		sprintf(filename,"CE %u.bin",id);
		DebugPrint(filename);
	} 
//	else {
//		sprintf(filename,"CL %u s %d",id,size);
//		DebugPrint(filename);
//	}
	
	if (size)
	{
		newfileptr = new uint8[size];
		memcpy(newfileptr,fileptr,size);
		//sprintf(filename,"%u.bin size %u ptr %u",id,size,fileptr);
		//DebugPrint(filename);
	} 
	return (u16 *)newfileptr;

}


u32 FileSize(u16 id)
{
	char filename[20];
	u16 * fileptr;
	u32 size;
	sprintf(filename,"%u.bin",id);
	fileptr = (u16 *)gbfs_get_obj(gbfs_file, filename, &size);
	//sprintf(filename,"%u.bin size %u ptr %u",id,size,fileptr);
	//DebugPrint(filename);
	return size;
}



void __DebugPrint(char * text)
{
	asm("swi 0xFF");
	asm("bx lr");
}

void DebugPrint(char * text)
{
	if (PersonalData->name[0] == 'G') __DebugPrint(text);
}

void bitblt16rle(u16 * target_img, u16 target_img_width, u16 target_x, u16 target_y, u16 * in)
{
    unsigned short int marker, symbol;
    unsigned int  i, inpos, outpos, count, x, insize, config,y;
	// unsigned int y;

	unsigned short int * out;

	out = target_img + (target_img_width * target_y) + target_x;

	inpos = 0;

	insize = (unsigned int)in[inpos];
	inpos++;
	inpos++;

	x = in[inpos];
	inpos++;

	y = in[inpos];
	inpos++;
	
	config = in[inpos];
	

	// loop compares base on inpos < insize which is length - header!!
	// so set everything to zero before starting
	inpos = 0;
	in += 5;


	//char dstr[30];
	//sprintf(dstr,"C %u X %u Y %u",config,x,y);
	//DebugPrint(dstr);

    //if( insize < 1 )
    //{
    //    return;
    //}

    /* Get marker symbol from input stream */
    marker = in[ inpos ++ ];

    /* Main decompression loop */
    outpos = 0;
    do
    {
        symbol = in[ inpos ++ ];
        if( symbol == marker )
        {
            /* We had a marker word */
            count = in[ inpos ++ ];

            if( count < 3 )
            {
				/* used for marker word repeat only */
                for( i = 0; i <= count; ++ i )
                {
					if (marker & (1 << 15)) out[outpos] = marker;
					else out[outpos] = 0;
					outpos ++;
					if (outpos == x) {
						out += target_img_width;
						outpos = 0;
					}
                }
            }
            else
            {
				/* regular word repeat */
                symbol = in[ inpos ++ ];
                for( i = 0; i <= count; ++ i )
                {
                    if (symbol & (1 << 15)) out[outpos] = symbol;
					else out[outpos] = 0;
					outpos++;
					if (outpos == x) {
						out += target_img_width;
						outpos = 0;
					}
                }
            }
        }
        else
        {
            /* No marker, plain copy */
            if (symbol & (1 << 15)) out[outpos] = symbol;
			else out[outpos] = 0;
			outpos++;
			if (outpos == x) {
				out += target_img_width;
				outpos = 0;
			}
        }
    }
    while ( inpos < insize );
}



void bitblt8rle(u8 * target_img, u16 target_img_width, u16 target_x, u16 target_y, unsigned char * in)
{
	unsigned char marker, symbol;
	unsigned short int count;
	unsigned int  i, inpos, outpos,  x, insize, config,y;
	// unsigned int y;

	u8 * out;

	u8 * buf;


	out = target_img + (target_img_width * target_y) + target_x;

	inpos = 0;

	/**************************************************/
	u16 * file_in;

	file_in = (u16 *)in;

	insize = (unsigned int) (*file_in);
	file_in++;
	file_in++;

	x = (unsigned short int) (*file_in);
	file_in++;

	y = (unsigned short int) (*file_in);
	file_in++;

	config = (unsigned short int) (*file_in);
	
	/**************************************************/
	buf = new u8[x];

	//int lines = 0;

	// loop compares base on inpos < insize which is length - header!!
	// so set everything to zero before starting
	in += 10;
	inpos = 0;

	//char dstr[30];
	//sprintf(dstr,"C %u X %u Y %u SIZE %u",config,x,y,insize);
	//DebugPrint(dstr);

	//if( insize < 1 )
	//{
	//    return;
	//}

	/* Get marker symbol from input stream */
	marker = in[ inpos ++ ];

	/* Main decompression loop */
	outpos = 0;
	do
	{
		symbol = in[ inpos ++ ];
		if( symbol == marker )
		{
			/* We had a marker word */
			count = in[ inpos ++ ];

			if( count < 3 )
			{
				/* used for marker word repeat only */
				for( i = 0; i <= count; ++ i )
				{
					//out[outpos] = marker;
					buf[outpos] = marker;
					outpos ++;
					if (outpos == x) {
						/*
						while(DMA_CR(2) & DMA_BUSY);
						dmaCopyWordsAsynch(2,buf,out,x);
						*/
						for (short int i=0;i < (x) ;i+=2) *((u16*)&out[i]) = *((u16*)&buf[i]);
						out += target_img_width;
						outpos = 0;
						//lines++;
					}
				}
			}
			else
			{
				/* regular word repeat */
				if( count & 0x80 )
				{
					count = ((count & ((unsigned int)0x007f)) << 8) + in[ inpos ++ ];
				}

				symbol = in[ inpos ++ ];

				for( i = 0; i <= count; ++ i )
				{
					buf[outpos] = symbol;
					//out[outpos] = symbol;
					outpos++;
					if (outpos == x) {
						for (short int i=0;i < (x) ;i+=2) *((u16*)&out[i]) = *((u16*)&buf[i]);
						/*
						while(DMA_CR(2) & DMA_BUSY);
						dmaCopyWordsAsynch(2,buf,out,x);
						*/
						out += target_img_width;
						outpos = 0;
						//lines++;
					}
				}
			}
		}
		else
		{
			/* No marker, plain copy */

			buf[outpos] = symbol;
			//out[outpos] = symbol;
			outpos++;
			if (outpos == x) {
				for (short int i=0;i < (x) ;i+=2) *((u16*)&out[i]) = *((u16*)&buf[i]);
				/*
				while(DMA_CR(2) & DMA_BUSY);
				dmaCopyWordsAsynch(2,buf,out,x);
				*/
				out += target_img_width;
				outpos = 0;
				//lines++;
			}
		}
	}
	while ( inpos < insize);
	// if (outpos != 0) dmaCopy(buf,out,outpos);
	delete buf;
}

void bitblt(u8 * target_img, u16 target_img_width, u16 target_x, u16 target_y, u8 * source_img, u16 source_img_width, u16 source_img_height)
{
	target_img += target_y * target_img_width + target_x;

	source_img_width >>= 2;

	register uint32 lineoffset = target_img_width - source_img_width;

	for (int y = 0; y < source_img_height; y++)
	{
		while(DMA_CR(3) & DMA_BUSY);

		DMA_SRC(3) = (uint32)source_img;
		DMA_DEST(3) = (uint32)target_img;
		DMA_CR(3) = DMA_COPY_WORDS | source_img_width;

		target_img += lineoffset;
		source_img += source_img_width;
	}
}



void bitblt16(register u16 * target_img, u16 target_img_width, u16 target_img_height, int16 target_x, int16 target_y, register u16 * source_img, u16 source_img_width, u16 source_img_height)
{


	uint32 sourceoffset = 0;

	if (target_y < 0)
	{
		if (target_y < (-source_img_height)) return;
		source_img_height += target_y;
		source_img -= (target_y * source_img_width);
		target_y = 0;
	} 
	else 
	{
		if (target_y > target_img_height) return;
		int16 ydiff = target_y + source_img_height - target_img_height;
		if (ydiff > 0) {
			source_img_height -= ydiff;
		}
	}

	if (target_x < 0) 
	{
		if (target_x < (-source_img_width)) return;
		sourceoffset = -target_x;
		source_img_width += target_x;
		source_img -= target_x;
		target_x = 0;
	}
	else 
	{
		if (target_x > target_img_width) return;
		int16 xdiff = (target_x + source_img_width - target_img_width);
		if (xdiff > 0)
		{
			sourceoffset = xdiff;
			source_img_width -= xdiff;
		}
	}

	target_img += target_y * target_img_width + target_x;

	register uint32 lineoffset = target_img_width - source_img_width;
	register uint32 sourcepixel;
	register uint32 x;
	register uint32 y;

	for (y = 0; y < source_img_height; y++)
	{
		for (x = 0; x < source_img_width; x++) 
		{
			sourcepixel = *source_img;
			if (sourcepixel & (1 << 15)) *target_img = sourcepixel;
			source_img++;
			target_img++;
		}

		target_img += lineoffset;
		source_img += sourceoffset;
	}
}


void bitblt16alpha(register u16 * target_img, register u16 * source_img, register u8 * source_alpha, u16 target_img_width, u16 target_img_height, int16 target_x, int16 target_y, register u16 source_img_width, u16 source_img_height)
{

	uint32 sourceoffset = 0;

	if (target_y < 0)
	{
		source_img_height += target_y;
		source_img -= (target_y * source_img_width);
		source_alpha -= (target_y * source_img_width);
		target_y = 0;
	} 
	else 
	{
		int16 ydiff = target_y + source_img_height - target_img_height;
		if (ydiff > 0) target_img_height -= ydiff;
	}

	if (target_x < 0) 
	{
		if (target_x < (-source_img_width)) return;
		sourceoffset = -target_x;
		source_img_width += target_x;
		source_img -= target_x;
		source_alpha -= target_x;
		target_x = 0;
	}
	else 
	{
		int16 xdiff = (target_x + source_img_width - target_img_width);
		if (xdiff > 0)
		{
			sourceoffset = xdiff;
			source_img_width -= xdiff;
		}
	}

	target_img += target_y * target_img_width + target_x;

	uint32 lineoffset = target_img_width - source_img_width;
	uint32 y;

	register uint32 alpha;
	register uint32 invalpha;
	register uint32 x;
	register uint32 sourcepixel;
	register uint32 targetpixel;

	for (y = 0; y < source_img_height; y++)
	{
		for (x = 0; x < source_img_width; x++) 
		{
			alpha = *source_alpha;

			if ( alpha > 0)
			{
				sourcepixel = *source_img;

				if (alpha == 255) *target_img = sourcepixel;
				else
				{
					invalpha = 255 - alpha;

					targetpixel = *target_img;

					*target_img = 
						(
							 ( (  ( (RGB_R(sourcepixel) * alpha) + (RGB_R(targetpixel) * invalpha) )  >> 8 )       ) |
							 ( (  ( (RGB_G(sourcepixel) * alpha) + (RGB_G(targetpixel) * invalpha) )  >> 8 ) << 5  ) |
							 ( (  ( (RGB_B(sourcepixel) * alpha) + (RGB_B(targetpixel) * invalpha) )  >> 8 ) << 10 ) 
						);
				}
			}
			source_alpha++;

			source_img++;
			target_img++;

		}
		target_img += lineoffset;
		source_img += sourceoffset;
		source_alpha += sourceoffset;
	}
}







uint32 buf[65536];

u32 DecompressFileToMemory( const char *name, uint16 * target_address)
{
	u32 size = 0;
	u32 * obj;
	obj = (u32 *)gbfs_get_obj(gbfs_file, name, NULL);
	size = *obj >> 8;

	swiDecompressLZSSWram(obj,(uint32 *)buf);

	// char debstring[30];
	// sprintf(debstring,"LOAD %s (%u)",name,size);
	// DebugPrint(debstring);

	while(DMA_CR(3) & DMA_BUSY);

	DMA_SRC(3) = (uint32)&buf;
	DMA_DEST(3) = (uint32)target_address;
	DMA_CR(3) = DMA_COPY_WORDS | (size  >> 2);
	while(DMA_CR(3) & DMA_BUSY);

	return size;
}


void SendMessage(int MsgId)
{
	MessageQueue.push(MsgId);
}

int ReadMessage()
{
	int val = 0;
	if (!MessageQueue.empty())
	{
		val = MessageQueue.front();
		MessageQueue.pop();
	}
	return val;
}





const uint8  x3table[256] = {
	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,
	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	1	,
	1	,	1	,	1	,	1	,	1	,	1	,	1	,	1	,	1	,	1	,	1	,	1	,	1	,	1	,	2	,	2	,
	2	,	2	,	2	,	2	,	2	,	2	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	4	,	4	,	4	,
	4	,	4	,	5	,	5	,	5	,	5	,	5	,	6	,	6	,	6	,	6	,	7	,	7	,	7	,	8	,	8	,
	8	,	8	,	9	,	9	,	9	,	10	,	10	,	10	,	11	,	11	,	11	,	12	,	12	,	13	,	13	,	14	,
	14	,	14	,	15	,	15	,	16	,	16	,	17	,	17	,	18	,	18	,	19	,	19	,	20	,	20	,	21	,	21	,
	22	,	23	,	23	,	24	,	24	,	25	,	26	,	26	,	27	,	28	,	28	,	29	,	30	,	31	,	31	,	32	,
	33	,	34	,	34	,	35	,	36	,	37	,	38	,	38	,	39	,	40	,	41	,	42	,	43	,	44	,	45	,	46	,
	47	,	47	,	48	,	49	,	50	,	51	,	53	,	54	,	55	,	56	,	57	,	58	,	59	,	60	,	61	,	63	,
	64	,	65	,	66	,	67	,	69	,	70	,	71	,	72	,	74	,	75	,	76	,	78	,	79	,	80	,	82	,	83	,
	85	,	86	,	88	,	89	,	90	,	92	,	94	,	95	,	97	,	98	,	100	,	101	,	103	,	105	,	106	,	108	,
	110	,	111	,	113	,	115	,	117	,	118	,	120	,	122	,	124	,	126	,	128	,	130	,	131	,	133	,	135	,	137	,
	139	,	141	,	143	,	145	,	147	,	150	,	152	,	154	,	156	,	158	,	160	,	162	,	165	,	167	,	169	,	172	,
	174	,	176	,	178	,	181	,	183	,	186	,	188	,	191	,	193	,	196	,	198	,	201	,	203	,	206	,	208	,	211	,
	214	,	216	,	219	,	222	,	224	,	227	,	230	,	233	,	236	,	238	,	241	,	244	,	247	,	250	,	253	,	255	,
};
