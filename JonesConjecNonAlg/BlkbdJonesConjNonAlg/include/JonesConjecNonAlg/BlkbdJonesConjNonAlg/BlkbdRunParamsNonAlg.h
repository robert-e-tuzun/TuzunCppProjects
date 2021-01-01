//----------------------------------------------------------------
//
//     Run parameters object for JonesConj.
//
//     Bob Tuzun
//

#pragma once

#include "TuzunUtil/CppDatatypes.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Blkbd_Jones_Conj_NonAlg {

class BlkbdRunParamsNonAlg
{
   public:
      BlkbdRunParamsNonAlg();

      void setNumCrossings(DT::Int32 numCrossings_x);
      void setNumVertices(DT::Int32 numVertices_x);
      void setDirPathPolyhData(const DT::String& dirPathPolyhData_x);
      void setLargestSmallNc(DT::Int32 largestNcInMemory_x);
      void setLargestNcInMemory(DT::Int32 largestNcInMemory_x);
      void setNumNcPartitionsStoredMax(DT::Int32 numNcPartitionsStoredMax_x);
      void setNcMaxAttainable(DT::Int32 ncMaxAttainable_x);
      DT::Int32 getNumCrossings() const;
      DT::Int32 getNumVertices() const;
      DT::String getDirPathPolyhData() const;
      DT::Int32 getLargestSmallNc() const;
      DT::Int32 getLargestNcInMemory() const;
      DT::Int32 getNumNcPartitionsStoredMax() const;
      DT::Int32 getNcMaxAttainable() const;

   private:
      DT::Int32 largestSmallNc_;
      DT::Int32 largestNcInMemory_;
      DT::Int32 ncMaxAttainable_;
      DT::Int32 numCrossings_;
      DT::Int32 numNcPartitionsStoredMax_;
      DT::Int32 numVertices_;

      DT::String dirPathPolyhData_;
};

} // namespace Jones_Conjec_NonAlg::Blkbd_Jones_Conj_NonAlg

