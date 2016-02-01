
#include "bitmap.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void Bitmap::_initialize()
{
	_width = 0;
	_height = 0;
	_config = 0;

	_image_file = 0;
	_image_buffer = 0;

	_alpha_file = 0;
	_alpha_buffer = 0;

	_pixelcount = 0;
	_size = 0;

	_alpha_enabled = 0;

	_compressed_image_size = 0;
	_compressed_alpha_size = 0;

	_data_valid = 0;
}

Bitmap::Bitmap(int16 width, int16 height)
{
	// make buffer, do not initialize
	_initialize();
	_width = width;
	_height = height;
	_pixelcount = _width * _height;
	_image_buffer = new uint16[_pixelcount];
	_alpha_buffer = new uint8[_pixelcount];
}

Bitmap::Bitmap(int16 width, int16 height, uint16 * buffer)
{
	// use existing buffer
	_initialize();
	_width = width;
	_height = height;
	_pixelcount = _width * _height;
	_image_buffer = buffer;
}

Bitmap::Bitmap(int16 imagefilenumber)
{
	// set data from compressed file with header, 
	// if immediate set ->  make buffer and uncompress
	_initialize();

	_image_file = LoadFile(imagefilenumber);

	if (_image_file)
	{
		_compressed_image_size = (unsigned int)*_image_file;
		_image_file++;
		_image_file++;

		_width = (uint16) *_image_file;
		_image_file++;

		_height = (uint16) *_image_file;
		_image_file++;
	
		_config = *_image_file;
		_image_file++;

		_pixelcount = _width * _height;

	}
}

Bitmap::Bitmap(int16 imagefilenumber, int16 alphafilenumber, bool immediate)
{
	// set data from compressed file with header, 
	// if immediate set ->  make buffer and uncompress
	_initialize();

	_image_file = LoadFile(imagefilenumber);

	if (_image_file)
	{
		unsigned int * _header32 = (unsigned int *)_image_file;
		_compressed_image_size = *_header32;

		_image_file++;
		_image_file++;

		_width = (uint16) *_image_file;
		_image_file++;

		_height = (uint16) *_image_file;
		_image_file++;

		_config = *_image_file;
		_image_file++;

		_pixelcount = _width * _height;

		_alpha_file = (uint8 *)LoadFile(alphafilenumber);

		if (_alpha_file)
		{
			unsigned int * _alpha_header32 = (unsigned int *)_alpha_file;
			_compressed_alpha_size = *_alpha_header32;

			_alpha_file++;
			_alpha_file++;
			_alpha_file++;
			_alpha_file++;

			//_width = (uint16) *_image_file;
			_alpha_file++;
			_alpha_file++;

			//_height = (uint16) *_image_file;
			_alpha_file++;
			_alpha_file++;

			//_config = *_image_file;
			_alpha_file++;
			_alpha_file++;
		}

		if (immediate) Load();
	}
}
	
	
Bitmap::~Bitmap()
{
	if (_alpha_buffer) {
		delete [] _alpha_buffer;
		_alpha_buffer = 0;
	}

	if (_image_buffer) {
		delete [] _image_buffer;
		_image_buffer = 0;
	}
}

void Bitmap::DecompressRLE16(unsigned short int * out, unsigned short int * in, unsigned short int * insize)
{
#ifdef _DEBUGME
	if ( (!out) || (!in) || (!insize) ) DebugPrint("DecompressRLE16 PERR");
#endif
		unsigned short int marker, symbol;
		unsigned int  i, count;

		/* Get marker symbol from input stream */
		marker = *in++;

		/* Main decompression loop */
		do
		{
			symbol = *in++;
			if( symbol == marker )
			{
				/* We had a marker word */
				count = *in++;

				if( count < 3 )
				{
					/* used for marker word repeat only */
					for( i = 0; i <= count; ++ i ) *(out++) = marker;
				}
				else
				{
					/* regular word repeat */
					symbol = *in++;
					for( i = 0; i <= count; ++ i ) *(out++) = symbol;
				}
			}
			else
			{
				*(out++) = symbol;
			}
		}
		while ( in < insize );
}

void Bitmap::DecompressRLE8(unsigned char * out, unsigned char * in, unsigned char * insize ) 
{
#ifdef _DEBUGME
	if ( (!out) || (!in) || (!insize) ) DebugPrint("DecompressRLE8 PERR");
#endif
		unsigned char marker, symbol;
		unsigned short int count;
		unsigned int  i;

		/* Get marker symbol from input stream */
		marker = *in++;

		/* Main decompression loop */
		do
		{
			symbol = *in++;

			if( symbol == marker )
			{
				/* We had a marker word */
				count = *in++;

				if( count < 3 )
				{
					/* used for marker word repeat only */
					for( i = 0; i <= count; ++ i ) *(out++) = marker;
				}
				else
				{
					/* regular word repeat */
					if( count & 0x80 )
					{
						count = ((count & ((unsigned int)0x007f)) << 8) + (*in++);
					}

					symbol = *in++;
					for( i = 0; i <= count; ++ i ) *(out++) = symbol;
				}
			}
			else
			{
				*(out++) = symbol;
			}
		}
		while ( in < insize );
}

void Bitmap::Load()
{
	if (_compressed_image_size)
	{
		_image_buffer = new uint16[_pixelcount];

		DecompressRLE16(_image_buffer,_image_file,_image_file + _compressed_image_size);
		_data_valid = 1;
	}

	if (_compressed_alpha_size)
	{
		_alpha_buffer = new uint8[_pixelcount];
		DecompressRLE8(_alpha_buffer,_alpha_file,_alpha_file + _compressed_alpha_size);
	}

}

void Bitmap::Unload()
{
	if (_alpha_buffer) {
		delete [] _alpha_buffer;
		_alpha_buffer = 0;
	}

	if (_image_buffer) {
		delete [] _image_buffer;
		_image_buffer = 0;
	}

	_data_valid = 0;
}

bool Bitmap::IsValid()
{
	return _data_valid;
}

int16 Bitmap::Height()
{
	return _height;
}

int16 Bitmap::Width()
{
	return _width;
}

uint16 * Bitmap::GetImageBuffer()
{
	return _image_buffer;
}

uint8 * Bitmap::GetAlphaBuffer()
{
	return _alpha_buffer;
}

void Bitmap::Clear(uint16 color)
{
	uint32 a = color | (color << 16);
	swiFastCopy(&a, _image_buffer,COPY_MODE_WORD | COPY_MODE_FILL | (_pixelcount / 2) );
}

