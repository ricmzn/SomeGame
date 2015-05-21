#ifndef GUI_TRUETYPEFONT_H
#define GUI_TRUETYPEFONT_H
#include <Engine/GUI/Text/BitmapFont.h>
#include <Engine/Filesystem/File.h>

namespace GUI {
namespace Text {
class api_public TrueTypeFont : public Font
{
    private:
        void* data;
    public:
        TrueTypeFont(const File& ttf);
        virtual ~TrueTypeFont();
        virtual Glyph getGlyph(int32_t codepoint);
        virtual bool exists(int32_t codepoint) const;
        BitmapFont toBitmapFont() const;
};
}}

#endif // TRUETYPEFONT_H
