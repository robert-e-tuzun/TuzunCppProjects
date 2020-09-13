//----------------------------------------------------------------
//
//     Run parameters object for JonesConj (implementation).
//
//     Bob Tuzun
//

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <any>

#include "JonesConjecNonAlg/BlkbdJonesConjNonAlg/BlkbdRunParamsNonAlg.h"

namespace Jones_Conjec_NonAlg::Blkbd_Jones_Conj_NonAlg {

//----------------------------------------------------------------

BlkbdRunParamsNonAlg::BlkbdRunParamsNonAlg()
{
}

//--------------------------------------------------------------

void BlkbdRunParamsNonAlg::setNumCrossings(DT::Int32 numCrossings_x)
{
   numCrossings_ = numCrossings_x;
}

//--------------------------------------------------------------

void BlkbdRunParamsNonAlg::setNumVertices(DT::Int32 numVertices_x)
{
   numVertices_ = numVertices_x;
}

//--------------------------------------------------------------

void
BlkbdRunParamsNonAlg::setDirPathPolyhData(const DT::String& dirPathPolyhData_x)
{
   dirPathPolyhData_ = dirPathPolyhData_x;
}

//--------------------------------------------------------------

void BlkbdRunParamsNonAlg::setNcLow(DT::Int32 ncLow_x)
{
   ncLow_ = ncLow_x;
}

//--------------------------------------------------------------

void BlkbdRunParamsNonAlg::setNcMem(DT::Int32 ncMem_x)
{
   ncMem_ = ncMem_x;
}

//--------------------------------------------------------------

void BlkbdRunParamsNonAlg::setNcMaxAttainable(DT::Int32 ncMaxAttainable_x)
{
   ncMaxAttainable_ = ncMaxAttainable_x;
}

//--------------------------------------------------------------

DT::Int32 BlkbdRunParamsNonAlg::getNumCrossings() const
{
   return numCrossings_;
}

//--------------------------------------------------------------

DT::Int32 BlkbdRunParamsNonAlg::getNumVertices() const
{
   return numVertices_;
}

//--------------------------------------------------------------

DT::String BlkbdRunParamsNonAlg::getDirPathPolyhData() const
{
   return DT::String(dirPathPolyhData_);
}

//--------------------------------------------------------------

DT::Int32 BlkbdRunParamsNonAlg::getNcLow() const
{
   return ncLow_;
}

//--------------------------------------------------------------

DT::Int32 BlkbdRunParamsNonAlg::getNcMem() const
{
   return ncMem_;
}

//--------------------------------------------------------------

DT::Int32 BlkbdRunParamsNonAlg::getNcMaxAttainable() const
{
   return ncMaxAttainable_;
}

//----------------------------------------------------------------

} // namespace Jones_Conjec_NonAlg::Blkbd_Jones_Conj_NonAlg

