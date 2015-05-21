#ifndef GUI_BITMAPFONT_H
#define GUI_BITMAPFONT_H
#include <Engine/GUI/Text/Font.h>
#include <Engine/Filesystem/File.h>

namespace GUI {
namespace Text {
class api_public BitmapFont : public Font
{
    private:
        Byte* pixels;
        int charWidth;
        int charHeight;
        int columns;
    public:
        BitmapFont(const File& bmp, int charWidth, int charHeight, int columns);
        virtual ~BitmapFont();
        virtual Glyph getGlyph(int32_t codepoint);
        virtual bool exists(int32_t codepoint) const;
};
}}

#endif // BITMAPFONT_H
