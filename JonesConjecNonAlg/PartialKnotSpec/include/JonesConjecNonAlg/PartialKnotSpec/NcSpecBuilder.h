//----------------------------------------------------------------------
//
//     Nc specification builder for partial knot specs.
//
//     Bob Tuzun
//

#pragma once

#include "JonesConjecNonAlg/PartialKnotSpec/I_SmallNcSpecBuilder.h"
#include "JonesConjecNonAlg/PartialKnotSpec/I_MediumNcSpecBuilder.h"
#include "JonesConjecNonAlg/PartialKnotSpec/I_LargeNcSpecBuilder.h"
#include "JonesConjecNonAlg/PartialKnotSpec/I_NcSpecBuilder.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

class NcSpecBuilder : public I_NcSpecBuilder
{
   public:
      NcSpecBuilder(std::shared_ptr<I_SmallNcSpecBuilder> smallNcSpecBuilder,
                    std::shared_ptr<I_MediumNcSpecBuilder> mediumNcSpecBuilder,
                    std::shared_ptr<I_LargeNcSpecBuilder> largeNcSpecBuilder);
      ~NcSpecBuilder();

//     Perform work of computing nc partitions.
      virtual void prepareForUse(DT::Int32 numCrossings,
             DT::Int32 numVertices, DT::Int32 largestSmallNc,
             DT::Int32 largestNcInMemory, DT::Int32 ncMaxAttainable,
             DT::Int32 numNcPartitionsStoredMax, bool isDnSymmetric);
      virtual void computeNextSetOfNcPartitions();

//     Retrieve results.
      virtual DT::Int32 getCyclicPermutationShift();
      virtual std::vector<DT::VecInt32> getNcSpecs();
      virtual bool haveComputedNewNcSpecs();
      virtual bool isDoneComputingNewNcSpecs();

   private:
      DT::Int32 cyclicPermutationShift_;
      DT::Int32 largestNcInMemory_;
      DT::Int32 largestSmallNc_;
      DT::Int32 ncMaxAttainable_;
      DT::Int32 numCrossings_;
      DT::Int32 numNcPartitionsStoredMax_;
      DT::Int32 numVertices_;

      bool doneComputingNewNcSpecs_;
      bool haveComputedNewNcSpecs_;
      bool isDnSymmetric_;

      DT::String stage_;

      std::vector<DT::VecInt32> ncPartitions_;

      std::shared_ptr<I_SmallNcSpecBuilder> smallNcSpecBuilder_;
      std::shared_ptr<I_MediumNcSpecBuilder> mediumNcSpecBuilder_;
      std::shared_ptr<I_LargeNcSpecBuilder> largeNcSpecBuilder_;
};

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

