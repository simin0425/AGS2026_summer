#include <DxLib.h>
#include "FontManager.h"

FontManager* FontManager::instance_ = nullptr;

bool FontManager::Init()
{
	AddFont(TAGS::LOGO, "ÇlÇr ñæí©", 80, 6, DX_FONTTYPE_ANTIALIASING_EDGE);
	AddFont(TAGS::GENERAL, "ÇlÇr ÉSÉVÉbÉN", 48, 5, DX_FONTTYPE_ANTIALIASING_EDGE);
	AddFont(TAGS::GENERAL_SMALL, "ÇlÇr ÉSÉVÉbÉN", 24, 5, DX_FONTTYPE_ANTIALIASING_EDGE);
	AddFont(TAGS::GENERAL_LARGE, "ÇlÇr ÉSÉVÉbÉN", 64, 5, DX_FONTTYPE_ANTIALIASING_EDGE);

	return true;
}

bool FontManager::Release()
{
	for (auto& f : fontList_)
		DeleteFontToHandle(f.second.handle);

	fontList_.clear();

	return true;
}

void FontManager::AddFont(TAGS tag, const char* font_name, int size, int thick, int font_type, int char_set, int edge_size, int italic)
{
	if (fontList_.find(tag) != fontList_.end()) return;

	int h = CreateFontToHandle(font_name, size, thick, font_type, char_set, edge_size, italic);

	DATA data = { h, font_name, size, thick, font_type, char_set, edge_size, italic };

	fontList_.emplace(tag, data);
}

FontManager::DATA FontManager::GetFontData(TAGS tag)
{
	auto it = fontList_.find(tag);

	if (it != fontList_.end())
		return (*it).second;
	else
		return DATA();
}

int FontManager::GetFontHandle(TAGS tag)
{
	auto it = fontList_.find(tag);

	if (it != fontList_.end())
		return (*it).second.handle;
	else
		return DATA().handle;
}
