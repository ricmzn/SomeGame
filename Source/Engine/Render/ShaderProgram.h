#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#include <Engine/Render/ContextObject.h>
#include <string>

namespace Render
{
    class ShaderProgram : public ContextObject
    {
    protected:
        std::string errorLog;

    public:
        ShaderProgram();
        virtual ~ShaderProgram();
        void addShader(GLenum type, const GLchar* src, GLint size);
        const char* getLog() const;
        void link();
    };
}

#endif // SHADERPROGRAM_H
