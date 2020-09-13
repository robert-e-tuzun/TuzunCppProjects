//----------------------------------------------------------------------
//
//     Checker for whether a partition is the representative for its
//     set of cyclic permutations.
//
//     Bob Tuzun
//

#pragma once

#include "JonesConjecNonAlg/PartialKnotSpec/I_RepresentativeChecker.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

class RepresentativeChecker : public I_RepresentativeChecker
{
   public:
      RepresentativeChecker();
      ~RepresentativeChecker();

      virtual bool isRepresentative(const DT::VecInt32& v);

   private:
};

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

