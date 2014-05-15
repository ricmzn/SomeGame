#include "Exceptions.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>

namespace Exceptions
{
    /*---------------*/
    /* BaseException */
    /*---------------*/
    BaseException::BaseException(const char *msg,
                                 const char *start,
                                 const char *end)
    {
        // Concatenate an error message to inform the user of the error
        const int len = strlen(msg) + strlen(start) + strlen(end) + 1;
        buffer = new char[len];
        sprintf(buffer, "%s%s%s", start, msg, end);

        // And generate an empty stack trace
        btrace = new char[256];
        memset(btrace, '\0', 256);
        strncpy(btrace, "No trace is available.", 255);
    }

    BaseException::~BaseException()
    {
        delete[] btrace;
        delete[] buffer;
    }

    const char* BaseException::message() const
    {
        return buffer;
    }

    const char* BaseException::trace() const
    {
        return btrace;
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
}
