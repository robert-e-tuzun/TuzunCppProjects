//---------------------------------------------------------------------
//
//     Application object for performing Jones conjecture calculations;
//     (implementation).
//
//     Bob Tuzun
//

#include <iostream>

#include "JonesConjecNonAlg/JonesConjNonAlg/JonesConjNonAlgApp.h"

namespace JCPa = Jones_Conjec_NonAlg::Partial_Knot_Spec;

namespace Jones_Conjec_NonAlg::Jones_Conj_NonAlg {

//--------------------------------------------------------------------

JonesConjNonAlgApp::JonesConjNonAlgApp(
     std::shared_ptr<I_InitializerNonAlg> initializerPtr,
     std::shared_ptr<JCPa::I_PartialKnotSpecManager> pksManagerPtr)
:initializerPtr_(initializerPtr),
 pksManagerPtr_(pksManagerPtr)
{
}

//--------------------------------------------------------------------

JonesConjNonAlgApp::~JonesConjNonAlgApp()
{
}

//--------------------------------------------------------------------

void JonesConjNonAlgApp::setupApplication()
{
//     Read in run parameters and initialize data structures to be used in
//     the calculations.

   initializerPtr_->addObjectsToBlackboard();
   initializerPtr_->processInput();
   initializerPtr_->initializeObjectsInBlackboard();
   blkbdPtr_ = initializerPtr_->getBlackboard();

//     Prepare partial knot spec manager for use.
   pksManagerPtr_->prepareForUse(blkbdPtr_);
}

//--------------------------------------------------------------------

void JonesConjNonAlgApp::runApplication()
{
//     Invoke the PartialKnotSpecManager, in which partial knot specifications
//     are built, and from which the calculation engine and its setup are
//     invoked.

   pksManagerPtr_->buildNcPartitions();
   pksManagerPtr_->loopThroughPolyhedra();
}

//--------------------------------------------------------------------

} // namespace Jones_Conjec_NonAlg::Jones_Conj_NonAlg

