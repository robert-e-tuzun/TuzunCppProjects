//----------------------------------------------------------------------
//
//     Wrapper for nc spec builder for partial knot specs.
//
//     Bob Tuzun
//

#pragma once

#include "TuzunUtil/I_Blackboard.h"
#include "JonesConjecNonAlg/PartialKnotSpec/I_NcSpecBuilderWrapper.h"
#include "JonesConjecNonAlg/PartialKnotSpec/I_NcSpecBuilder.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

class NcSpecBuilderWrapper : public I_NcSpecBuilderWrapper
{
   public:
      NcSpecBuilderWrapper(
            std::shared_ptr<I_NcSpecBuilder> ncSpecBuilder);
      ~NcSpecBuilderWrapper();

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
      std::shared_ptr<I_NcSpecBuilder> ncSpecBuilder_;

      DT::Int32 largestSmallNc_;
      DT::Int32 largestNcInMemory_;
      DT::Int32 ncMaxAttainable_;
      DT::Int32 numCrossings_;
      DT::Int32 numVertices_;
};

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

