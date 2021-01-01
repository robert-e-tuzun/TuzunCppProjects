//----------------------------------------------------------------------
//
//     Factory for ConwayLikeGraph objects (interface).
//
//     Bob Tuzun
//

#pragma once

#include <vector>
#include <memory>

#include "TuzunUtil/CppDatatypes.h"
#include "KnotCommon/KnotGraph/I_ConwayLikeGraph.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Knot_Common::Conway_Graph {

class I_ConwayLikeGraphFactory
{
   public:
      virtual ~I_ConwayLikeGraphFactory() {};

      virtual std::shared_ptr<I_ConwayLikeGraph>
            createGraph(const std::vector<DT::VecInt32>& conTableSimple) = 0;
      virtual std::shared_ptr<I_ConwayLikeGraph>
            createGraph(const std::vector<Math_Common::Vertex>& graph) = 0;

   private:
};

} // namespace Knot_Common::Conway_Graph

