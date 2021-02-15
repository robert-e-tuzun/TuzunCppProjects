//----------------------------------------------------------------
//
//     Nc partition chunk prepper for partial knot specs (implementation).
//
//     Bob Tuzun
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <memory>
#include <algorithm>

#include "CombinCommon/buildSomeFilteredTransformedCompositions.h"

#include "MathCommon/integerFactorsOf.h"
#include "JonesConjecNonAlg/PartialKnotSpec/NcPartitionChunkPrepper.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

//----------------------------------------------------------------

NcPartitionChunkPrepper::NcPartitionChunkPrepper()
{
}

//----------------------------------------------------------------

NcPartitionChunkPrepper::~NcPartitionChunkPrepper()
{
}

//----------------------------------------------------------------

void NcPartitionChunkPrepper::setParams(DT::Int32 numCrossings,
       DT::Int32 numVertices, DT::Int32 maxChunkSize,
       DT::Int32 largestSmallNc, DT::Int32 maxCyclicPermutationShift)
{
   numCrossings_ = numCrossings;
   numVertices_ = numVertices;
   maxChunkSize_ = maxChunkSize;
   largestSmallNc_ = largestSmallNc;
   maxCyclicPermutationShift_ = maxCyclicPermutationShift;
}

//----------------------------------------------------------------

void NcPartitionChunkPrepper::setFilterFunction(DT::Int32 kForComposition,
       DT::Int32 nForComposition, FilterFuncType filterFunction)
{
   kForComposition_ = kForComposition;
   nForComposition_ = nForComposition;
   filterFunction_ = filterFunction;
}

//----------------------------------------------------------------

void NcPartitionChunkPrepper::setTransformationFunction(
       TransformFuncType transformationFunction)
{
   transformationFunction_ = transformationFunction;
}

//----------------------------------------------------------------

void NcPartitionChunkPrepper::setInitialStateAtBeginning()
{
//     Start at the beginning of the partition sequence.
   prevComposition_ = { -1 };

//     
   computeCyclicPermutationShiftBoundaries();

//     As a consequence of cyclic permutation shift = 0, will be
//     necessary to generate next (first) chunk.
   cyclicPermutationShift_ = 0;
}

//----------------------------------------------------------------

void NcPartitionChunkPrepper::computeCyclicPermutationShiftBoundaries()
{
//     If only one cyclic permutation shift value, should update nc
//     partitions for this value.
   if (maxCyclicPermutationShift_ == 0) {
      return;
   }

//     Find calculation boundaries for cyclic permutations.
   DT::VecInt32 cyclicPermutationShiftBoundaries;

   DT::Int32 rMax = std::min((numCrossings_-numVertices_)/largestSmallNc_,
                             numVertices_);
   factorsOfNumVertices_ = Math_Common::integerFactorsOf(numVertices_);
   for (DT::Int32 r : factorsOfNumVertices_)
      if (r <= rMax)
         cyclicPermutationShiftBoundaries.push_back(numVertices_/r);

//     Specify exactly for which cyclic permutation shifts the nc
//     partitions vector should be updated.
   shouldUpdateNcParts_.clear();
   shouldUpdateNcParts_.assign(maxCyclicPermutationShift_+1, false);
   for (DT::Int32 boundary : cyclicPermutationShiftBoundaries)
      shouldUpdateNcParts_[boundary-1] = true;
}

//----------------------------------------------------------------

void NcPartitionChunkPrepper::computeNextSetOfNcPartitions()
{
   cyclicPermutationShift_--;
   bool shouldPrepareNcChunk = (cyclicPermutationShift_ < 0);
   if (shouldPrepareNcChunk) {
      cyclicPermutationShift_ = maxCyclicPermutationShift_;
      ncPartitionsChunk_.clear();
      prepareNcChunk();
   }

   if ((! chunkIsEmpty_) && shouldUpdateNcParts_[cyclicPermutationShift_]) {
   }
}

//----------------------------------------------------------------

void NcPartitionChunkPrepper::prepareNcChunk()
{
//     Get full unsorted chunk.
   ncPartitionsChunk_ = Combin_Common::buildSomeFilteredTransformedCompositions(
            kForComposition_, nForComposition_, maxChunkSize_, prevComposition_,
            filterFunction_, transformationFunction_);

   if (! ncPartitionsChunk_.empty()) {
      findRanksIndexesAccordingToPeriodicity();
      sortNcPartitionsByPeriodicity();
//     TODO: Find number of partitions at each rank.
   }
}

//----------------------------------------------------------------

void NcPartitionChunkPrepper::findRanksIndexesAccordingToPeriodicity()
{
   ranksIndexes_.clear();
   ranksIndexes_.reserve(ncPartitionsChunk_.size());

   DT::Int32 index=-1;
   for (const DT::VecInt32& p : ncPartitionsChunk_) {
      index++;
      DT::Int32 period = periodOf(p);
      ranksIndexes_.push_back({index, period});
   }
}

//----------------------------------------------------------------

DT::Int32 NcPartitionChunkPrepper::periodOf(const DT::VecInt32& p)
{
   DT::VecInt32 locs;

//     Get locations of target value.
   DT::Int32 target = p[numVertices_-1];
   DT::Int32 index = -1;
   for (DT::Int32 x : p) {
      index++;
      if (x == target)
         locs.push_back(index);
   }

//     If more than one occurrence, check if they are equally spaced.  If
//     not, or just one occurrence, period is numVertices_.

   DT::Int32 period = numVertices;
   DT::Int32 numLocs = locs.size();
   if (numLocs > 1) {
//     Find intervals between successive values, including wraparound.
      DT::VecInt32 intervals;
      for (DT::Int32 i=0; i<(numLocs-1); ++i)
         intervals.push_back(locs[i+1] - locs[i]);
      intervals.push_back(loc[0]+numVertices_-loc[numLocs-1]);

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

void NcPartitionChunkPrepper::sortNcPartitionsByPeriodicity()
{
}

//----------------------------------------------------------------

bool NcPartitionChunkPrepper::isDoneComputingNewNcSpecs()
{
   return doneComputingNewNcSpecs_;
}

//----------------------------------------------------------------

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

