//----------------------------------------------------------------------
//
//     Ct spec filter for partial knot specs.
//
//     Bob Tuzun
//

#pragma once

#include "JonesConjecNonAlg/Polyh/I_PolyhManager.h"
#include "JonesConjecNonAlg/PartialKnotSpec/I_CtSpecFilter.h"

namespace DT = Tuzun_Util::Datatypes;
namespace JP = Jones_Conjec_NonAlg::Polyh;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

class CtSpecFilter : public I_CtSpecFilter
{
   public:
      CtSpecFilter(std::shared_ptr<JP::I_PolyhManager> polyhManager);
      ~CtSpecFilter();

      virtual void prepareForUse(DT::Int32 maxAllowedNumNcEq1);
      virtual void filterCtSpecs(std::vector<DT::VecInt32>& ctSpecs);

   private:
      DT::Int32 maxAllowedNumNcEq1_;

      std::shared_ptr<JP::I_PolyhManager> polyhManager_;
};

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

