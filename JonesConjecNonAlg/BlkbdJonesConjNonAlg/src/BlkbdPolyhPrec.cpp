//----------------------------------------------------------------
//
//     Polyhedron precursor object for JonesConjecNonAlg (implementation).
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

namespace Jones_Conjec_NonAlg::Blkbd_Jones_Conj_NonAlg {

//----------------------------------------------------------------

BlkbdPolyhPrec::BlkbdPolyhPrec()
{
}

//--------------------------------------------------------------

void BlkbdPolyhPrec::setNumVertices(DT::Int32 numVertices_x)
{
   numVertices_ = numVertices_x;
}

//--------------------------------------------------------------

void BlkbdPolyhPrec::setNumPolyh(DT::Int32 numPolyh_x)
{
   numPolyh_ = numPolyh_x;
}

//--------------------------------------------------------------

DT::Int32 BlkbdPolyhPrec::getNumVertices() const
{
   return numVertices_;
}

//--------------------------------------------------------------

DT::Int32 BlkbdPolyhPrec::getNumPolyh() const
{
   return numPolyh_;
}

//----------------------------------------------------------------

} // namespace Blkbd_Jones_Conj_NonAlg::Jones_Conjec_NonAlg

