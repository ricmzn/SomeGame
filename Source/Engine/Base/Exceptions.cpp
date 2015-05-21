#include "Exceptions.h"
#include <cstring>
#include <cstdio>
using namespace Base;

/*---------------*/
/* BaseException */
/*---------------*/
BaseException::BaseException(const char* msg,
                             const char* start,
                             const char* end)
{
    // Concatenate an error message to inform the user of the error
    const size_t len = strlen(msg) + strlen(start) + strlen(end) + 1;
    buffer = new char[len];
    sprintf(buffer, "%s%s%s", start, msg, end);
}

BaseException::~BaseException()
{
    delete[] buffer;
}

const char* BaseException::message() const
{
    return buffer;
}

/*--------------*/
/* GenericError */
/*--------------*/
GenericError::GenericError(const char* what)
    : BaseException(what)
{
}

/*-------------*/
/* MissingFile */
/*-------------*/
MissingFile::MissingFile(const char* filename)
    : BaseException(filename, "File does not exist in search path: \'", "\'!")
{
}

/*------------------*/
/* InvalidParameter */
/*------------------*/
InvalidParameter::InvalidParameter(const char *param, const char* func)
    : BaseException("\nInvalid parameter: ", func, param)
{
}
