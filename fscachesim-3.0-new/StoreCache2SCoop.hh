/*
  RCS:          $Header: /afs/cs.cmu.edu/user/tmwong/Cvs/fscachesim/StoreCacheSimple.hh,v 1.4 2002/02/15 18:17:30 tmwong Exp $
  Author:       T.M. Wong <tmwong+@cs.cmu.edu>
*/

#ifndef _STORECACHE2SCOOP_HH_
#define _STORECACHE2SCOOP_HH_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif /* HAVE_STDINT_H */
#include <stdio.h>

#include "Block.hh"
#include "Cache.hh"
#include "IORequest.hh"
#include "2QCache.hh"
#include "StoreCacheSimpleCoop.hh"

class StoreCache2SCoop : public StoreCacheSimpleCoop {

private:

  Cache cache;
  TQCache TQ;



private:
  // Copy constructors - declared private and never defined

  StoreCache2SCoop(const StoreCache2SCoop&);
  StoreCache2SCoop& operator=(const StoreCache2SCoop&);

  int blockGetCascade(const Block::block_t& inBlock, 
       IORequest::IORequestOp_t op, bool keep = true);
  void blockPutAtSegCascade(const Block::block_t& inBlock,
			    int inSeg, IORequest::IORequestOp_t op);

protected:
  virtual bool ReadFromCache(const IORequest& inIOReq,
			  const Block::block_t& inBlock);
  virtual void DemoteToCache(const IORequest& inIOReq,
			  const Block::block_t& inBlock);  


public:
  /**
   * Create a segmented adaptive cache with uniform size segments.
   *
   * @param inName A string name for the cache.
   * @param inBlockSize The size of each block, in bytes.
   * @param inSize The size of the total cache, in blocks.

   */
  StoreCache2SCoop(const char *inName,
		uint64_t inBlockSize,
		uint64_t inSize):
  StoreCacheSimpleCoop(inName, inBlockSize, inSize),
  cache(4*inSize/5),
  TQ(1*inSize/5) {;};



  /**
   * Destroy the cache.
   */
  ~StoreCache2SCoop() { ;} ;  

  // Statistics management


  virtual void statisticsShow() const;
};

#endif /* _STORECACHE2SCOOP_HH_ */
