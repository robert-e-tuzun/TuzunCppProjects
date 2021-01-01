//--------------------------------------------------------------------
//
//     Initializer for JonesConj.  Read in parameters, set up blackboard,
//     and initialize data to be used in later computations (implementation).
//
//     Bob Tuzun
//

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <any>

#include "JonesConjecNonAlg/JonesConjNonAlg/InitializerNonAlg.h"
#include "JonesConjecNonAlg/BlkbdJonesConjNonAlg/BlkbdRunParamsNonAlg.h"
#include "JonesConjecNonAlg/BlkbdJonesConjNonAlg/GetPointerRunParamsNonAlg.h"

namespace JCB = Jones_Conjec_NonAlg::Blkbd_Jones_Conj_NonAlg;

namespace Jones_Conjec_NonAlg::Jones_Conj_NonAlg {

//--------------------------------------------------------------------

InitializerNonAlg::InitializerNonAlg(
    std::shared_ptr<Tuzun_Util::I_Blackboard> blkbdPtr)
: blkbdPtr_(blkbdPtr)
{
}

//--------------------------------------------------------------------

InitializerNonAlg::~InitializerNonAlg()
{
}

//--------------------------------------------------------------------
//
//     Add objects to blackboard.
//

void InitializerNonAlg::addObjectsToBlackboard()
{
   std::shared_ptr<JCB::BlkbdRunParamsNonAlg> runParamI =
      std::make_shared<JCB::BlkbdRunParamsNonAlg>();
   blkbdPtr_->addObject(runParamI, "RunParams");
}

//--------------------------------------------------------------------
//
//     Read in input parameters and initialize run parameter object.
//

void InitializerNonAlg::processInput()
{
   std::cin >> numCrossings_
            >> numVertices_
            >> dirPathPolyhData_
            >> largestSmallNc_
            >> largestNcInMemory_
            >> numNcPartitionsStoredMax_
           ;

   computeDerivedParameters();

   std::shared_ptr<JCB::BlkbdRunParamsNonAlg> runParamI =
      JCB::GetPointerRunParamsNonAlg(blkbdPtr_);
   runParamI->setNumCrossings(numCrossings_);
   runParamI->setNumVertices(numVertices_);
   runParamI->setDirPathPolyhData(dirPathPolyhData_);
   runParamI->setLargestSmallNc(largestSmallNc_);
   runParamI->setLargestNcInMemory(largestNcInMemory_);
   runParamI->setNumNcPartitionsStoredMax(numNcPartitionsStoredMax_);
   runParamI->setNcMaxAttainable(ncMaxAttainable_);
}

//--------------------------------------------------------------------
//
//     Compute derived parameters from input parameters.
//

void InitializerNonAlg::computeDerivedParameters()
{
//     For the 6-vertex polyhedron, at least two vertices must contain
//     tangles not of type 1 (and therefore, with more than 1 crossing)
//     in order to admit a knot.

   ncMaxAttainable_ = (numVertices_ > 6)?
                  numCrossings_ - numVertices_ + 1:
                  numCrossings_ - numVertices_;

//     The actual values for largestSmallNc_ and largestNcInMemory_ cannot
//     exceed the maximum attainable nc (see PartitionBuilder class for
//     more information).

   largestSmallNc_ = std::min(largestSmallNc_, ncMaxAttainable_);
   largestNcInMemory_ = std::min(largestNcInMemory_, ncMaxAttainable_);
}

//--------------------------------------------------------------------
//
//     Initialize objects that appear in blackboard.
//

void InitializerNonAlg::initializeObjectsInBlackboard()
{
}

//--------------------------------------------------------------------
//
//     Retrieve blackboard pointer.
//

Tuzun_Util::BlackboardPtr InitializerNonAlg::getBlackboard()
{
   return blkbdPtr_;
}

//--------------------------------------------------------------------

} // namespace Jones_Conjec_NonAlg::Jones_Conj_NonAlg

