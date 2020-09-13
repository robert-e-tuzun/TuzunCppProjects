//----------------------------------------------------------------
//
//     Graph type used for checking knot admission (implementation).
//
//     A vertex refers to a vertex of a Conway polyhedron.  Each vertex
//     has 4 nodes in directions 0, 1, 2, and 3, which refer to NW, NE,
//     SE, and SW.  Nodes are numbered 4v + d, where v is the vertex
//     number and d is the direction.
//
//     Each node has two connections, the first within the vertex and the
//     second to another vertex.
//
//     Bob Tuzun
//

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

#include "KnotCommon/KnotGraph/LoopCountGraph.h"

namespace Knot_Common::Graph {

//----------------------------------------------------------------

LoopCountGraph::LoopCountGraph()
{
}

//----------------------------------------------------------------

LoopCountGraph::LoopCountGraph(
         const std::vector<DT::VecInt32>& conwayPolyh)
{
   numVertices_ = conwayPolyh.size();
   maxVertexNum_ = numVertices_;
   vertexNumIsUsed_.assign(numVertices_, true);

//     Fill the part of the connection table it is possible to fill
//     (i.e., not springing from vertex connection types).

   DT::VecInt32 row = { -1, -1 };
   for (DT::Int32 v=0; v<4*numVertices_; ++v)
      conTable_.push_back(row);

   DT::Int32 nodeNum = -1;
   for (DT::Int32 v=0; v<numVertices_; ++v) {
      for (DT::Int32 d=static_cast<DT::Int32>(Direction::NW);
               d != static_cast<DT::Int32>(Direction::FakeDirection); ++d) {
         nodeNum++;
         DT::Int32 otherVertex = conwayPolyh[v][d];
         conTable_[nodeNum][1] = nodeNumFor(conwayPolyh, otherVertex, v);
      }
   }
}

//----------------------------------------------------------------

LoopCountGraph::LoopCountGraph(
         const LoopCountGraph& rhs)
{
   numVertices_ = rhs.numVertices_;
   maxVertexNum_ = rhs.maxVertexNum_;
   vertexNumIsUsed_ = rhs.vertexNumIsUsed_;
   conTable_ = rhs.conTable_;
}

//----------------------------------------------------------------

LoopCountGraph& LoopCountGraph::operator=(
         const LoopCountGraph& rhs)
{
   if (this != &rhs) {
      numVertices_ = rhs.numVertices_;
      maxVertexNum_ = rhs.maxVertexNum_;
      vertexNumIsUsed_ = rhs.vertexNumIsUsed_;
      conTable_ = rhs.conTable_;
   }

   return *this;
}

//----------------------------------------------------------------

LoopCountGraph::~LoopCountGraph()
{
}

//----------------------------------------------------------------

DT::Int32 LoopCountGraph::nodeNumFor(
               const std::vector<DT::VecInt32>& conwayPolyh,
                          DT::Int32 otherVertex, DT::Int32 v)
{
   for (DT::Int32 d=0; d<4; ++d)
      if (conwayPolyh[otherVertex][d] == v) {
         DT::Int32 nodeNum = 4*otherVertex + d;
         return nodeNum;
      }

//     Should never reach here.

   std::cout << "Badly formed connection table in "
             << "LoopCountGraph::nodeNumFor" << std::endl;
   abort();

   return -1; // Return statement suppresses error message.
}

//----------------------------------------------------------------

DT::Int32 LoopCountGraph::numLoopsForCts(const DT::VecInt32& setOfCt)
{
//     The following must be done in order to be able to traverse loops.
   fillInConnectionTableFrom(setOfCt);

   std::deque<bool> used(4*maxVertexNum_, false); // Mark all nodes as unused.
   DT::Int32 numNodesTotal = 4*numVertices_;
   DT::Int32 numNodesUsed = 0;
   DT::Int32 numLoops = 0;
   do {
//     Traverse next loop ...
      DT::Int32 nodeNum = findFirstUnusedNode(used);
      DT::Int32 numNodesInLoop = markLoopStartingFrom(nodeNum, used);
      numNodesUsed += numNodesInLoop;
      numLoops++;
   }
   while (numNodesUsed != numNodesTotal);
             // ... until all loops are traversed.

   return numLoops;
}

//----------------------------------------------------------------

DT::Int32
LoopCountGraph::findFirstUnusedNode(const std::deque<bool>& used)
{
   DT::Int32 length = used.size();
   for (DT::Int32 node=0; node<length; ++node) {
      DT::Int32 vertexNum = node/4;
      if ((! used[node]) && vertexNumIsUsed_[vertexNum])
         return node;
   }

//     Should not reach here.

   std::cout << "Should not reach this spot in "
             << "LoopCountGraph::findFirstUnusedNode" << std::endl;
   abort();

   return -1;  // Return statement suppresses error message.
}

//----------------------------------------------------------------

DT::Int32
LoopCountGraph::markLoopStartingFrom(DT::Int32 nodeNumStart,
         std::deque<bool>& used)
{
   DT::Int32 numNodesInLoop = 0;
   DT::Int32 nodeNumCur = nodeNumStart;
   do {
      used[nodeNumCur] = true;
      DT::Int32 nextNode = conTable_[nodeNumCur][0];  // 0 means connection
                                                      // within vertex.
      used[nextNode] = true;
      nodeNumCur = conTable_[nextNode][1];  // 1 means connection outside
                                            // of vertex.
      numNodesInLoop += 2;
   }
   while (nodeNumCur != nodeNumStart);

   return numNodesInLoop;
}

//----------------------------------------------------------------

void
LoopCountGraph::fillInConnectionTableFrom(const DT::VecInt32& setOfCt)
{
   for (DT::Int32 v=0; v<numVertices_; ++v)
      setConnectionTypeForVertex(v, setOfCt[v]);
}

//----------------------------------------------------------------

void LoopCountGraph::setConnectionTypeForVertex(DT::Int32 v,
            DT::Int32 ct)
{
   DT::Int32 vNW = 4*v + static_cast<DT::Int32>(Direction::NW);
   DT::Int32 vNE = 4*v + static_cast<DT::Int32>(Direction::NE);
   DT::Int32 vSE = 4*v + static_cast<DT::Int32>(Direction::SE);
   DT::Int32 vSW = 4*v + static_cast<DT::Int32>(Direction::SW);

   if (ct == 1) {
      conTable_[vNW][0] = vSE;
      conTable_[vNE][0] = vSW;
      conTable_[vSE][0] = vNW;
      conTable_[vSW][0] = vNE;
   }
   else if (ct == 2) {
      conTable_[vNW][0] = vNE;
      conTable_[vNE][0] = vNW;
      conTable_[vSE][0] = vSW;
      conTable_[vSW][0] = vSE;
   }
   else if (ct == 3) {
      conTable_[vNW][0] = vSW;
      conTable_[vNE][0] = vSE;
      conTable_[vSE][0] = vNE;
      conTable_[vSW][0] = vNW;
   }
}

//----------------------------------------------------------------

bool LoopCountGraph::admitsKnotForCts(const DT::VecInt32& setOfCt)
{
   return (numLoopsForCts(setOfCt) == 1);
}

//----------------------------------------------------------------

} // namespace Knot_Common::Graph

