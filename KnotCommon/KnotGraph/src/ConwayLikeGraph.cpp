//----------------------------------------------------------------
//
//     Graph type used for unmodified and modified Conway polyhedra
//     (implementation).
//
//     Bob Tuzun
//

#include <iostream>
#include <vector>
#include <algorithm>

#include "KnotCommon/KnotGraph/ConwayLikeGraph.h"

namespace Knot_Common::Conway_Graph {

//----------------------------------------------------------------
//
//     Constructor for when a simple graph is specified by a connection
//     table.
//

ConwayLikeGraph::ConwayLikeGraph(
         const std::vector<DT::VecInt32>& conTableSimple)
: UndirectedPlanarGraph(conTableSimple)
{
   CheckFor4Valent();
}

//----------------------------------------------------------------
//
//     Constructor for when an undirected graph is specified.
//

ConwayLikeGraph::ConwayLikeGraph(const std::vector<Math_Common::Vertex>& graph)
: UndirectedPlanarGraph(graph)
{
   CheckFor4Valent();
}

//----------------------------------------------------------------
//
//     Default constructor (clear all structure).
//

ConwayLikeGraph::ConwayLikeGraph()
{
}

//----------------------------------------------------------------

ConwayLikeGraph::ConwayLikeGraph(const ConwayLikeGraph& rhs)
{
}

//----------------------------------------------------------------

ConwayLikeGraph& ConwayLikeGraph::operator=(const ConwayLikeGraph& rhs)
{
   UndirectedPlanarGraph::operator=(rhs);

   if (this != &rhs) {         // Handle self-assignment.
   }

   return *this;
}

//----------------------------------------------------------------

ConwayLikeGraph::~ConwayLikeGraph()
{
}

//----------------------------------------------------------------

void ConwayLikeGraph::CheckFor4Valent()
{
   for (const Math_Common::Vertex& v : graph_) {
      if (v.size() != 4) {
         std::cout << "Not a 4-valent graph." << std::endl;
         abort();
      }
   }
}

//----------------------------------------------------------------

DT::Int32 ConwayLikeGraph::numLoopsForCts(const DT::VecInt32& setOfCt)
{
   DT::VecInt32 used(numEndpoints_, 0); // Mark all endpoints as unused.
   DT::Int32 numEndpointsUsed = 0;
   DT::Int32 numLoops = 0;
   do {
//     Traverse next loop ...
      DT::Int32 firstUnusedEndpointNum =
           std::find_if(used.begin(), used.end(), [](int i) {return i == 0;})
               - used.begin();
      DT::Int32 numEndpointsInLoop =
             markLoopStartingFrom(firstUnusedEndpointNum, used, setOfCt);
      numEndpointsUsed += numEndpointsInLoop;
      numLoops++;
   }
   while (numEndpointsUsed != numEndpoints_);
             // ... until all loops are traversed.

   return numLoops;
}

//----------------------------------------------------------------

DT::Int32
ConwayLikeGraph::markLoopStartingFrom(DT::Int32 firstUnusedEndpointNum,
         DT::VecInt32& used, const DT::VecInt32& setOfCt)
{
   DT::Int32 numEndpointsInLoop = 0;
   DT::Int32 index = 1;

   DT::Int32 nextEndpointNum = firstUnusedEndpointNum;
   do {
      DT::Int32 curEndpointNum = nextEndpointNum;
      used[curEndpointNum] = index++;

//     Find partner direction within vertex of current endpoint.
      DT::Int32 vertexNum = curEndpointNum/4;
      DT::Int32 direction = curEndpointNum%4;
      DT::Int32 ct = setOfCt[vertexNum];
      DT::Int32 partnerDirection = partners_Ct_Direction[ct-1][direction];
      DT::Int32 partnerEndpointNum = 4*vertexNum + partnerDirection;
      used[partnerEndpointNum] = index++;

//     Find endpoint outside of current vertex that connects to partner
//     endpoint.
      Math_Common::Endpoint nextEndpoint = graph_[vertexNum][partnerDirection];
      vertexNum = nextEndpoint.vertexNum_;
      direction = nextEndpoint.locOnVertex_;
      nextEndpointNum = 4*vertexNum + direction;

      numEndpointsInLoop += 2;  // 2 comes from cur and partner endpoints.
   }
   while (nextEndpointNum != firstUnusedEndpointNum);

   return numEndpointsInLoop;
}

//----------------------------------------------------------------

std::vector<ConwayLikeGraph::LoopType>
ConwayLikeGraph::loopsForCts(const DT::VecInt32& setOfCt)
{
   std::vector<LoopType> loops;

   DT::VecInt32 used(numEndpoints_, 0); // Mark all endpoints as unused.
   DT::Int32 numEndpointsUsed = 0;
   do {
//     Traverse next loop ...
      DT::Int32 firstUnusedEndpointNum =
           std::find_if(used.begin(), used.end(), [](int i) {return i == 0;})
               - used.begin();

      DT::VecInt32 usedPrev(used);
      DT::Int32 numEndpointsInLoop =
             markLoopStartingFrom(firstUnusedEndpointNum, used, setOfCt);
      LoopType loop = formLoopFrom(usedPrev, used);
      loops.push_back(loop);

      numEndpointsUsed += numEndpointsInLoop;
   }
   while (numEndpointsUsed != numEndpoints_);
             // ... until all loops are traversed.

   return std::vector<ConwayLikeGraph::LoopType>(loops);
}

//----------------------------------------------------------------

ConwayLikeGraph::LoopType ConwayLikeGraph::formLoopFrom(
     const DT::VecInt32& usedPrev, const DT::VecInt32& used)
{
//     diff[i] is non-zero only if endpoint i belongs to most recently
//     formed loop (i.e., in used, not usedPrev).
   DT::VecInt32 diff(used);
   for (int i=0; i<numEndpoints_; ++i)
      diff[i] -= usedPrev[i];

//     Arrange endpoints in loop in the order in which they were generated.
//     First, create a list of indexed endpoints in the loop.
   std::vector<IndexedEndpoint> indEndpts;
   for (int i=0; i<numEndpoints_; ++i)
      if (diff[i] != 0)
         indEndpts.push_back(IndexedEndpoint(diff[i], used[i]));

//     Now sort in the order of generation.
   std::sort(indEndpts.begin(), indEndpts.end());

//     Finally, create a vector of endpoints from the indexed endpoints.
   LoopType loop;
   for (IndexedEndpoint indEndpt : indEndpts)
      loop.push_back(
        Math_Common::Endpoint(indEndpt.vertexNum_, indEndpt.locOnVertex_));

   return LoopType(loop);
}

//----------------------------------------------------------------

bool ConwayLikeGraph::admitsKnotForCts(const DT::VecInt32& setOfCt)
{
   return (numLoopsForCts(setOfCt) == 1);
}

//----------------------------------------------------------------

} // namespace Knot_Common::Conway_Graph

