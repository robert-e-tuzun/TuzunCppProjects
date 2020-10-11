//---------------------------------------------------------------
//
//     Class of speedometrically traversed vector.
//
//     Bob Tuzun
//

#pragma once

#include "TuzunUtil/CppDatatypes.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Combin_Common {

class Speedometric {
   public:
      Speedometric(const DT::VecInt32& minDigits_x,
                   const DT::VecInt32& maxDigits_x);
      Speedometric(const DT::VecInt32& maxDigits_x);
      Speedometric();
      Speedometric(const Speedometric& rhs);
      Speedometric& operator=(const Speedometric& rhs);
      ~Speedometric();

      void goToBeginning();
      void findNextSpeedo();
      void incrementDigit(int Digit);
      void setDigitsTo(const DT::VecInt32& digits_x);
      bool atLastSpeedo() const;
      DT::VecInt32 getCurDigits() const;

      std::string output() const;

   private:
      bool atBeginning_;

      int numDigits_;

      DT::VecInt32 minDigits_;
      DT::VecInt32 maxDigits_;
      DT::VecInt32 digits_;
};

} // namespace TuzunCombin

