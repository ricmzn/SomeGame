#include "Exceptions.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <string>
using namespace Exceptions;

#if defined(__WIN32)
/*----------------------------*/
/* createStackTrace (Windows) */
/*----------------------------*/
#define NotAvailableStr "No trace is available."
static void createStackTrace(char*& buffer)
{
    buffer = new char[sizeof NotAvailableStr];
    strcpy(buffer, NotAvailableStr);
}

#elif defined(__GLIBC__)
/*------------------------------*/
/* createStackTrace (Linux/BSD) */
/*------------------------------*/
#include <execinfo.h>
#include <cxxabi.h>
static void createStackTrace(char*& buffer)
{
    void* symbols[25];
    size_t bufferSize = 1;
    size_t backtraceSkip = 2;
    size_t backtraceSize = backtrace(symbols, 25);
    char** backtraceStrings = backtrace_symbols(symbols, backtraceSize);

    for(size_t i = backtraceSkip; i < backtraceSize; i++)
    {
        bufferSize += strlen(backtraceStrings[i]) + sizeof('\n');
    }

    buffer = new char[bufferSize] {0};
    for(size_t i = backtraceSkip; i < backtraceSize; i++)
    {
        strcat(buffer, backtraceStrings[i]);
        strcat(buffer, "\n");
    }

    buffer[bufferSize - 1] = 0;
}

#endif

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

    // And generate a stack trace
    createStackTrace(btrace);
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
