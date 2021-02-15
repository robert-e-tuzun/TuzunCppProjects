//----------------------------------------------------------------
//
//     Nc specification manager for partial knot specs (implementation).
//
//     Bob Tuzun
//

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "JonesConjecNonAlg/PartialKnotSpec/SmallNcSpecManager.h"
#include "JonesConjecNonAlg/PartialKnotSpec/MediumcSpecBuilder.h"
#include "JonesConjecNonAlg/PartialKnotSpec/LargeNcSpecManager.h"
#include "JonesConjecNonAlg/PartialKnotSpec/NcSpecManager.h"

namespace DT = Tuzun_Util::Datatypes;
namespace JCB = Jones_Conjec_NonAlg::Blkbd_Jones_Conj_NonAlg;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

//----------------------------------------------------------------

NcSpecManager::NcSpecManager(
     std::shared_ptr<I_SmallNcSpecManager> smallNcSpecManager,
     std::shared_ptr<I_MediumNcSpecManager> mediumNcSpecManager,
     std::shared_ptr<I_LargeNcSpecManager> largeNcSpecManager)
:smallNcSpecManager_(smallNcSpecManager),
 mediumNcSpecManager_(mediumNcSpecManager),
 largeNcSpecManager_(largeNcSpecManager)
{
}

//----------------------------------------------------------------

NcSpecManager::~NcSpecManager()
{
}

//----------------------------------------------------------------
//
//     Prepare this object for use.
//

void NcSpecManager::prepareForUse(const NcSpecBuildInfo& info)
{
   largestSmallNc_ = info.largestSmallNc_;
   largestNcInMemory_ = info.largestNcInMemory_;
   ncMaxAttainable_ = info.ncMaxAttainable_;

   setInitialState();

//     Prepare chunk managers for use.
   smallNcSpecManager_->prepareForUse(info);
   mediumNcSpecManager_->prepareForUse(info);
   largeNcSpecManager_->prepareForUse(info);
}

//----------------------------------------------------------------

void NcSpecManager::setInitialState()
{
//     Determine which sizes of chunks are present.
   noSmall_ = (largestSmallNc_ == 0);
   noMedium_ = (largestSmallNc_ == largestNcInMemory_);
   noLarge_ = (ncMaxAttainable_ <= largestNcInMemory_);

//     Set the possible chunk size array.
   chunkSizes_.clear();
   if (! noSmall_)
      chunkSizes_.push_back("Small");
   if (! noMedium_)
      chunkSizes_.push_back("Medium");
   if (! noLarge_)
      chunkSizes_.push_back("Large");
   chunkSizes_.push_back("Done");

//     Determine the stage of the calculation.
   chunkSizeIndex_ = 0;
   stage_ = chunkSizes_[chunkSizeIndex_];

//     Set the chunk manager according to chunk size.
   if (stage_ == "Small")
      chunkManager_ = smallNcSpecManager_;
   else if (stage_ == "Medium")
      chunkManager_ = mediumNcSpecManager_;
   else
      chunkManager_ = largeNcSpecManager_;
}

//----------------------------------------------------------------

void NcSpecManager::findNextNcChunk()
{
   do {
      chunkManager_->findNextNcChunk();
      ncChunk_ = chunkManager_->getNcChunk();
      cyclicPermutationShift_ = chunkManager_->getCyclicPermutationShift();
      numNcSpecs_ = chunkManager_->getNumNcSpecs();
      if (chunkManager_->atLastNcChunk())
         goToNextStage();
   }
   while (ncChunk_.empty() && (stage_ != "Done"));
}

//----------------------------------------------------------------

void NcSpecManager::goToNextStage()
{
//     Determine what the next stage of the calculation is.
   chunkSizeIndex_++;
   stage_ = chunkSizes_[chunkSizeIndex_];

//     Reassign the chunk manager accordingly.
   if (stage == "Medium")
      chunkManager_ = mediumNcSpecManager_;
   else if (stage_ == "Large")
      chunkManager_ = largeNcSpecManager_;
}

//----------------------------------------------------------------

DT::VecInt32 NcSpecManager::getNcChunk() const
{
   return ncChunk_;
}

//----------------------------------------------------------------

DT::VecInt32 NcSpecManager::getCyclicPermutationShift() const
{
   return cyclicPermutationShift_;
}

//----------------------------------------------------------------

DT::VecInt32 NcSpecManager::getNumNcSpecs() const
{
   return numNcSpecs_;
}

//----------------------------------------------------------------

DT::String NcSpecManager::getChunkSizeCategory() const
{
   return stage_;
}

//----------------------------------------------------------------

bool NcSpecManager::finished() const
{
   return (stage_ == "Done");
}

//----------------------------------------------------------------

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

