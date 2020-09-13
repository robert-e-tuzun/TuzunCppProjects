//------------------------------------------------------------------
//
//     Barest-bones generalized blackboard.
//
//     Bob Tuzun
//

#pragma once

#include <string>
#include <any>
#include <map>
#include <memory>

#include "TuzunUtil/CppDatatypes.h"
#include "TuzunUtil/I_Blackboard.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Tuzun_Util {

class Blackboard : public I_Blackboard {
   public:
      Blackboard();
      Blackboard(const Blackboard& rhs);
      Blackboard& operator=(const Blackboard& rhs);
      ~Blackboard();

      void initialize();
      void addObject(std::any blackboardObject, DT::String key);
      void removeObject(DT::String key);
      std::any getObject(DT::String key);

   private:
      std::map<DT::String, std::any> mapToObjects_;
};

} // namespace Tuzun_Util

