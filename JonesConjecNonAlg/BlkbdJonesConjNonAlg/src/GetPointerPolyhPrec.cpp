//--------------------------------------------------------------
//
//     Get pointer to polyhedron precursors (implementation).
//
//     Bob Tuzun
//

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <any>

#include "JonesConjecNonAlg/BlkbdJonesConjNonAlg/BlkbdPolyhPrec.h"
#include "JonesConjecNonAlg/BlkbdJonesConjNonAlg/GetPointerPolyhPrec.h"

namespace Jones_Conjec_NonAlg::Blkbd_Jones_Conj_NonAlg {

std::shared_ptr<BlkbdPolyhPrec>
GetPointerRunParamsNonAlg(Tuzun_Util::BlackboardPtr blkbdPtr)
{
   std::any POLYH_BO = blkbdPtr->getObject("PolyhPrec");
   return std::any_cast<std::shared_ptr<BlkbdPolyhPrec> >(POLYH_BO);
}

} // namespace Jones_Conjec_NonAlg::Blkbd_Jones_Conj_NonAlg

