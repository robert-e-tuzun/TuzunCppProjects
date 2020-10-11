//----------------------------------------------------------------------
//
//     Candidate ct spec builder for partial knot specs.
//
//     Bob Tuzun
//

#pragma once

#include "CombinCommon/Speedometric.h"

#include "JonesConjecNonAlg/PartialKnotSpec/I_CandidateCtSpecBuilder.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

class CandidateCtSpecBuilder : public I_CandidateCtSpecBuilder
{
   public:
      CandidateCtSpecBuilder();
      ~CandidateCtSpecBuilder();

      virtual void computeCandidateCtSpecs(
            const std::vector<DT::VecInt32>& partitions);
      virtual std::vector<DT::VecInt32> getCandidateCtSpecs() const;

   private:
      void replace4PlusWith3(const std::vector<DT::VecInt32>& partitions);
      void replace2Or3With23Or123();
      void setUpSpeedoForV(const DT::VecInt32& v);
      void addToCandidateCtSpecs();

      std::vector<DT::VecInt32> part3_;
      std::vector<DT::VecInt32> candidateCtSpecs_;

      Combin_Common::Speedometric speedo_;
};

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

