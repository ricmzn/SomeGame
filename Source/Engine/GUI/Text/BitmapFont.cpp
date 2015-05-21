#include "BitmapFont.h"
#include <SDL2/SDL.h>
using namespace GUI::Text;

BitmapFont::BitmapFont(const Filesystem::File& bmp, int charWidth, int charHeight, int columns)
:   charWidth(charWidth)
,   charHeight(charHeight)
,   columns(columns)
{
    auto surf = SDL_LoadBMP_RW(SDL_RWFromMem(bmp.data(), bmp.size()), 0);
}

BitmapFont::~BitmapFont()
{}

Glyph BitmapFont::getGlyph(int32_t codepoint)
{
    return Glyph();
}

bool BitmapFont::exists(int32_t codepoint) const
{
    return false;
}
