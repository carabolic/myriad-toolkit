//
//  GeneratorSubsystem.h
//  myriad-toolkit
//
//  Created by Christoph Bruecke on 14.05.14.
//
//

#ifndef myriad_toolkit_GeneratorSubsystem_h
#define myriad_toolkit_GeneratorSubsystem_h

#include "myriad/generator/AbstractGeneratorSubsystem.h"

namespace Myriad {
    
    class GeneratorSubsystem: public AbstractGeneratorSubsystem
    {
    public:
        
        GeneratorSubsystem(NotificationCenter& notificationCenter, const vector<bool>& executeStages) :
        AbstractGeneratorSubsystem(notificationCenter, executeStages)
        {
        }
        
        ~GeneratorSubsystem()
        {
        }
        
    protected:
        
        void registerGenerators();
    };
    
} // namespace Myriad

#endif
