#include "PlayerController.h"

PlayerController::PlayerController(InputArray* keyArrayPtr)
    : mode(FlightMode::SPACE),
      input(keyArrayPtr),
      drag(0.9925)
{
    transform.pos = {0, 16, 0};
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
        if (input->keyPressed[SDL_SCANCODE_W])
        {
            velocity += transform.forward();
        }
        else if (input->keyPressed[SDL_SCANCODE_S])
        {
            velocity -= transform.forward();
        }
        if (input->keyPressed[SDL_SCANCODE_D])
        {
            velocity += transform.right();
        }
        else if (input->keyPressed[SDL_SCANCODE_A])
        {
            velocity -= transform.right();
        }
        if (input->keyPressed[SDL_SCANCODE_Q])
        {
            velocity += transform.up();
        }
        else if (input->keyPressed[SDL_SCANCODE_Z])
        {
            velocity -= transform.up();
        }

        transform.rotate(transform.up(), input->mouse.xrel * deltaTime * sensitivity);
        transform.rotate(transform.right(), input->mouse.yrel * deltaTime * sensitivity);
        if (transform.right().y > 1 * deltaTime)
        {
            transform.rotate(transform.forward(), -deltaTime);
        }
        else if (transform.right().y < -1 * deltaTime)
        {
            transform.rotate(transform.forward(), deltaTime);
        }
    }
    else if (mode == FlightMode::ATMO)
    {
        if (input->keyPressed[SDL_SCANCODE_W])
        {
            velocity += transform.forward();
        }
        else if (input->keyPressed[SDL_SCANCODE_S])
        {
            velocity -= transform.forward();
        }
        if (input->keyPressed[SDL_SCANCODE_D])
        {
            angvel.y = angvel.y + 0.00025f;
        }
        else if (input->keyPressed[SDL_SCANCODE_A])
        {
            angvel.y = angvel.y - 0.00025f;
        }

        angvel.x = angvel.x + input->mouse.yrel * sensitivity/1000.f;
        angvel.z = angvel.z - input->mouse.xrel * sensitivity/1000.f;
    }

    if (input->keyPressed[SDL_SCANCODE_SPACE])
    {
        transform.pos += transform.forward() * deltaTime * 1500.f;
    }

    transform.translate(velocity * 0.5f * deltaTime);
    transform.rotate(transform.right(),   angvel.x);
    transform.rotate(transform.up(),      angvel.y);
    transform.rotate(transform.forward(), angvel.z);
    velocity *= drag;
    angvel *= drag;
}

void PlayerController::setFlightMode(FlightMode newMode)
{
    this->mode = newMode;
}
