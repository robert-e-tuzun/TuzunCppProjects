//----------------------------------------------------------------------
//
//     Checker for whether a partition is the representative for its
//     set of cyclic permutations (interface).
//
//     Bob Tuzun
//

#pragma once

#include "TuzunUtil/CppDatatypes.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

class I_RepresentativeChecker
{
   public:
      virtual ~I_RepresentativeChecker() {};

      virtual bool isRepresentative(const DT::VecInt32& v) = 0;

   private:
};

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

