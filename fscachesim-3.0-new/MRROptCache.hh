#ifndef _MRROPTCACHE_HH_
#define _MRROPTCACHE_HH_

using namespace std;

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#define NDEBUG

#include <assert.h>
#include <list>
#include <map>
#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif /* HAVE_STDINT_H */
#include "MemoryRegion.hh"
#include "RegCache.hh"


class MRROptCache : public RegCache {


private:
  // Copy constructors - declared private and never defined

  MRROptCache(const MRROptCache&);
  MRROptCache& operator=(const MRROptCache&);

protected:
  virtual void CalcReg(RegCacheIndex::iterator& regionIter, 
                       const MemoryRegion::memory_region_t& inRegion, 
                       list<MemoryRegion::memory_region_t>& mr, 
                       uint64_t& regsize);

  virtual void EvictCache(uint64_t regsize); 

public:

  MRROptCache(uint64_t inCacheSize) :
    RegCache(inCacheSize)
    { ; };


  ~MRROptCache() { ; };


};

#endif /* _MRROPTCACHE_HH_ */
