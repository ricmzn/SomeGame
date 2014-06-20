#ifndef OPTIONPARSER_H
#define OPTIONPARSER_H
#include <Engine/Base/SharedTypes.h>
#include <memory>

class ConfigVar
{
    public:
        enum class Type
        {
            Boolean,
            Integer,
            String
        };

        const std::string name;
        const Type type;
        void* ptr;

        ConfigVar(std::string name, bool value);
        ConfigVar(std::string name, int value);
        ConfigVar(std::string name, const char* value);
        ConfigVar(const ConfigVar& other);
        ~ConfigVar();
};

class OptionParser
{
    private:
        Array<ConfigVar> options;
        Array<std::string> defaults;
    public:
        OptionParser(int argc, char** argv);
        ~OptionParser();
        bool getBoolean(std::string opt) const;
        int getInteger(std::string opt) const;
        std::string getString(std::string opt) const;
        const Array<std::string>& getDefaults() const;
};

#endif // OPTIONPARSER_H
