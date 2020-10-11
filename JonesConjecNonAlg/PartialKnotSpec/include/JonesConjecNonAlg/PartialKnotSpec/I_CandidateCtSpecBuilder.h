//----------------------------------------------------------------------
//
//     Candidate ct spec builder for partial knot specs (interface class).
//
//     Bob Tuzun
//

#pragma once

#include "TuzunUtil/CppDatatypes.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

class I_CandidateCtSpecBuilder
{
   public:
      virtual ~I_CandidateCtSpecBuilder() {};

      virtual void computeCandidateCtSpecs(
            const std::vector<DT::VecInt32>& partitions) = 0;
      virtual std::vector<DT::VecInt32> getCandidateCtSpecs() const = 0;

   private:
};

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

