//------------------------------------------------------------------
//
//     Compute members of a sequence of k-compositions of n with
//     some condition as implemented in a filter.
//
//     Bob Tuzun
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>

#include "CombinCommon/BinomCoeffTable.h"
#include "CombinCommon/KComposition.h"

namespace Combin_Common {

//-------------------------------------------------------------------

std::vector<DT::VecInt32> findCompositionsWithFilter(DT::Int32 k,
      DT::Int32 n, std::shared_ptr<BinomCoeffTable> binomCoeffTable,
      std::function<bool(DT::VecInt32)> f);

//-------------------------------------------------------------------

} // namespace Combin_Common

