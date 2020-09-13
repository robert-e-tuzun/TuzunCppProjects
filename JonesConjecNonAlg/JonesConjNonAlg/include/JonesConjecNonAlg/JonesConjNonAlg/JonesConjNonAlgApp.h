//--------------------------------------------------------------------
//
//     Application object for performing Jones conjecture calculations
//     (declaration).
//
//     Bob Tuzun
//

#pragma once

#include <vector>
#include <string>
#include <map>
#include <memory>
#include <any>

#include "TuzunUtil/Blackboard.h"
#include "JonesConjecNonAlg/JonesConjNonAlg/I_InitializerNonAlg.h"
#include "JonesConjecNonAlg/JonesConjNonAlg/I_JonesConjNonAlgApp.h"
#include "JonesConjecNonAlg/PartialKnotSpec/I_PartialKnotSpecManager.h"

namespace JCPa = Jones_Conjec_NonAlg::Partial_Knot_Spec;

namespace Jones_Conjec_NonAlg {

namespace Jones_Conj_NonAlg {

class JonesConjNonAlgApp : public I_JonesConjNonAlgApp
{
   public:
      JonesConjNonAlgApp(std::shared_ptr<I_InitializerNonAlg> initializerPtr,
            std::shared_ptr<JCPa::I_PartialKnotSpecManager> pksManagerPtr);
      virtual ~JonesConjNonAlgApp();

      virtual void setupApplication();
      virtual void runApplication();

   private:

      Tuzun_Util::BlackboardPtr blkbdPtr_;
      std::shared_ptr<I_InitializerNonAlg> initializerPtr_;
      std::shared_ptr<JCPa::I_PartialKnotSpecManager> pksManagerPtr_;
};

} // namespace Jones_Conj_NonAlg

} // namespace Jones_Conjec_NonAlg

