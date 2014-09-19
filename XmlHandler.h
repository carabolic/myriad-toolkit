//
//  MyParser.h
//  myriad-toolkit
//
//  Created by Christoph Bruecke on 15.05.14.
//
//

#ifndef myriad_toolkit_MyParser_h
#define myriad_toolkit_MyParser_h

#include <string>
#include <list>

#include "Poco/SAX/Attributes.h"
#include "Poco/SAX/ContentHandler.h"

namespace Myriad {

class Func {
public:
    Func(std::string name, std::string type) : _name(name), _type(type) {
        
    }
    
    std::string name() {
        return _name;
    }
    
    std::string type() {
        return _type;
    }
    
private:
    std::string _name;
    std::string _type;
};

struct Function {
    std::string name;
    std::string type;
    // TODO insert argument list here
};

struct Parameter {
    std::string key;
    std::string value;
};

struct EnumSet {
    std::string name;
    std::string fileName;
};

class XmlHandler : public Poco::XML::ContentHandler {
public:
    XmlHandler() : _functions(), isFunc(false), isParam(false), isEnumSet(false)
    {}
    
    std::list<Func> functions() {
        return _functions;
    }
    
    std::list<Parameter> parameters() {
        return _parameters;
    }
    
    std::list<EnumSet> enumSets() {
        return _enumSets;
    }
    
    void setDocumentLocator(const Poco::XML::Locator *loc) {}
    
    void startDocument() {}
    
    void endDocument() {}
    
    void startElement(const Poco::XML::XMLString &uri,
                      const Poco::XML::XMLString &localName,
                      const Poco::XML::XMLString &qname,
                      const Poco::XML::Attributes &attrList);
    
    void endElement(const Poco::XML::XMLString &uri,
                    const Poco::XML::XMLString &localName,
                    const Poco::XML::XMLString &qname);
    
    void characters(const Poco::XML::XMLChar *ch, int start, int length);
    
    void ignorableWhitespace(const Poco::XML::XMLChar *ch, int start, int length) {}
    
    void processingInstruction(const Poco::XML::XMLString &target, const Poco::XML::XMLString &data) {}
    
    void startPrefixMapping(const Poco::XML::XMLString &prefix, const Poco::XML::XMLString &uri) {}
    
    void endPrefixMapping(const Poco::XML::XMLString &prefix) {}
    
    void skippedEntity(const Poco::XML::XMLString &name) {}
    
private:
    std::list<Func> _functions;
    std::list<Parameter> _parameters;
    std::list<EnumSet> _enumSets;
    
    // mutable values
    bool isFunc, isParam, isEnumSet;
    Parameter currentParam;
    EnumSet currentEnumSet;
    //    std::vector<std::string> _functions;
}; // class XmlHandler

} // namespace Myriad
#endif
