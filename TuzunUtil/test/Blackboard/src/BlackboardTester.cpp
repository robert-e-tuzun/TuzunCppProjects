//--------------------------------------------------------------------
//
//     Test Blackboard class (implementation).
//
//     Bob Tuzun
//
//--------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <any>

#include "TuzunUtil/Blackboard.h"
#include "BlackboardTester.h"

#include "A.h"

namespace DT = Tuzun_Util::Datatypes;

//--------------------------------------------------------------------

BlackboardTester::BlackboardTester(
       std::shared_ptr<Tuzun_Util::I_Blackboard> blkbdPtr)
{
   init(blkbdPtr);

   std::any A_BO = blkbdPtr->getObject("A");
   std::shared_ptr<A> A_p = std::any_cast<std::shared_ptr<A> >(A_BO);

   i_ = A_p->getA();
}

//--------------------------------------------------------------------

void BlackboardTester::init(std::shared_ptr<Tuzun_Util::I_Blackboard> blkbdPtr)
{
   blkbdPtr->initialize();

   std::shared_ptr<A> aObject = std::make_shared<A>();
   DT::String s = "A";
   blkbdPtr->addObject(aObject, s);
}

//--------------------------------------------------------------------

DT::Int32 BlackboardTester::get_i() const
{
   return i_;
}

