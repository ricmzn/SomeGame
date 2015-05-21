#include "TrueTypeFont.h"
#include <Engine/Base/Exceptions.h>
#include <ft2build.h>
#include FT_FREETYPE_H

static FT_Library getFreeTypeInstance()
{
    static FT_Library ftLibrary = nullptr;
    if(!ftLibrary) {
        FT_Error error = FT_Init_FreeType(&ftLibrary);
        if(error) {
            throw GenericError("Failed to initialize FreeType");
        }
    }
    return ftLibrary;
}

GUI::Text::TrueTypeFont::TrueTypeFont(const File& ttf)
{
    auto ftLibrary = getFreeTypeInstance();
    FT_New_Memory_Face(ftLibrary, ttf.data(), ttf.size(), 0, (FT_Face*) &data);
}

GUI::Text::TrueTypeFont::~TrueTypeFont()
{
    FT_Done_Face(FT_Face(data));
}

GUI::Text::Glyph GUI::Text::TrueTypeFont::getGlyph(int32_t codepoint)
{
    return Glyph();
}

bool GUI::Text::TrueTypeFont::exists(int32_t codepoint) const
{
    return true;
}

GUI::Text::BitmapFont GUI::Text::TrueTypeFont::toBitmapFont() const
{
    return BitmapFont("");
}
