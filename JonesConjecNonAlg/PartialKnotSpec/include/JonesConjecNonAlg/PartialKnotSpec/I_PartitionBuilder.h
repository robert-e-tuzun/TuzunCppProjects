//----------------------------------------------------------------------
//
//     Partition builder for partial knot specs (interface class).
//
//     Bob Tuzun
//

#pragma once

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

class I_PartitionBuilder
{
   public:
      virtual ~I_PartitionBuilder() {};

//     Go through work of computing partitions.
      virtual void prepareForUse(DT::Int32 numCrossings,
            DT::Int32 numVertices, DT::Int32 ncLow, DT::Int32 ncMem,
            DT::Int32 ncMaxAttainable) = 0;
      virtual void computePartitions() = 0;

//     Retrieve results.
      virtual std::vector<DT::VecInt32> getLowPartitions() const = 0;
      virtual std::vector<DT::VecInt32> getInBetweenPartitions() const = 0;
      virtual std::vector<std::vector<DT::VecInt32> >
            getHighPartitions() const = 0;
      virtual DT::VecInt32 getInBetweenPartitionPeriods() const = 0;
      virtual std::vector<DT::VecInt32> getHighPartitionPeriods() const = 0;

   private:
};

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

