//---------------------------------------------------------------------
//
//     Composition root object for Jones conjecture application
//     (implementation).
//
//     Bob Tuzun
//

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>

#include "JonesConjecNonAlg/JonesConjNonAlg/JonesConjNonAlgCompRoot.h"

namespace JCPa = Jones_Conjec_NonAlg::Partial_Knot_Spec;
namespace JCPo = Jones_Conjec_NonAlg::Polyh_Prec;

namespace Jones_Conjec_NonAlg::Jones_Conj_NonAlg {

//--------------------------------------------------------------------

JonesConjNonAlgCompRoot::JonesConjNonAlgCompRoot()
{
   std::shared_ptr<Tuzun_Util::I_Blackboard> blackboardPtr =
           std::make_shared<Tuzun_Util::Blackboard>();
   std::shared_ptr<I_InitializerNonAlg> initializerPtr =
           std::make_shared<InitializerNonAlg>(blackboardPtr);

   std::shared_ptr<JCPo::I_PolyhPrecManager> polyhPrecManagerPtr =
           std::make_shared<JCPo::PolyhPrecManager>();

   std::shared_ptr<JCPa::I_RepresentativeChecker> representativeCheckerPtr =
           std::make_shared<JCPa::RepresentativeChecker>();
   std::shared_ptr<JCPa::I_PartitionBuilder> partitionBuilderPtr =
           std::make_shared<JCPa::PartitionBuilder>(representativeCheckerPtr);
   std::shared_ptr<JCPa::I_PartialKnotSpecManager> pksManagerPtr =
           std::make_shared<JCPa::PartialKnotSpecManager>(
                partitionBuilderPtr, polyhPrecManagerPtr);

   app_ = std::make_shared<JonesConjNonAlgApp>(initializerPtr, pksManagerPtr);
}

//--------------------------------------------------------------------

JonesConjNonAlgCompRoot::~JonesConjNonAlgCompRoot()
{
}

//--------------------------------------------------------------------

std::shared_ptr<I_JonesConjNonAlgApp>
JonesConjNonAlgCompRoot::getCompositionRoot()
{
   return app_;
}

//--------------------------------------------------------------------

} // namespace Jones_Conjec_NonAlg::Jones_Conj_NonAlg

