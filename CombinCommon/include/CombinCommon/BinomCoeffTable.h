//------------------------------------------------------------------
//
//     Compute and store binomial coefficients (definition).
//
//     Bob Tuzun
//

#pragma once

#include "TuzunUtil/CppDatatypes.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Combin_Common {

class BinomCoeffTable
{
   public:
      BinomCoeffTable();
      BinomCoeffTable(const BinomCoeffTable& rhs);
      BinomCoeffTable& operator=(const BinomCoeffTable& rhs);
      ~BinomCoeffTable();

      void init(DT::Int32 nmax_x);
      DT::Int32 getBinom(DT::Int32 n, DT::Int32 k);

   private:
      DT::Int32 nmax_;

      std::vector<DT::VecInt32> binom_;
};

} // namespace Combin_Common

