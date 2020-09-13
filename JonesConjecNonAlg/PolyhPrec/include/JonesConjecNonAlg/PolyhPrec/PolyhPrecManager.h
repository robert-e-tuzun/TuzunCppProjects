//----------------------------------------------------------------------
//
//     Polyhedron precursor manager (declaration).
//
//     Bob Tuzun
//

#pragma once

#include "JonesConjecNonAlg/PolyhPrec/I_PolyhPrecManager.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Polyh_Prec {

class PolyhPrecManager : public I_PolyhPrecManager
{
   public:
      PolyhPrecManager();
      ~PolyhPrecManager();

      virtual void
          prepareForUse(std::shared_ptr<Tuzun_Util::I_Blackboard> blkbdPtr);
      virtual DT::Int32 getNumPolyh();

   private:
      void initRunParams();

      bool readVertexData_;

      DT::Int32 curPolyhNum_;
      DT::Int32 numPolyh_;
      DT::Int32 numVertices_;

      DT::String dirPathPolyhData_;

      std::shared_ptr<Tuzun_Util::I_Blackboard> blkbdPtr_;
};

} // namespace Jones_Conjec_NonAlg::Polyh_Prec