void Bitmap::DrawBitmap(Bitmap * source, int px, int py)
{
#ifdef _DEBUGME
	if ( (!source) ) DebugPrint("DrawBitmap PERR");
#endif
	u16 * target_img = _image_buffer; 
	u16 target_img_width = _width; 
	u16 target_img_height = _height;
	int16 target_x = px; 
	int16 target_y = py; 
	u16 * source_img = source->GetImageBuffer(); 
	u16 source_img_width = source->Width();
	u16 source_img_height = source->Height();
	
		
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

void Bitmap::DrawBitmapAlpha(Bitmap * source, int px, int py)
{
#ifdef _DEBUGME
	if ( (!source) ) DebugPrint("DrawBitmapAlpha PERR");
#endif
	// TODO optimieren
	unsigned int target_img_width = _width; 
	unsigned int target_img_height = _height;

	int target_x = px; 
	int target_y = py; 

	u8 * source_alpha;
	source_alpha = source->GetAlphaBuffer(); 

	u16 * source_img;
	source_img = source->GetImageBuffer(); 

	unsigned int source_img_width;
	source_img_width = source->Width() ;

	int source_img_height;
	source_img_height = source->Height();

	unsigned int sourceoffset;
	sourceoffset = 0;

	unsigned int lineoffset;
	lineoffset = 0;

	u16 * target_img;

	target_img = _image_buffer; 

	if (target_y < 0)
	{
		source_img_height += target_y;
		source_img -= (target_y * source_img_width);
		source_alpha -= (target_y * source_img_width);
		target_y = 0;
	} 
	else 
	{
		int ydiff = target_y + source_img_height - target_img_height;
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
	
	lineoffset = target_img_width - source_img_width;

	uint32 alpha;
	uint32 invalpha;
	int x;
	int y;
	uint32 sourcepixel;
	uint32 targetpixel;

	for (y = source_img_height; y != 0; y--)
	{
		for (x = source_img_width; x != 0; x--) 
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

			++source_alpha;
			++source_img;
			++target_img;
		}

		target_img += lineoffset;
		source_img += sourceoffset;
		source_alpha += sourceoffset;
	}

}

void Bitmap::DrawBitmapAlphaFixed(Bitmap * source, uint8 alpha, int px, int py)
{
#ifdef _DEBUGME
	if ( (!source) ) DebugPrint("DrawBitmapAlphaFixed PERR");
#endif
	// TODO optimieren
	u16 target_img_width = _width; 
	u16 target_img_height = _height;

	int16 target_x = px; 
	int16 target_y = py; 

	register u16 * source_img;
	source_img = source->GetImageBuffer(); 

	register int32 source_img_width;
	source_img_width = source->Width() ;

	register int32 source_img_height;
	source_img_height = source->Height();

	register uint32 sourceoffset;
	sourceoffset = 0;

	register uint32 lineoffset;
	lineoffset = 0;

	register u16 * target_img;
	target_img = _image_buffer; 

	if (target_y < 0)
	{
		source_img_height += target_y;
		source_img -= (target_y * source_img_width);
		target_y = 0;
	} 
	else 
	{
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
		int16 xdiff = (target_x + source_img_width - target_img_width);
		if (xdiff > 0)
		{
			sourceoffset = xdiff;
			source_img_width -= xdiff;
		}
	}

	target_img += target_y * target_img_width + target_x;

	lineoffset = target_img_width - source_img_width;

	int32 x;
	int32 y;
	uint32 sourcepixel;
	uint32 targetpixel;
	uint32 invalpha = 255 - alpha;

	for (y = source_img_height; y != 0; y--)
	{
		for (x = source_img_width; x != 0; x--) 
		{
			sourcepixel = *source_img;
			targetpixel = *target_img;

			*target_img = 
				(
				( (  ( (RGB_R(sourcepixel) * alpha) + (RGB_R(targetpixel) * invalpha) )  >> 8 )       ) |
				( (  ( (RGB_G(sourcepixel) * alpha) + (RGB_G(targetpixel) * invalpha) )  >> 8 ) << 5  ) |
				( (  ( (RGB_B(sourcepixel) * alpha) + (RGB_B(targetpixel) * invalpha) )  >> 8 ) << 10 ) 
				);
			++source_img;
			++target_img;
		}

		target_img += lineoffset;
		source_img += sourceoffset;
	}

}

void Bitmap::DrawText(Font * font, Rectangle * rect, char * text, uint16 color)
{
#ifdef _DEBUGME
	if ( (!font) || (!rect) || (!text) ) DebugPrint("DrawText PERR");
#endif
	// TODO Optimieren

	uint8 * fontptr = (uint8 *)font->_map;
	uint8 * widthptr = (uint8 *)font->_width_map;
	
	uint16 offset = (_width - font->_char_width);

	uint16 px = 0;
	uint16 py = 0;
	char character;

	while (*text)
	{
		character = (*text++)-32;

		uint8 * characterptr =	fontptr + character * (font->_char_width/8) * font->_char_height;


		uint8 width;

		if (character == 32) {
			if (!py) width = 0;
			else width = font->_spacing_h_space;
		}else width = widthptr[character];

		uint16 * bufptr = _image_buffer 
			+ (rect->Top * _width)
			+ (rect->Left)
			+ (py * _width ) 
			+ (px);

		register uint8 x;
		register uint8 y;
		register uint8 pix;

		for (y = 0; y < font->_char_height; y++) 
		{
			for (x = 0; x < (font->_char_width / 8); x++)
			{
				pix = *(characterptr++);

				if (pix & 0x01) *(bufptr) = color;
				bufptr++;

				if (pix & 0x02) *(bufptr) = color;
				bufptr++;

				if (pix & 0x04) *(bufptr) = color;
				bufptr++;

				if (pix & 0x08) *(bufptr) = color;
				bufptr++;

				if (pix & 0x10) *(bufptr) = color;
				bufptr++;

				if (pix & 0x20) *(bufptr) = color;
				bufptr++;

				if (pix & 0x40) *(bufptr) = color;
				bufptr++;

				if (pix & 0x80) *(bufptr) = color;
				bufptr++;
			}

			bufptr += offset;
		}

		if ( (px + width + font->_spacing_h) > rect->Width)
		{
			if ( (py + font->_spacing_h) > rect->Height) return;
			py += font->_spacing_v;
			px = 0;

		} else px += width + font->_spacing_h;
	}

}

void Bitmap::DrawRectangle(Rectangle * rect, uint16 color, uint16 width)
{
#ifdef _DEBUGME
	if ( (!rect) ) DebugPrint("DrawRectangle PERR");
#endif
	// TODO optimieren
	// TODO Linienbreite implementieren
	uint16 offset = _width;
	uint16 * bufptr;
	int i;

	bufptr = _image_buffer + (uint16)(rect->Top * _width + rect->Left);
	for (i = 0; i < rect->Height; i++) 
	{
		(*bufptr) = color;
		bufptr += offset;
	}
		
	bufptr = _image_buffer + (uint16)(rect->Top * _width + rect->Left + rect->Width - 1);
	for (i = 0; i < rect->Height; i++) 
	{
		(*bufptr) = color;
		bufptr += offset;
	}

	bufptr = _image_buffer + (uint16)(rect->Top * _width + rect->Left);
	for (i = 0; i < rect->Width; i++) 
	{
		(*bufptr) = color;
		bufptr++;
	}

	bufptr = _image_buffer + (uint16)( _width * ( rect->Top + rect->Height -1 ) + rect->Left);
	for (i = 0; i < rect->Width; i++) 
	{
		(*bufptr) = color;
		bufptr++;
	}

}

void Bitmap::DrawLine(Point * start, Point * end, uint16 color, uint16 width)
{

}

void Bitmap::FillRectangle(Rectangle * rect, uint16 color)
{

}

void Bitmap::SetAlpha(uint8 pValue)
{
	uint32 a = pValue | (pValue << 8)  | (pValue << 16)  | (pValue << 24);
	swiFastCopy(&a, _alpha_buffer, COPY_MODE_WORD | COPY_MODE_FILL | _pixelcount/4 );
}

void Bitmap::CopyBufferVRAM(Bitmap * pTarget)
{
	swiFastCopy(this->_image_buffer, pTarget->_image_buffer, COPY_MODE_WORD | (_pixelcount/2) );
}

void Bitmap::CopyBuffer(Bitmap * pTarget)
{
#ifdef _DEBUGME
	if ( (!pTarget) ) DebugPrint("CopyBuffer PERR");
#endif

	register uint32 * src asm("r1");
	src = (uint32 *)this->_image_buffer;

	register uint32 * lastposition asm("r0");
	lastposition = src + ( (_pixelcount) >> 1 );

	register uint32 * trg asm("r2");
	trg = (uint32 *)pTarget->_image_buffer;

	asm(
	 "loop:\n\t"
	 "ldmia r1!,{r3,r4,r5,r6}\n\t"
	 "stmia r2!,{r3,r4,r5,r6}\n\t"
	 "cmp   r0,r1\n\t"
	 "bne   loop\n\t" 
	 :
	 : "r" (lastposition), "r" (src), "r" (trg)
	 : "r3", "r4", "r5", "r6"
	);

	/*

	// Andere Variante: Schaltet in ARM-Mode und schickt dann 8 WORDs gleichzeitig.
	// ist auf der HW aber nicht schneller. Evtl wg der Umschaltung TODO nochmal evaluieren
	asm(
	 "adr   r3,loop\n\t"
	 "bx    r3\n"
	 ".code 32\n"
	 "loop:\n\t"
	 "ldmia r1!,{r3,r4,r5,r6,r7,r8,r9,r10}\n\t"
	 "stmia r2!,{r3,r4,r5,r6,r7,r8,r9,r10}\n\t"
	 "cmp   r0,r1\n\t"
	 "bne   loop\n\t" 
	 "adr   r3,end+1\n\t"
	 "bx    r3\n"
	 ".code 16\n"
	 "end:\n\t"
	 :
	 : "r" (lastposition), "r" (src), "r" (trg)
	 : "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10"
	);

	// FastCopy ist wohl am schnellsten, funktioniert auf der HW super, aber nicht in Dualis (MSW/LSW falschrum)
	// scheinbar nur ein Problem mit Kopien WRAM -> VRAM, WRAM -> WRAM läuft anstandslos
	// Langsam, frameindex für 256x192 = 496
	//	swiFastCopy(this->_image_buffer, pTarget->_image_buffer, COPY_MODE_WORD | (_width*_height*2/4) );
			
	// Bester Kompromiss der auf beiden läuft ist DMA Halfword Copy, 
	// Word Copy macht in Dualis die gleichen Probleme wie FastCopy (MSW/LSW falschrum)
	// Furchtbar langsam, frameindex für 256x192 = 790
	//dmaCopyWords(3,this->_image_buffer, pTarget->_image_buffer,(_width*_height*2));

	*/
}


void Bitmap::FadeLow(register uint8 value)
{
	register uint16 * buffer = _image_buffer;

	register uint16 pos = _pixelcount;
	register uint16 pixel;
//	register uint32 invalpha = ((255 - value) >> 3) | ( ((255 - value) >> 3) << 10 ) | ( ((255 - value) >> 3) << 20 ) ;
	register uint16 invalpha = 255 - value;

	while (pos)
	{
		pixel = *buffer;

//		*buffer = 	 (   (  ((RGB_B_NS(pixel) << 10) | (RGB_G_NS(pixel) << 5) | (RGB_R_NS(pixel)))    &    0x1F07C1F )    * invalpha)  >> 5;


		*buffer = 	(
						 ( ( ( (RGB_R(pixel) * invalpha) )  >> 8 )       ) |
						 ( ( ( (RGB_G(pixel) * invalpha) )  >> 8 ) << 5  ) |
						 ( ( ( (RGB_B(pixel) * invalpha) )  >> 8 ) << 10 ) 
					);

		++buffer;
		--pos;
	}
}

void Bitmap::FadeHigh(register uint8 value)
{
	register uint16 * buffer = _image_buffer;

	register uint16 pos = _width * _height;
	register uint16 pixel;
	register uint16 invalpha = 255 + value;

	while (pos)
	{
		pixel = *buffer;

		*buffer = 	(
						 ( ( ( (RGB_R(pixel) * invalpha) )  >> 8 )       ) |
						 ( ( ( (RGB_G(pixel) * invalpha) )  >> 8 ) << 5  ) |
						 ( ( ( (RGB_B(pixel) * invalpha) )  >> 8 ) << 10 ) 
					);

		++buffer;
		--pos;
	}
}

void Bitmap::LoadCompressedFile(uint16 * pFile)
{
	bitblt16rle(_image_buffer,_width,0,0,pFile);	
}


