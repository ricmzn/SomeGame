#ifndef GUIDRAWABLE_H
#define GUIDRAWABLE_H
#include <Engine/Render/Texture2D.h>
#include <Engine/Render/VertexArray.h>

namespace GUI {
class api_public Canvas;
}

namespace GUI {
namespace Primitives {
class api_public GUIDrawable
{
    public:
        struct Origin {
            int x, y;
            Origin();
        };
    protected:
        Render::Texture2D texture;
        Render::VertexArray vertexArray;
    public:
        Origin origin;
        const Render::Texture2D& getTexture() const;
        const Render::VertexArray& getVertexArray() const;
};
}}

#endif // GUIDRAWABLE_H
