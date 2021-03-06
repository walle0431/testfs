#ifndef _PINDDOWNBATECHDEREGCACHE_HH_
#define _PINDDOWNBATECHDEREGCACHE_HH_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif /* HAVE_STDINT_H */
#include <stdio.h>

#include "MemoryRegion.hh"
#include "PindownCache.hh"


class PindownBatchDeRegCache : public PindownCache {


private:
  // Copy constructors - declared private and never defined

  PindownBatchDeRegCache(const PindownBatchDeRegCache&);
  PindownBatchDeRegCache& operator=(const PindownBatchDeRegCache&);

protected:

  virtual void EvictCache(uint64_t regsize); 

public:

  PindownBatchDeRegCache(uint64_t inCacheSize) :
    PindownCache(inCacheSize)
    { ; };


  ~PindownBatchDeRegCache() { ; };


};

#endif /* _PINDDOWNBATECHDEREGCACHE_HH_ */
