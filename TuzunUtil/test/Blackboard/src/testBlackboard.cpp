//--------------------------------------------------------------------
//
//     Test Blackboard class.
//
//     Bob Tuzun
//
//--------------------------------------------------------------------

#define BOOST_TEST_MODULE testBlackboard
#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <any>

#include "TuzunUtil/Blackboard.h"
#include "BlackboardTester.h"

namespace DT = Tuzun_Util::Datatypes;

BOOST_AUTO_TEST_CASE( BlackboardRetrieve )
{
//     Inject blackboard into BlackboardTester object.
   Tuzun_Util::BlackboardPtr blkbdPtr =
          std::make_shared<Tuzun_Util::Blackboard>();
   BlackboardTester bt1(blkbdPtr);

//     BlackboardTester object returns its i value, which should be 2.
   DT::Int32 i = bt1.get_i();
   BOOST_TEST( i == 2 );
}

