#ifndef GUI_FONT_H
#define GUI_FONT_H
#include <Engine/GUI/Text/Glyph.h>

namespace GUI {
namespace Text {
class api_public Font
{
    public:
        virtual ~Font() = 0;
        virtual Glyph getGlyph(int32_t codepoint) = 0;
        virtual bool exists(int32_t codepoint) const = 0;

        static const Font& getDefaultFont();
};
}}

#endif // FONT_H
