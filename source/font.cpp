
#include "font.h"

Font::Font(FontType type)
{
	if (type == FontTypeLucidaConsole10)
	{
		_fixed_width = true;
		_char_width = 16;
		_char_height = 16;
		_spacing_h = 8;
		_spacing_h_space = 2;
		_spacing_v = 12;
		_map = (uint8 *)LoadFile(LucidaConsole10_bin);
		_width_map = (uint8 *)LoadFile(LucidaConsole10_width_bin);
	}
	else if (type == FontTypeComicSans10)
	{
		_fixed_width = false;
		_char_width = 16;
		_char_height = 16;
		_spacing_h = 1;
		_spacing_h_space = 2;
		_spacing_v = 14;
		_map = (uint8 *)LoadFile(ComicSansMS10_bin);
		_width_map = (uint8 *)LoadFile(ComicSansMS10_width_bin);
	}
	else if (type == FontTypeComicSans12)
	{
		_fixed_width = false;
		_char_width = 16;
		_char_height = 16;
		_spacing_h = 2;
		_spacing_h_space = 2;
		_spacing_v = 16;
		_map = (uint8 *)LoadFile(ComicSansMS12_bin);
		_width_map = (uint8 *)LoadFile(ComicSansMS12_width_bin);
	}

}

Font::~Font(void)
{
}


