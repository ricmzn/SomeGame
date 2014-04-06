#include "Exceptions.h"
#include <cstdlib>
#include <cstdio>

/*---------------*/
/* BaseException */
/*---------------*/
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
{
    const char* fmt = "%s";
    const int len = snprintf(NULL, 0, fmt, what) + 1;
    buffer = new char[len];
    snprintf(buffer, len, fmt, what);
}

/*----------------------*/
/* MissingFileException */
/*----------------------*/
MissingFileException::MissingFileException(const char* filename)
{
    const char* fmt = "File does not exist in search path: \'%s\'";
    const int len = snprintf(NULL, 0, fmt, filename) + 1;
    buffer = new char[len];
    snprintf(buffer, len, fmt, filename);
}
