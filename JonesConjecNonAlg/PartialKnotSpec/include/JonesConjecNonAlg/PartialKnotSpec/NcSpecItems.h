//----------------------------------------------------------------------
//
//     Useful items for nc specification calculations.
//
//     Bob Tuzun
//

#pragma once

#include "TuzunUtil/CppDatatypes.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

struct NcSpecBuildInfo
{
   DT::Int32 largestNcInMemory_;
   DT::Int32 largestSmallNc_;
   DT::Int32 maxAllowedNumNcEq1_;
   DT::Int32 ncMaxAttainable_;
   DT::Int32 numCrossings_;
   DT::Int32 numNcPartitionsStoredMax_;
   DT::Int32 numVertices_;

   bool polyhedronIsDnSymmetric_;
};

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

