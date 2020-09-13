//----------------------------------------------------------------
//
//     Class A (definition).
//
//     Bob Tuzun
//

#pragma once

#include "TuzunUtil/CppDatatypes.h"

namespace DT = Tuzun_Util::Datatypes;

class A {
   public:
      A();
      DT::Int32 getA();

   private:
      DT::Int32 i_;
};

