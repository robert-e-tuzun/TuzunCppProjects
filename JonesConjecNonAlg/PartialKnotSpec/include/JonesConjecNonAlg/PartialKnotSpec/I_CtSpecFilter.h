//----------------------------------------------------------------------
//
//     Ct spec filter for partial knot specs (interface class).
//
//     Bob Tuzun
//

#pragma once

#include "TuzunUtil/CppDatatypes.h"

namespace DT = Tuzun_Util::Datatypes;
namespace JP = Jones_Conjec_NonAlg::Polyh;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

class I_CtSpecFilter
{
   public:
      virtual ~I_CtSpecFilter() {};

      virtual void prepareForUse(DT::Int32 maxAllowedNumNcEq1) = 0;
      virtual void filterCtSpecs(std::vector<DT::VecInt32>& ctSpecs) = 0;
};

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

