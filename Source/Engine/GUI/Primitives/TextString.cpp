#include "TextString.h"
using namespace GUI::Primitives;

TextString::TextString(const GUI::Text::Font& font, const Base::Types::String& str)
{
    setFont(font);
    (void)str;
}

TextString::TextString(const GUI::Text::Font& font)
    : TextString(font, "")
{}

TextString::TextString()
    : TextString(Text::Font::getDefaultFont())
{}

void TextString::setFont(const GUI::Text::Font& font)
{
    (void)font;
}

void TextString::setString(const Base::Types::String& str)
{
    (void)str;
}
