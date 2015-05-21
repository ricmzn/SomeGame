#include "Rectangle.h"
using namespace GUI::Primitives;

Rectangle::Rectangle(int width, int height)
    : width(width), height(height)
{}

int Rectangle::getWidth() const
{
    return width;
}

int Rectangle::getHegiht() const
{
    return height;
}
