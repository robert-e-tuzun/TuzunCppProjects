//----------------------------------------------------------------------
//
//     Polyhedron manager.
//
//     Bob Tuzun
//

#pragma once

#include "JonesConjecNonAlg/Polyh/I_PolyhManager.h"

namespace DT = Tuzun_Util::Datatypes;
namespace KCIO = Knot_Common::Input_Output;
namespace KCCG = Knot_Common::Conway_Graph;

namespace Jones_Conjec_NonAlg::Polyh {

class PolyhManager : public I_PolyhManager
{
   public:
      PolyhManager(std::shared_ptr<KCIO::I_PolyhedronReader> polyhReader,
        std::shared_ptr<KCCG::I_ConwayLikeGraphFactory> conwayLikeGraphFactory);
      ~PolyhManager();

      virtual void
          prepareForUse(std::shared_ptr<Tuzun_Util::I_Blackboard> blkbdPtr);
      virtual DT::Int32 getNumPolyh();
      virtual bool shouldPerformCalcsForPolyhedron(DT::Int32 polyhNum);
      virtual void finishPreppingPolyhedron();

   private:
      void initRunParams();

      DT::Int32 curPolyhNum_;
      DT::Int32 numPolyh_;
      DT::Int32 numCrossings_;
      DT::Int32 numVertices_;

      DT::String dirPathPolyhData_;

      std::shared_ptr<Tuzun_Util::I_Blackboard> blkbdPtr_;
      std::shared_ptr<KCIO::I_PolyhedronReader> polyhReader_;
      std::shared_ptr<KCCG::I_ConwayLikeGraphFactory> conwayLikeGraphFactory_;
      std::shared_ptr<KCCG::I_ConwayLikeGraph> polyhGraph_;
};

} // namespace Jones_Conjec_NonAlg::Polyh

