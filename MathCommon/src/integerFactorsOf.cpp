//------------------------------------------------------------------
//
//     Compute integer factors of a positive integer (implementation).
//     This function is suitable for small integers only, for not often
//     repeated calculations.
//
//     Bob Tuzun
//

#include <iostream>
#include <vector>

#include "MathCommon/integerFactorsOf.h"

namespace Math_Common {

//-------------------------------------------------------------------

DT::VecInt32 integerFactorsOf(DT::Int32 k)
{
   DT::VecInt32 factors = { 1 };
   for (DT::Int32 i=2; i <= k/2; ++i) {
      if ((k%i) == 0)
         factors.push_back(i);
   }
   if (k > 1)
      factors.push_back(k);

   return DT::VecInt32(factors);
}

//-------------------------------------------------------------------

} // namespace Math_Common

