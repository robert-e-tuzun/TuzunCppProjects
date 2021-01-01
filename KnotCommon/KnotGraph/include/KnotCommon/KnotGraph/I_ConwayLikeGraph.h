//----------------------------------------------------------------------
//
//     Graph type used for modified and unmodified Conway polyhedra
//     (interface).
//
//     Bob Tuzun
//

#pragma once

#include <vector>

#include "TuzunUtil/CppDatatypes.h"
#include "MathCommon/UndirectedGraphTypeDefs.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Knot_Common::Conway_Graph {

class I_ConwayLikeGraph
{
   public:
      using LoopType = std::vector<Math_Common::Endpoint>;

      virtual ~I_ConwayLikeGraph() {};

      virtual DT::Int32 numLoopsForCts(const DT::VecInt32& setOfCt) = 0;
      virtual std::vector<LoopType>
          loopsForCts(const DT::VecInt32& setOfCt) = 0;
      virtual bool admitsKnotForCts(const DT::VecInt32& setOfCt) = 0;

   private:
};

} // namespace Knot_Common::Conway_Graph

