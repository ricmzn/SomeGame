#include "Node.h"
#include <pugixml.hpp>

/////////////////////////
// Private definitions //
/////////////////////////
namespace Base {
namespace XML {
namespace Private {
struct Node
{
    bool isAttr;
    pugi::xml_node node;
    pugi::xml_attribute attr;

    Node(const pugi::xml_node& node);
    Node(const pugi::xml_attribute& attr);
    explicit operator bool();
};

Node::Node(const pugi::xml_node& node)
    : isAttr(false), node(node), attr() {}

Node::Node(const pugi::xml_attribute& attr)
    : isAttr(true), node(), attr(attr) {}

Node::operator bool()
{
    if(isAttr) {
        return !attr.empty();
    } else {
        return !node.empty();
    }
}

}}}

///////////////
// XML::Node //
///////////////
using namespace Base::XML;

Node::Node(Private::Node* node)
{
    priv = node;
}

Node::~Node()
{
    delete priv;
}

bool Node::asBoolean(bool def) const
{
    if(priv->isAttr) {
        return priv->attr.as_bool(def);
    } else {
        return priv->node.text().as_bool(def);
    }
}

int Node::asInteger(int def) const
{
    if(priv->isAttr) {
        return priv->attr.as_int(def);
    } else {
        return priv->node.text().as_int(def);
    }
}

float Node::asFloat(float def) const
{
    if(priv->isAttr) {
        return priv->attr.as_float(def);
    } else {
        return priv->node.text().as_float(def);
    }
}

String Node::asString(StringRef def) const
{
    if(priv->isAttr) {
        return priv->attr.as_string(def.c_str());
    } else {
        return priv->node.text().as_string(def.c_str());
    }
}
