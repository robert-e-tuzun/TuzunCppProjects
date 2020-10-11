//--------------------------------------------------------------------
//
//     Composition root object for Jones conjecture application
//     (declaration).
//
//     Bob Tuzun
//

#pragma once

#include <memory>

#include "JonesConjecNonAlg/JonesConjNonAlg/InitializerNonAlg.h"

#include "JonesConjecNonAlg/PolyhPrec/PolyhPrecManager.h"

#include "JonesConjecNonAlg/PartialKnotSpec/RepresentativeChecker.h"
#include "JonesConjecNonAlg/PartialKnotSpec/PartitionBuilder.h"
#include "JonesConjecNonAlg/PartialKnotSpec/CandidateCtSpecBuilder.h"
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

