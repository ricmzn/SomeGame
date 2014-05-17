#include <Base/System/Application.h>
#include <Base/System/Messagebox.h>
#include <Base/Exceptions.h>
#include <iostream>

int main(int argc, char** argv) try
{
    Application app(argc, argv);
    return app.run();
}
catch (const BaseException& ex)
{
    MessageBoxError("Fatal Error", ex.message());
    std::cerr << ex.trace() << std::endl;
    return 1;
}
