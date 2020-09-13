//--------------------------------------------------------------------
//
//     Initializer for JonesConjNonAlg.  Read in parameters, set up blackboard,
//     and initialize data to be used in later computations (interface).
//
//     Bob Tuzun
//

#pragma once

#include <map>
#include <any>

#include "TuzunUtil/Blackboard.h"

namespace Jones_Conjec_NonAlg::Jones_Conj_NonAlg {

class I_InitializerNonAlg
{
   public:
      virtual ~I_InitializerNonAlg() {};

      virtual void addObjectsToBlackboard() = 0;
      virtual void processInput() = 0;
      virtual void initializeObjectsInBlackboard() = 0;
      virtual Tuzun_Util::BlackboardPtr getBlackboard() = 0;

   private:
};

} // namespace Jones_Conjec_NonAlg::Jones_Conj_NonAlg

