
#include "generator/AbstractGeneratorSubsystem.h"

namespace Myriad {
    class GeneratorSubsystem : public AbstractGeneratorSubsystem {

    public:
        GeneratorSubsystem(NotificationCenter& notificationCenter, const vector<bool>& executeStages) :
                AbstractGeneratorSubsystem(notificationCenter, executeStages)
        {

        }

        virtual ~GeneratorSubsystem()
        {
        }

    protected:

        virtual void registerGenerators();
    };
} // namespace