#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

namespace Exceptions
{
    class BaseException
    {
    protected:
        char* buffer;
        char* btrace;
    public:
        BaseException(const char* msg, const char* start = "", const char* end = "");
        virtual ~BaseException() = 0;
        const char* message() const;
        const char* trace() const;
    };

    class GenericError : public BaseException
    {
    public:
        GenericError(const char* what);
    };

    class MissingFile : public BaseException
    {
    public:
        MissingFile(const char* filename);
    };

    class InvalidParameter : public BaseException
    {
    public:
        InvalidParameter(const char* param, const char* func);
    };
}

// Pollute the global namespace like a champ
using namespace Exceptions;

#endif // EXCEPTIONS_H
