#include <Engine/Filesystem/Filesystem.h>
#include <Engine/System/Messagebox.h>
#include <Engine/Base/Exceptions.h>
#include <Game/Game.h>
#include <iostream>

int main(int argc, char** argv) try
{
    // Set the root path
    Filesystem::setRootPath("../Data");
    // Initialize the application
    Game game(argc, argv);
    // And run the game
    return game.run();
}
catch (const BaseException& ex)
{
    System::Messagebox::Error("Fatal Error", ex.message());
    std::cerr << ex.trace() << std::endl;
    return 1;
}
