//--------------------------------------------------------------------
//
//     Test KnotGraph class.
//
//     Bob Tuzun
//
//--------------------------------------------------------------------

#define BOOST_TEST_MODULE test_KnotGraph
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <vector>
#include <deque>
#include <string>

#include "KnotCommon/KnotGraph/LoopCountGraph.h"

namespace DT = Tuzun_Util::Datatypes;

using ConwayPolyh = std::vector<DT::VecInt32>;

struct F_KnotGraph {
   F_KnotGraph() {}
   ~F_KnotGraph() {}
};

//---------------------------------------------------------------------

ConwayPolyh getPolyhDesired(DT::Int32 numVertices)
{
   ConwayPolyh polyh;

   if (numVertices == 6) {
      polyh = {{4, 3, 1, 2},
               {0, 3, 5, 2},
               {4, 0, 1, 5},
               {0, 4, 5, 1},
               {5, 3, 0, 2},
               {1, 3, 4, 2}};
   }
   else if (numVertices == 8) {
      polyh = {{4, 2, 1, 3},
               {3, 0, 2, 5},
               {4, 6, 1, 0},
               {7, 0, 1, 5},
               {7, 6, 2, 0},
               {6, 7, 3, 1},
               {2, 4, 7, 5},
               {4, 3, 5, 6}};
   }

   return polyh;
}

//---------------------------------------------------------------------

BOOST_FIXTURE_TEST_SUITE( KnotGraph, F_KnotGraph )

//---------------------------------------------------------------------

BOOST_AUTO_TEST_CASE( correct6 )
{
   ConwayPolyh polyh = getPolyhDesired(6);

   Knot_Common::Graph::LoopCountGraph lcg(polyh);
   DT::VecInt32 setOfCt = { 1, 1, 1, 1, 1, 1 };
   DT::Int32 numLoops = lcg.numLoopsForCts(setOfCt);
   bool admitsKnot = lcg.admitsKnotForCts(setOfCt);

   BOOST_CHECK(numLoops == 3);
   BOOST_CHECK(admitsKnot == false);
}

//---------------------------------------------------------------------

BOOST_AUTO_TEST_CASE( correct8 )
{
   ConwayPolyh polyh = getPolyhDesired(8);

   Knot_Common::Graph::LoopCountGraph lcg(polyh);
   DT::VecInt32 setOfCt = { 1, 1, 1, 1, 1, 1, 1, 1 };
   DT::Int32 numLoops = lcg.numLoopsForCts(setOfCt);
   bool admitsKnot = lcg.admitsKnotForCts(setOfCt);

   BOOST_CHECK(numLoops == 1);
   BOOST_CHECK(admitsKnot == true);
}

//---------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE_END()

