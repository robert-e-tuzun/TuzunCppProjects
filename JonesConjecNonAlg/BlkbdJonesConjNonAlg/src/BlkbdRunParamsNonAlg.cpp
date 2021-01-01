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

void BlkbdRunParamsNonAlg::setLargestSmallNc(DT::Int32 largestSmallNc_x)
{
   largestSmallNc_ = largestSmallNc_x;
}

//--------------------------------------------------------------

void BlkbdRunParamsNonAlg::setLargestNcInMemory(DT::Int32 largestNcInMemory_x)
{
   largestNcInMemory_ = largestNcInMemory_x;
}

//--------------------------------------------------------------

void BlkbdRunParamsNonAlg::setNumNcPartitionsStoredMax(
         DT::Int32 numNcPartitionsStoredMax_x)
{
   numNcPartitionsStoredMax_ = numNcPartitionsStoredMax_x;
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

DT::Int32 BlkbdRunParamsNonAlg::getLargestSmallNc() const
{
   return largestSmallNc_;
}

//--------------------------------------------------------------

DT::Int32 BlkbdRunParamsNonAlg::getLargestNcInMemory() const
{
   return largestNcInMemory_;
}

//--------------------------------------------------------------

DT::Int32 BlkbdRunParamsNonAlg::getNumNcPartitionsStoredMax() const
{
   return numNcPartitionsStoredMax_;
}

//--------------------------------------------------------------

DT::Int32 BlkbdRunParamsNonAlg::getNcMaxAttainable() const
{
   return ncMaxAttainable_;
}

//----------------------------------------------------------------

} // namespace Jones_Conjec_NonAlg::Blkbd_Jones_Conj_NonAlg

