//----------------------------------------------------------------------
//
//     Partition builder for partial knot specs (interface class).
//
//     Bob Tuzun
//

#pragma once

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

class I_NcSpecBuilder
{
   public:
      virtual ~I_NcSpecBuilder() {};

//     Go through work of computing partitions.
      virtual void prepareForUse(DT::Int32 numCrossings, DT::Int32 numVertices,
            DT::Int32 largestSmallNc, DT::Int32 largestNcInMemory,
            DT::Int32 ncMaxAttainable, DT::Int32 numNcPartitionsSoredMax,
            bool isDnSymmetric) = 0;
      virtual void computeNextSetOfNcPartitions() = 0;
      virtual DT::Int32 getCyclicPermutationShift() = 0;
      virtual std::vector<DT::VecInt32> getNcSpecs() = 0;
      virtual bool haveComputedNewNcSpecs() = 0;
      virtual bool isDoneComputingNewNcSpecs() = 0;

   private:
};

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

