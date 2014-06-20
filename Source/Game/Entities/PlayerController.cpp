#include "PlayerController.h"
#include <Engine/System/Application.h>

PlayerController::PlayerController()
    : TransformEntity("player"),
      mode(FlightMode::SPACE),
      drag(0.99875)
{}

void PlayerController::spawn()
{
    std::cout << "New player created" << std::endl;
}

void PlayerController::think()
{
    const float sensitivity = 0.25;
    const float deltaTime = System::ActiveApplication->deltaTime;
    const System::Input& input = System::ActiveApplication->input;
    static float fov = 60;

    static Camera* pCamera = nullptr; if (!pCamera)
    {
        pCamera = dynamic_cast<Camera*>(this->getRoot()->find("camera"));
    }

    if (input.keyDown[SDL_SCANCODE_0])
    {
        if (pCamera)
        {
            pCamera->setPerspective(fov = 60);
        }
    }
    if (input.keyPressed[SDL_SCANCODE_EQUALS])
    {
        if (pCamera)
        {
            pCamera->setPerspective(fov -= 25 * deltaTime);
        }
    }
    else if (input.keyPressed[SDL_SCANCODE_MINUS])
    {
        if (pCamera)
        {
            pCamera->setPerspective(fov += 25 * deltaTime);
        }
    }

    // Go fast if shift is held
    float speedMultiplier = 1.0;
    if (input.keyPressed[SDL_SCANCODE_LSHIFT])
    {
        speedMultiplier = 25.0;
    }

    // Toggle spaceship/plane controls
    if (input.keyDown[SDL_SCANCODE_F])
    {
        mode = (mode == FlightMode::ATMO) ? FlightMode::SPACE : FlightMode::ATMO;
    }

    if (mode == FlightMode::SPACE)
    {
        if (input.keyPressed[SDL_SCANCODE_W])
        {
            velocity += transform.forward() * speedMultiplier;
        }
        else if (input.keyPressed[SDL_SCANCODE_S])
        {
            velocity -= transform.forward() * speedMultiplier;
        }
        if (input.keyPressed[SDL_SCANCODE_D])
        {
            velocity += transform.right() * speedMultiplier;
        }
        else if (input.keyPressed[SDL_SCANCODE_A])
        {
            velocity -= transform.right() * speedMultiplier;
        }
        if (input.keyPressed[SDL_SCANCODE_Q])
        {
            velocity += transform.up() * speedMultiplier;
        }
        else if (input.keyPressed[SDL_SCANCODE_Z])
        {
            velocity -= transform.up() * speedMultiplier;
        }

        transform.rotate(transform.up(), input.mouse.xrel * deltaTime * sensitivity);
        transform.rotate(transform.right(), input.mouse.yrel * deltaTime * sensitivity);
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
        if (input.keyPressed[SDL_SCANCODE_W])
        {
            velocity += transform.forward();
        }
        else if (input.keyPressed[SDL_SCANCODE_S])
        {
            velocity -= transform.forward();
        }
        if (input.keyPressed[SDL_SCANCODE_D])
        {
            angvel.y = angvel.y + 0.00025f;
        }
        else if (input.keyPressed[SDL_SCANCODE_A])
        {
            angvel.y = angvel.y - 0.00025f;
        }

        angvel.x = angvel.x + input.mouse.yrel * sensitivity/1000.f;
        angvel.z = angvel.z - input.mouse.xrel * sensitivity/1000.f;
    }

    if (input.keyPressed[SDL_SCANCODE_SPACE])
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
