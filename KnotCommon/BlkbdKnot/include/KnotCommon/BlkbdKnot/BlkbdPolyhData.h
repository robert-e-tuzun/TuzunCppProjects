//----------------------------------------------------------------
//
//     Conway polyhedron related blackboard object.
//
//     Bob Tuzun
//

#pragma once

#include "TuzunUtil/CppDatatypes.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Knot_Common::Blkbd_Knot {

class BlkbdPolyhData
{
   public:
      BlkbdPolyhData();

      void setConwayPolyhedron(
             const std::vector<DT::VecUInt32>& conwayPolyh_x);
      void setPolynNum(DT::Int32 polyhNum);
      void setPolyhAdmitsKnot(bool polyAdmitsKnot);
      std::vector<DT::VecUInt32> getConwayPolyhedron() const;
      DT::Int32 getPolyhNum() const;
      bool getPolyhAdmitsKnot() const;

   private:
      bool polyhAdmitsKnot_;

      DT::Int32 polyhNum_;

      std::vector<DT::VecUInt32> conwayPolyh_;
};

} // namespace Knot_Common::Blkbd_Knot

