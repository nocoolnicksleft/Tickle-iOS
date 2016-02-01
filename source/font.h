#pragma once

#include "common.h"

enum FontType
{
	FontTypeLucidaConsole10,
	FontTypeComicSans10,
	FontTypeComicSans12
};

class Font
{

public:
	int8 _char_width;
	int8 _char_height;
	int8 _spacing_h;
	int8 _spacing_h_space;
	int8 _spacing_v;
	bool _fixed_width;
	uint8 * _map;
	uint8 * _width_map;

public:
	Font(FontType type);

public:
	~Font(void);

};

