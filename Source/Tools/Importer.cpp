#include <Tools/Import/GenericAssimp.h>
#include <Engine/Base/OptionParser.h>
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

int main(int argc, char** argv) try
{
    OptionParser opts(argc, argv);
    if (opts.getBoolean("--help") || opts.getBoolean("-h"))
    {
        std::cout << helpString << std::endl;
        return 0;
    }
    std::cout << opts.getString("-o") << std::endl;
    std::cout << opts.getInteger("--test") << std::endl;

    for (auto& str : opts.getDefaults())
    {
        std::cout << "Non-arg: " << str << std::endl;
    }

    return 0;
}
catch (BaseException& ex)
{
    std::cerr << ex.message() << std::endl;
    return 1;
}
