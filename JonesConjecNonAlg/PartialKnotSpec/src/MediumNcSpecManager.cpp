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

#include "JonesConjecNonAlg/PartialKnotSpec/MediumNcSpecBuilder.h"
#include "JonesConjecNonAlg/PartialKnotSpec/MediumNcSpecManager.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

//----------------------------------------------------------------

MediumNcSpecManager::MediumNcSpecManager(
     std::shared_ptr<I_MediumNcSpecBuilder> mediumNcSpecBuilder)
:mediumNcSpecBuilder_(mediumNcSpecBuilder)
{
}

//----------------------------------------------------------------

MediumNcSpecManager::~MediumNcSpecManager()
{
}

//----------------------------------------------------------------
//
//     Prepare this object for use.
//

void MediumNcSpecManager::prepareForUse(const NcSpecBuildInfo& info)
{
   mediumNcSpecBuilder_->prepareForUse(info);
}

//----------------------------------------------------------------

void MediumNcSpecManager::findNextNcChunk()
{
   mediumNcSpecBuilder_->findNextNcChunk();
   ncChunk_ = mediumNcSpecBuilder_->getNcChunk();
   cyclicPermutationShift_ = mediumNcSpecBuilder_->getCyclicPermutationShift();
   done_ = mediumNcSpecBuilder_->isDone();
}

//----------------------------------------------------------------

std::vector<DT::VecInt32> MediumNcSpecManager::getNcChunk() const
{
   return ncChunk_;
}

//----------------------------------------------------------------

DT::Int32 MediumNcSpecManager::getCyclicPermutationShift() const
{
   return cyclicPermutationShift_;
}

//----------------------------------------------------------------

DT::Int32 MediumNcSpecManager::getNumNcSpecs() const
{
   DT::Int32 numNcSpecs = ncChunk_.size();
   return numNcSpecs;
}

//----------------------------------------------------------------

bool MediumNcSpecManager::isDone() const
{
   return done_;
}

//----------------------------------------------------------------

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

