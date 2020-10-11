//----------------------------------------------------------------
//
//     Partial knot specification manager (implementation).
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

#include "JonesConjecNonAlg/PolyhPrec/I_PolyhPrecManager.h"
//#include "KnotCommon/InputOutput/EmbedReader.h"
#include "JonesConjecNonAlg/PartialKnotSpec/PartialKnotSpecManager.h"

#include "JonesConjecNonAlg/BlkbdJonesConjNonAlg/BlkbdRunParamsNonAlg.h"
#include "JonesConjecNonAlg/BlkbdJonesConjNonAlg/GetPointerRunParamsNonAlg.h"

namespace DT = Tuzun_Util::Datatypes;
namespace JCB = Jones_Conjec_NonAlg::Blkbd_Jones_Conj_NonAlg;
namespace JCPo = Jones_Conjec_NonAlg::Polyh_Prec;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

//----------------------------------------------------------------

PartialKnotSpecManager::PartialKnotSpecManager(
        std::shared_ptr<I_PartitionBuilder> partitionBuilder,
        std::shared_ptr<I_CandidateCtSpecBuilder> candidateCtSpecBuilder,
        std::shared_ptr<JCPo::I_PolyhPrecManager> polyhPrecManager)
: partitionBuilder_(partitionBuilder),
  candidateCtSpecBuilder_(candidateCtSpecBuilder),
  polyhPrecManager_(polyhPrecManager)
{
   curPolyhNum_ = -1;
}

//----------------------------------------------------------------

PartialKnotSpecManager::~PartialKnotSpecManager()
{
}

//----------------------------------------------------------------
//
//     Prepare this object for use.
//

void PartialKnotSpecManager::prepareForUse(
        std::shared_ptr<Tuzun_Util::I_Blackboard> blkbdPtr)
{
   blkbdPtr_ = blkbdPtr;
   initRunParams();

   partitionBuilder_->prepareForUse(blkbdPtr_);
   polyhPrecManager_->prepareForUse(blkbdPtr_);
}

//----------------------------------------------------------------
//
//     Obtain run parameters from blackboard.
//

void PartialKnotSpecManager::initRunParams()
{
//     Retrieve run parameters.
   std::shared_ptr<JCB::BlkbdRunParamsNonAlg> runParamI =
      JCB::GetPointerRunParamsNonAlg(blkbdPtr_);

   numCrossings_ = runParamI->getNumCrossings();
   numVertices_ = runParamI->getNumVertices();
}

//----------------------------------------------------------------

void PartialKnotSpecManager::buildNcPartitions()
{
   partitionBuilder_->computePartitions();
   lowPartitions_ = partitionBuilder_->getLowPartitions();
   inBetweenPartitions_ = partitionBuilder_->getInBetweenPartitions();
   highPartitions_ = partitionBuilder_->getHighPartitions();
}

//----------------------------------------------------------------

void PartialKnotSpecManager::loopThroughPolyhedra()
{
//     Get number of Conway polyhedra.
   numPolyh_ = polyhPrecManager_->getNumPolyh();
}

//----------------------------------------------------------------

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

