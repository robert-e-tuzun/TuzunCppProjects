//----------------------------------------------------------------------
//
//     Partition builder for partial knot specs.
//
//     Bob Tuzun
//

#pragma once

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

//     Perform work of computing partitions.
      virtual void prepareForUse(DT::Int32 numCrossings,
             DT::Int32 numVertices, DT::Int32 largestSmallNc,
             DT::Int32 largestNcInMemory, DT::Int32 ncMaxAttainable);
      virtual void computePartitions();

//     Retrieve the results.
      virtual std::vector<DT::VecInt32> getLowPartitions() const;
      virtual std::vector<DT::VecInt32> getInBetweenPartitions() const;
      virtual std::vector<std::vector<DT::VecInt32> > getHighPartitions() const;
      virtual DT::VecInt32 getInBetweenPartitionPeriods() const;
      virtual std::vector<DT::VecInt32> getHighPartitionPeriods() const;

   private:
//     Set up computations of partitions.
      void computePossiblePeriods();
      void computeBinomialCoefficientsUpTo(DT::Int32 nmax);

//     Compute various types of partitions and their periods.
      void computeLowPartitions();
      void computeInBetweenPartitions();
      DT::VecInt32 computePartitionPeriods(const std::vector<DT::VecInt32>& p);
      DT::Int32 period(const DT::VecInt32& p);
      void computeHighPartitions();

//     Checker for whether a partition is representative of its set of
//     cyclic permutations.
      std::shared_ptr<I_RepresentativeChecker> representativeChecker_;

      DT::Int32 largestSmallNc_;
      DT::Int32 largestNcInMemory_;
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

