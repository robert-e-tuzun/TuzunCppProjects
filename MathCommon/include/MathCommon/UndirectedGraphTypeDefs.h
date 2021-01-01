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

namespace DT = Tuzun_Util::Datatypes;

namespace Math_Common {

struct Endpoint
{
   Endpoint(DT::Int32 vNum, DT::Int32 loc)
   : vertexNum_(vNum), locOnVertex_(loc)
   {}

   bool operator==(const Endpoint& rhs)
   {
      return ((vertexNum_ == rhs.vertexNum_) ||
              (locOnVertex_ == rhs.locOnVertex_));
   }

   bool operator<(const Endpoint& rhs)
   {
      return ((vertexNum_ < rhs.vertexNum_) ||
   ((vertexNum_ == rhs.vertexNum_) && (locOnVertex_ < rhs.locOnVertex_)));
   }

   DT::Int32 vertexNum_;
   DT::Int32 locOnVertex_;
};

struct Edge
{
   Edge(const Endpoint& e1, const Endpoint& e2)
   : endpt1_(e1), endpt2_(e2)
   {}

   bool operator<(Edge& rhs)
   {
      return ((endpt1_ < rhs.endpt1_) ||
              ((endpt1_ == rhs.endpt1_) && (endpt2_ < rhs.endpt2_)));
   }

   Endpoint endpt1_;
   Endpoint endpt2_;
};

using Vertex = std::vector<Endpoint>;

} // namespace Math_Common

