//----------------------------------------------------------------
//
//     Compute period with respect to maximum elements (implementation).
//
//     Bob Tuzun
//

#include <iostream>
#include <vector>
#include <algorithm>

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

//----------------------------------------------------------------

DT::Int32 periodWithRespectToMaximumElements(const DT::VecInt32& p)
{
   DT::VecInt32 locs;

//     Get locations of target value.
   DT::Int32 target = p.back();
   DT::Int32 index = -1;
   for (DT::Int32 x : p) {
      index++;
      if (x == target)
         locs.push_back(index);
   }

//     If more than one occurrence, check if they are equally spaced.  If
//     not, or just one occurrence, period is numVertices_.

   DT::Int32 numElements = p.size();
   DT::Int32 period = numElements;
   DT::Int32 numLocs = locs.size();
   if (numLocs > 1) {
//     Find intervals between successive values, including wraparound.
      DT::VecInt32 intervals;
      for (DT::Int32 i=0; i<(numLocs-1); ++i)
         intervals.push_back(locs[i+1] - locs[i]);
      intervals.push_back(loc[0]+numElements-loc[numLocs-1]);

//     Check if all intervals are equal.
      DT::Int32 interval0 = intervals[0]
      bool allEqual = std::all_of(intervals.begin()+1, intervals.end(),
            [interval0](DT::Int32 i){return i == interval0});
      if (allEqual)
         period = interval0;
   }

   return period;
}

//----------------------------------------------------------------

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

