/*
  RCS:          $Header: /afs/cs.cmu.edu/user/tmwong/Cvs/fscachesim/StoreRegCache.hh,v 1.3 2002/02/15 15:44:25 tmwong Exp $
  Author:       T.M. Wong <tmwong+@cs.cmu.edu>
*/

#ifndef _STOREREGCACHE_HH_
#define _STOREREGCACHE_HH_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include <list>
#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif /* HAVE_STDINT_H */
#include <stdio.h>


#include "IORequest.hh"
#include "Store.hh"
#include "RegCache.hh"
#include "PindownCache.hh"
#include "PindownBatchDeRegCache.hh"
#include "MRRCache.hh"
#include "MRROptCache.hh"
#include "MRRResortCache.hh"
#include "PindownResortCache.hh"
#include "RegSimpleCache.hh"
/**
 * Interface for finite block caches. Classes that inherit from
 * StoreRegCache must implement all abstract methods.

 */

  
class StoreRegCache : public Store {

private:



  // Copy constructors - declared private and never defined

  StoreRegCache(const StoreRegCache&);
  StoreRegCache& operator=(const StoreRegCache&);

  uint64_t size;
  RegCache *cache;
  double totaltime;  

public:


  StoreRegCache(const char *inName,
	     uint64_t inBlockSize,
             uint64_t inSize);



  ~StoreRegCache() {delete cache;};


  virtual bool IORequestDown(const IORequest& inIOReq);

  virtual void statisticsShow() const;

};

#endif /* _STOREREGCACHE_HH_ */
