#include "Filesystem.h"
#include <sstream>

namespace Filesystem
{
    void initialize(int argc, char **argv)
    {
        if (!PHYSFS_isInit())
            PHYSFS_init(argv[0]);
    }

    // TODO maybe make a function to generate mount system-specific errors?
    void setRootPath(const std::string &relativeToExecutable)
    {
        // Build the root path
        std::string baseDir = PHYSFS_getBaseDir() + relativeToExecutable;
        // Check for existance of MountList.txt
        std::string mountListPath = baseDir + "/MountList.txt";
        if (FILE* mountListFile = fopen(mountListPath.c_str(), "r"))
        {
            fclose(mountListFile);
        }
        else
        {
            std::string error;
            error += "Failed to open MountList.txt in \'";
            error += relativeToExecutable;
            error += "\'";
            throw std::runtime_error(error);
        }
        // Mount the root path
        PHYSFS_mount(baseDir.c_str(), "/", 1);

        // Mount archives
        File mountList("MountList.txt");
        while (mountList)
        {
            std::istringstream ss(mountList.string());
            std::string line;
            // For each line
            while (std::getline(ss, line))
            {
                if (!line.empty())
                {
                    // Windows CR-LF trailing CR fix
                    if (line.at(line.size()-1) == '\r')
                    {
                        line.resize(line.size()-1);
                    }

                    // Build the mount path
                    std::string mountPath = baseDir + "/" + line;
                    // Skip folders and non-existing files
                    if (FILE* file = fopen(mountPath.c_str(), "r"))
                    {
                        fclose(file);
                    }
                    else
                    {
                        std::string error;
                        error += "File not exist in virtual filesystem: \'";
                        error += line;
                        error += "\'";
                        throw std::runtime_error(error);
                    }
                    // Mount the file
                    int status = PHYSFS_mount(mountPath.c_str(), "/", 0);
                    // Abort if it's not an archive
                    if(!status)
                    {
                        std::string error;
                        error += "File is not a valid .zip archive: \'";
                        error += line;
                        error += "\'";
                        throw std::runtime_error(error);
                    }
                }
            }
            mountList.close();
        }
    }
}
