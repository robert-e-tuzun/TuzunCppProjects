//----------------------------------------------------------------------
//
//     Medium nc specification builder for partial knot specs.
//
//     Bob Tuzun
//

#pragma once

#include <functional>

#include "JonesConjecNonAlg/PartialKnotSpec/I_MediumNcSpecBuilder.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

class MediumNcSpecBuilder : public I_MediumNcSpecBuilder
{
   public:
      MediumNcSpecBuilder(std::shared_ptr<I_RepresentativeChecker> repChecker);
      ~MediumNcSpecBuilder();

      virtual void prepareForUse(const NcSpecBuildInfo& info);

//     Perform work of computing nc partitions.
      virtual void findNextNcChunk();

//     Retrieve results.
      virtual std::vector<DT::VecInt32> getNcChunk() const;
      virtual DT::Int32 getCyclicPermutationShift() const;
      virtual bool isDone() const;

   private:
      void setInitialState();
      DT::Int32 periodOf(const DT::VecInt32& p);
      void setLambdaFunctions();
      void findNextNcChunkIfExists();
      void findNextNcChunkGeneralSymmetry();
      DT::VecInt32 periodsThatOccur();
      void removeElementsWithPeriod(DT::Int32 period);

      DT::Int32 cyclicPermutationShift_;
      DT::Int32 largestSmallNc_;
      DT::Int32 largestNcInMemory_;
      DT::Int32 maxAllowedNumNcEq1_;
      DT::Int32 maxPeriod_;
      DT::Int32 numCrossings_;
      DT::Int32 numNcPartitionsStoredMax_;
      DT::Int32 numVertices_;

      bool atLastNcChunk_;
      bool done_;
      bool polyhedronIsDnSymmetric_;

      DT::VecInt32 periods_;
      DT::VecInt32 periodsThatOccur_;
      DT::VecInt32 prevComposition_;

      std::vector<DT::VecInt32> ncChunk_;

      std::shared_ptr<I_RepresentativeChecker> repChecker_;

      std::function<bool(const DT::VecInt32&)> filterFunction_;
      std::function<DT::VecInt32(const DT::VecInt32&)> transformationFunction_;
};

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

