//------------------------------------------------------------
//
//     Bare-bones undirected graph class (implementation).
//
//     Bob Tuzun
//

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

#include "MathCommon/UndirectedGraph.h"

namespace Math_Common {

//------------------------------------------------------------
//
//     Constructor for when a simple graph is specified by a connection
//     table.
//

UndirectedGraph::UndirectedGraph(
       const std::vector<DT::VecInt32>& conTableSimple)
{
   set(conTableSimple);
}

//------------------------------------------------------------
//
//     Constructor for when an undirected graph is specified.
//

UndirectedGraph::UndirectedGraph(const std::vector<Vertex>& graph)
{
   set(graph);
}

//------------------------------------------------------------
//
//     Default constructor (clear all structure).
//

UndirectedGraph::UndirectedGraph()
{
   numVertices_ = 0;
   numEndpoints_ = 0;
   numEdges_ = 0;

   graph_.clear();
   edges_.clear();
}

//------------------------------------------------------------
//
//     Copy constructor.
//

UndirectedGraph::UndirectedGraph(const UndirectedGraph& rhs)
{
   numVertices_ = rhs.numVertices_;
   numEndpoints_ = rhs.numEndpoints_;
   numEdges_ = rhs.numEdges_;
   graph_ = rhs.graph_;
   edges_ = rhs.edges_;
}

//------------------------------------------------------------
//
//     Assignment operator.
//

UndirectedGraph& UndirectedGraph::operator=(const UndirectedGraph& rhs)
{
   if (this != &rhs) {        // Handle self-assignment.
      numVertices_ = rhs.numVertices_;
      numEndpoints_ = rhs.numEndpoints_;
      numEdges_ = rhs.numEdges_;
      graph_ = rhs.graph_;
      edges_ = rhs.edges_;
   }

   return *this;
}

//------------------------------------------------------------

UndirectedGraph::~UndirectedGraph()
{
   graph_.clear();
   edges_.clear();
}

//------------------------------------------------------------

void UndirectedGraph::set(const std::vector<DT::VecInt32>& conTableSimple)
{
   if (isValidSimpleConTable(conTableSimple))
      createGraphFromSimpleConTable(conTableSimple);

   else {
      std::cout << "Not a valid simple connection table." << std::endl;
      abort();
   }
}

//------------------------------------------------------------

void UndirectedGraph::set(const std::vector<Vertex>& graph)
{
   if (isValidGraph(graph)) {
      graph_ = graph;
      numVertices_ = graph_.size();
      numEndpoints_ = 0;
      for (Vertex vertex : graph_)
         numEndpoints_ += vertex.size();

      createEdgesForGraph();
   }

   else {
      std::cout << "Not a valid graph." << std::endl;
      abort();
   }
}

//------------------------------------------------------------

bool UndirectedGraph::isValidSimpleConTable(
       const std::vector<DT::VecInt32>& conTableSimple)
{
   return (isSimpleConTable(conTableSimple) &&
           isValidConTable(conTableSimple));
}

//------------------------------------------------------------

bool UndirectedGraph::isSimpleConTable(
       const std::vector<DT::VecInt32>& conTableSimple)
{
   for (DT::VecInt32 row : conTableSimple) {
      std::sort(row.begin(), row.end());

//     Check if, within sorted row, any two consecutive elements are the same.
      DT::Int32 length = row.size();
      for (DT::Int32 i=0; i<length-1; ++i)
         if (row[i] == row[i+1])
            return false;
   }

//     Check for loops (entry in row == rowNum).
   DT::Int32 rowNum = -1;
   for (const DT::VecInt32& row : conTableSimple) {
      rowNum++;

      for (DT::Int32 entry : row)
         if (entry == rowNum)
            return false;
   }

   return true;
}

//------------------------------------------------------------

bool UndirectedGraph::isValidConTable(
       const std::vector<DT::VecInt32>& conTableSimple)
{
   DT::Int32 rowNum = -1;
   for (DT::VecInt32 row : conTableSimple) {
      rowNum++;

      for (DT::Int32 j : row) {
//     Look within row j for occurrence of rowNum.
//     Since the graph is simple, the number of occurrences is 0 or 1.
          DT::VecInt32 row_j = conTableSimple[j];

          DT::Int32 numOccur = 0;
          for (DT::Int32 entry : row_j)
             if (entry == rowNum)
                numOccur++;

          if (numOccur == 0)
             return false;
      }
   }

   return true;
}

//------------------------------------------------------------

bool UndirectedGraph::isValidGraph(const std::vector<Vertex>& graph)
{
   DT::Int32 vertexNum = -1;
   for (Vertex vertex : graph) {
      vertexNum++;

      DT::Int32 loc = -1;
      for (Endpoint e : vertex) {
         loc++;

//     Make sure that endpt that is pointed to points back at original endpt.
         DT::Int32 eVertexNum = e.vertexNum_;
         DT::Int32 eLoc = e.locOnVertex_;
         Endpoint e2 = graph[eVertexNum][eLoc];
         if ((e2.vertexNum_ != vertexNum) || (e2.locOnVertex_ != loc))
            return false;

//     Also make sure that endpoint does not point to itself.
         if ((eVertexNum == vertexNum) && (eLoc == loc))
            return false;
      }
   }

   return true;
}

//------------------------------------------------------------

void UndirectedGraph::createGraphFromSimpleConTable(
       const std::vector<DT::VecInt32>& conTableSimple)
{
//     Create vertices with no connections.
   numVertices_ = conTableSimple.size();
   graph_.clear();

   numEndpoints_ = 0;
   for (int i=0; i<numVertices_; ++i) {
      DT::Int32 numEndpoints = conTableSimple[i].size();
      numEndpoints_ += numEndpoints;
      insertVertex(i, numEndpoints);
   }

//     Add edges.
   numEdges_ = 0;
   for (int i=0; i<numVertices_; ++i) {
      DT::VecInt32 row_i = conTableSimple[i];
      DT::Int32 length = row_i.size();

      for (DT::Int32 j=0; j<length; ++j) {
         Endpoint endpt1(i, j);

         DT::Int32 vNum = row_i[j];
         DT::VecInt32 row_v = conTableSimple[vNum];
         DT::Int32 loc = std::find(row_v.begin(), row_v.end(), i) -
                         row_v.begin();
         Endpoint endpt2(vNum, loc);

         if (endpt1 < endpt2)
            addEdge(endpt1, endpt2);
      }
   }
}

//------------------------------------------------------------

void UndirectedGraph::createEdgesForGraph()
{
   DT::Int32 vertexNum = -1;
   for (Vertex vertex : graph_) {
      vertexNum++;

      DT::Int32 loc = -1;
      for (Endpoint e : vertex) {
         loc++;
         Endpoint eOrig(vertexNum, loc);

//     Add edges in sorted order.
//     Create edge only if lesser relation holds, to avoid duplicate edges.
         if (eOrig < e)
            edges_.push_back(Edge(eOrig, e));
      }
   }

   numEdges_ = edges_.size();
}

//------------------------------------------------------------

void UndirectedGraph::insertVertex(DT::Int32 vertexNum, DT::Int32 numEndpoints)
{
   Endpoint e(-1, -1);
   Vertex v(numEndpoints, e);
   graph_.insert(graph_.begin()+vertexNum, v);
}

//------------------------------------------------------------

void UndirectedGraph::addEdge(const Endpoint& endpt1, const Endpoint& endpt2)
{
//     Set endpoints within graph_.
   DT::Int32 v1 = endpt1.vertexNum_;
   DT::Int32 loc1 = endpt1.locOnVertex_;
   DT::Int32 v2 = endpt2.vertexNum_;
   DT::Int32 loc2 = endpt2.locOnVertex_;
   graph_[v1][loc1] = endpt2;
   graph_[v2][loc2] = endpt1;

//     Insert edge, keeping edges_ array sorted.
   Edge e(endpt1, endpt2);
   auto it = std::find_if(edges_.begin(), edges_.end(),
        [&e](Edge& edge)->bool {return e < edge;});
   edges_.insert(it, e);

   numEdges_++;
}

//------------------------------------------------------------

/*
DT::Int32 UndirectedGraph::dijkstra(DT::Int32 v1, DT::Int32 v2)
{
   if (v1 == v2)
      return 0;

//     Start with only v1 marked as visited.
   std::deque<bool> visited;
   visited.assign(numVertices_, false);
   visited[v1] = true;

//     Iterate until v2 is visited or until no new vertices visited.
   DT::Int32 numVisited = 1;
   DT::Int32 dist = 0;
   do {
      DT::Int32 numPrevVisited = numVisited;

//     Update visited list.
      deque<bool> previouslyVisited = visited;
      for (DT::Int32 i=0; i<numVertices_; ++i)
         if (previouslyVisited[i])
            for (DT::Int32 j=0; j<(DT::Int32)conTable_[i].size(); ++j) {
               DT::Int32 v = conTable_[i][j];
               visited[v] = true;
            }

      numVisited = std::count(visited.begin(), visited.end(), true);
      if (numVisited != numPrevVisited)
         dist++;

//     Test, in order, whether v2 was visited, and whether no more
//     vertices were visited, which only occurs for disconnected graphs.
      if (visited[v2])
         return dist;

      if (numVisited == numPrevVisited)
         return -1;
   }
   while (true);

//     The following statement was added to prevent a compiler error message.
//     It should never be reached.
   return 0;
}
*/

//------------------------------------------------------------

} // namespace Math_Common

