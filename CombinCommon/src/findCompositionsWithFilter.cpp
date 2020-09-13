//------------------------------------------------------------------
//
//     Compute members of a sequence of k-compositions of n with
//     some condition as implemented in a filter (implementation).
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
      std::function<bool(DT::VecInt32)> f)
{
//     Reserve space for results vector.
   binomCoeffTable->init(n+k-1);
   std::vector<DT::VecInt32> results;
   DT::Int32 numKNCompos = binomCoeffTable->getBinom(n+k-1, k-1);
   results.reserve(numKNCompos);

//     Perform the calculation and filtering.
   KComposition kComp;
   kComp.init(k, n);

   DT::Int32 numCompositions = 0;
   bool done = false;
   do {
      kComp.findNextComposition();
      done = kComp.atLastComposition();
      DT::VecInt32 comp = kComp.getComposition();

      if (f(comp)) {
         results.push_back(comp);
         numCompositions++;
      }
   }
   while (! done);

//     Remove unused elements.
   results.erase(results.begin()+numCompositions, results.end());

   return std::vector<DT::VecInt32>(results);
}

//-------------------------------------------------------------------

} // namespace Combin_Common

