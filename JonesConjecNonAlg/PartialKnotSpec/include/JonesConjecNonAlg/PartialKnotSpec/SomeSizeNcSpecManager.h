//----------------------------------------------------------------------
//
//     Base class for small, medium, and large nc specification managers
//     for partial knot specs (interface class).
//
//     Bob Tuzun
//

#pragma once

#include "JonesConjecNonAlg/PartialKnotSpec/NcSpecItems.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

class SomeSizeNcSpecManager
{
   public:
      virtual ~SomeSizeNcSpecManager() {};

      virtual void prepareForUse(const NcSpecBuildInfo& info) = 0;

//     Perform work of computing nc partitions.
      virtual void findNextNcChunk() = 0;

//     Retrieve results.
      virtual std::vector<DT::VecInt32> getNcChunk() const = 0;
      virtual DT::Int32 getCyclicPermutationShift() const = 0;
      virtual DT::Int32 getNumNcSpecs() const = 0;
      virtual bool isDone() const = 0;

   private:
};

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

