#ifndef GUI_GLYPH_H
#define GUI_GLYPH_H
#include <Engine/System/Macros.h>
#include <Engine/Base/Types/Shared.h>

namespace GUI {
namespace Text {
class api_public Glyph
{
    public:
        struct Metrics {
            int width, height;
            int horizAdvance, vertAdvance;
            int horizOffset, vertOffset;
        };
    private:
        Metrics metrics;
        int32_t codepoint;
    public:
        Metrics getMetrics() const;
        int32_t getCodepoint() const;
};
}}

#endif // GLYPH_H
