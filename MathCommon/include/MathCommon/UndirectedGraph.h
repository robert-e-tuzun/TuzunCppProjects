//------------------------------------------------------------
//
//     Bare-bones undirected graph class.
//
//     Bob Tuzun
//

#pragma once

#include <iostream>
#include <vector>
#include <functional>

#include "TuzunUtil/CppDatatypes.h"
#include "MathCommon/UndirectedGraphTypeDefs.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Math_Common {

class UndirectedGraph
{
   public:

//     Constructors, copy constructor, assignment operator, and destructor.
      UndirectedGraph(const std::vector<DT::VecInt32>& conTableSimple);
      UndirectedGraph(const std::vector<Vertex>& graph);
      UndirectedGraph();
      UndirectedGraph(const UndirectedGraph& rhs);
      UndirectedGraph& operator=(const UndirectedGraph& rhs);
      ~UndirectedGraph();

//     Setters.
      void set(const std::vector<DT::VecInt32>& conTableSimple);
      void set(const std::vector<Vertex>& conTable);

//     Primitive graph operations.
      void insertVertex(DT::Int32 vertexNum, DT::Int32 numEndpoints);
//      void removeVertex(DT::Int32 vertexNum);
//      void insertEndpoint(DT::Int32 vertexNum, DT::Int32 insertionLoc);
//      void removeEndpoint(DT::Int32 vertexNum, DT::Int32 removalLoc);
      void addEdge(const Endpoint& e1, const Endpoint& e2);
//      void removeEdge(const Endpoint& e1, const Endpoint& e2);
//      void removeEdge(DT::Int32 edgeNum);

/*
      DT::Int32 shortestPathLength(DT::Int32 v1, DT::Int32 v2);
      std::vector<DT::VecInt32> shortestPaths(DT::Int32 v1, DT::Int32 v2);
      DT::Int32 shortestPathLengthConstrained(DT::Int32 v1, DT::Int32 v2,
             std::function<bool(const DT::VecInt32&)> vertexConstraintFunction,
             std::function<bool(const DT::VecInt32&)> finalConstraintFunction);
      std::vector<DT::VecInt32> shortestPathsConstrained(DT::Int32 v1,
                   DT::Int32 v2,
             std::function<bool(const DT::VecInt32&)> vertexConstraintFunction,
             std::function<bool(const DT::VecInt32&)> finalConstraintFunction);
*/

   protected:
//     Checkers for validity.
      bool isValidSimpleConTable(
            const std::vector<DT::VecInt32>& conTableSimple);
      bool isSimpleConTable(const std::vector<DT::VecInt32>& conTableSimple);
      bool isValidConTable(const std::vector<DT::VecInt32>& conTableSimple);
      bool isValidGraph(const std::vector<Vertex>& graph);

//     Graph and edge set creation functions.
      void createGraphFromSimpleConTable(
            const std::vector<DT::VecInt32>& conTableSimple);
      void createEdgesForGraph();

      DT::Int32 numEdges_;
      DT::Int32 numEndpoints_;
      DT::Int32 numVertices_;

      std::vector<Vertex> graph_;
      std::vector<Edge> edges_;
};

} // namespace Math_Common

