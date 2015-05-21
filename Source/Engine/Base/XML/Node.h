#ifndef XMLNODE_H
#define XMLNODE_H
#include <Engine/Base/Types/Shared.h>
#include <Engine/System/Macros.h>

namespace Base {
namespace XML {

namespace Private {
struct Node;
}

class api_public Node
{
    private:
        Private::Node* priv;
    public:
        Node(Private::Node* node);
        ~Node();

        bool asBoolean(bool def = false) const;
        int asInteger(int def = 0) const;
        float asFloat(float def = 0) const;
        String asString(StringRef def = "") const;
};
}}

#endif // XMLNODE_H
