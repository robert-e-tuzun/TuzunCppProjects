//----------------------------------------------------------------------
//
//     Graph type used for unmodified and modified Conway polyhedra.
//
//     Bob Tuzun
//

#pragma once

#include <vector>

#include "KnotCommon/KnotGraph/I_ConwayLikeGraph.h"
#include "MathCommon/UndirectedPlanarGraph.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Knot_Common::Conway_Graph {

class ConwayLikeGraph : public Math_Common::UndirectedPlanarGraph,
                        public I_ConwayLikeGraph
{
   public:
      struct IndexedEndpoint
      {
         IndexedEndpoint(DT::Int32 index, DT::Int32 endpointNum)
         : index_(index)
         {
            vertexNum_ = endpointNum/4;
            locOnVertex_ = endpointNum%4;
         }

         bool operator<(const IndexedEndpoint& rhs)
         {
            return index_ < rhs.index_;
         }

         DT::Int32 vertexNum_;
         DT::Int32 locOnVertex_;
         DT::Int32 index_;
      };

//     Constructors, copy constructor, assignment operator, and destructor.
      ConwayLikeGraph(const std::vector<DT::VecInt32>& conTableSimple);
      ConwayLikeGraph(const std::vector<Math_Common::Vertex>& graph);
      ConwayLikeGraph();
      ConwayLikeGraph(const ConwayLikeGraph& rhs);
      ConwayLikeGraph& operator=(const ConwayLikeGraph& rhs);
      ~ConwayLikeGraph();

      virtual DT::Int32 numLoopsForCts(const DT::VecInt32& setOfCt);
      virtual std::vector<ConwayLikeGraph::LoopType>
                loopsForCts(const DT::VecInt32& setOfCt);
      virtual bool admitsKnotForCts(const DT::VecInt32& setOfCt);

   private:
      void CheckFor4Valent();
      DT::Int32 markLoopStartingFrom(DT::Int32 firstUnusedEndpointNum,
                      DT::VecInt32& used, const DT::VecInt32& setOfCt);
      LoopType formLoopFrom(const DT::VecInt32& usedPrev,
                            const DT::VecInt32& used);

      enum Direction { NW, NE, SE, SW};
      std::vector<DT::VecInt32> partners_Ct_Direction =
          { { SE, SW, NW, NE },
            { NE, NW, SW, SE },
            { SW, SE, NE, NW } };
};

} // namespace Knot_Common::Conway_Graph

