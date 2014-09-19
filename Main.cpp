//
//  Main.cpp
//  myriad-toolkit
//
//  Created by Christoph Bruecke on 14.05.14.
//
//

#include "myriad/core/types.h"
#include "myriad/core/constants.h"
#include "myriad/math/probability/UniformPrFunction.h"
#include "XmlHandler.h"

// testHashRandomStream
#include "myriad/math/random/HashRandomStream.h"

#include "Poco/SAX/SAXParser.h"
    using Poco::XML::SAXParser;
//#include "myriad/core/Frontend.h"

#include <iostream>
#include <list>
    using std::list;

//namespace Myriad {

using namespace Myriad;

/**
 * Application name.
 */
const String Constant::APP_NAME = "tpch-gen - Parallel Data Generator";

/**
 * Application version.
 */
const String Constant::APP_VERSION = "0.1.0";

void testUniformPrFunc() {
    I16u max = 0xFFFF;
    UniformPrFunction<I16u> myUniformPrFunc("test", 0, max);
    std::vector<I16u> values(max);
    I16u pad = 0x0110;
    for (int i = 0; i < max; i++) {
        I16u sample = myUniformPrFunc.sample(i / (Decimal) max);
        values[i ^ pad] = sample;
    }
    
    std::cout << "values:" << std::endl;
    for (int i = 0; i < max; i++) {
        std::cout << values[i] << std::endl;
    }
    
    std::sort(values.begin(), values.end());
    std::unique(values.begin(), values.end());
    bool isUnique = values.size() == max;
    if (isUnique) {
        std::cout << "sequence is unique" << std::endl;
    } else {
        std::cout << "sequence is not unique" << std::endl;
    }
}

void testHashRandomStream() {
    HashRandomStream hrs("MyStream");
    hrs.dumpState();
    for (int i = 0; i < 10; i++) {
        double v = hrs.next();
        std::cout << v << std::endl;
    }
}

int main(int argc, char** argv) {
    // naive parser implementation
//    if (argc >= 2) {
//        string inputPath = argv[1];
//        std::cout << "Reading from: " << inputPath << std::endl;
//        XmlHandler handler;
//        
//        SAXParser parser;
//        parser.setContentHandler(&handler);
//        
//        parser.parse(inputPath);
//        
//        list<Func> funcs = handler.functions();
//        list<Func>::iterator fIter;
//        for (fIter = funcs.begin(); fIter != funcs.end(); fIter++) {
//            Func f = *fIter;
//            std::cout << "function:\n\t" << f.name() << " " << f.type() << std::endl;
//        }
//        
//        list<Parameter> params = handler.parameters();
//        list<Parameter>::iterator pIter;
//        for (pIter = params.begin(); pIter != params.end(); pIter++) {
//            Parameter p = *pIter;
//            std::cout << "parameter:\n\t" << p.key << " " << p.value << std::endl;
//        }
//        
//        list<EnumSet> enums = handler.enumSets();
//        list<EnumSet>::iterator eIter;
//        for (eIter = enums.begin(); eIter != enums.end(); eIter++) {
//            EnumSet e = *eIter;
//            std::cout << "enum_set:\n\t" << e.name << " " << e.fileName << std::endl;
//        }
//    }
    
//    testUniformPrFunc();
    testHashRandomStream();
    

    // actual implementation
    // parse the xml
    //  create parameter map
    //  create function map
    //  create enum_set map
    // create generator plan
    //  create schema
    //  PRNG >> rand_val >> s = sample(dist_func, rand_val) >> map(s => domain_val) => write(domain_val) >> end
}

void prototype() {
    // seed the master PRNG
}

void generator(double scalingFactor, ID noteId, ID numberOfNodes) {
    
}

//} // Myriad namespace

// define the application main method
//POCO_APP_MAIN(Myriad::Frontend)
