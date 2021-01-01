//------------------------------------------------------------
//
//     Undirected planar graph class (implementation).
//
//     The graph is not necessarily simple.
//
//     Bob Tuzun
//

#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <algorithm>

#include "MathCommon/UndirectedPlanarGraph.h"

namespace Math_Common {

//------------------------------------------------------------
//
//     Constructor for when a simple graph is specified by a connection
//     table.
//

UndirectedPlanarGraph::UndirectedPlanarGraph(
        const std::vector<DT::VecInt32>& conTableSimple)
:UndirectedGraph(conTableSimple)
{
//   setUndirectedPlanar(conTableSimple);
}

//------------------------------------------------------------
//
//     Constructor for when an undirected graph is specified.
//

UndirectedPlanarGraph::UndirectedPlanarGraph(const std::vector<Vertex>& graph)
:UndirectedGraph(graph)
{
//   setUndirectedPlanar(graph);
}

//------------------------------------------------------------
//
//     Default constructor (clear all structure).
//

UndirectedPlanarGraph::UndirectedPlanarGraph() : UndirectedGraph()
{
   numFaces_ = 0;
   faces_.clear();
}

//------------------------------------------------------------
//
//     Copy constructor.
//

UndirectedPlanarGraph::UndirectedPlanarGraph(const UndirectedPlanarGraph& rhs)
: UndirectedGraph(rhs)
{
   numFaces_ = rhs.numFaces_;
   faces_ = rhs.faces_;
}

//------------------------------------------------------------
//
//     Assignment operator.
//

UndirectedPlanarGraph& UndirectedPlanarGraph::operator=(
         const UndirectedPlanarGraph& rhs)
{
   UndirectedGraph::operator=(rhs);

   if (this != &rhs) {          // Handle self-assignment.
      numFaces_ = rhs.numFaces_;
      faces_ = rhs.faces_;
   }

   return *this;
}

//------------------------------------------------------------

UndirectedPlanarGraph::~UndirectedPlanarGraph()
{
   faces_.clear();
}

//------------------------------------------------------------

} // namespace Math_Common

