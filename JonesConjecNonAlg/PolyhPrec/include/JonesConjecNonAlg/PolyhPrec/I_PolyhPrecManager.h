//----------------------------------------------------------------------
//
//     Polyhedron precursor manager (interface).
//
//     Bob Tuzun
//

#pragma once

#include <any>

//#include "TuzunUtil/CppDatatypes.h"
#include "TuzunUtil/I_Blackboard.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Polyh_Prec {

class I_PolyhPrecManager
{
   public:
      virtual ~I_PolyhPrecManager() {};

      virtual void prepareForUse(
          std::shared_ptr<Tuzun_Util::I_Blackboard> blkbdPtr) = 0;
      virtual DT::Int32 getNumPolyh() = 0;

   private:
};

} // namespace Jones_Conjec_NonAlg::Polyh_Prec

