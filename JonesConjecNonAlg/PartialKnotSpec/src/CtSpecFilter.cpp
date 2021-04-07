//----------------------------------------------------------------
//
//     Ct spec filter for partial knot specs (implementation).
//     Checks ct specs for (1) number of 1's and (2) knot admission.
//
//     Bob Tuzun
//

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

#include "JonesConjecNonAlg/Polyh/I_PolyhManager.h"
#include "JonesConjecNonAlg/PartialKnotSpec/CtSpecFilter.h"

namespace DT = Tuzun_Util::Datatypes;
namespace JP = Jones_Conjec_NonAlg::Polyh;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

//----------------------------------------------------------------

CtSpecFilter::CtSpecFilter(std::shared_ptr<JP::I_PolyhManager> polyhManager)
:polyhManager_(polyhManager)
{
}

//----------------------------------------------------------------

CtSpecFilter::~CtSpecFilter()
{
}

//----------------------------------------------------------------

void CtSpecFilter::prepareForUse(DT::Int32 maxAllowedNumNcEq1)
{
   maxAllowedNumNcEq1_ = maxAllowedNumNcEq1;
}

//----------------------------------------------------------------
//
//     Filter a set of ct specs according to criteria (1) and (2) above.
//

void CtSpecFilter::filterCtSpecs(std::vector<DT::VecInt32>& ctSpecs)
{
   auto filterFunction = [this](const DT::VecInt32& ctSpec)
          {
             DT::Int32 numOnes = std::count(ctSpec.begin(), ctSpec.end(), 1);
             if (numOnes > maxAllowedNumNcEq1_)
                return true;

             return (! polyhManager_->polyhAdmitsKnotsForCts(ctSpec));
          };

   ctSpecs.erase(std::remove_if(ctSpecs.begin(), ctSpecs.end(), filterFunction),
                 ctSpecs.end());
}

//----------------------------------------------------------------

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

