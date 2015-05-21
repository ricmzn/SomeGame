#include "Canvas.h"
using namespace GUI;

Canvas::Canvas(int width, int height)
    : width(width),
      height(height)
{}

Canvas::~Canvas()
{}

void Canvas::resize(int newWidth, int newHeight)
{
    width = newWidth;
    height = newHeight;
}

void Canvas::paint(const Primitives::GUIDrawable& drawable)
{
    (void)drawable;
}
