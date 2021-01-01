//----------------------------------------------------------------
//
//     Partition builder for partial knot specs (implementation).
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

#include "MathCommon/integerFactorsOf.h"

#include "CombinCommon/KComposition.h"
#include "CombinCommon/findCompositionsWithFilter.h"
#include "JonesConjecNonAlg/PartialKnotSpec/PartitionBuilder.h"

#include "JonesConjecNonAlg/BlkbdJonesConjNonAlg/BlkbdRunParamsNonAlg.h"
#include "JonesConjecNonAlg/BlkbdJonesConjNonAlg/GetPointerRunParamsNonAlg.h"

#include "JonesConjecNonAlg/PartialKnotSpec/RepresentativeChecker.h"

namespace DT = Tuzun_Util::Datatypes;
namespace JCB = Jones_Conjec_NonAlg::Blkbd_Jones_Conj_NonAlg;

namespace Jones_Conjec_NonAlg::Partial_Knot_Spec {

//----------------------------------------------------------------

PartitionBuilder::PartitionBuilder(
       std::shared_ptr<I_RepresentativeChecker> representativeChecker)
:representativeChecker_(representativeChecker)
{
}

//----------------------------------------------------------------

PartitionBuilder::~PartitionBuilder()
{
}

//----------------------------------------------------------------
//
//     Prepare this object for use.
//

void PartitionBuilder::prepareForUse(DT::Int32 numCrossings,
       DT::Int32 numVertices, DT::Int32 largestSmallNc,
       DT::Int32 largestNcInMemory, DT::Int32 ncMaxAttainable)
{
   numCrossings_ = numCrossings;
   numVertices_ = numVertices;
   largestSmallNc_ = largestSmallNc;
   largestNcInMemory_ = largestNcInMemory;
   ncMaxAttainable_ = ncMaxAttainable;

   binomCoeffTable_ = std::make_shared<Combin_Common::BinomCoeffTable>();

//     Possible partition periods are integer factors of numVertices_.
//     Erase the last factor, numVertices_, which has special treatment later.

   possiblePartitionPeriods_ = Math_Common::integerFactorsOf(numVertices_);
   possiblePartitionPeriods_.erase(possiblePartitionPeriods_.end()-1,
       possiblePartitionPeriods_.end());
}

//----------------------------------------------------------------

void PartitionBuilder::computePartitions()
{
//     Compute binomial coefficient table.
   binomCoeffTable_->init(numCrossings_-1);

//     Compute partitions with nc_i <= largestSmallNc.
   lowPartitions_.clear();
   computeLowPartitions();

//     Compute partitions with largestSmallNc < nc_i <= largestNcInMemory and
//     last nc = ncMax, where ncMax = max { nc_i }.
   inBetweenPartitions_.clear();
   inBetweenPartitionPeriods_.clear();
   if (largestSmallNc_ < largestNcInMemory_) {
      computeInBetweenPartitions();
      inBetweenPartitionPeriods_ =
           computePartitionPeriods(inBetweenPartitions_);
   }

//     Compute partitions with nc_max > largestNcInMemory and last nc = ncMax.
   highPartitions_.clear();
   highPartitionPeriods_.clear();
   if (largestNcInMemory_ < ncMaxAttainable_) {
      computeHighPartitions();
      for (const std::vector<DT::VecInt32>& h : highPartitions_) {
         DT::VecInt32 hPeriods = computePartitionPeriods(h);
         highPartitionPeriods_.push_back(hPeriods);
      }
   }
}

//----------------------------------------------------------------

void PartitionBuilder::computeLowPartitions()
{
//     Positive k-partitions of n with max element <= largestSmallNc_ are
//     bijective with k-compositions of (n-k) with max element <=
//     (largestSmallNc_-1).

//     Using largestSmallNc in lambda prevents compile error.
   DT::Int32 largestSmallNc = largestSmallNc_;
   lowPartitions_ = findCompositionsWithFilter(
         numVertices_, numCrossings_-numVertices_, binomCoeffTable_,
               [largestSmallNc](const DT::VecInt32& v)
               {
                  return (*std::max_element(v.begin(), v.end()) <=
                          (largestSmallNc-1));
               });

//     The bijection consists of adding/subtracting 1 to/from each entry.
//     To go from compositions to partitions, add.

   for (DT::VecInt32& p : lowPartitions_) {
      for (DT::Int32& x : p) {
         x++;
      }
   }
}

//----------------------------------------------------------------

void PartitionBuilder::computeInBetweenPartitions()
{
//     Let ncMax be the maximum element in { nc_i }.
//     Positive k-partitions of n with nc_k = ncMax and
//     largestSmallNc_ < ncMax <= largestNcInMemory_ are bijective with
//     k-compositions of (n-k) with nc_k = ncMax and
//     largestSmallNc_-1 < ncMax <= largestNcInMemory_-1.

//     Using largestSmallNc in lambda prevents compile error.
//     Similar for largestNcInMemory.
   DT::Int32 largestSmallNc = largestSmallNc_;
   DT::Int32 largestNcInMemory = largestNcInMemory_;
   inBetweenPartitions_ = findCompositionsWithFilter(
         numVertices_, numCrossings_-numVertices_, binomCoeffTable_,
               [largestSmallNc, largestNcInMemory](const DT::VecInt32& v)
               {
                  DT::Int32 ncMax = *std::max_element(v.begin(), v.end());
                  return ((v.back() == ncMax) && ((largestSmallNc-1) < ncMax) &&
                          (ncMax <= (largestNcInMemory-1)));
               });

//     Remove partitions that are not the representatives of their sets
//     of cyclic permutations.

   auto repChecker = representativeChecker_;
   inBetweenPartitions_.erase(
        std::remove_if(inBetweenPartitions_.begin(), inBetweenPartitions_.end(),
                    [repChecker](const DT::VecInt32& v)
                    {
                       return (! repChecker->isRepresentative(v));
                    }),
        inBetweenPartitions_.end());

//     The bijection consists of adding/subtracting 1 to/from each entry.
//     To go from compositions to partitions, add.

   for (DT::VecInt32& p : inBetweenPartitions_) {
      for (DT::Int32& x : p) {
         x++;
      }
   }
}

//----------------------------------------------------------------

DT::VecInt32 PartitionBuilder::computePartitionPeriods(
        const std::vector<DT::VecInt32>& partitions)
{
   DT::VecInt32 partitionPeriods;
   partitionPeriods.reserve(partitions.size());

   for (const DT::VecInt32& p : partitions) {
      partitionPeriods.push_back(period(p));
   }

   return DT::VecInt32(partitionPeriods);
}

//----------------------------------------------------------------

DT::Int32 PartitionBuilder::period(const DT::VecInt32& p)
{
   for (DT::Int32 x : possiblePartitionPeriods_) {
      DT::VecInt32 cyclicPermutation(p);
      std::rotate(cyclicPermutation.begin(), cyclicPermutation.begin()+x,
                  cyclicPermutation.end());
      if (cyclicPermutation == p)
         return x;
   }

   return numVertices_;
}

//----------------------------------------------------------------

void PartitionBuilder::computeHighPartitions()
{
   auto repChecker = representativeChecker_;

//     Positive k-partitions of n with nc_k > largestNcInMemory are bijective
//     with (k-1)-compositions of (n - nc_k - (k-1)).

   for (DT::Int32 ncLast=(largestNcInMemory_+1); ncLast<=ncMaxAttainable_;
                   ++ncLast) {
      std::vector<DT::VecInt32> compositions = findCompositionsWithFilter(
         numVertices_, numCrossings_-ncLast-numVertices_+1, binomCoeffTable_,
               [](const DT::VecInt32& v)
               {
                  return true;
               });

//     The bijection consists of adding/subtracting 1 to/from each entry,
//     then adding/removing the last element of the vector, which has the
//     value ncLast.
//     To go from compositions to partitions, add and add.

      std::vector<DT::VecInt32> partitions;
      partitions.reserve(compositions.size());

      for (DT::VecInt32& c : compositions) {
         for (DT::Int32& x : c) {
            x++;
         }
         c.push_back(ncLast);
         partitions.push_back(c);
      }

//     Remove partitions that are not the representatives of their sets
//     of cyclic permutations.

      partitions.erase(
          std::remove_if(partitions.begin(), partitions.end(),
                         [&repChecker](const DT::VecInt32& v)
                         {
                            return (! repChecker->isRepresentative(v));
                         }),
          partitions.end());

      highPartitions_.push_back(partitions);
   }
}

//----------------------------------------------------------------

std::vector<DT::VecInt32> PartitionBuilder::getLowPartitions() const
{
   return std::vector<DT::VecInt32>(lowPartitions_);
}

//----------------------------------------------------------------

std::vector<DT::VecInt32> PartitionBuilder::getInBetweenPartitions() const
{
   return std::vector<DT::VecInt32>(inBetweenPartitions_);
}

//----------------------------------------------------------------

std::vector<std::vector<DT::VecInt32> >
PartitionBuilder::getHighPartitions() const
{
   return std::vector<std::vector<DT::VecInt32> >(highPartitions_);
}

//----------------------------------------------------------------

DT::VecInt32 PartitionBuilder::getInBetweenPartitionPeriods() const
{
   return DT::VecInt32(inBetweenPartitionPeriods_);
}

//----------------------------------------------------------------

std::vector<DT::VecInt32> PartitionBuilder::getHighPartitionPeriods() const
{
   return std::vector<DT::VecInt32>(highPartitionPeriods_);
}

//----------------------------------------------------------------

} // namespace Jones_Conjec_NonAlg::Partial_Knot_Spec

