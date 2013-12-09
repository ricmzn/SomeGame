#ifndef CONFIGFILE_H_INCLUDED
#define CONFIGFILE_H_INCLUDED
#include <cstdio>
#include <cstring>
#include <sstream>
#include <vector>
#include "filesystem.h"

namespace cfg
{
    struct Vec2
    {
        float x, y;
    };
	
	struct Vec3
	{
		float x, y, z;
	};
	
	struct Vec4
	{
		float x, y, z, w;
	};

    enum VarType
    {
        Void,
        Int,
        Float,
        Bool,
        String,
        Vector2,
		Vector3,
		Vector4,
        ArrayNode
    };

    struct Node
    {
        Node(const std::string& _str, int16_t _t) : name(_str), type(_t) {}
        std::string name;
        int16_t type;
        virtual std::string get() = 0;
        virtual void set(const std::string& val) = 0;
    };

    struct Variable : public Node
    {
        Variable(const std::string& _str) : Node(_str, Void) {}
        union
        {
            int32_t asInt;
            float asFloat;
            struct
            {
                char* ptr;
                uint32_t size;
            } string;
            Vec2 asVector;
        } varData;
        std::string get();
        void set (const std::string& val);
    };

    struct Array : public std::vector<Node*>, public Node
    {
        Array(const std::string& _str) : Node(_str, ArrayNode) {}
        std::string get();
        virtual void set(const std::string& val) {}
    };

    std::string Node::get()
    {
        return "(BaseNodeClass)";
    }

    void Variable::set (const std::string& val)
    {
        if (type == String)
        {
            type = String;
            delete[] varData.string.ptr;
            varData.string.size = 0;
        }
        if (val[0] >= '0' and val[0] <= '9') // We have a float
        {
            type = Float;
            sscanf(val.c_str(), "%f", &varData.asFloat);
        }
        else if (val == "true" or val == "false") // We have a boolean
        {
            type = Bool;
            varData.asInt = (val == "true")? 1 : 0;
        }
        else if (val[0] == '(') // We have a vector
        {
            type = Vector4;
            sscanf(val.c_str(), "(%f, %f)", &varData.asVector.x, &varData.asVector.y);
        }
        else if (val[0] == '"') // We have a string
        {
            type = String;
            varData.string.size = strlen(val.c_str());
            varData.string.ptr = new char[varData.string.size];
            sscanf(val.c_str(), "\"%[^\"]", varData.string.ptr);
        }
        else
        {
            type = Void;
        }
    }

    std::string Variable::get()
    {
        std::stringstream ss;
        switch(type)
        {
            case Int:
                ss << varData.asInt;
                break;
            case Float:
                ss << varData.asFloat;
                break;
            case Bool:
                ss << ((varData.asInt == 1) ? "true" : "false");
                break;
            case String:
                ss << varData.string.ptr;
                break;
            case Vector4:
                ss << varData.asVector.x << ' ' << varData.asVector.y;
                break;
            case Void:
                ss << "(void)";
                break;
        }
        return ss.str();
    }

    std::string Array::get()
    {
        std::stringstream ss;
        ss << "{";
        for (size_t i = 0; i < this->size(); i++)
        {
            ss << this->at(i)->get();
            if (i < this->size() - 1)
                ss << ", ";
        }
        ss << "}";
        return ss.str();
    }
}

struct ConfigTree
{
    std::vector<cfg::Node*> nodes;
};

ConfigTree ParseConfig(const std::string& file)
{
    ConfigTree tree;
    File temp(file);
    std::istringstream is(temp.string());

    std::string line;
    temp.clear();

    int i = 1;
    while (std::getline(is, line))
    {
        if (line[0] == '#' or line.size() <= 1) continue;
        tree.nodes.push_back(new cfg::Variable(line.substr(0, line.find_first_of('='))));
        for (size_t c = 0; c < line.size(); c++)
        {
            if (line[c-2] == '=')
            {
                tree.nodes.back()->set (line.substr(c, line.find_last_of(';')-c));
                break;
            }
        }
        i++;
    }

    return tree;
}

#endif // CONFIGFILE_H_INCLUDED
