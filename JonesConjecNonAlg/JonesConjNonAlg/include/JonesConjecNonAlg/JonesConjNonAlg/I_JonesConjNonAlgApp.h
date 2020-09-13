//--------------------------------------------------------------------
//
//     Application object for performing Jones conjecture calculations
//     (interface class).
//
//     Bob Tuzun
//

#pragma once

//#include <vector>
//#include <unordered_map>
//#include <memory>
//#include <any>

//#include "TuzunUtil/CppDatatypes.h"

//namespace DT = Tuzun_Util::Datatypes;

//using DepMap = std::unordered_map<DT::String, std::any>;

namespace Jones_Conjec_NonAlg {

namespace Jones_Conj_NonAlg {

class I_JonesConjNonAlgApp
{
   public:
      virtual ~I_JonesConjNonAlgApp() {};

      virtual void setupApplication() = 0;
      virtual void runApplication() = 0;

   private:
};

} // namespace Jones_Conj_NonAlg

} // namespace Jones_Conjec_NonAlg

