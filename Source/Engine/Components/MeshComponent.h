#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H
#include <Engine/Components/SceneComponent.h>
#include <Engine/Render/ShaderProgram.h>
#include <Engine/Render/VertexArray.h>
#include <Engine/Render/Texture2D.h>

namespace Components {
class api_public MeshComponent : public SceneComponent
{
    public:
        Base::Types::Mat4 modelMatrix;
        Render::VertexArray vertexArray;
        Render::ShaderProgram meshShader;
        Array<Render::Texture2D> textures;
};
}

#endif // MESHCOMPONENT_H
