//----------------------------------------------------------------
//
//     Checker for whether a partition is the representative for its
//     set of cyclic permutations (implementation).
//
//     Bob Tuzun
//

#include <iostream>
#include <vector>
#include <algorithm>

#include "JonesConjecNonAlg/PartialKnotSpec/RepresentativeChecker.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

//----------------------------------------------------------------

RepresentativeChecker::RepresentativeChecker()
{
}

//----------------------------------------------------------------

RepresentativeChecker::~RepresentativeChecker()
{
}

//----------------------------------------------------------------

bool RepresentativeChecker::isRepresentative(const DT::VecInt32& v)
{
//     Generate, for each cyclic permutation of v, a vector with
//     numbers of all elements that have the maximum value within v.

   DT::Int32 maxValue = *std::max_element(v.begin(), v.end());

   std::vector<DT::VecInt32> maxArrays;
   DT::Int32 length = v.size();
   for (DT::Int32 x=0; x<length; ++x) {
//     First, compute cyclic permutation.
      DT::VecInt32 cyclicPermutation(v);
      std::rotate(cyclicPermutation.begin(), cyclicPermutation.begin()+x,
                  cyclicPermutation.end());

//     Next, find element numbers with maximum value.
      DT::VecInt32 maxArray;
      for (DT::Int32 x=0; x<length; ++x)
         if (v[x] == maxValue)
            maxArray.push_back(x);

//     Reverse array so as to allow direct lexicographic comparison of
//     decreasing sequences.
      std::reverse(maxArray.begin(), maxArray.end());
      maxArrays.push_back(maxArray);
   }

//     Determine maximum element within maxArrays, where the maximum
//     is determined by lexicographic comparison.
//     Then return whether v is representative (first element is maximal).

   DT::VecInt32 maxOfMaxArrays =
           *std::max_element(maxArrays.begin(), maxArrays.end());
   return (maxArrays[0] == maxOfMaxArrays);
}

//----------------------------------------------------------------

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

