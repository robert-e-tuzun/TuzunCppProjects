//----------------------------------------------------------------
//
//     Polyhedron manager (implementation).
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

#include "KnotCommon/InputOutput/PolyhedronReader.h"
#include "KnotCommon/KnotGraph/I_ConwayLikeGraph.h"
#include "KnotCommon/KnotGraph/I_ConwayLikeGraphFactory.h"

#include "JonesConjecNonAlg/BlkbdJonesConjNonAlg/BlkbdRunParamsNonAlg.h"
#include "JonesConjecNonAlg/BlkbdJonesConjNonAlg/GetPointerRunParamsNonAlg.h"

#include "JonesConjecNonAlg/Polyh/PolyhManager.h"

namespace DT = Tuzun_Util::Datatypes;
namespace JCB = Jones_Conjec_NonAlg::Blkbd_Jones_Conj_NonAlg;
namespace KCIO = Knot_Common::Input_Output;
namespace KCCG = Knot_Common::Conway_Graph;

namespace Jones_Conjec_NonAlg::Polyh {

//----------------------------------------------------------------

PolyhManager::PolyhManager(
       std::shared_ptr<KCIO::I_PolyhedronReader> polyhReader,
       std::shared_ptr<KCCG::I_ConwayLikeGraphFactory> conwayLikeGraphFactory)
:polyhReader_(polyhReader), conwayLikeGraphFactory_(conwayLikeGraphFactory)
{
   curPolyhNum_ = -1;
}

//----------------------------------------------------------------

PolyhManager::~PolyhManager()
{
}

//----------------------------------------------------------------

void PolyhManager::prepareForUse(
        std::shared_ptr<Tuzun_Util::I_Blackboard> blkbdPtr)
{
   blkbdPtr_ = blkbdPtr;

   initRunParams();

   polyhReader_->prepareForUse(numVertices_, dirPathPolyhData_);
}

//----------------------------------------------------------------

void PolyhManager::initRunParams()
{
//     Retrieve run parameters.
   std::shared_ptr<JCB::BlkbdRunParamsNonAlg> runParamI =
      JCB::GetPointerRunParamsNonAlg(blkbdPtr_);

   dirPathPolyhData_ = runParamI->getDirPathPolyhData();
   numCrossings_ = runParamI->getNumCrossings();
   numVertices_ = runParamI->getNumVertices();
}

//----------------------------------------------------------------

DT::Int32 PolyhManager::getNumPolyh()
{
   return polyhReader_->getNumPolyhedra();
}

//----------------------------------------------------------------
//
//     Check if further computations for the current Conway polyhedron
//     are warranted, i.e., the polyhedron cannot be mutated into a
//     graph with bigons AND given the numbers of crossings and vertices
//     the polyhedron admits knots.
//

bool PolyhManager::shouldPerformCalcsForPolyhedron(DT::Int32 polyhNum)
{
   bool noBigons = true;     // TODO: Implement reading the appropriate
                             // data file containing whether bigons are formed.
   if (noBigons) {
//     Build the Conway polyhedron graph.
      curPolyhNum_ = polyhNum;
      std::vector<DT::VecInt32> polyh = polyhReader_->getConTable(curPolyhNum_);
      polyhGraph_ = conwayLikeGraphFactory_->createGraph(polyh);

//     Check if knots are admitted;
      DT::VecInt32 setOfCt(numVertices_, 1);
      DT::Int32 numLoops = polyhGraph_->numLoopsForCts(setOfCt);
      bool polyhAdmitsKnots = (numLoops <= numCrossings_ - numVertices_ + 1);

//     TODO: If knots are admitted, store the graph in the polyhedron
//     blackboard element.

      return polyhAdmitsKnots;
   }

//     Conway polyhedron can be mutated into a graph with bigons.
   return false;
}

//----------------------------------------------------------------

bool PolyhManager::polyhAdmitsKnotsForCts(const DT::VecInt32& setOfCt)
{
   DT::Int32 numLoops = polyhGraph_->numLoopsForCts(setOfCt);
   return (numLoops == 1);
}

//----------------------------------------------------------------

void PolyhManager::finishPreppingPolyhedron()
{
//     TODO: Implement finishPreppingPolyhedron.
}

//----------------------------------------------------------------

bool PolyhManager::polyhedronHasDnSymmetry()
{
   return false;
//     TODO: Implement polyhedronHasDnSymmetry.
}

//----------------------------------------------------------------

} // namespace Jones_Conjec_NonAlg::Polyh

