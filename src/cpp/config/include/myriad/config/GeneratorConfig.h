//
//  GeneratorConfig.h
//  myriad-toolkit
//
//  Created by Christoph Bruecke on 14.05.14.
//
//

#ifndef myriad_toolkit_GeneratorConfig_h
#define myriad_toolkit_GeneratorConfig_h

#include "myriad/config/AbstractGeneratorConfig.h"

namespace Myriad {
    
class GeneratorConfig: public AbstractGeneratorConfig
{
public:
    
    GeneratorConfig(GeneratorPool& generatorPool) : AbstractGeneratorConfig(generatorPool)
    {
    }
    
protected:
    
//    void configurePartitioning()
//    {
        // TODO: this piece of auto-generating code / Config API needs to be rewritten
        
        // setup linear scale estimator for region
//        setString("partitioning.region.base-cardinality", toString<I64u>(parameter<I64u>("region.sequence.base_cardinality")));
//        computeLinearScalePartitioning("region");
//        // setup linear scale estimator for nation
//        setString("partitioning.nation.base-cardinality", toString<I64u>(parameter<I64u>("nation.sequence.base_cardinality")));
//        computeLinearScalePartitioning("nation");
//        // setup linear scale estimator for supplier
//        setString("partitioning.supplier.base-cardinality", toString<I64u>(parameter<I64u>("supplier.sequence.base_cardinality")));
//        computeLinearScalePartitioning("supplier");
//        // setup linear scale estimator for part
//        setString("partitioning.part.base-cardinality", toString<I64u>(parameter<I64u>("part.sequence.base_cardinality")));
//        computeLinearScalePartitioning("part");
//        // setup linear scale estimator for partsupp
//        setString("partitioning.partsupp.base-cardinality", toString<I64u>(parameter<I64u>("partsupp.sequence.base_cardinality")));
//        computeLinearScalePartitioning("partsupp");
//    }
    
    void configureFunctions()
    {
        // register prototype functions
        function(new Myriad::CombinedPrFunction<Enum>("Pr[db2inst2.nation.n_comment]", parameter<String>("ENV.config-dir") + "/distributions/db2inst2/nation/n_comment.distribution"));
//        function(new Myriad::CombinedPrFunction<Enum>("Pr[db2inst2.nation.n_name]", static_cast<String>(parameter<String>("ENV.config-dir") + "/distributions/db2inst2/nation/n_name.distribution")));
//        function(new Myriad::UniformPrFunction<I32>("Pr[db2inst2.nation.n_nationkey]", 1, static_cast<I32>(parameter<I32>("nation.sequence.cardinality") + 1)));
//        function(new Myriad::CombinedPrFunction<Enum>("Pr[db2inst2.part.p_brand]", static_cast<String>(parameter<String>("ENV.config-dir") + "/distributions/db2inst2/part/p_brand.distribution")));
//        function(new Myriad::CombinedPrFunction<Enum>("Pr[db2inst2.part.p_comment]", static_cast<String>(parameter<String>("ENV.config-dir") + "/distributions/db2inst2/part/p_comment.distribution")));
//        function(new Myriad::CombinedPrFunction<Enum>("Pr[db2inst2.part.p_container]", static_cast<String>(parameter<String>("ENV.config-dir") + "/distributions/db2inst2/part/p_container.distribution")));
//        function(new Myriad::CombinedPrFunction<Enum>("Pr[db2inst2.part.p_mfgr]", static_cast<String>(parameter<String>("ENV.config-dir") + "/distributions/db2inst2/part/p_mfgr.distribution")));
//        function(new Myriad::CombinedPrFunction<Enum>("Pr[db2inst2.part.p_name]", static_cast<String>(parameter<String>("ENV.config-dir") + "/distributions/db2inst2/part/p_name.distribution")));
//        function(new Myriad::UniformPrFunction<I32>("Pr[db2inst2.part.p_partkey]", 2, static_cast<I32>(parameter<I32>("part.sequence.cardinality") + 2)));
//        function(new Myriad::CombinedPrFunction<Decimal>("Pr[db2inst2.part.p_retailprice]", static_cast<String>(parameter<String>("ENV.config-dir") + "/distributions/db2inst2/part/p_retailprice.distribution")));
//        function(new Myriad::CombinedPrFunction<I32>("Pr[db2inst2.part.p_size]", static_cast<String>(parameter<String>("ENV.config-dir") + "/distributions/db2inst2/part/p_size.distribution")));
//        function(new Myriad::CombinedPrFunction<Enum>("Pr[db2inst2.part.p_type]", static_cast<String>(parameter<String>("ENV.config-dir") + "/distributions/db2inst2/part/p_type.distribution")));
//        function(new Myriad::CombinedPrFunction<I32>("Pr[db2inst2.partsupp.ps_availqty]", static_cast<String>(parameter<String>("ENV.config-dir") + "/distributions/db2inst2/partsupp/ps_availqty.distribution")));
//        function(new Myriad::CombinedPrFunction<Enum>("Pr[db2inst2.partsupp.ps_comment]", static_cast<String>(parameter<String>("ENV.config-dir") + "/distributions/db2inst2/partsupp/ps_comment.distribution")));
//        function(new Myriad::CombinedPrFunction<Decimal>("Pr[db2inst2.partsupp.ps_supplycost]", static_cast<String>(parameter<String>("ENV.config-dir") + "/distributions/db2inst2/partsupp/ps_supplycost.distribution")));
//        function(new Myriad::CombinedPrFunction<Enum>("Pr[db2inst2.region.r_comment]", static_cast<String>(parameter<String>("ENV.config-dir") + "/distributions/db2inst2/region/r_comment.distribution")));
//        function(new Myriad::CombinedPrFunction<Enum>("Pr[db2inst2.region.r_name]", static_cast<String>(parameter<String>("ENV.config-dir") + "/distributions/db2inst2/region/r_name.distribution")));
//        function(new Myriad::UniformPrFunction<I32>("Pr[db2inst2.region.r_regionkey]", 1, static_cast<I32>(parameter<I32>("region.sequence.cardinality") + 1)));
//        function(new Myriad::CombinedPrFunction<Decimal>("Pr[db2inst2.supplier.s_acctbal]", static_cast<String>(parameter<String>("ENV.config-dir") + "/distributions/db2inst2/supplier/s_acctbal.distribution")));
//        function(new Myriad::CombinedPrFunction<Enum>("Pr[db2inst2.supplier.s_address]", static_cast<String>(parameter<String>("ENV.config-dir") + "/distributions/db2inst2/supplier/s_address.distribution")));
//        function(new Myriad::CombinedPrFunction<Enum>("Pr[db2inst2.supplier.s_comment]", static_cast<String>(parameter<String>("ENV.config-dir") + "/distributions/db2inst2/supplier/s_comment.distribution")));
//        function(new Myriad::CombinedPrFunction<Enum>("Pr[db2inst2.supplier.s_name]", static_cast<String>(parameter<String>("ENV.config-dir") + "/distributions/db2inst2/supplier/s_name.distribution")));
//        function(new Myriad::CombinedPrFunction<Enum>("Pr[db2inst2.supplier.s_phone]", static_cast<String>(parameter<String>("ENV.config-dir") + "/distributions/db2inst2/supplier/s_phone.distribution")));
//        function(new Myriad::UniformPrFunction<I32>("Pr[db2inst2.supplier.s_suppkey]", 2, static_cast<I32>(parameter<I32>("supplier.sequence.cardinality") + 2)));
    }
    
