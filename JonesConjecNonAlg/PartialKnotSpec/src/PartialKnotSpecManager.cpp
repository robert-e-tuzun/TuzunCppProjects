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

#include "JonesConjecNonAlg/Polyh/I_PolyhManager.h"
#include "JonesConjecNonAlg/PartialKnotSpec/PartialKnotSpecManager.h"

#include "JonesConjecNonAlg/BlkbdJonesConjNonAlg/BlkbdRunParamsNonAlg.h"
#include "JonesConjecNonAlg/BlkbdJonesConjNonAlg/GetPointerRunParamsNonAlg.h"

namespace DT = Tuzun_Util::Datatypes;
namespace JCB = Jones_Conjec_NonAlg::Blkbd_Jones_Conj_NonAlg;
namespace JCPo = Jones_Conjec_NonAlg::Polyh;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

//----------------------------------------------------------------

PartialKnotSpecManager::PartialKnotSpecManager(
        std::shared_ptr<JCPo::I_PolyhManager> polyhManager)
: polyhManager_(polyhManager)
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

   polyhManager_->prepareForUse(blkbdPtr_);
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

void PartialKnotSpecManager::loopThroughPolyhedra()
{
//     Get number of Conway polyhedra, then loop through them.
   numPolyh_ = polyhManager_->getNumPolyh();
   for (int i=0; i<numPolyh_; ++i) {
      if (polyhManager_->shouldPerformCalcsForPolyhedron(i)) {
         polyhManager_->finishPreppingPolyhedron();
         std::cout << "Polyhedron " << i << " calcs should proceed."
                   << std::endl;
      }
      else
         std::cout << "Polyhedron " << i << " calcs should not proceed."
                   << std::endl;
   }
}

//----------------------------------------------------------------

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

