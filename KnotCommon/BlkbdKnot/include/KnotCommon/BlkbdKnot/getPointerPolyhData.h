//--------------------------------------------------------------
//
//     Get pointer to Conway polyhedron data.
//
//     Bob Tuzun
//

#pragma once

#include "TuzunUtil/I_Blackboard.h"

namespace Knot_Common::Blkbd_Knot {

std::shared_ptr<BlkbdPolyhData>
getPointerPolyhData(Tuzun_Util::BlackboardPtr blkbdPtr);

} // namespace Knot_Common::Blkbd_Knot

