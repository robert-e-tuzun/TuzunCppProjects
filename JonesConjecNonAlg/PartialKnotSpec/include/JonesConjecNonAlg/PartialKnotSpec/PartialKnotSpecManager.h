//----------------------------------------------------------------------
//
//     Partial knot specification manager.
//
//     Bob Tuzun
//

#pragma once

#include "JonesConjecNonAlg/Polyh/I_PolyhManager.h"
#include "JonesConjecNonAlg/PartialKnotSpec/I_PartialKnotSpecManager.h"

namespace DT = Tuzun_Util::Datatypes;
namespace JCPo = Jones_Conjec_NonAlg::Polyh;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

class PartialKnotSpecManager : public I_PartialKnotSpecManager
{
   public:
      PartialKnotSpecManager(
          std::shared_ptr<JCPo::I_PolyhManager> polyhManager);
      virtual ~PartialKnotSpecManager();

      virtual void prepareForUse(
           std::shared_ptr<Tuzun_Util::I_Blackboard> blkbdPtr);
      virtual void loopThroughPolyhedra();

   private:
      void initRunParams();

      DT::Int32 curPolyhNum_;
      DT::Int32 numCrossings_;
      DT::Int32 numPolyh_;
      DT::Int32 numVertices_;

      std::shared_ptr<Tuzun_Util::I_Blackboard> blkbdPtr_;
      std::shared_ptr<JCPo::I_PolyhManager> polyhManager_;
};

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec


