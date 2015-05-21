#include <Tools/Import/GenericAssimp.h>
#include <Engine/Base/Exceptions.h>
#include <iostream>

const char helpString[] =
"Usage:\n"
"    Importer <inputs> [-h]\n"
"\n"
"Parameters:\n"
"    -h --help:      Show this help text\n"
"    -v --verbose:   Enable extra debug output\n"
"\n"
"Supported formats:\n"
"    .blend - Blender model\n"
"    .dae - Collada Dae (XML)\n"
"    .obj - Wavefront Obj\n"
"    .3ds - 3DS Max model\n"
"    Others (check Assimp docs)\n";

int main() try
{
    std::cout << helpString << std::endl;
    return 0;
}
catch (BaseException& ex)
{
    std::cerr << ex.message() << std::endl;
    return 1;
}
