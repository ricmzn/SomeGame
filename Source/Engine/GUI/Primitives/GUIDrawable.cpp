#include "GUIDrawable.h"
using namespace GUI::Primitives;

GUIDrawable::Origin::Origin()
    : x(0), y(0)
{}

const Render::Texture2D&GUIDrawable::getTexture() const
{
    return texture;
}

const Render::VertexArray&GUIDrawable::getVertexArray() const
{
    return vertexArray;
}
