//----------------------------------------------------------------
//
//     Medium nc specification builder for partial knot specs (implementation).
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
#include "JonesConjecNonAlg/PartialKnotSpec/periodWithRespectToMaximumElements.h"

#include "JonesConjecNonAlg/PartialKnotSpec/MediumNcSpecBuilder.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

//----------------------------------------------------------------

MediumNcSpecBuilder::MediumNcSpecBuilder(
     std::shared_ptr<I_RepresentativeChecker> repChecker)
:repChecker_(repChecker)
{
}

//----------------------------------------------------------------

MediumNcSpecBuilder::~MediumNcSpecBuilder()
{
}

//----------------------------------------------------------------
//
//     Prepare this object for use.
//

void MediumNcSpecBuilder::prepareForUse(const NcSpecBuildInfo& info)
{
   numCrossings_ = info.numCrossings_;
   numVertices_ = info.numVertices_;
   largestSmallNc_ = info.largestSmallNc_;
   largestNcInMemory_ = info.largestNcInMemory_;
   numNcPartitionsStoredMax_ = info.numNcPartitionsStoredMax_;
   polyhedronIsDnSymmetric_ = info.polyhedronIsDnSymmetric_;
   maxAllowedNumNcEq1_ = info.maxAllowedNumNcEq1_;

   setInitialState();
   setLambdaFunctions();
}

//----------------------------------------------------------------

void MediumNcSpecBuilder::setInitialState()
{
   ncChunk_.clear();
   ncChunk_.reserve(numNcPartitionsStoredMax_);

   prevComposition_ = { -1 };   // Start at beginning of partition sequence.
   maxPeriod_ = -3;  // Set to a positive value when a non-empty chunk occurs.
   done_ = false;

   if (polyhedronIsDnSymmetric_)
      cyclicPermutationShift_ = 0;  // This value always zero.
   else
      cyclicPermutationShift_ = -1;  // Should get next chunk.
}

//----------------------------------------------------------------

void MediumNcSpecBuilder::setLambdaFunctions()
{
//     For general symmetry polyhedra, conditions on v-partitions of n:
//     (1) largestSmallNc < max element <= largestNcInMemory.
//     (2) last element = max element.
//     (3) number of 1's in nc partition does not exceed prescribed limit.
//     (4) (period != v) or ((period == v) and (partition is representative)).
//
//     Bijective with v-compositions of (n-v-largestSmallNc) with:
//     (1) Let ncMax = max(first v-1 nc_i, last element+largestSmallNc).  Then
//         largestSmallNc <= ncMax < largestNcInMemory.
//     (2) ncMax = last element + largestSmallNc.
//     (3) number of 0's in composition, with largestSmallNc added to last
//         element, does not exceed prescribed limit for number of 1's in
//         partition.
//     (4) Let period be the period of C, the composition with largestSmallNc
//         added to the last element.  Then
//         (period != v) or ((period == v) and (C is representative)).
//
//     For polyhedra with Dn symmetry, conditions on v-partitions of n
//     are the same as conditions (1)-(3) for general symmetry polyhedra.
//     Bijective with v-compositions of (n-v-largestSmallNc) that satisfy
//     conditions (1)-(3) for general symmetry polyhedra.

   if (polyhedronIsDnSymmetric_) {
      filterFunction_ = [this](const DT::VecInt32& v)
           {
              DT::VecInt32 w(v);
              w.back() += largestSmallNc_;

              DT::Int32 numZeros = std::count(w.begin(), w.end()-1, 0);
              if (numZeros > maxAllowedNumNcEq1_)
                 return false;

              DT::Int32 maxElement = *std::max_element(w.begin(), w.end());
              return ((largestSmallNc_ <= maxElement) &&
                      (maxElement < largestNcInMemory_) &&
                      (maxElement == w.back()));
           };
   }
   else {
      filterFunction_ = [this](const DT::VecInt32& v)
           {
              DT::VecInt32 w(v);
              w.back() += largestSmallNc_;

              DT::Int32 numZeros = std::count(w.begin(), w.end()-1, 0);
              if (numZeros > maxAllowedNumNcEq1_)
                 return false;

              DT::Int32 maxElement = *std::max_element(w.begin(), w.end());
              if (! ((largestSmallNc_ <= maxElement) &&
                     (maxElement < largestNcInMemory_) &&
                     (maxElement == w.back())) )
                  return false;

              DT::Int32 period = periodOf(w);
              periods_.push_back(period);
              return ((period != numVertices_) ||
                      ((period == numVertices_) &&
                        repChecker_->isRepresentative(w)));
           };
   }

//     Transformation function performs the bijection.  For both Dn
//     symmetric and general symmetry polyhedra, the bijection consists
//     of adding 1 to all but the last entry in the composition, and
//     largestSmallNc+1 to the last.

   transformationFunction_ = [this](const DT::VecInt32& v)
           {
              DT::VecInt32 w(v);
              for (DT::Int32& x : w)
                 x++;

              w.back() += largestSmallNc_;

              return DT::VecInt32(w);
           };
}

