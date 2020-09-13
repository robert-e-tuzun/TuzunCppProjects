//----------------------------------------------------------------------
//
//     Partial knot specification manager (interface).
//
//     Bob Tuzun
//

#pragma once

#include "TuzunUtil/I_Blackboard.h"

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

class I_PartialKnotSpecManager
{
   public:
      virtual ~I_PartialKnotSpecManager() {};

      virtual void prepareForUse(
           std::shared_ptr<Tuzun_Util::I_Blackboard> blkbdPtr) = 0;
      virtual void buildNcPartitions() = 0;
      virtual void loopThroughPolyhedra() = 0;

   private:
};

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

