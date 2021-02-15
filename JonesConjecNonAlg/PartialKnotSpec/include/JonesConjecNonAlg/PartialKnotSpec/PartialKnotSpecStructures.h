//----------------------------------------------------------------------
//
//     Structures used for partial knot spec work.
//
//     Bob Tuzun
//

#pragma once

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

//     Structure containing run parameters for nc partition chunk generation.
struct NcPartitionChunkInfo
{
   DT::Int32 numCrossings_;
   DT::Int32 numVertices_;
   DT::Int32 largestSmallNc_;
   DT::Int32 maxChunkSize_;
   DT::Int32 maxNumAllowedNcEq1_;
   bool polyhedronIsDnSymmetric_;

   std::function<bool(const DT::VecInt32&)> filterFunction_;
   std::function<DT::VecInt32(const DT::VecInt32&)> transformationFunction_;
};

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

