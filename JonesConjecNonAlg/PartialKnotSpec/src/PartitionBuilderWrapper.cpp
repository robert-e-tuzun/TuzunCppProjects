//----------------------------------------------------------------
//
//     Wrapper for partition builder for partial knot specs (implementation).
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

#include "JonesConjecNonAlg/PartialKnotSpec/PartitionBuilderWrapper.h"

#include "JonesConjecNonAlg/BlkbdJonesConjNonAlg/BlkbdRunParamsNonAlg.h"
#include "JonesConjecNonAlg/BlkbdJonesConjNonAlg/GetPointerRunParamsNonAlg.h"

namespace DT = Tuzun_Util::Datatypes;
namespace JCB = Jones_Conjec_NonAlg::Blkbd_Jones_Conj_NonAlg;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

//----------------------------------------------------------------

PartitionBuilderWrapper::PartitionBuilderWrapper(
       std::shared_ptr<I_PartitionBuilder> partitionBuilder)
:partitionBuilder_(partitionBuilder)
{
}

//----------------------------------------------------------------

PartitionBuilderWrapper::~PartitionBuilderWrapper()
{
}

//----------------------------------------------------------------
//
//     Prepare this object for use.
//

void PartitionBuilderWrapper::prepareForUse(
       std::shared_ptr<Tuzun_Util::I_Blackboard> blkbdPtr)
{
   blkbdPtr_ = blkbdPtr;

   initRunParams();

//     Compute partitions.

   partitionBuilder_->prepareForUse(numCrossings_, numVertices_,
                     largestSmallNc_, largestNcInMemory_, ncMaxAttainable_);
   partitionBuilder_->computePartitions();
}

//----------------------------------------------------------------

void PartitionBuilderWrapper::initRunParams()
{
//     Retrieve run parameters.
   std::shared_ptr<JCB::BlkbdRunParamsNonAlg> runParamI =
      JCB::GetPointerRunParamsNonAlg(blkbdPtr_);

   numCrossings_ = runParamI->getNumCrossings();
   numVertices_ = runParamI->getNumVertices();
   largestSmallNc_ = runParamI->getLargestSmallNc();
   largestNcInMemory_ = runParamI->getLargestNcInMemory();
   ncMaxAttainable_ = runParamI->getNcMaxAttainable();
}

//----------------------------------------------------------------

std::vector<DT::VecInt32> PartitionBuilderWrapper::getLowPartitions() const
{
   return partitionBuilder_->getLowPartitions();
}

//----------------------------------------------------------------

std::vector<DT::VecInt32>
PartitionBuilderWrapper::getInBetweenPartitions() const
{
   return partitionBuilder_->getInBetweenPartitions();
}

//----------------------------------------------------------------

std::vector<std::vector<DT::VecInt32> >
PartitionBuilderWrapper::getHighPartitions() const
{
   return partitionBuilder_->getHighPartitions();
}

//----------------------------------------------------------------

DT::VecInt32 PartitionBuilderWrapper::getInBetweenPartitionPeriods() const
{
   return partitionBuilder_->getInBetweenPartitionPeriods();
}

//----------------------------------------------------------------

std::vector<DT::VecInt32>
PartitionBuilderWrapper::getHighPartitionPeriods() const
{
   return partitionBuilder_->getHighPartitionPeriods();
}

//----------------------------------------------------------------

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

