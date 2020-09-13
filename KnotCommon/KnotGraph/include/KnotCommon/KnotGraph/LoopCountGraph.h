//----------------------------------------------------------------------
//
//     Graph type used for checking knot admission.
//
//     Bob Tuzun
//

#pragma once

#include <vector>
#include <deque>

#include "KnotCommon/KnotGraph/I_LoopCountGraph.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Knot_Common::Graph {

class LoopCountGraph : public I_LoopCountGraph
{
   public:
      LoopCountGraph();
      LoopCountGraph(const std::vector<DT::VecInt32>& conwayPolyh);
      LoopCountGraph(const LoopCountGraph& rhs);
      LoopCountGraph& operator=(const LoopCountGraph& rhs);
      ~LoopCountGraph();

      virtual DT::Int32 numLoopsForCts(const DT::VecInt32& setOfCt);
      virtual bool admitsKnotForCts(const DT::VecInt32& setOfCt);

      enum class Direction { NW, NE, SE, SW, FakeDirection };

   private:
      DT::Int32 nodeNumFor(const std::vector<DT::VecInt32>& conwayPolyh,
                     DT::Int32 otherVertex, DT::Int32 v);
      DT::Int32 findFirstUnusedNode(const std::deque<bool>& used);
      DT::Int32 markLoopStartingFrom(DT::Int32 nodeNumStart,
                      std::deque<bool>& used);
      void fillInConnectionTableFrom(const DT::VecInt32& setOfCt);
      void setConnectionTypeForVertex(DT::Int32 v, DT::Int32 ct);

      DT::Int32 numVertices_;
      DT::Int32 maxVertexNum_;

      std::deque<bool> vertexNumIsUsed_;

      std::vector<DT::VecInt32> conTable_;
};

} // namespace Knot_Common::Graph

