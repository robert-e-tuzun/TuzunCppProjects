//----------------------------------------------------------------------
//
//     Small nc specification builder for partial knot specs.
//
//     Bob Tuzun
//

#pragma once

#include <functional>

#include "JonesConjecNonAlg/PartialKnotSpec/I_SmallNcSpecBuilder.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

class SmallNcSpecBuilder : public I_SmallNcSpecBuilder
{
   public:
      SmallNcSpecBuilder();
      ~SmallNcSpecBuilder();

      virtual void prepareForUse(const NcSpecBuildInfo& info);

//     Perform work of computing nc partitions.
      virtual void findNextNcChunk();

//     Retrieve results.
      virtual std::vector<DT::VecInt32> getNcChunk();
      virtual bool isDone();

   private:
      void setInitialState();
      void setLambdaFunctions();

      DT::Int32 largestSmallNc_;
      DT::Int32 maxAllowedNumNcEq1_;
      DT::Int32 numCrossings_;
      DT::Int32 numNcPartitionsStoredMax_;
      DT::Int32 numVertices_;

      bool done_;
      bool polyhedronIsDnSymmetric_;

      DT::VecInt32 prevComposition_;

      std::vector<DT::VecInt32> ncChunk_;

      std::function<bool(const DT::VecInt32&)> filterFunction_;
      std::function<DT::VecInt32(const DT::VecInt32&)> transformationFunction_;
};

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

