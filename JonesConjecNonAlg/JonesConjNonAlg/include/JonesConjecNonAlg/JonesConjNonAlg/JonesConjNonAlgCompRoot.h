//--------------------------------------------------------------------
//
//     Composition root object for Jones conjecture application.
//
//     Bob Tuzun
//

#pragma once

#include <memory>

#include "JonesConjecNonAlg/JonesConjNonAlg/InitializerNonAlg.h"

#include "KnotCommon/InputOutput/PolyhedronReader.h"
#include "KnotCommon/KnotGraph/ConwayLikeGraphFactory.h"
#include "JonesConjecNonAlg/Polyh/PolyhManager.h"

#include "JonesConjecNonAlg/PartialKnotSpec/PartialKnotSpecManager.h"
#include "JonesConjecNonAlg/JonesConjNonAlg/JonesConjNonAlgApp.h"

namespace Jones_Conjec_NonAlg::Jones_Conj_NonAlg {

class JonesConjNonAlgCompRoot
{
   public:
      JonesConjNonAlgCompRoot();
      ~JonesConjNonAlgCompRoot();

      std::shared_ptr<I_JonesConjNonAlgApp> getCompositionRoot();

   private:
      std::shared_ptr<I_JonesConjNonAlgApp> app_;
};

} // namespace Jones_Conjec_NonAlg::Jones_Conj_NonAlg

