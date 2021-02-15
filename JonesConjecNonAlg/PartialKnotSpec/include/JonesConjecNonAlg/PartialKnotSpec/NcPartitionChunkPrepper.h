//----------------------------------------------------------------------
//
//     Nc partition chunk prepper for partial knot specs.
//     Not only prepares the chunks, but knows when to do so and what
//     the chunks should consist of.
//     Chunks differ according to the cyclic permutation shift of the
//     sequence of vertices.
//
//     Bob Tuzun
//

#pragma once

#include "JonesConjecNonAlg/PartialKnotSpec/I_NcPartitionChunkPrepper.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

class NcPartitionChunkPrepper : public I_NcPartitionChunkPrepper
{
   using FilterFuncType = std::function<bool(const DT::VecInt32&)>;
   using TransformFuncType = std::function<DT::VecInt32(const DT::VecInt32&)>;

   public:
      NcPartitionChunkPrepper();
      ~NcPartitionChunkPrepper();

//     Set up work of computing nc partitions.
      virtual void setParams(DT::Int32 numCrossings_, DT::Int32 numVertices,
             DT::Int32 maxChunkSize, DT::Int32 largestSmallNc,
             DT::Int32 maxCyclicPermutationShift);
      virtual void setFilterFunction(DT::Int32 kForComposition,
             DT::Int32 nForComposition, FilterFunctionType filterFunction);
      virtual void setTransformationFunction(
             TransformFuncType transformationFunction);
      virtual void setInitialStateAtBeginning();

//     Perform work of computing nc partitions.
      virtual void computeNextSetOfNcPartitions();

//     Retrieve results.
      virtual void getNcSpecs(DT::Int32& cyclicPermutationShift,
             std::vector<DT::VecInt32>& ncPartitions);
      virtual bool isDoneComputingNcSpecs();

   private:
      void computeCyclicPermutationShiftBoundaries();
      void prepareNcChunk();
      void findRanksIndexesAccordingToPeriodicity();
      DT::Int32 periodOf(const DT::VecInt32& p);

      DT::Int32 cyclicPermutationShift_;
      DT::Int32 kForComposition_;
      DT::Int32 nForComposition_;
      DT::Int32 largestSmallNc_;
      DT::Int32 maxChunkSize_;
      DT::Int32 maxNumAllowedNcEq1_;
      DT::Int32 numCrossings_;
      DT::Int32 numVertices_;

      bool chunkIsEmpty_;
      bool doneComputingNcSpecs_;

      DT::VecInt32 factorsOfNumVertices_;
      DT::VecInt32 partitionBoundaries_;
      DT::VecInt32 prevComposition_;

      deque<bool> shouldUpdatePartitionsChunk_;

      std::vector<DT::VecInt32> ncPartitionsChunk_;
      std::vector<DT::VecInt32> ranksIndexes_;

      FilterFuncType filterFunction_;
      TransformFuncType transformationFunction_;
};

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

