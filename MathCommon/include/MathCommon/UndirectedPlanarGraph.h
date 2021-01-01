//------------------------------------------------------------
//
//     Undirected planar graph class.
//
//     Bob Tuzun
//

#pragma once

#include <vector>

#include "MathCommon/UndirectedGraph.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Math_Common {

class UndirectedPlanarGraph : public UndirectedGraph
{
   public:
      using Face = std::vector<Endpoint>;

//     Constructors, copy constructor, assignment operator, and destructor.
      UndirectedPlanarGraph(const std::vector<DT::VecInt32>& conTableSimple);
      UndirectedPlanarGraph(const std::vector<Vertex>& graph);
      UndirectedPlanarGraph();
      UndirectedPlanarGraph(const UndirectedPlanarGraph& rhs);
      UndirectedPlanarGraph& operator=(const UndirectedPlanarGraph& rhs);
      ~UndirectedPlanarGraph();

   protected:
      int numFaces_;

      std::vector<Face> faces_;
};

} // namespace Math_Common

