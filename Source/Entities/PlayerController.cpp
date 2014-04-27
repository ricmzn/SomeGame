#include "PlayerController.h"

PlayerController::PlayerController(InputArray* keyArrayPtr)
    : mode(FlightMode::SPACE),
      keys(keyArrayPtr),
      drag(0.9925)
{
    pos = {0, 4, 0};
}

PlayerController::~PlayerController()
{}

void PlayerController::spawn(SpawnFlags flags)
{
    (void)flags;
}

void PlayerController::think(float deltaTime)
{
    static const float sensitivity = 0.25;
    if (mode == FlightMode::SPACE)
    {
        if (keys->pressed[SDL_SCANCODE_W])
        {
            velocity += forward();
        }
        else if (keys->pressed[SDL_SCANCODE_S])
        {
            velocity -= forward();
        }
        if (keys->pressed[SDL_SCANCODE_D])
        {
            velocity += right();
        }
        else if (keys->pressed[SDL_SCANCODE_A])
        {
            velocity -= right();
        }
        if (keys->pressed[SDL_SCANCODE_Q])
        {
            velocity += up();
        }
        else if (keys->pressed[SDL_SCANCODE_Z])
        {
            velocity -= up();
        }

        this->rotate(this->up(), keys->mouse.xrel * deltaTime * sensitivity);
        this->rotate(this->right(), keys->mouse.yrel * deltaTime * sensitivity);
        if (this->right().y > 0.01)
        {
            this->rotate(this->forward(), -deltaTime);
        }
        else if (this->right().y < -0.01)
        {
            this->rotate(this->forward(), deltaTime);
        }
    }
    else if (mode == FlightMode::ATMO)
    {
        if (keys->pressed[SDL_SCANCODE_W])
        {
            velocity += forward();
        }
        else if (keys->pressed[SDL_SCANCODE_S])
        {
            velocity -= forward();
        }
        if (keys->pressed[SDL_SCANCODE_D])
        {
            angvel.y = angvel.y + 0.00025f;
        }
        else if (keys->pressed[SDL_SCANCODE_A])
        {
            angvel.y = angvel.y - 0.00025f;
        }

        angvel.x = angvel.x + keys->mouse.yrel * sensitivity/1000.f;
        angvel.z = angvel.z - keys->mouse.xrel * sensitivity/1000.f;
    }

    this->translate(velocity * 0.5f * deltaTime);
    this->rotate(right(),   angvel.x);
    this->rotate(up(),      angvel.y);
    this->rotate(forward(), angvel.z);
    velocity *= drag;
    angvel *= drag;
}
