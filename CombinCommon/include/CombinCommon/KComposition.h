//------------------------------------------------------------------
//
//     Compute members of a sequence of k-compositions of n (definition).
//
//     Bob Tuzun
//

#pragma once

#include "TuzunUtil/CppDatatypes.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Combin_Common {

class KComposition
{
   public:
      KComposition();
      KComposition(const KComposition& rhs);
      KComposition& operator=(const KComposition& rhs);
      ~KComposition();

      void init(DT::Int32 k_x, DT::Int32 n_x);
      void findNextComposition();
      DT::VecInt32 getComposition();
      bool atLastComposition();

//     The next two functions allow one to re-start a calculation somewhere
//     not at the beginning of a sequence of compositions.
      DT::VecInt32 getState();
      void setState(const DT::VecInt32& state);

   private:
      DT::Int32 k_;
      DT::Int32 n_;

      bool isFirstEntry_;
      bool isLastEntry_;

      DT::VecInt32 array_;
};

} // namespace Combin_Common

