//----------------------------------------------------------------
//
//     Polyhedron precursor object for JonesConjecNonAlg.
//
//     Bob Tuzun
//

#pragma once

#include "TuzunUtil/CppDatatypes.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Blkbd_Jones_Conj_NonAlg {

class BlkbdPolyhPrec
{
   public:
      BlkbdPolyhPrec();

      void setNumVertices(DT::Int32 numVertices_x);
      void setNumPolyh(DT::Int32 numPolyh_x);
      DT::Int32 getNumVertices() const;
      DT::Int32 getNumPolyh() const;

   private:
      DT::Int32 numVertices_;
      DT::Int32 numPolyh_;
};

} // namespace Jones_Conjec_NonAlg::Blkbd_Jones_Conj_NonAlg

