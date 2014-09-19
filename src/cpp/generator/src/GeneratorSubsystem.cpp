//
//  GeneratorSubsystem.cpp
//  myriad-toolkit
//
//  Created by Christoph Bruecke on 14.05.14.
//
//

#include "myriad/generator/GeneratorSubsystem.h"

using namespace std;
using namespace Poco;

namespace Myriad {
    
    // the initial stage ID should always be zero
    I32u AbstractSequenceGenerator::Stage::NEXT_STAGE_ID = 0;
    
    // register the valid stages for the Myriad generator extension
    AbstractSequenceGenerator::StageList initList()
    {
        AbstractSequenceGenerator::StageList tmp;
        
//        tmp.push_back(AbstractSequenceGenerator::Stage("region"));
//        tmp.push_back(AbstractSequenceGenerator::Stage("nation"));
//        tmp.push_back(AbstractSequenceGenerator::Stage("supplier"));
//        tmp.push_back(AbstractSequenceGenerator::Stage("part"));
//        tmp.push_back(AbstractSequenceGenerator::Stage("partsupp"));
        
        return tmp;
    }
    
    const AbstractSequenceGenerator::StageList AbstractSequenceGenerator::STAGES(initList());
    
    // register the record sequence generators
    void GeneratorSubsystem::registerGenerators()
    {
//        registerGenerator<TpchGen::RegionGenerator>("region");
//        registerGenerator<TpchGen::NationGenerator>("nation");
//        registerGenerator<TpchGen::SupplierGenerator>("supplier");
//        registerGenerator<TpchGen::PartGenerator>("part");
//        registerGenerator<TpchGen::PartsuppGenerator>("partsupp");
    }
    
} // namespace Myriad

