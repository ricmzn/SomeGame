#include <Engine/System/Messagebox.h>
#include <Engine/Base/Exceptions.h>
#include <Game/Game.h>
#include <iostream>

int main(int argc, char** argv) try
{
    // Initialize the application
    Game game(argc, argv);
    // And run it
    return game.run();
}
catch (const BaseException& ex)
{
    MessageBoxError("Fatal Error", ex.message());
    std::cerr << ex.trace() << std::endl;
    return 1;
}
