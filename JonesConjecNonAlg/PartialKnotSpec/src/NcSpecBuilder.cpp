//----------------------------------------------------------------
//
//     Nc specification builder for partial knot specs (implementation).
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

#include "JonesConjecNonAlg/PartialKnotSpec/SmallNcSpecBuilder.h"
#include "JonesConjecNonAlg/PartialKnotSpec/MediumcSpecBuilder.h"
#include "JonesConjecNonAlg/PartialKnotSpec/LargeNcSpecBuilder.h"
#include "JonesConjecNonAlg/PartialKnotSpec/NcSpecBuilder.h"

namespace DT = Tuzun_Util::Datatypes;
namespace JCB = Jones_Conjec_NonAlg::Blkbd_Jones_Conj_NonAlg;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

//----------------------------------------------------------------

NcSpecBuilder::NcSpecBuilder(
     std::shared_ptr<I_SmallNcSpecBuilder> smallNcSpecBuilder,
     std::shared_ptr<I_MediumNcSpecBuilder> mediumNcSpecBuilder,
     std::shared_ptr<I_LargeNcSpecBuilder> largeNcSpecBuilder)
:smallNcSpecBuilder_(smallNcSpecBuilder),
 mediumNcSpecBuilder_(mediumNcSpecBuilder),
 largeNcSpecBuilder_(largeNcSpecBuilder)
{
}

//----------------------------------------------------------------

NcSpecBuilder::~NcSpecBuilder()
{
}

//----------------------------------------------------------------
//
//     Prepare this object for use.
//

void NcSpecBuilder::prepareForUse(DT::Int32 numCrossings,
       DT::Int32 numVertices, DT::Int32 largestSmallNc,
       DT::Int32 largestNcInMemory, DT::Int32 ncMaxAttainable,
       DT::Int32 numNcPartitionsStoredMax, bool isDnSymmetric)
{
   numCrossings_ = numCrossings;
   numVertices_ = numVertices;
   largestSmallNc_ = largestSmallNc;
   largestNcInMemory_ = largestNcInMemory;
   ncMaxAttainable_ = ncMaxAttainable;
   numNcPartitionsStoredMax_ = numNcPartitionsStoredMax;
   isDnSymmetric_ = isDnSymmetric;

   stage_ = "Small";

//     Initialize small, medium, and large nc partition builders.
   smallNcSpecBuilder_->prepareForUse(numCrossings_, numVertices_,
           largestSmallNc_, isDnSymmetric_);
   mediumNcSpecBuilder_->prepareForUse(numCrossings_, numVertices_,
           largestSmallNc_, largestNcInMemory_, isDnSymmetric_);
   largeNcSpecBuilder_->prepareForUse(numCrossings_, numVertices_,
           largestNcInMemory_, isDnSymmetric_);
}

//----------------------------------------------------------------

void NcSpecBuilder::computeNextSetOfNcPartitions()
{
//     Calculate cyclic permutation shift and, if necessary, the next
//     set of nc partitions.
//     We say "if necessary" because for any set of cyclic permutation
//     shifts that uses the same nc partitions, the nc partitions only
//     need to be computed once.

   bool needToGetNcSpecs = true;
   bool doneWithCurrentPhase = false;
   if (stage_ == "Small") {
      needToGetNcSpecs = true;
      smallNcSpecBuilder_->computeNextSetOfNcPartitions(
           cyclicPermutationShift_, ncPartitions_);
      doneWithCurrentPhase = smallNcSpecBuilder_->isDoneComputingNewNcSpecs();
   }

   else if (stage_ == "Medium") {
      mediumNcSpecBuilder_->computeNextSetOfNcPartitionsIfNeeded();
      cyclicPermutationShift_ =
          mediumNcSpecBuilder->getCyclicPermutationShift();
      needToGetNcSpecs = mediumNcSpecBuilder->needToGetNcSpecs();
      if (needToGetNcSpecs)
         ncPartitions_ = mediumNcSpecBuilder->getNcSpecs();
      doneWithCurrentPhase = mediumNcSpecBuilder_->isDoneComputingNewNcSpecs();
   }

   else {
      largeNcSpecBuilder_->computeNextSetOfNcPartitionsIfNeeded();
      cyclicPermutationShift_ =
          largeNcSpecBuilder->getCyclicPermutationShift();
      needToGetNcSpecs = largeNcSpecBuilder->needToGetNcSpecs();
      if (needToGetNcSpecs)
         ncPartitions_ = largeNcSpecBuilder->getNcSpecs();
      doneWithCurrentPhase = largeNcSpecBuilder_->isDoneComputingNewNcSpecs();
   }
   haveComputedNewNcSpecs_ = needToGetNcSpecs;

//     Determine which type of nc partitions needs to be computed
//     next, if any, and from there whether nc partitions are done
//     being computed for this batch.

   if (stage_ == "Small") {
      if (doneWithCurrentPhase && isMediumPhaseNeeded)
         stage_ = "Medium";
      else
         doneComputingNcSpecs_ = true;
   }

   else if (stage_ == "Medium") {
      if (doneWithCurrentPhase && isLargePhaseNeeded)
         stage_ = "Large";
      else
         doneComputingNcSpecs_ = true;
   }

   else
      doneComputingNcSpecs_ = doneWithCurrentPhase;
}

//----------------------------------------------------------------

DT::Int32 NcSpecBuilder::getCyclicPermutationShift()
{
   return cyclicPermutationShift_;
}

//----------------------------------------------------------------

std::vector<DT::VecInt32> NcSpecBuilder::getNcSpecs()
{
   return ncPartitions_;
}

//----------------------------------------------------------------

bool NcSpecBuilder::haveComputedNewNcSpecs()
{
   return haveComputedNewNcSpecs_;
}

//----------------------------------------------------------------

bool NcSpecBuilder::isDoneComputingNewNcSpecs()
{
   return doneComputingNewNcSpecs_;
}

//----------------------------------------------------------------

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

