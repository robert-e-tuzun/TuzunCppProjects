//----------------------------------------------------------------------
//
//     Small nc specification builder for partial knot specs.
//
//     Bob Tuzun
//

#pragma once

#include "JonesConjecNonAlg/PartialKnotSpec/SomeSizeNcSpecManager.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

class SmallNcSpecManager : public SomeSizeNcSpecManager
{
   public:
      SmallNcSpecManager(
         std::shared_ptr<I_SmallNcSpecBuilder> smallNcSpecBuilder);
      ~SmallNcSpecManager();

      virtual void prepareForUse(const NcSpecBuildInfo& info);

//     Perform work of computing nc partitions.
      virtual void findNextNcChunk();

//     Retrieve results.
      virtual std::vector<DT::VecInt32> getNcChunk() const;
      virtual DT::Int32 getCyclicPermutationShift() const;
      virtual DT::Int32 getNumNcSpecs() const;
      virtual bool isDone() const;

   private:
      bool done_;

      std::vector<DT::VecInt32> ncChunk_;

      std::shared_ptr<I_SmallNcSpecBuilder> smallNcSpecBuilder_;
};

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

