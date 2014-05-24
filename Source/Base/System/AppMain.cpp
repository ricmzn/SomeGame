#include <Base/System/Application.h>
#include <Base/System/Messagebox.h>
#include <Base/Exceptions.h>
#include <iostream>
const char* __binPath;

int main(int argc, char** argv) try
{
    // Glue argv[0] into a global
    __binPath = argv[0];
    // Initialize the application
    Application app(argc, argv);
    // And run it
    return app.run();
}
catch (const BaseException& ex)
{
    MessageBoxError("Fatal Error", ex.message());
    std::cerr << ex.trace() << std::endl;
    return 1;
}