//----------------------------------------------------------------
//
//     This function is used by a lambda function.  It is used to wrap
//     a free function, which cannot be directly captured by a lambda.
//

DT::Int32 MediumNcSpecBuilder::periodOf(const DT::VecInt32& p)
{
   return periodWithRespectToMaximumElements(p);
}

//----------------------------------------------------------------

void MediumNcSpecBuilder::findNextNcChunk()
{
   if (polyhedronIsDnSymmetric_)
      findNextNcChunkIfExists();  // This sets atLastNcChunk_.
   else
      findNextNcChunkGeneralSymmetry();  // Sets atLastNcChunk_ and periods_.
}

//----------------------------------------------------------------

void MediumNcSpecBuilder::findNextNcChunkIfExists()
{
   DT::Int32 k = numVertices_;
   DT::Int32 n = numCrossings_ - numVertices_ - largestSmallNc_;

   atLastNcChunk_ =  // Note that this produces periods_ vector.
          Combin_Common::buildSomeFilteredTransformedCompositions(k, n,
               numNcPartitionsStoredMax_, prevComposition_, filterFunction_,
               transformationFunction_, ncChunk_);
}

//----------------------------------------------------------------

void MediumNcSpecBuilder::findNextNcChunkGeneralSymmetry()
{
   DT::Int32 k = numVertices_;
   DT::Int32 n = numCrossings_ - numVertices_ - largestSmallNc_;

   if (cyclicPermutationShift_ == (maxPeriod_ - 1))
      cyclicPermutationShift_ = -1;

//     Execute the following block if it's time to get the next nc chunk.
   if (cyclicPermutationShift_ == -1) {
      ncChunk_.clear();
      findNextNcChunkIfExists();      // Determines atLastNcChunk_ and
                                      // periods_ vector.

      if (ncChunk_.empty()) {
         done_ = true;
         return;
      }
      else {
         periodsThatOccur_ = periodsThatOccur();
         maxPeriod_ = periodsThatOccur_.back();
      }
   }

//     Determine if parts of nc chunk should be removed, and do so if yes.
   cyclicPermutationShift_++;
   bool shouldRemoveElements = (std::find(periodsThatOccur_.begin(),
         periodsThatOccur_.end(), cyclicPermutationShift_) !=
         periodsThatOccur_.end());
   if (shouldRemoveElements)
      removeElementsWithPeriod(cyclicPermutationShift_);

   done_ = (atLastNcChunk_ && (cyclicPermutationShift_ == (maxPeriod_-1)));
}

//----------------------------------------------------------------

DT::VecInt32 MediumNcSpecBuilder::periodsThatOccur()
{
   DT::VecInt32 results(periods_);

   std::sort(results.begin(), results.end());
   results.erase(unique(results.begin(), results.end()), results.end());

   return results;
}

//----------------------------------------------------------------

void MediumNcSpecBuilder::removeElementsWithPeriod(DT::Int32 period)
{
   DT::Int32 sizeOfNcChunk = ncChunk_.size();
   for (DT::Int32 i=sizeOfNcChunk-1; i >= 0; --i)
      if (periods_[i] == period) {
         periods_.erase(periods_.begin() + i);
         ncChunk_.erase(ncChunk_.begin() + i);
      }
}

//----------------------------------------------------------------

std::vector<DT::VecInt32> MediumNcSpecBuilder::getNcChunk() const
{
   return ncChunk_;
}

//----------------------------------------------------------------

DT::Int32 MediumNcSpecBuilder::getCyclicPermutationShift() const
{
   return cyclicPermutationShift_;
}

//----------------------------------------------------------------

bool MediumNcSpecBuilder::isDone() const
{
   return done_;
}

//----------------------------------------------------------------

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

