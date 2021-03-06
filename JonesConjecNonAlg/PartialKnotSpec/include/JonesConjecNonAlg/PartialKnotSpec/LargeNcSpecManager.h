//----------------------------------------------------------------------
//
//     Large nc specification builder for partial knot specs.
//
//     Bob Tuzun
//

#pragma once

#include "JonesConjecNonAlg/PartialKnotSpec/I_LargeNcSpecBuilder.h"
#include "JonesConjecNonAlg/PartialKnotSpec/SomeSizeNcSpecManager.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

class LargeNcSpecManager : public SomeSizeNcSpecManager
{
   public:
      LargeNcSpecManager(
         std::shared_ptr<I_LargeNcSpecBuilder> largeNcSpecBuilder);
      ~LargeNcSpecManager();

      virtual void prepareForUse(const NcSpecBuildInfo& info);

//     Perform work of computing nc partitions.
      virtual void findNextNcChunk();

//     Retrieve results.
      virtual std::vector<DT::VecInt32> getNcChunk() const;
      virtual DT::Int32 getCyclicPermutationShift() const;
      virtual DT::Int32 getNumNcSpecs() const;
      virtual bool isDone() const;

   private:
      DT::Int32 cyclicPermutationShift_;
      DT::Int32 numNcSpecs_;

      bool done_;

      std::vector<DT::VecInt32> ncChunk_;

      std::shared_ptr<I_LargeNcSpecBuilder> largeNcSpecBuilder_;
};

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

