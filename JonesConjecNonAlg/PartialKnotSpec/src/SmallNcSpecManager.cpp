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

#include "JonesConjecNonAlg/PartialKnotSpec/SmallNcSpecBuilder.h"
#include "JonesConjecNonAlg/PartialKnotSpec/SmallNcSpecManager.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

//----------------------------------------------------------------

SmallNcSpecManager::SmallNcSpecManager(
     std::shared_ptr<I_SmallNcSpecBuilder> smallNcSpecBuilder)
:smallNcSpecBuilder_(smallNcSpecBuilder)
{
}

//----------------------------------------------------------------

SmallNcSpecManager::~SmallNcSpecManager()
{
}

//----------------------------------------------------------------
//
//     Prepare this object for use.
//

void SmallNcSpecManager::prepareForUse(const NcSpecBuildInfo& info)
{
   smallNcSpecBuilder_->prepareForUse(info);
}

//----------------------------------------------------------------

void SmallNcSpecManager::findNextNcChunk()
{
   smallNcSpecBuilder_->findNextNcChunk();
   ncChunk_ = smallNcSpecBuilder_->getNcChunk();
   done_ = smallNcSpecBuilder_->isDone();
}

//----------------------------------------------------------------

std::vector<DT::VecInt32> SmallNcSpecManager::getNcChunk() const
{
   return ncChunk_;
}

//----------------------------------------------------------------

DT::Int32 SmallNcSpecManager::getCyclicPermutationShift() const
{
   return 0;
}

//----------------------------------------------------------------

DT::Int32 SmallNcSpecManager::getNumNcSpecs() const
{
   DT::Int32 numNcSpecs = ncChunk_.size();
   return numNcSpecs;
}

//----------------------------------------------------------------

bool SmallNcSpecManager::isDone() const
{
   return done_;
}

//----------------------------------------------------------------

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

