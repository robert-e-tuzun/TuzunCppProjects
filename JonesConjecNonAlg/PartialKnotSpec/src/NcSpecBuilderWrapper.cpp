//----------------------------------------------------------------
//
//     Wrapper for nc spec builder for partial knot specs (implementation).
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

#include "JonesConjecNonAlg/PartialKnotSpec/NcSpecBuilderWrapper.h"

#include "JonesConjecNonAlg/BlkbdJonesConjNonAlg/BlkbdRunParamsNonAlg.h"
#include "JonesConjecNonAlg/BlkbdJonesConjNonAlg/GetPointerRunParamsNonAlg.h"

namespace DT = Tuzun_Util::Datatypes;
namespace JCB = Jones_Conjec_NonAlg::Blkbd_Jones_Conj_NonAlg;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

//----------------------------------------------------------------

NcSpecBuilderWrapper::NcSpecBuilderWrapper(
       std::shared_ptr<I_NcSpecBuilder> ncSpecBuilder)
:ncSpecBuilder_(ncSpecBuilder)
{
}

//----------------------------------------------------------------

NcSpecBuilderWrapper::~NcSpecBuilderWrapper()
{
}

//----------------------------------------------------------------
//
//     Prepare this object for use.
//

void NcSpecBuilderWrapper::prepareForUse(
       std::shared_ptr<Tuzun_Util::I_Blackboard> blkbdPtr)
{
   blkbdPtr_ = blkbdPtr;

   initRunParams();

   ncSpecBuilder_->prepareForUse(numCrossings_, numVertices_,
             largestSmallNc_, largestNcInMemory_, ncMaxAttainable_,
             numNcPartitionsStoredMax_);
}

//----------------------------------------------------------------

void NcSpecBuilderWrapper::initRunParams()
{
//     Retrieve run parameters.
   std::shared_ptr<JCB::BlkbdRunParamsNonAlg> runParamI =
      JCB::GetPointerRunParamsNonAlg(blkbdPtr_);

   numCrossings_ = runParamI->getNumCrossings();
   numVertices_ = runParamI->getNumVertices();
   largestSmallNc_ = runParamI->getLargestSmallNc();
   largestNcInMemory_ = runParamI->getLargestNcInMemory();
   numNcPartitionsStoredMax_ = runParamI->getNumNcPartitionsStoredMax();
   ncMaxAttainable_ = runParamI->getNcMaxAttainable();
}

//----------------------------------------------------------------

std::vector<DT::VecInt32> NcSpecBuilderWrapper::getLowPartitions() const
{
   return ncSpecBuilder_->getLowPartitions();
}

//----------------------------------------------------------------

std::vector<DT::VecInt32>
NcSpecBuilderWrapper::getInBetweenPartitions() const
{
   return ncSpecBuilder_->getInBetweenPartitions();
}

//----------------------------------------------------------------

std::vector<std::vector<DT::VecInt32> >
NcSpecBuilderWrapper::getHighPartitions() const
{
   return ncSpecBuilder_->getHighPartitions();
}

//----------------------------------------------------------------

DT::VecInt32 NcSpecBuilderWrapper::getInBetweenPartitionPeriods() const
{
   return ncSpecBuilder_->getInBetweenPartitionPeriods();
}

//----------------------------------------------------------------

std::vector<DT::VecInt32>
NcSpecBuilderWrapper::getHighPartitionPeriods() const
{
   return ncSpecBuilder_->getHighPartitionPeriods();
}

//----------------------------------------------------------------

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

