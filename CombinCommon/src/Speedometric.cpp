//-------------------------------------------------------
//
//     Class of speedometrically traversed vector (implementation).
//     Note: no error checking for bad input.
//
//     Bob Tuzun
//

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

#include "CombinCommon/Speedometric.h"

namespace Combin_Common {

//-------------------------------------------------------

Speedometric::Speedometric(const DT::VecInt32& minDigits_x,
                           const DT::VecInt32& maxDigits_x)
:minDigits_(minDigits_x), maxDigits_(maxDigits_x)
{
   numDigits_ = maxDigits_.size();
   goToBeginning();
}

//-------------------------------------------------------

Speedometric::Speedometric(const DT::VecInt32& maxDigits_x)
:maxDigits_(maxDigits_x)
{
   numDigits_ = maxDigits_.size();
   minDigits_.assign(numDigits_, 0);

   goToBeginning();
}

//-------------------------------------------------------

Speedometric::Speedometric()
{
}

//-------------------------------------------------------
//
//     Copy constructor for deep copy.
//

Speedometric::Speedometric(const Speedometric& rhs)
{
   minDigits_ = rhs.minDigits_;
   maxDigits_ = rhs.maxDigits_;
   digits_ = rhs.digits_;

   numDigits_ = rhs.numDigits_;

   atBeginning_ = rhs.atBeginning_;
}

//-------------------------------------------------------

Speedometric& Speedometric::operator=(const Speedometric& rhs)
{
   if (this != &rhs) {
      minDigits_ = rhs.minDigits_;
      maxDigits_ = rhs.maxDigits_;
      digits_ = rhs.digits_;

      numDigits_ = rhs.numDigits_;

      atBeginning_ = rhs.atBeginning_;
   }

   return *this;
}

//-------------------------------------------------------

Speedometric::~Speedometric()
{
   minDigits_.clear();
   maxDigits_.clear();
   digits_.clear();
}

//-------------------------------------------------------

void Speedometric::goToBeginning()
{
   atBeginning_ = true;
}

//-------------------------------------------------------

void Speedometric::findNextSpeedo()
{
   if (atBeginning_) {
      digits_ = minDigits_;
      atBeginning_ = false;
   }
   else {
      digits_[numDigits_-1]++;

      for (int i=numDigits_-1; i>=1; i--)
         if (digits_[i] > maxDigits_[i]) {
            digits_[i] = minDigits_[i];
            digits_[i-1]++;
         }
   }
}

//-------------------------------------------------------

void Speedometric::incrementDigit(int digit)
{
//     If at beginning, set digits to their minimum values.

   if (atBeginning_) {
      digits_ = minDigits_;
      atBeginning_ = false;
   }

//     Increment desired digit and set later digits equal to their minDigits_.

   digits_[digit]++;
   for (int i=digit; i>=1; i--)
      if (digits_[i] > maxDigits_[i]) {
         digits_[i] = minDigits_[i];
         digits_[i-1]++;
      }

   for (int i=(digit+1); i<numDigits_; i++)
      digits_[i] = minDigits_[i];
}

//-------------------------------------------------------

void Speedometric::setDigitsTo(const DT::VecInt32& digits_x)
{
   digits_ = digits_x;
   atBeginning_ = false;
}

//-------------------------------------------------------

bool Speedometric::atLastSpeedo() const
{
   return (digits_ == maxDigits_);
}

//-------------------------------------------------------

DT::VecInt32 Speedometric::getCurDigits() const
{
   return DT::VecInt32(digits_);
}

//-------------------------------------------------------

std::string Speedometric::output() const
{
   std::stringstream s;
   for (int i=0; i<numDigits_; i++)
      s << " " << digits_[i];

   return s.str();
}

//-------------------------------------------------------

} // namespace Combin_Combin

