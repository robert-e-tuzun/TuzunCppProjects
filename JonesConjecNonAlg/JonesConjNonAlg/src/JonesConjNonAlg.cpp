//---------------------------------------------------------------------
//
//     Perform Jones conjecture calculations using many new improvements.
//     Version 6.0.
//
//     Bob Tuzun
//

#include <iostream>
#include <memory>

#include "JonesConjecNonAlg/JonesConjNonAlg/JonesConjNonAlgCompRoot.h"

namespace JJ = Jones_Conjec_NonAlg::Jones_Conj_NonAlg;

int main(int argc, char **argv)
{
//     Build composition root for dependency injection and obtain application.

   std::shared_ptr<JJ::JonesConjNonAlgCompRoot> compRoot =
       std::make_shared<JJ::JonesConjNonAlgCompRoot>();

   std::shared_ptr<JJ::I_JonesConjNonAlgApp> app =
       compRoot->getCompositionRoot();

//     Set up and run the application.

   app->setupApplication();
   app->runApplication();
}

