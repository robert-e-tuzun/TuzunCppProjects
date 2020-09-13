//--------------------------------------------------------------
//
//     Get pointer to Conway polyhedron data (implementation).
//
//     Bob Tuzun
//

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <any>

using std::vector;
using std::string;
using std::map;

#include "KnotCommon/BlkbdKnot/BlkbdPolyhData.h"
#include "KnotCommon/BlkbdKnot/getPointerPolyhData.h"

namespace Knot_Common::Blkbd_Knot {

std::shared_ptr<BlkbdPolyhData>
getPointerPolyhData(Tuzun_Util::BlackboardPtr blkbdPtr)
{
   std::any POLYHDATA_BO = blkbdPtr->getObject("PolyhData");
   return std::any_cast<std::shared_ptr<BlkbdPolyhData> >(POLYHDATA_BO);
}

} // namespace Knot_Common::Blkbd_Knot

