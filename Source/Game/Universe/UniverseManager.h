#ifndef UNIVERSEMANAGER_H
#define UNIVERSEMANAGER_H
#include <Engine/Render/API.h>
#include <Engine/Entity/DrawableEntity.h>
#include <Engine/Render/VertexArray.h>
#include <Engine/Render/ShaderProgram.h>
#include <Engine/Render/Texture1D.h>
#include <Engine/Render/Texture2D.h>
#include <Game/Entities/PlayerController.h>
#include <Game/Entities/SpaceObject.h>

namespace Universe
{
    class UniverseManager : public DrawableEntity
    {
    private:
        Array<SpaceObject*> stars;
        const Vec3& reference;
        Render::VertexBuffer vbo;
        Render::VertexArray vao;
        Render::ShaderProgram shader;
        Render::Texture1D heatTexture;
        Render::Texture2D maskTexture;
        GLint matrixLocation;
        GLint heatLocation;
        GLint maskLocation;
    public:
        UniverseManager(const PlayerController& player);
        virtual ~UniverseManager();
        virtual void spawn();
        virtual void think();
        virtual void draw(const Camera* camera);
        const Array<SpaceObject*>& getStars() const;
    };
}

#endif // UNIVERSEMANAGER_H
