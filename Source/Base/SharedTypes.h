#ifndef SHAREDTYPES_H
#define SHAREDTYPES_H
#include <forward_list>
#include <cstdint>

// Primitive types
typedef unsigned char Byte;
typedef unsigned long tick_t;

// Container types
#include <vector>

template <typename T> using Array = std::vector<T>;
#include <list>
template <typename T> using List = std::forward_list<T>;

// Vector types
#include <glm/vec2.hpp>
typedef glm::vec2 Vec2;

#include <glm/vec3.hpp>
typedef glm::vec3 Vec3;

#include <glm/vec4.hpp>
typedef glm::vec4 Vec4;

#endif // SHAREDTYPES_H
