//----------------------------------------------------------------------
//
//     Partition builder for partial knot specs.
//
//     Bob Tuzun
//

#pragma once

#include "TuzunUtil/I_Blackboard.h"
#include "CombinCommon/BinomCoeffTable.h"
#include "JonesConjecNonAlg/PartialKnotSpec/I_RepresentativeChecker.h"
#include "JonesConjecNonAlg/PartialKnotSpec/I_PartitionBuilder.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

class PartitionBuilder : public I_PartitionBuilder
{
   public:
      PartitionBuilder(
            std::shared_ptr<I_RepresentativeChecker> representativeChecker);
      ~PartitionBuilder();

      virtual void prepareForUse(
            std::shared_ptr<Tuzun_Util::I_Blackboard> blkbdPtr);
      virtual void computePartitions();
      virtual std::vector<DT::VecInt32> getLowPartitions() const;
      virtual std::vector<DT::VecInt32> getInBetweenPartitions() const;
      virtual std::vector<std::vector<DT::VecInt32> > getHighPartitions() const;
      virtual DT::VecInt32 getInBetweenPartitionPeriods() const;
      virtual std::vector<DT::VecInt32> getHighPartitionPeriods() const;

   private:
      void initRunParams();
      void computePossiblePeriods();
      void computeBinomialCoefficientsUpTo(DT::Int32 nmax);
      void computeLowPartitions();
      void computeInBetweenPartitions();
      DT::VecInt32 computePartitionPeriods(const std::vector<DT::VecInt32>& p);
      DT::Int32 period(const DT::VecInt32& p);
      void computeHighPartitions();

      std::shared_ptr<Tuzun_Util::I_Blackboard> blkbdPtr_;
      std::shared_ptr<I_RepresentativeChecker> representativeChecker_;

      DT::Int32 ncLow_;
      DT::Int32 ncMem_;
      DT::Int32 ncMaxAttainable_;
      DT::Int32 numCrossings_;
      DT::Int32 numVertices_;

      DT::VecInt32 inBetweenPartitionPeriods_;
      DT::VecInt32 possiblePartitionPeriods_;

      std::vector<DT::VecInt32> highPartitionPeriods_;
      std::vector<DT::VecInt32> lowPartitions_;
      std::vector<DT::VecInt32> inBetweenPartitions_;

      std::vector<std::vector<DT::VecInt32> > highPartitions_;

      std::shared_ptr<Combin_Common::BinomCoeffTable> binomCoeffTable_;
};

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

