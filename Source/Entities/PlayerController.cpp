#include "PlayerController.h"

PlayerController::PlayerController(KeyArray* keyArrayPtr)
    : keys(keyArrayPtr),
      drag(0.995)
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

    pos += velocity * 0.25f * deltaTime;
    velocity *= drag;
}
