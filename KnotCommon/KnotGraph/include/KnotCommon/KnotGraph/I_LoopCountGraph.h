//----------------------------------------------------------------------
//
//     Graph type used for checking knot admission (interface).
//
//     Bob Tuzun
//

#pragma once

#include <vector>

#include "TuzunUtil/CppDatatypes.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Knot_Common::Graph {

class I_LoopCountGraph
{
   public:
      virtual ~I_LoopCountGraph() {};

      virtual DT::Int32 numLoopsForCts(const DT::VecInt32& setOfCt) = 0;
      virtual bool admitsKnotForCts(const DT::VecInt32& setOfCt) = 0;

   private:
};

} // namespace Knot_Common::Graph

