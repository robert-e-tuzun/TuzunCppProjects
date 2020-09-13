//------------------------------------------------------------------
//
//     Barest-bones generalized blackboard (interface).
//
//     Bob Tuzun
//

#pragma once

#include <string>
#include <any>
#include <map>

#include "TuzunUtil/CppDatatypes.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Tuzun_Util {

class I_Blackboard {
   public:
      virtual ~I_Blackboard() {};

      virtual void initialize() = 0;
      virtual void addObject(std::any blackboardObject, DT::String key) = 0;
      virtual void removeObject(DT::String key) = 0;
      virtual std::any getObject(DT::String key) = 0;

   private:
};

using BlackboardPtr = std::shared_ptr<I_Blackboard>;

} // namespace Tuzun_Util

