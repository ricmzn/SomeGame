#include "Document.h"
#include <Engine/Base/Exceptions.h>
#include <pugixml.hpp>
#include <sstream>

/////////////////////////
// Private definitions //
/////////////////////////
namespace Base {
namespace XML {
namespace Private {
struct Document
{
    String name;
    pugi::xml_document xml;

    Document(const File& file);

    explicit operator bool() const;
};
struct Node
{
    bool isAttr;
    pugi::xml_node node;
    pugi::xml_attribute attr;

    Node(const pugi::xml_node& node);
    Node(const pugi::xml_attribute& attr);
    explicit operator bool();
};

Document::Document(const Filesystem::File& file)
{
    name = file.filename();
    auto result = xml.load_buffer(file.data(), file.size());
    if(!result) {
//        throw XMLParseException(name, result.description());
        throw GenericError("Failed to parse document");
    }
}

Document::operator bool() const
{
    return !xml.empty();
}

}}}

///////////////////
// XML::Document //
///////////////////
using namespace Base::XML;

Document::Document(const File& file)
{
    priv = new Private::Document(file);
}

Document::~Document()
{
    delete priv;
}

Node Document::getNode(StringRef path) const
{
    using namespace std;

    stringstream stream(path);
    String pathComponent;
    String attrName;
    pugi::xml_node node = priv->xml.root();

    // Separate the path from the attribute, if one exists
    {
        auto invalid = stream.str().npos;
        auto attrPos = stream.str().find(":");
        if(attrPos != invalid) {
            // Special case: do not allow any other separators after a colon
            if(stream.str().find(":/", attrPos) != invalid) {
//                throw XMLParseException(priv->name, "Found a separator after \':\'!");
                throw;
            } else {
                attrName = stream.str().substr(attrPos+1);
                stream.str(stream.str().substr(0, attrPos));
            }
        }
    }

    // Separate children with the slash character
    while(getline(stream, pathComponent, '/')) {
        // Skip empty nodes
        if(pathComponent.empty()) {
            continue;
        }

        // Get the requested child
        node = node.child(pathComponent.c_str());

        // If the node doesn't exist, report the error
        if(!node) {
//            throw XMLNodeException(pathComponent, path);
            throw;
        }
    }

    Private::Node* wrapper;
    if(attrName.empty()) {
        wrapper = new Private::Node(node);
    } else {
        wrapper = new Private::Node(node.attribute(attrName.c_str()));
    }
    return XML::Node(wrapper);
}
