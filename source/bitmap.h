#pragma once

#include "common.h"
#include "font.h"
#include "rectangle.h"

class Bitmap
{

public:
	int16 _width;
	int16 _height;
	uint32 _config;

	uint16 * _image_file;
	uint16 * _image_buffer;
	uint32 _compressed_image_size;

	uint8 * _alpha_file;
	uint8 * _alpha_buffer;
	uint32 _compressed_alpha_size;

	int32 _pixelcount;
	uint32 _size;

	bool _alpha_enabled;

	bool _data_valid;

protected:
	void _initialize();

public:
	Bitmap(int16 width, int16 height); 
				// make buffer, do not initialize

	Bitmap(int16 width, int16 height, uint16 * buffer);  
				// use existing buffer

	Bitmap(int16 imagefilenumber); 
				// set data from compressed file with header, 
				// if immediate set ->  make buffer and uncompress

	Bitmap(int16 imagefilenumber, int16 alphafilenumber, bool immediate); 
				// set data from compressed file with header, 
				// if immediate set ->  make buffer and uncompress
public:
	~Bitmap(void);

public:
	void Load(); // load and uncompress 

	void Unload(); // keep data, free resources

	bool IsValid();

	int16 Height();

	int16 Width();

	uint16 * GetImageBuffer();

	uint8 * GetAlphaBuffer();

	void DecompressRLE16(
		unsigned short int * out, 
		unsigned short int * in, 
		unsigned short int * insize);

	void DecompressRLE8(
		unsigned char * out, 
		unsigned char * in, 
		unsigned char * insize);

	void Clear(uint16 color);

	void DrawBitmap(
		Bitmap * source, 
		int x, 
		int y);

	void DrawBitmapAlpha(
		Bitmap * source, 
		int x, 
		int y);

	void DrawBitmapAlphaFixed(
		Bitmap * source, 
		uint8 AlphaValue, 
		int x, 
		int y);

	void DrawText(
		Font * font, 
		Rectangle * rect, 
		char * text, 
		uint16 color);

	void DrawRectangle(
		Rectangle * rect, 
		uint16 color, 
		uint16 width);

	void DrawLine(
		Point * start, 
		Point * end, 
		uint16 color, 
		uint16 width);

	void FillRectangle(
		Rectangle * rect, 
		uint16 color);

	void SetAlpha(
		uint8 pValue);

	void CopyBuffer(
		Bitmap * pTarget);

	void CopyBufferVRAM(
		Bitmap * pTarget);

	void FadeHigh(
		uint8 value);

	void FadeLow(
		uint8 value);

	void LoadCompressedFile(
		uint16 * pFile);

};

