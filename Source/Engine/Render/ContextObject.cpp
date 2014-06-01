#include "ContextObject.h"
using namespace Render;

ContextObject::ContextObject()
    : handle(GL_NONE)
{}

ContextObject::~ContextObject()
{}

GLuint ContextObject::getHandle() const
{
    return handle;
}

ContextObject::operator GLuint() const
{
    return handle;
}
