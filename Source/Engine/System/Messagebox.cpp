#include <Engine/System/Messagebox.h>
using namespace System;

#if defined(_WIN32)
#define WIN32_MEAN_AND_LEAN
#include <windows.h>

Messagebox::Option Messagebox::Error(const char* title, const char* message)
{
    MessageBoxA(NULL, message, title, MB_ICONERROR | MB_OK);
    return Option::Ok;
}

Messagebox::Option Messagebox::Warning(const char* title, const char* message)
{
    MessageBoxA(NULL, message, title, MB_ICONWARNING | MB_OK);
    return Option::Ok;
}

Messagebox::Option Messagebox::YesNo(const char* title, const char* message)
{
    switch(MessageBoxA(NULL, message, title, MB_ICONQUESTION | MB_YESNO))
    {
        default:
        case IDYES: return Option::Yes;
        case IDNO: return Option::No;
    }
}
#elif 0
// TODO: OSX support
#else
// @TODO: Replace with GTK+ code
#include <iostream>
#include <sstream>
#include <cstdlib>

static int showZenityDialog(const char* type, const char* title, const char* text)
{
    std::stringstream ss;
    ss << "zenity "
       << "--" << type
       << " --title=\"" << title << "\""
       << " --text=\"" << text << "\"";
#ifdef __linux__
    ss << " 2> /dev/null";
#endif
    int status = system(ss.str().c_str());
    if(status >= 255) {
        std::cerr << "FATAL: Zenity command line failed: " << ss.str() << std::endl;
    }
    return status;
}

Messagebox::Option Messagebox::Error(const char* title, const char* message)
{
    showZenityDialog("error", title, message);
    return Option::Ok;
}

Messagebox::Option Messagebox::Warning(const char* title, const char* message)
{
    showZenityDialog("warning", title, message);
    return Option::Ok;
}

Messagebox::Option Messagebox::YesNo(const char* title, const char* message)
{
    int code = showZenityDialog("question", title, message);
    if(code == 0) {
        return Option::Yes;
    } else {
        return Option::No;
    }
}
#endif
