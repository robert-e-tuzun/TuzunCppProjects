//----------------------------------------------------------------------
//
//     Nc specification manager for partial knot specs (interface class).
//
//     Bob Tuzun
//

#pragma once

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

class I_NcSpecManager
{
   public:
      virtual void prepareForUse(const NcSpecBuildInfo& info) = 0;

//     Perform work of computing nc partitions.
      virtual void findNextNcChunk() = 0;

//     Retrieve results.
      virtual std::vector<DT::VecInt32> getNcChunk() const = 0;
      virtual DT::Int32 getCyclicPermutationShift() const = 0;
      virtual DT::Int32 getNumNcSpecs() const = 0;
      virtual DT::String getChunkSizeCategory() const = 0;
      virtual bool finished() const = 0;

   private:
};

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

