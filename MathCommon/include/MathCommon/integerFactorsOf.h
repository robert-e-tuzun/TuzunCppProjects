//------------------------------------------------------------------
//
//     Compute integer factors of a positive integer.
//
//     Bob Tuzun
//

#pragma once

#include <iostream>
#include <vector>

#include "TuzunUtil/CppDatatypes.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Math_Common {

//-------------------------------------------------------------------

DT::VecInt32 integerFactorsOf(DT::Int32 k);

//-------------------------------------------------------------------

} // namespace Math_Common

