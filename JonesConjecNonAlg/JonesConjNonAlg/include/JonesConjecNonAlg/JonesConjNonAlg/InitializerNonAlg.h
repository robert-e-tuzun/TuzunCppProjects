//--------------------------------------------------------------------
//
//     Initializer for JonesConjNonAlg.  Read in parameters, set up blackboard,
//     and initialize data to be used in later computations.
//
//     Bob Tuzun
//

#pragma once

#include "TuzunUtil/I_Blackboard.h"
#include "JonesConjecNonAlg/JonesConjNonAlg/I_InitializerNonAlg.h"

namespace DT = Tuzun_Util::Datatypes;

namespace Jones_Conjec_NonAlg::Jones_Conj_NonAlg {

class InitializerNonAlg : public I_InitializerNonAlg
{
   public:
      InitializerNonAlg(std::shared_ptr<Tuzun_Util::I_Blackboard> blkbdPtr);
      virtual ~InitializerNonAlg();

      void addObjectsToBlackboard();
      void processInput();
      void initializeObjectsInBlackboard();
      virtual Tuzun_Util::BlackboardPtr getBlackboard();

   private:
      void computeDerivedParameters();

      DT::Int32 numCrossings_;
      DT::Int32 numVertices_;
      DT::Int32 ncLow_;
      DT::Int32 ncMem_;
      DT::Int32 ncMaxAttainable_;

      DT::String dirPathPolyhData_;

      Tuzun_Util::BlackboardPtr blkbdPtr_;
};

} // namespace Jones_Conjec_NonAlg::Jones_Conj_NonAlg

