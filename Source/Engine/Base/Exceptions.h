#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <Engine/Base/Types/Shared.h>

namespace Base
{
class api_public BaseException
{
    protected:
        char* buffer;
    public:
        BaseException(const char* msg, const char* start = "", const char* end = "");
        virtual ~BaseException() = 0;
        const char* message() const;
};

class api_public GenericError : public BaseException
{
    public:
        GenericError(const char* what);
};

class api_public MissingFile : public BaseException
{
    public:
        MissingFile(const char* filename);
};

class api_public InvalidParameter : public BaseException
{
    public:
        InvalidParameter(const char* param, const char* func);
};
}

using Base::BaseException;
using Base::GenericError;
using Base::MissingFile;
using Base::InvalidParameter;

#endif // EXCEPTIONS_H
