#include "OptionParser.h"

ConfigVar::ConfigVar(std::string name, bool value)
    : name(name),
      type(Type::Boolean)
{
    ptr = new bool(value);
}

ConfigVar::ConfigVar(std::string name, int value)
    : name(name),
      type(Type::Integer)
{
    ptr = new int(value);
}

ConfigVar::ConfigVar(std::string name, const char* value)
    : name(name),
      type(Type::String)
{
    ptr = new std::string(value);
}

ConfigVar::ConfigVar(const ConfigVar& other)
    : name(other.name),
      type(other.type)
{
    switch (type)
    {
        case Type::Boolean:
            ptr = new bool(*(bool*)other.ptr);
            break;
        case Type::Integer:
            ptr = new int(*(int*)other.ptr);
            break;
        case Type::String:
            ptr = new std::string(*(std::string*)other.ptr);
            break;
    }
}

ConfigVar::~ConfigVar()
{
    switch(type)
    {
        case Type::Boolean:
            delete static_cast<bool*>(ptr);
            break;
        case Type::Integer:
            delete static_cast<int*>(ptr);
            break;
        case Type::String:
            delete static_cast<std::string*>(ptr);
            break;
    }
}

OptionParser::OptionParser(int argc, char** argv)
{
    for (int i = 1; i < argc; i++)
    {
        const char* arg = argv[i];
        const char* next = argv[i+1];
        if (arg[0] == '-' && next && next[0] != '-')
        {
            int asInt;
            if (sscanf(next, "%d", &asInt) == 1)
            {
                options.emplace_back(arg, atoi(next));
            }
            else
            {
                options.emplace_back(arg, next);
            }
            ++i;
        }
        else if (arg[0] == '-')
        {
            options.emplace_back(arg, true);
        }
        else
        {
            defaults.emplace_back(arg);
        }
    }
}

OptionParser::~OptionParser()
{}

bool OptionParser::getBoolean(std::string opt) const
{
    for (const ConfigVar& var : options)
    {
        if (var.name == opt && var.type == ConfigVar::Type::Boolean)
        {
            return *(bool*)var.ptr;
        }
    }
    return false;
}


int OptionParser::getInteger(std::string opt) const
{
    for (const ConfigVar& var : options)
    {
        if (var.name == opt && var.type == ConfigVar::Type::Integer)
        {
            return *(int*)var.ptr;
        }
    }
    return 0;
}

std::string OptionParser::getString(std::string opt) const
{
    for (const ConfigVar& var : options)
    {
        if (var.name == opt && var.type == ConfigVar::Type::String)
        {
            return *(std::string*)var.ptr;
        }
    }
    return "";
}

const Array<std::string>& OptionParser::getDefaults() const
{
    return defaults;
}
