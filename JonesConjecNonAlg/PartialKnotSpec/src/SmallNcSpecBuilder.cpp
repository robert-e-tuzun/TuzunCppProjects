//----------------------------------------------------------------
//
//     Small nc specification builder for partial knot specs (implementation).
//
//     Bob Tuzun
//

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>

#include "CombinCommon/KComposition.h"
#include "CombinCommon/buildSomeFilteredTransformedCompositions.h"

#include "JonesConjecNonAlg/PartialKnotSpec/SmallNcSpecBuilder.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

//----------------------------------------------------------------

SmallNcSpecBuilder::SmallNcSpecBuilder()
{
}

//----------------------------------------------------------------

SmallNcSpecBuilder::~SmallNcSpecBuilder()
{
}

//----------------------------------------------------------------
//
//     Prepare this object for use.
//

void SmallNcSpecBuilder::prepareForUse(const NcSpecBuildInfo& info)
{
   numCrossings_ = info.numCrossings_;
   numVertices_ = info.numVertices_;
   largestSmallNc_ = info.largestSmallNc_;
   numNcPartitionsStoredMax_ = info.numNcPartitionsStoredMax_;
   polyhedronIsDnSymmetric_ = info.polyhedronIsDnSymmetric_;
   maxAllowedNumNcEq1_ = info.maxAllowedNumNcEq1_;

   setInitialState();
   setLambdaFunctions();
}

//----------------------------------------------------------------

void SmallNcSpecBuilder::setInitialState()
{
   ncChunk_.clear();
   ncChunk_.reserve(numNcPartitionsStoredMax_);

   prevComposition_ = { -1 };   // Start at beginning of partition sequence.

   done_ = false;
}

//----------------------------------------------------------------

void SmallNcSpecBuilder::setLambdaFunctions()
{
//     For Dn symmetric polyhedra,
//     k-partitions of n with max element <= largestSmallNc_ and
//     last element = max element and number of 1's in nc partition
//     does not exceed prescribed limit are bijective with
//     k-compositions of (n-k) with max element < largestSmallNc_
//     and last element = max element and number of 0's in composition
//     does not exceed prescribed limit.
//
//     For polyhedra with general symmetry,
//     k-partitions of n with max element <= largestSmallNc_ and
//     last element = max element and number of 1's in nc partition
//     does not exceed prescribed limit are bijective with
//     k-compositions of (n-k) with max element < largestSmallNc_
//     number of 0's in composition does not exceed prescribed limit.

   if (polyhedronIsDnSymmetric_) {
      filterFunction_ = [this](const DT::VecInt32& v)
           {
              DT::Int32 numZeros = std::count(v.begin(), v.end(), 0);
              if (numZeros > maxAllowedNumNcEq1_)
                 return false;

              DT::Int32 maxElement = *std::max_element(v.begin(), v.end());
              return ((maxElement < largestSmallNc_) &&
                      (maxElement == v.back()));
           };
   }
   else {
      filterFunction_ = [this](const DT::VecInt32& v)
           {
              DT::Int32 numZeros = std::count(v.begin(), v.end(), 0);
              if (numZeros > maxAllowedNumNcEq1_)
                 return false;

              DT::Int32 maxElement = *std::max_element(v.begin(), v.end());
              return (maxElement < largestSmallNc_);
           };
   }

//     Transformation function performs the bijection.  For both Dn
//     symmetric and general symmetry polyhedra, the bijection consists
//     of adding 1 to each entry in the composition.

   transformationFunction_ = [](const DT::VecInt32& v)
           {
              DT::VecInt32 w(v);
              for (DT::Int32& x : w)
                 x++;

              return DT::VecInt32(w);
           };
}

//----------------------------------------------------------------

void SmallNcSpecBuilder::findNextNcChunk()
{
   DT::Int32 k = numVertices_;
   DT::Int32 n = numCrossings_ - numVertices_;

   done_ = Combin_Common::buildSomeFilteredTransformedCompositions(
         k, n, numNcPartitionsStoredMax_, prevComposition_, filterFunction_,
         transformationFunction_, ncChunk_);
}

//----------------------------------------------------------------

std::vector<DT::VecInt32> SmallNcSpecBuilder::getNcChunk()
{
   return ncChunk_;
}

//----------------------------------------------------------------

bool SmallNcSpecBuilder::isDone()
{
   return done_;
}

//----------------------------------------------------------------

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

