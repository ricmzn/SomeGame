#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <Engine/GUI/Primitives/GUIDrawable.h>

namespace GUI {
namespace Primitives {
class api_public Rectangle : public GUIDrawable
{
    private:
        int width, height;
    public:
        Rectangle(int width, int height);
        int getWidth() const;
        int getHegiht() const;
};
}}

#endif // RECTANGLE_H
