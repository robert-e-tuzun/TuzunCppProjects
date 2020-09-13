//--------------------------------------------------------------------
//
//     Test Blackboard class (definition).
//
//     Bob Tuzun
//
//--------------------------------------------------------------------

#pragma once

#include "TuzunUtil/I_Blackboard.h"

namespace DT = Tuzun_Util::Datatypes;

class BlackboardTester {
   public:
      BlackboardTester(std::shared_ptr<Tuzun_Util::I_Blackboard> blkbdPtr);
      void init(std::shared_ptr<Tuzun_Util::I_Blackboard> blkbdPtr);
      DT::Int32 get_i() const;

   private:
      DT::Int32 i_;
};

