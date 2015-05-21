#ifndef TEXT_H
#define TEXT_H
#include <Engine/GUI/Primitives/GUIDrawable.h>
#include <Engine/GUI/Text/Font.h>

namespace GUI {
namespace Primitives {
class api_public TextString : public GUIDrawable
{
    public:
        TextString(const Text::Font& font, StringRef str);
        TextString(const Text::Font& font);
        TextString();
        void setFont(const Text::Font& font);
        void setString(StringRef str);
};
}}

#endif // TEXT_H
