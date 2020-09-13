//----------------------------------------------------------------
//
//     Polyhedron precursor manager (implementation).
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

#include "KnotCommon/InputOutput/EmbedReader.h"
#include "KnotCommon/InputOutput/getNumPolyh.h"

#include "JonesConjecNonAlg/BlkbdJonesConjNonAlg/BlkbdRunParamsNonAlg.h"
#include "JonesConjecNonAlg/BlkbdJonesConjNonAlg/GetPointerRunParamsNonAlg.h"

#include "JonesConjecNonAlg/PolyhPrec/PolyhPrecManager.h"

namespace DT = Tuzun_Util::Datatypes;
namespace JCB = Jones_Conjec_NonAlg::Blkbd_Jones_Conj_NonAlg;
namespace JCPo = Jones_Conjec_NonAlg::Polyh_Prec;

namespace Jones_Conjec_NonAlg::Polyh_Prec {

//----------------------------------------------------------------

PolyhPrecManager::PolyhPrecManager()
{
}

//----------------------------------------------------------------

PolyhPrecManager::~PolyhPrecManager()
{
}

//----------------------------------------------------------------

void PolyhPrecManager::prepareForUse(
        std::shared_ptr<Tuzun_Util::I_Blackboard> blkbdPtr)
{
   blkbdPtr_ = blkbdPtr;

   initRunParams();
}

//----------------------------------------------------------------

void PolyhPrecManager::initRunParams()
{
//     Retrieve run parameters.
   std::shared_ptr<JCB::BlkbdRunParamsNonAlg> runParamI =
      JCB::GetPointerRunParamsNonAlg(blkbdPtr_);

   dirPathPolyhData_ = runParamI->getDirPathPolyhData();
   numVertices_ = runParamI->getNumVertices();
   
}

//----------------------------------------------------------------

DT::Int32 PolyhPrecManager::getNumPolyh()
{
   curPolyhNum_ = -1;
   DT::String prefix = "NumNonCSPolyh";
   numPolyh_ = Knot_Common::Polyh_IO::getNumPolyh(dirPathPolyhData_,
                    prefix, numVertices_);
   std::cout << numPolyh_ << std::endl;
   return numPolyh_;
}

//----------------------------------------------------------------

} // namespace Jones_Conjec_NonAlg::Polyh_Prec

