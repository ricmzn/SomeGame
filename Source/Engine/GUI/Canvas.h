#ifndef CANVAS_H
#define CANVAS_H
#include <Engine/Render/Texture2D.h>
#include <Engine/Base/Types/Shared.h>
#include <Engine/GUI/Primitives/Shape.h>
#include <Engine/GUI/Primitives/Image.h>

namespace GUI {
class api_public Canvas : public Primitives::GUIDrawable
{
    private:
        int width, height;
    public:
        Canvas(int width, int height);
        virtual ~Canvas();

        void resize(int newWidth, int newHeight);
        void paint(const Primitives::GUIDrawable& drawable);
};
}

#endif // CANVAS_H
