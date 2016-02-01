
#include "common.h"

#include "wconsole.h"
#include "font.h"

WConsole::WConsole(Rectangle * pRect, uint16 pRows, uint16 pCols, Font * pFont) : Window(pRect,"wconsole")
{
	_font = pFont;
	_rows = pRows;
	_cols = pCols;
	_current_row = 0;
	_current_col = 0;
	_charbuffer = 0;
	_charbuffer = new uint16[_rows * _cols];
	_padding = 4;
	_frame_color = RGB15(0xFF,0x00,0x00) | (1 << 15);
	_frame_width = 1;

	testbmp = new Bitmap((int16)bigpinky_bubbles_drynaked_6_rle_bin,(int16)alphabigpinky_bubbles_drynaked_6_rle_bin,true);

	Clear();
}

void WConsole::Clear()
{
	for (uint16 row = 0; row < _rows; row++)
		for (uint16 col = 0; col < _cols; col++)
			_charbuffer[row * _cols + col] = 32;
	_valid = false;
}
/*
void WConsole::SetChar(uint16 row, uint16 col, uint16 c)
{
}
*/

void WConsole::printf(const char *fmt,...)
{
  _valid = false;
  va_list ap; /*will point to each unnamed argument in turn*/
  int num;
  double d;
  const char *p=fmt;
  va_start(ap,fmt); /* point to first element after fmt*/
  while(*p)
  {
   if (*p=='i') /*int*/
   {
    num=va_arg(ap,int);
	printf(fmt,ap);
    printf("%d",num);
   }
   else if (*p=='d') /*double*/
   {
    d=va_arg(ap,double);
    printf("%f",d);
   }
   else 
   {
    printf("unsupported format flag");
    break;
   }
   ++p; /* get the next char of the format string */
  }/*while*/
  va_end(ap); /*cleanup*/ 
}


void WConsole::Prepare()
{
	if (!_valid)
	{
		Window::Clear();

		_buffer->DrawBitmapAlpha(testbmp,100,0);

		for (uint16 row = 0; row < _rows; row++)
			for (uint16 col = 0; col < _cols; col++)
				PaintChar (row,col,_charbuffer[row * _cols + col] );

		_buffer->DrawRectangle(_inner_rect, _frame_color, _frame_width);

		//	_buffer->DrawText(new Font(FontTypeComicSans10), new Rectangle(2,55,110,40), "Comic Sans MS 10pt  auch sehr schön", 1 << 15);
		//	_buffer->DrawText(new Font(FontTypeComicSans12), new Rectangle(120,55,105,40), "Comic Sans MS 12pt bold", 1 << 15);
		_valid = true;
	}
	Window::Prepare();

}


void WConsole::PaintChar(uint16 row, uint16 col, char c)
{
	_valid = false;
	Rectangle * targetRect = new Rectangle(
		_padding + col * _font->_spacing_h,
		_padding + row * _font->_spacing_v,
		_font->_char_width,
		_font->_char_height
		);

	char * text = new char[2];
	text[0] = c;
	text[1] = '\0';

	_buffer->DrawText(this->_font,targetRect,text,_fore_color);
}

void WConsole::TestFill(char c)
{
	for (uint16 row = 0; row < _rows; row++)
		for (uint16 col = 0; col < _cols; col++)
			_charbuffer[row * _cols + col] = c + col;

}

void WConsole::ScrollUp()
{
	for (uint y = 1; y < _rows; y++)
		for (uint x = 0; x < _cols; x++)
			_charbuffer[ ((y-1)*_cols) + x ] = _charbuffer[ (y*_cols) + x ];
	for (uint x = 0; x < _cols; x++) _charbuffer[ ((_rows-1)*_cols) + x ] = ' ';

}

void WConsole::ScrollDown()
{

}

void WConsole::GotoXY(uint16 pX, uint16 pY)
{
	if (pX < _cols) _current_col = pX;
	if (pY < _rows) _current_row = pY;
}

void WConsole::Print(char * pString)
{
	_valid = false;
	while (*pString)
	{
		if ( *pString == '\n' )
		{
			if (_current_row == (_rows-1)) ScrollUp();
			else _current_row++;
			_current_col = 0;
		}
		else
		{
			_charbuffer[_current_row * _cols + _current_col] = *pString;

			if (_current_col == (_cols -1)) 
			{	
				if (_current_row == (_rows-1)) ScrollUp();
				else _current_row++;
				_current_col = 0;
			} else _current_col++;
		}

		pString++;
	}
}




