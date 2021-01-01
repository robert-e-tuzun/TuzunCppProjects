//----------------------------------------------------------------
//
//     Factory for ConwayLikeGraph objects (implementation).
//
//     Bob Tuzun
//
//     This class is needed because an unknown number of ConwayLikeGraphs
//     are produced in some functions.
//

#include <iostream>
#include <vector>
#include <algorithm>

#include "KnotCommon/KnotGraph/ConwayLikeGraph.h"
#include "KnotCommon/KnotGraph/ConwayLikeGraphFactory.h"

namespace Knot_Common::Conway_Graph {

//----------------------------------------------------------------
//
//     Default constructor.
//

ConwayLikeGraphFactory::ConwayLikeGraphFactory()
{
}

//----------------------------------------------------------------
//
//     Destructor.
//

ConwayLikeGraphFactory::~ConwayLikeGraphFactory()
{
}

//----------------------------------------------------------------
//
//     Create ConwayLikeGraph specified by a connection table.
//

std::shared_ptr<I_ConwayLikeGraph> ConwayLikeGraphFactory::createGraph(
         const std::vector<DT::VecInt32>& conTableSimple)
{
   std::shared_ptr<I_ConwayLikeGraph> graphPtr =
         std::make_shared<ConwayLikeGraph>(conTableSimple);
   return graphPtr;
}

//----------------------------------------------------------------
//
//     Create ConwayLikeGraph specified by an undirected graph.
//

std::shared_ptr<I_ConwayLikeGraph> ConwayLikeGraphFactory::createGraph(
        const std::vector<Math_Common::Vertex>& graph)
{
   std::shared_ptr<I_ConwayLikeGraph> graphPtr =
         std::make_shared<ConwayLikeGraph>(graph);
   return graphPtr;
}

//----------------------------------------------------------------

} // namespace Knot_Common::Conway_Graph

