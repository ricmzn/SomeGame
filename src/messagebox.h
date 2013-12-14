#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#ifdef __WIN32__
    #define WIN32_MEAN_AND_LEAN
    #include <windows.h>
    #define MessageBoxError(title, message) {MessageBoxA(0, message, title, MB_ICONERROR | MB_OK);}
#else
    #include <Qt/QMessageBox>
    #define MessageBoxError(title, message) {QMessageBox::MessageBoxError();} // TODO
#endif

#endif // MESSAGEBOX_H
