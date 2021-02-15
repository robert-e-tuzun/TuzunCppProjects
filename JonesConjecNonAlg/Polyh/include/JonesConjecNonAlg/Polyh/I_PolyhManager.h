//----------------------------------------------------------------------
//
//     Polyhedron precursor manager (interface).
//
//     Bob Tuzun
//

#pragma once

#include <any>

#include "TuzunUtil/I_Blackboard.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Polyh {

class I_PolyhManager
{
   public:
      virtual ~I_PolyhManager() {};

      virtual void prepareForUse(
          std::shared_ptr<Tuzun_Util::I_Blackboard> blkbdPtr) = 0;
      virtual DT::Int32 getNumPolyh() = 0;
      virtual bool shouldPerformCalcsForPolyhedron(DT::Int32 polyhNum) = 0;
      virtual void finishPreppingPolyhedron() = 0;
      virtual bool polyhedronHasDnSymmetry() = 0;

   private:
};

} // namespace Jones_Conjec_NonAlg::Polyh

