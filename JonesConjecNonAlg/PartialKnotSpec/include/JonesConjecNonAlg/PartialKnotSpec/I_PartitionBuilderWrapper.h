//----------------------------------------------------------------------
//
//     Wrapper for partition builder for partial knot specs (interface class).
//
//     Bob Tuzun
//

#pragma once

#include "TuzunUtil/I_Blackboard.h"
#include "JonesConjecNonAlg/PartialKnotSpec/I_PartitionBuilder.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

class I_PartitionBuilderWrapper
{
   public:
      virtual ~I_PartitionBuilderWrapper() {};

      virtual void prepareForUse(
            std::shared_ptr<Tuzun_Util::I_Blackboard> blkbdPtr) = 0;

//     Retrieve results.
      virtual std::vector<DT::VecInt32> getLowPartitions() const = 0;
      virtual std::vector<DT::VecInt32> getInBetweenPartitions() const = 0;
      virtual std::vector<std::vector<DT::VecInt32> >
                  getHighPartitions() const = 0;
      virtual DT::VecInt32 getInBetweenPartitionPeriods() const = 0;
      virtual std::vector<DT::VecInt32> getHighPartitionPeriods() const = 0;

   private:
};

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

