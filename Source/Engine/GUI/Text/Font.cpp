#include "Font.h"
#include <Engine/GUI/Text/BitmapFont.h>
using namespace GUI::Text;

Font::~Font()
{}

const Font& Font::getDefaultFont()
{
    static BitmapFont defaultFont("Fonts/curses_640x300.bmp");
    return defaultFont;
}
