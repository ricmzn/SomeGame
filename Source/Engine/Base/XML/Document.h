#ifndef XMLDOCUMENT_H
#define XMLDOCUMENT_H
#include <Engine/Filesystem/File.h>
#include <Engine/Base/XML/Node.h>

struct XMLObject;

namespace Base {
namespace XML {

namespace Private {
struct Document;
}

class api_public Document
{
    private:
        Private::Document* priv;
    public:
        /**
         * @brief XMLFile
         * @param file
         * @throws XMLParseException
         */
        Document(const File& file);

        /**
         * @brief ~XMLFile
         */
        ~Document();

        /**
         * @brief getNode
         * @param path
         * @return
         */
        Node getNode(StringRef path) const;
};
}}

#endif // XMLDOCUMENT_H
