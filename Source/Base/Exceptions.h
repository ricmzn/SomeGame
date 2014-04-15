#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

class BaseException
{
    protected:
        char* buffer;
    public:
        BaseException(const char* msg, const char* start = "", const char* end = "");
        virtual ~BaseException() = 0;
        const char* message() const;
        const char* trace() const;
};

class InitializationException : public BaseException
{
    public:
        InitializationException(const char* what);
};

class MissingFileException : public BaseException
{
    public:
        MissingFileException(const char* filename);
};

class InvalidParameterException : public BaseException
{
    public:
        InvalidParameterException(const char* param, const char* func);
};

#endif // EXCEPTIONS_H
