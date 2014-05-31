#ifndef CONSOLE_H
#define CONSOLE_H
#include <iostream>

class Console
{
    public:
        const char* getLine(int line) const;

        template<typename T, typename... Args>
        void printLine(T str)
        {
            std::cout << str << "\n";
        }

        template<typename T, typename... Args>
        void printLine(T str, Args... next)
        {
            std::cout << str;
            printLine(next...);
        }

        void overwrite(int line, const char* str);
        void clearLine(int line);
        void clearAll();
};

#endif // CONSOLE_H
