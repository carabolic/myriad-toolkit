
#include "config/AbstractGeneratorConfig.h"

namespace Myriad {

    class GeneratorConfig : public AbstractGeneratorConfig {

    public:
        GeneratorConfig(GeneratorPool& generatorPool) :
                AbstractGeneratorConfig(generatorPool)
        {

        }
    };

} // namespace