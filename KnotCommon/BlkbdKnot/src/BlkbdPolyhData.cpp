//----------------------------------------------------------------
//
//     Conway polyhedron related blackboard object (implementation).
//
//     Bob Tuzun
//

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <any>

#include "KnotCommon/BlkbdKnot/BlkbdPolyhData.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Knot_Common::Blkbd_Knot {

//----------------------------------------------------------------

BlkbdPolyhData::BlkbdPolyhData()
{
}

//--------------------------------------------------------------

void BlkbdPolyhData::
setConwayPolyhedron(const std::vector<DT::VecUInt32>& conwayPolyh_x)
{
   conwayPolyh_ = conwayPolyh_x;
}

//--------------------------------------------------------------

void BlkbdPolyhData::setPolynNum(DT::Int32 polyhNum)
{
   polyhNum_ = polyhNum;
}

//--------------------------------------------------------------

void BlkbdPolyhData::setPolyhAdmitsKnot(bool polyhAdmitsKnot)
{
   polyhAdmitsKnot_ = polyhAdmitsKnot;
}

//--------------------------------------------------------------

std::vector<DT::VecUInt32> BlkbdPolyhData::getConwayPolyhedron() const
{
   return std::vector<DT::VecUInt32>(conwayPolyh_);
}

//--------------------------------------------------------------

DT::Int32 BlkbdPolyhData::getPolyhNum() const
{
   return polyhNum_;
}

//--------------------------------------------------------------

bool BlkbdPolyhData::getPolyhAdmitsKnot() const
{
   return polyhAdmitsKnot_;
}

//----------------------------------------------------------------

} // namespace Knot_Common::Blkbd_Knot

