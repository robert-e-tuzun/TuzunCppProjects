//----------------------------------------------------------------------
//
//     Small nc specification builder for partial knot specs (interface
//     class).
//
//     Bob Tuzun
//

#pragma once

#include "JonesConjecNonAlg/PartialKnotSpec/NcSpecItems.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

class I_SmallNcSpecBuilder
{
   public:
      virtual ~I_SmallNcSpecBuilder() {};

      virtual void prepareForUse(const NcSpecBuildInfo& info) = 0;

//     Perform work of computing nc partitions.
      virtual void findNextNcChunk() = 0;

//     Retrieve results.
      virtual std::vector<DT::VecInt32> getNcChunk() const = 0;
      virtual bool isDone() const = 0;
};

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

