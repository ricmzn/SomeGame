#ifndef SHAREDTYPES_H
#define SHAREDTYPES_H
#include <forward_list>
#include <cstdint>

// Primitive types
typedef unsigned char Byte;
typedef unsigned long Tick;

// Container types
#include <vector>
template <typename T> using Array = std::vector<T>;

#include <list>
template <typename T> using List = std::forward_list<T>;

// GLM types
#include <glm/vec2.hpp>
typedef glm::vec2 Vec2;

#include <glm/vec3.hpp>
typedef glm::vec3 Vec3;

#include <glm/vec4.hpp>
typedef glm::vec4 Vec4;

#include <glm/mat4x4.hpp>
typedef glm::mat4 Mat4;

#include <glm/gtc/quaternion.hpp>
typedef glm::quat Quaternion;

// Commonly-used vectors
#define VEC3_FORWARD Vec3(0, 0, -1)
#define VEC3_RIGHT   Vec3(1, 0, 0)
#define VEC3_UP      Vec3(0, 1, 0)

// Misc
#include <thread>
typedef std::thread Thread;

#include <SDL2/SDL_scancode.h>
struct InputArray
{
    int pressed[SDL_NUM_SCANCODES];
    struct
    {
        int left;
        int right;
        int xrel;
        int yrel;
    } mouse;
};

#endif // SHAREDTYPES_H
