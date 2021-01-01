//----------------------------------------------------------------------
//
//     Factory for ConwayLikeGraph objects.
//
//     Bob Tuzun
//

#pragma once

#include <vector>

#include "KnotCommon/KnotGraph/I_ConwayLikeGraphFactory.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Knot_Common::Conway_Graph {

class ConwayLikeGraphFactory : public I_ConwayLikeGraphFactory
{
   public:
//     Constructors, copy constructor, assignment operator, and destructor.
      ConwayLikeGraphFactory();
      ~ConwayLikeGraphFactory();

      std::shared_ptr<I_ConwayLikeGraph>
         createGraph(const std::vector<DT::VecInt32>& conTableSimple) override;
      std::shared_ptr<I_ConwayLikeGraph>
         createGraph(const std::vector<Math_Common::Vertex>& graph) override;

   private:
};

} // namespace Knot_Common::Conway_Graph

