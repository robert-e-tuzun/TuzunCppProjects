//--------------------------------------------------------------
//
//     Get pointer to TuzunConjNonAlg run parameters.
//
//     Bob Tuzun
//

#pragma once

#include "TuzunUtil/Blackboard.h"

namespace Jones_Conjec_NonAlg::Blkbd_Jones_Conj_NonAlg {

std::shared_ptr<BlkbdRunParamsNonAlg>
GetPointerRunParamsNonAlg(Tuzun_Util::BlackboardPtr blkbdPtr);

} // namespace Jones_Conjec_NonAlg::Blkbd_Jones_Conj_NonAlg

