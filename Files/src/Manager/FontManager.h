#pragma once
#include <map>

class FontManager
{
public:
	enum class TAGS
	{
		LOGO,
		GENERAL,
		GENERAL_SMALL,
		GENERAL_LARGE,
	};

	struct DATA
	{
		int handle = -1;
		const char* font_name = "ƒ[ƒhŽ¸”s";
		int size = 0;
		int thick = 0;
		int font_type = 0;
		int char_set = 0;
		int edge_size = 0;
		int italic = 0;
	};

	static void CreateInstance() { if (instance_ == nullptr) instance_ = new FontManager; instance_->Init(); }
	static FontManager& GetInstance() { return *instance_; }
	static void DeleteInstance() { if (instance_ != nullptr) delete instance_; instance_ = nullptr; }

	bool Init();
	bool Release();

	void AddFont(TAGS tag, const char* font_name, int size, int thick = -1, int font_type = -1, int char_set = -1, int edge_size = -1, int italic = 0);
	DATA GetFontData(TAGS tag);
	int GetFontHandle(TAGS tag);

private:
	static FontManager* instance_;

	FontManager() {}
	~FontManager() {}

	FontManager(const FontManager&) = delete;
	FontManager& operator=(const FontManager&) = delete;
	FontManager(FontManager&&) = delete;
	FontManager& operator=(FontManager&&) = delete;

	std::map<TAGS, DATA> fontList_;

};

