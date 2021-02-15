//------------------------------------------------------------------
//
//     Function template for sorting a std::vector of some type using
//     a table of precomputed ranks.
//
//     Bob Tuzun
//

#pragma once

#include <vector>
#include <algorithm>

#include "TuzunUtil/CppDatatypes.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Tuzun_Util {

template <typename T>
void sortByRank(std::vector<T>& vecT, const DT::VecInt32& ranksIn)
{
//     If vector is already sorted, return.
   if (std::is_sorted(ranksIn.begin(), ranksIn.end()))
         return;

//     Perform loop to sort vector by rank.  The copied ranks array is
//     sorted at the same time as vecT.
   DT::VecInt32 ranks(ranksIn);
   auto startIt = ranks.begin();

   do {
//     Determine if vector is sorted, and first location of non-sortedness
//     if not.
      DT::Int32 locNonSort = std::distance(startIt, ranks.begin()) - 1;
      startIt = std::find_if(startIt, ranks.end(), [&locNonSort](DT::Int32 r)
           {
               locNonSort++;
               return (r == locNonSort);
           } );
       bool isSorted = (startIt == ranks.end());

//     Perform swaps involving first non-sorted element location (locNonSort)
//     until that location has the element of the same rank.
//     For example, if locNonSort is 5, perform swaps involving location 5
//     until the element of rank 5 is in position 5.
       if (! isSorted) {
          bool done = false;
          do {
             DT::Int32 curRank = *(ranks.begin() + locNonSort);
             std::swap(vecT.begin() + locNonSort, vecT.begin() + curRank);
             std::swap(ranks.begin() + locNonSort, ranks.begin() + curRank);
             done = (*(ranks.begin() + locNonSort) == locNonSort);
          }
          while (! done);
       }
   }
   while (! isSorted);
}

} // namespace Tuzun_Util