    void configureSets()
    {
        // bind string sets to config members with the bindStringSet method
//        enumSet(new MyriadEnumSet("db2inst2.part.p_type", static_cast<String>(parameter<String>("ENV.config-dir") + "/domains/db2inst2/part/p_type.domain")));
//        enumSet(new MyriadEnumSet("db2inst2.nation.n_comment", static_cast<String>(parameter<String>("ENV.config-dir") + "/domains/db2inst2/nation/n_comment.domain")));
//        enumSet(new MyriadEnumSet("db2inst2.supplier.s_name", static_cast<String>(parameter<String>("ENV.config-dir") + "/domains/db2inst2/supplier/s_name.domain")));
//        enumSet(new MyriadEnumSet("db2inst2.part.p_mfgr", static_cast<String>(parameter<String>("ENV.config-dir") + "/domains/db2inst2/part/p_mfgr.domain")));
//        enumSet(new MyriadEnumSet("db2inst2.part.p_name", static_cast<String>(parameter<String>("ENV.config-dir") + "/domains/db2inst2/part/p_name.domain")));
//        enumSet(new MyriadEnumSet("db2inst2.region.r_name", static_cast<String>(parameter<String>("ENV.config-dir") + "/domains/db2inst2/region/r_name.domain")));
//        enumSet(new MyriadEnumSet("db2inst2.part.p_comment", static_cast<String>(parameter<String>("ENV.config-dir") + "/domains/db2inst2/part/p_comment.domain")));
//        enumSet(new MyriadEnumSet("db2inst2.supplier.s_address", static_cast<String>(parameter<String>("ENV.config-dir") + "/domains/db2inst2/supplier/s_address.domain")));
//        enumSet(new MyriadEnumSet("db2inst2.part.p_container", static_cast<String>(parameter<String>("ENV.config-dir") + "/domains/db2inst2/part/p_container.domain")));
//        enumSet(new MyriadEnumSet("db2inst2.supplier.s_phone", static_cast<String>(parameter<String>("ENV.config-dir") + "/domains/db2inst2/supplier/s_phone.domain")));
//        enumSet(new MyriadEnumSet("db2inst2.nation.n_name", static_cast<String>(parameter<String>("ENV.config-dir") + "/domains/db2inst2/nation/n_name.domain")));
//        enumSet(new MyriadEnumSet("db2inst2.partsupp.ps_comment", static_cast<String>(parameter<String>("ENV.config-dir") + "/domains/db2inst2/partsupp/ps_comment.domain")));
//        enumSet(new MyriadEnumSet("db2inst2.supplier.s_comment", static_cast<String>(parameter<String>("ENV.config-dir") + "/domains/db2inst2/supplier/s_comment.domain")));
//        enumSet(new MyriadEnumSet("db2inst2.part.p_brand", static_cast<String>(parameter<String>("ENV.config-dir") + "/domains/db2inst2/part/p_brand.domain")));
//        enumSet(new MyriadEnumSet("db2inst2.region.r_comment", static_cast<String>(parameter<String>("ENV.config-dir") + "/domains/db2inst2/region/r_comment.domain")));
    }
};

} // namespace Myriad

#endif