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
namespace JCPo = Jones_Conjec_NonAlg::Polyh;
namespace KCIO = Knot_Common::Input_Output;
namespace KCCG = Knot_Common::Conway_Graph;

namespace Jones_Conjec_NonAlg::Jones_Conj_NonAlg {

//--------------------------------------------------------------------

JonesConjNonAlgCompRoot::JonesConjNonAlgCompRoot()
{
   std::shared_ptr<Tuzun_Util::I_Blackboard> blackboardPtr =
           std::make_shared<Tuzun_Util::Blackboard>();
   std::shared_ptr<I_InitializerNonAlg> initializerPtr =
           std::make_shared<InitializerNonAlg>(blackboardPtr);

   std::shared_ptr<KCIO::I_PolyhedronReader> polyhedronReaderPtr =
           std::make_shared<KCIO::PolyhedronReader>();
   std::shared_ptr<KCCG::I_ConwayLikeGraphFactory> graphFactoryPtr =
           std::make_shared<KCCG::ConwayLikeGraphFactory>();
   std::shared_ptr<JCPo::I_PolyhManager> polyhManagerPtr =
           std::make_shared<JCPo::PolyhManager>(
                 polyhedronReaderPtr, graphFactoryPtr);

   std::shared_ptr<JCPa::I_PartialKnotSpecManager> pksManagerPtr =
           std::make_shared<JCPa::PartialKnotSpecManager>(polyhManagerPtr);

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

