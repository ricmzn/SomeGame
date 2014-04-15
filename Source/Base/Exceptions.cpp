#include "Exceptions.h"
#include <cstdlib>
#include <cstdio>

/*---------------*/
/* BaseException */
/*---------------*/
BaseException::BaseException(const char *msg,
                             const char *start,
                             const char *end)
{
    // Concatenate an error message to inform the user of the error
    const char* fmt = "%s%s%s";
    const int len = snprintf(NULL, 0, fmt, start, msg, end) + 1;
    buffer = new char[len];
    snprintf(buffer, len, fmt, start, msg, end);
}

BaseException::~BaseException()
{
    free(buffer);
}

const char* BaseException::message() const
{
    return buffer;
}

const char* BaseException::trace() const
{
    return "No trace is available.";
}

/*-------------------------*/
/* InitializationException */
/*-------------------------*/
InitializationException::InitializationException(const char* what)
    : BaseException(what)
{
}

/*----------------------*/
/* MissingFileException */
/*----------------------*/
MissingFileException::MissingFileException(const char* filename)
    : BaseException(filename, "File does not exist in search path: \'", "\'!")
{
}

/*---------------------------*/
/* InvalidParameterException */
/*---------------------------*/
InvalidParameterException::InvalidParameterException(const char *param, const char* func)
    : BaseException("\nInvalid parameter: ", func, param)
{
}
