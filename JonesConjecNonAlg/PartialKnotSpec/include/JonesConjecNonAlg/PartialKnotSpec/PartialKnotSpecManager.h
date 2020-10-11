//----------------------------------------------------------------------
//
//     Partial knot specification manager.
//
//     Bob Tuzun
//

#pragma once

#include "JonesConjecNonAlg/PolyhPrec/I_PolyhPrecManager.h"
#include "JonesConjecNonAlg/PartialKnotSpec/I_PartialKnotSpecManager.h"
#include "JonesConjecNonAlg/PartialKnotSpec/I_PartitionBuilder.h"
#include "JonesConjecNonAlg/PartialKnotSpec/I_CandidateCtSpecBuilder.h"

namespace DT = Tuzun_Util::Datatypes;
namespace JCPo = Jones_Conjec_NonAlg::Polyh_Prec;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

class PartialKnotSpecManager : public I_PartialKnotSpecManager
{
   public:
      PartialKnotSpecManager(
          std::shared_ptr<I_PartitionBuilder> partitionBuilder,
          std::shared_ptr<I_CandidateCtSpecBuilder> candidateCtSpecBuilder,
          std::shared_ptr<JCPo::I_PolyhPrecManager> polyhPrec);
      virtual ~PartialKnotSpecManager();

      virtual void prepareForUse(
           std::shared_ptr<Tuzun_Util::I_Blackboard> blkbdPtr);
      virtual void buildNcPartitions();
      virtual void loopThroughPolyhedra();

   private:
      void initRunParams();

      bool readVertexData_;

      DT::Int32 curPolyhNum_;
      DT::Int32 numCrossings_;
      DT::Int32 numPolyh_;
      DT::Int32 numVertices_;

      std::vector<DT::VecInt32> lowPartitions_;
      std::vector<DT::VecInt32> inBetweenPartitions_;
      std::vector<std::vector<DT::VecInt32> > highPartitions_;

      std::shared_ptr<Tuzun_Util::I_Blackboard> blkbdPtr_;
      std::shared_ptr<I_PartitionBuilder> partitionBuilder_;
      std::shared_ptr<I_CandidateCtSpecBuilder> candidateCtSpecBuilder_;
      std::shared_ptr<JCPo::I_PolyhPrecManager> polyhPrecManager_;
};

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec


