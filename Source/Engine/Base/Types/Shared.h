#ifndef TYPES_SHARED_H
#define TYPES_SHARED_H
// NOTE: This file is getting kinda big...

// Import all global macros
#include <Engine/System/Macros.h>

// Global namespace includes
#include <cstdint>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <initializer_list>
#include <memory>
#include <thread>
#include <mutex>

namespace Base {
namespace Types {

// Primitive types
typedef unsigned char   Byte;
typedef long long       Tick;
typedef unsigned        EntityID;
typedef std::string     String;
typedef const String&   StringRef;

// Struct types
struct Pixel {
    uint8_t r, g, b, a;
};

// Container types
template <typename T> using Array = std::vector<T>;
template <typename T> using List = std::list<T>;
template <typename T> using Queue = std::queue<T>;
template <typename KeyType, typename T> using HashMap = std::map<KeyType, T>;

// GLM types
typedef glm::vec2 Vec2;
typedef glm::vec3 Vec3;
typedef glm::vec4 Vec4;
typedef glm::mat4 Mat4;
typedef glm::quat Quat;

// Misc
template <typename T> using StaticList = std::initializer_list<T>;
template <typename T> using UniquePtr = std::unique_ptr<T>;
template <typename T> using UniqueRef = UniquePtr<T>&;
template <typename T> using SharedPtr = std::shared_ptr<T>;
template <typename T> using SharedRef = SharedPtr<T>&;
template <typename T> using WeakPtr = std::weak_ptr<T>;
template <typename T> using WeakRef = WeakPtr<T>&;
typedef std::thread Thread;
typedef std::mutex Mutex;

}}

// Escape some types into the global namespace
#define USE using Base::Types::
USE Byte;
USE Tick;
USE EntityID;
USE String;
USE StringRef;
USE Pixel;
USE Array;
USE List;
USE Queue;
USE HashMap;
USE Vec2;
USE Vec3;
USE Vec4;
USE Mat4;
USE Quat;
USE StaticList;
USE UniquePtr;
USE UniqueRef;
USE SharedPtr;
USE SharedRef;
USE WeakPtr;
USE WeakRef;
USE Thread;
USE Mutex;
#undef USE

// Commonly-used vectors
#define VEC3_FORWARD Vec3(0, 0, -1)
#define VEC3_RIGHT   Vec3(1, 0, 0)
#define VEC3_UP      Vec3(0, 1, 0)

#endif // TYPES_SHARED_H
