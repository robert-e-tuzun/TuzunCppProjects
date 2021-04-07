//----------------------------------------------------------------
//
//     Candidate ct spec builder for partial knot specs (implementation).
//
//     Bob Tuzun
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <memory>
#include <algorithm>
#include <numeric>

#include "CombinCommon/Speedometric.h"

#include "JonesConjecNonAlg/PartialKnotSpec/CandidateCtSpecBuilder.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

//----------------------------------------------------------------

CandidateCtSpecBuilder::CandidateCtSpecBuilder()
{
}

//----------------------------------------------------------------

CandidateCtSpecBuilder::~CandidateCtSpecBuilder()
{
}

//----------------------------------------------------------------
//
//     Compute candidate ct specs given a set of partitions.
//

void CandidateCtSpecBuilder::computeCandidateCtSpecs(
       const std::vector<DT::VecInt32>& partitions)
{
   replace4PlusWith3(partitions);
   replace2Or3With23Or123();
}

//----------------------------------------------------------------
//
//     (a) Copy partitions vector.
//     (b) Replace all entries in copy that are 4+ with 3.
//     (c) Sort and remove duplicates.
//

void CandidateCtSpecBuilder::replace4PlusWith3(
         const std::vector<DT::VecInt32>& partitions)
{
   part3_ = partitions;
   for (auto& v : part3_) {
      for (DT::Int32& e : v)
         e = std::min(e, 3);
   }

   std::sort(part3_.begin(), part3_.end());
   part3_.erase(unique(part3_.begin(), part3_.end()), part3_.end());
}

//----------------------------------------------------------------
//
//     Replace all entries that are 2 with 2 or 3, and 3 with 1, 2, or 3.
//

void CandidateCtSpecBuilder::replace2Or3With23Or123()
{
//     (a) Determine the required length of such a vector.
   DT::Int32 lengthTot = 0;
   for (const auto& v : part3_) {
      DT::Int32 lengthV =
         std::accumulate(v.begin(), v.end(), 1, std::multiplies<DT::Int32>());
      lengthTot += lengthV;
   }

//     (b) Reserve a vector of int32 vectors of that length.
   candidateCtSpecs_.reserve(lengthTot);

//     (c) Populate the vector with candidate ct specs.
   for (const auto& v : part3_) {
      setUpSpeedoForV(v);
      addToCandidateCtSpecs();
   }

//     (d) Sort and remove duplicates.
   std::sort(candidateCtSpecs_.begin(), candidateCtSpecs_.end());
   candidateCtSpecs_.erase(
         unique(candidateCtSpecs_.begin(), candidateCtSpecs_.end()),
         candidateCtSpecs_.end());

//     Then clear intermediate vector.
   part3_.clear();
}

//----------------------------------------------------------------

void CandidateCtSpecBuilder::setUpSpeedoForV(const DT::VecInt32& v)
{
   DT::VecInt32 minDigitsForCt = { 1, 2, 1 };
   DT::VecInt32 maxDigitsForCt = { 1, 3, 3 };

   DT::VecInt32 minDigits;
   DT::VecInt32 maxDigits;

   for (DT::Int32 ct : v) {
      minDigits.push_back(minDigitsForCt[ct-1]);
      maxDigits.push_back(maxDigitsForCt[ct-1]);
   }

   speedo_ = Combin_Common::Speedometric(minDigits, maxDigits);
}

//----------------------------------------------------------------

void CandidateCtSpecBuilder::addToCandidateCtSpecs()
{
   speedo_.goToBeginning();

   bool done = false;
   do {
      speedo_.findNextSpeedo();
      DT::VecInt32 ctSpec = speedo_.getCurDigits();
      candidateCtSpecs_.push_back(ctSpec);
      done = speedo_.atLastSpeedo();
   }
   while (! done);
}

//----------------------------------------------------------------

std::vector<DT::VecInt32> CandidateCtSpecBuilder::getCandidateCtSpecs() const
{
   return std::vector<DT::VecInt32>(candidateCtSpecs_);
}

//----------------------------------------------------------------

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

