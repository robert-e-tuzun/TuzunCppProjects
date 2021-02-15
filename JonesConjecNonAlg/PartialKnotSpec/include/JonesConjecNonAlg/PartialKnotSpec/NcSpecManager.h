//----------------------------------------------------------------------
//
//     Nc specification manager for partial knot specs.
//
//     Bob Tuzun
//

#pragma once

#include "JonesConjecNonAlg/PartialKnotSpec/SomeSizeNcSpecManager.h"
#include "JonesConjecNonAlg/PartialKnotSpec/I_NcSpecManager.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

class NcSpecManager : public I_NcSpecManager
{
   public:
      NcSpecManager(std::shared_ptr<SomeSizeNcSpecManager> smallNcSpecManager,
                    std::shared_ptr<SomeSizeNcSpecManager> mediumNcSpecManager,
                    std::shared_ptr<SomeSizeNcSpecManager> largeNcSpecManager);
      ~NcSpecManager();

      virtual void prepareForUse(const NcSpecBuildInfo& info);

//     Perform work of computing nc partitions.
      virtual void findNextNcChunk();

//     Retrieve results.
      virtual std::vector<DT::VecInt32> getNcChunk() const;
      virtual DT::Int32 getCyclicPermutationShift() const;
      virtual DT::Int32 getNumNcSpecs() const;
      virtual DT::String getChunkSizeCategory() const;
      virtual bool finished() const;

   private:
      void setInitialState();
      void goToNextStage();

      DT::Int32 chunkSizeIndex_;
      DT::Int32 cyclicPermutationShift_;
      DT::Int32 largestNcInMemory_;
      DT::Int32 largestSmallNc_;
      DT::Int32 ncMaxAttainable_;
      DT::Int32 numNcSpecs_;

      bool noLarge_;
      bool noMedium_;
      bool noSmall_;

      DT::String stage_;

      DT::VecString chunkSizes_;

      std::vector<DT::VecInt32> ncChunk_;

      std::shared_ptr<SomeSizeNcSpecManager> chunkManager_;
      std::shared_ptr<SomeSizeNcSpecManager> smallNcSpecManager_;
      std::shared_ptr<SomeSizeNcSpecManager> mediumNcSpecManager_;
      std::shared_ptr<SomeSizeNcSpecManager> largeNcSpecManager_;
};

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

