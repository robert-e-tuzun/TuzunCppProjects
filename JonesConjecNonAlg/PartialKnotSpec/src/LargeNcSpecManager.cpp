//----------------------------------------------------------------
//
//     Large nc specification builder for partial knot specs (implementation).
//
//     Bob Tuzun
//

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "JonesConjecNonAlg/PartialKnotSpec/LargeNcSpecManager.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

//----------------------------------------------------------------

LargeNcSpecManager::LargeNcSpecManager(
     std::shared_ptr<I_LargeNcSpecBuilder> largeNcSpecBuilder)
:largeNcSpecBuilder_(largeNcSpecBuilder)
{
}

//----------------------------------------------------------------

LargeNcSpecManager::~LargeNcSpecManager()
{
}

//----------------------------------------------------------------
//
//     Prepare this object for use.
//

void LargeNcSpecManager::prepareForUse(const NcSpecBuildInfo& info)
{
   largeNcSpecBuilder_->prepareForUse(info);
}

//----------------------------------------------------------------

void LargeNcSpecManager::findNextNcChunk()
{
   largeNcSpecBuilder_->findNextNcChunk();
   ncChunk_ = largeNcSpecBuilder_->getNcChunk();
   cyclicPermutationShift_ =
        largeNcSpecBuilder_->getCyclicPermutationShift();
   numNcSpecs_ = ncChunk_.size();
   done_ = largeNcSpecBuilder_->isDone();
}

//----------------------------------------------------------------

std::vector<DT::VecInt32> LargeNcSpecManager::getNcChunk() const
{
   return ncChunk_;
}

//----------------------------------------------------------------

DT::Int32 LargeNcSpecManager::getCyclicPermutationShift() const
{
   return cyclicPermutationShift_;
}

//----------------------------------------------------------------

DT::Int32 LargeNcSpecManager::getNumNcSpecs() const
{
   return numNcSpecs_;
}

//----------------------------------------------------------------

bool LargeNcSpecManager::isDone() const
{
   return done_;
}

//----------------------------------------------------------------

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

