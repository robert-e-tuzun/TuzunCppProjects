//--------------------------------------------------------------
//
//     Get pointer to JonesConjNonAlg run parameters (implementation).
//
//     Bob Tuzun
//

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <any>

#include "JonesConjecNonAlg/BlkbdJonesConjNonAlg/BlkbdRunParamsNonAlg.h"
#include "JonesConjecNonAlg/BlkbdJonesConjNonAlg/GetPointerRunParamsNonAlg.h"

namespace Jones_Conjec_NonAlg::Blkbd_Jones_Conj_NonAlg {

std::shared_ptr<BlkbdRunParamsNonAlg>
GetPointerRunParamsNonAlg(Tuzun_Util::BlackboardPtr blkbdPtr)
{
   std::any RUNP_BO = blkbdPtr->getObject("RunParams");
   return std::any_cast<std::shared_ptr<BlkbdRunParamsNonAlg> >(RUNP_BO);
}

} // namespace Jones_Conjec_NonAlg::Blkbd_Jones_Conj_NonAlg

