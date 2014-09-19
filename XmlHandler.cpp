//
//  MyParser.cpp
//  myriad-toolkit
//
//  Created by Christoph Bruecke on 15.05.14.
//
//

#include "XmlHandler.h"

#include <string>
#include <list>

#include "Poco/SAX/Attributes.h"
    using Poco::XML::Attributes;

using Poco::XML::XMLString;
using Poco::XML::XMLChar;

namespace Myriad {
    
    void XmlHandler::startElement(const XMLString &uri,
                                  const XMLString &localName,
                                  const XMLString &qname,
                                  const Attributes &attrList) {
        if (localName == "function") {
            std::string name = attrList.getValue("", "key");
            std::string type = attrList.getValue("", "type");
            _functions.push_back(Func(name, type));
        } else if (localName == "parameter") {
            isParam = true;
            std::string key = attrList.getValue("", "key");
            currentParam.key = key;
        } else if (localName == "enum_set") {
            std::string key = attrList.getValue("", "key");
            currentEnumSet.name = key;
            isEnumSet = true;
        } else if (localName == "record_sequence") {
            
        } else if (localName == "argument") {
            if (isEnumSet) {
                std::string path = attrList.getValue("", "value");
                currentEnumSet.fileName = path;
                _enumSets.push_back(currentEnumSet);
            }
        }
    }
    
    void XmlHandler::endElement(const XMLString &uri, const XMLString &localName, const XMLString &qname) {
        if (localName == "function") {
            isFunc = false;
        } else if (localName == "parameter") {
            _parameters.push_back(currentParam);
            currentParam.key = "";
            currentParam.value = "";
            isParam = false;
        } else if (localName == "enum_set") {
            isEnumSet = false;
        }
    }
    
    void XmlHandler::characters(const XMLChar *ch, int start, int length) {
        if (isFunc) {
            
        } else if (isParam) {
            currentParam.value.assign(ch, start, length);
        } else if (isEnumSet) {
            
        }
    }

} // namespace Myriad
