//----------------------------------------------------------------------
//
//     Wrapper for partition builder for partial knot specs.
//
//     Bob Tuzun
//

#pragma once

#include "TuzunUtil/I_Blackboard.h"
#include "JonesConjecNonAlg/PartialKnotSpec/I_PartitionBuilderWrapper.h"
#include "JonesConjecNonAlg/PartialKnotSpec/I_PartitionBuilder.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

class PartitionBuilderWrapper : public I_PartitionBuilderWrapper
{
   public:
      PartitionBuilderWrapper(
            std::shared_ptr<I_PartitionBuilder> partitionBuilder);
      ~PartitionBuilderWrapper();

      virtual void prepareForUse(
            std::shared_ptr<Tuzun_Util::I_Blackboard> blkbdPtr);

//     Retrieve results.
      virtual std::vector<DT::VecInt32> getLowPartitions() const;
      virtual std::vector<DT::VecInt32> getInBetweenPartitions() const;
      virtual std::vector<std::vector<DT::VecInt32> > getHighPartitions() const;
      virtual DT::VecInt32 getInBetweenPartitionPeriods() const;
      virtual std::vector<DT::VecInt32> getHighPartitionPeriods() const;

   private:
      void initRunParams();

      std::shared_ptr<Tuzun_Util::I_Blackboard> blkbdPtr_;
      std::shared_ptr<I_PartitionBuilder> partitionBuilder_;

      DT::Int32 largestSmallNc_;
      DT::Int32 largestNcInMemory_;
      DT::Int32 ncMaxAttainable_;
      DT::Int32 numCrossings_;
      DT::Int32 numVertices_;
};

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

