//--------------------------------------------------------------------
//
//     Test EmbedReader class.
//
//     Bob Tuzun
//
//--------------------------------------------------------------------

#define BOOST_TEST_MODULE test_EmbedReader
#include <boost/test/included/unit_test.hpp>
using namespace boost::unit_test;

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "KnotCommon/InputOutput/getNumPolyh.h"
#include "KnotCommon/InputOutput/EmbedReader.h"

namespace DT = Tuzun_Util::Datatypes;

using ConwayPolyh = std::vector<DT::VecInt32>;

//---------------------------------------------------------------------

std::vector<ConwayPolyh> readPolyhsGot(DT::Int32 numVertices,
           DT::String dirPolyh)
{
   std::vector<ConwayPolyh> polyhs;

//     Find number of Conway polyhedra for given number of vertices.

   DT::String prefix = "NumNonCSPolyh";
   DT::Int32 numPolyh =
       Knot_Common::Input_Output::getNumPolyh(dirPolyh, prefix, numVertices);

//     Read in Conway polyhedra and return.

   Knot_Common::Input_Output::EmbedReader embedReader;
   embedReader.init(numVertices, dirPolyh);

   for (DT::Int32 n=0; n<numPolyh; ++n) {
      ConwayPolyh cp = embedReader.readNext();
      polyhs.push_back(cp);
   }

   return std::vector<ConwayPolyh>(polyhs);
}

//---------------------------------------------------------------------

std::vector<ConwayPolyh> readPolyhsExpected(int numVertices,
           DT::String dirPolyh, DT::String dirInput)
{
   std::vector<ConwayPolyh> polyhs;

//     Find number of Conway polyhedra for given number of vertices.

   DT::String prefix = "NumNonCSPolyh";
   DT::Int32 numPolyh =
       Knot_Common::Input_Output::getNumPolyh(dirPolyh, prefix, numVertices);

//     Read in Conway polyhedra and return.

   std::stringstream filename;
   filename << dirInput << "in." << numVertices;
   std::ifstream ex(filename.str().c_str());
   if (! ex.is_open()) std::cout << filename.str() << " not open." << std::endl;

   DT::VecInt32 row(4);
   for (DT::Int32 n=0; n<numPolyh; ++n) {
      ConwayPolyh cp;
      for (DT::Int32 i=0; i<numVertices; ++i) {
         ex >> row[0] >> row[1] >> row[2] >> row[3];
         cp.push_back(row);
      }

      polyhs.push_back(cp);
   }

   return std::vector<ConwayPolyh>(polyhs);
}

//---------------------------------------------------------------------

struct F_EmbedReader {
   F_EmbedReader() {}

   ~F_EmbedReader() {}

   void setup()
   {
       dirPathPolyhData = framework::master_test_suite().argv[1];
       dirPathFileInput = framework::master_test_suite().argv[2];
   }

   void teardown()
   {
   }

   static DT::String dirPathPolyhData;
   static DT::String dirPathFileInput;
};

DT::String F_EmbedReader::dirPathPolyhData = "";
DT::String F_EmbedReader::dirPathFileInput = "";

//---------------------------------------------------------------------

BOOST_TEST_GLOBAL_FIXTURE ( F_EmbedReader );

//---------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(correct6)
{
   DT::Int32 numVertices = 6;
   DT::String dirPolyh = F_EmbedReader::dirPathPolyhData;
   DT::String dirInput = F_EmbedReader::dirPathFileInput;
   std::vector<ConwayPolyh> polyhsGot =
          readPolyhsGot(numVertices, dirPolyh);
   std::vector<ConwayPolyh> polyhsExpected =
          readPolyhsExpected(numVertices, dirPolyh, dirInput);
   BOOST_CHECK( polyhsGot == polyhsExpected);
}

//---------------------------------------------------------------------

BOOST_AUTO_TEST_CASE( correct8 )
{
   DT::Int32 numVertices = 8;
   DT::String dirPolyh = F_EmbedReader::dirPathPolyhData;
   DT::String dirInput = F_EmbedReader::dirPathFileInput;
   std::vector<ConwayPolyh> polyhsGot =
          readPolyhsGot(numVertices, dirPolyh);
   std::vector<ConwayPolyh> polyhsExpected =
           readPolyhsExpected(numVertices, dirPolyh, dirInput);
   BOOST_CHECK( polyhsGot == polyhsExpected);
}

//---------------------------------------------------------------------

BOOST_AUTO_TEST_CASE( correct10 )
{
   DT::Int32 numVertices = 10;
   DT::String dirPolyh = F_EmbedReader::dirPathPolyhData;
   DT::String dirInput = F_EmbedReader::dirPathFileInput;
   std::vector<ConwayPolyh> polyhsGot =
          readPolyhsGot(numVertices, dirPolyh);
   std::vector<ConwayPolyh> polyhsExpected =
           readPolyhsExpected(numVertices, dirPolyh, dirInput);
   BOOST_CHECK( polyhsGot == polyhsExpected);

   Knot_Common::Input_Output::EmbedReader embedReader;
   embedReader.init(numVertices, dirPolyh);

   ConwayPolyh p2 = embedReader.readPolyh(2);
   BOOST_CHECK( polyhsGot[2] == p2);

   ConwayPolyh p1 = embedReader.readPolyh(1);
   BOOST_CHECK( polyhsGot[1] == p1);

   ConwayPolyh p0 = embedReader.readPolyh(0);
   BOOST_CHECK( polyhsGot[0] == p0);

   p2 = embedReader.readPolyh(2);
   BOOST_CHECK( polyhsGot[2] == p2);
}

