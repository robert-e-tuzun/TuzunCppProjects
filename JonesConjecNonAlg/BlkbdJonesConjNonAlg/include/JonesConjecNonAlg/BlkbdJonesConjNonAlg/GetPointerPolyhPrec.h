//--------------------------------------------------------------
//
//     Get pointer to polyhedron precursors.
//
//     Bob Tuzun
//

#pragma once

#include "TuzunUtil/Blackboard.h"

namespace Jones_Conjec_NonAlg::Blkbd_Jones_Conj_NonAlg {

std::shared_ptr<BlkbdPolyhPrec>
GetPointerPolyhPrec(Tuzun_Util::BlackboardPtr blkbdPtr);

} // namespace Jones_Conjec_NonAlg::Blkbd_Jones_Conj_NonAlg

