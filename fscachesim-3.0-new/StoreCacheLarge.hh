/*
  RCS:          $Header: /afs/cs.cmu.edu/user/tmwong/Cvs/fscachesim/StoreCacheLarge.hh,v 1.4 2002/02/15 18:17:30 tmwong Exp $
  Author:       T.M. Wong <tmwong+@cs.cmu.edu>
*/

#ifndef _StoreCacheLarge_HH_
#define _StoreCacheLarge_HH_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif /* HAVE_STDINT_H */
#include <stdio.h>

#include "Block.hh"
#include "SeqCache.hh"
#include "IORequest.hh"
#include "StoreCache.hh"

/**
 * Simple LRU/MRU block cache with support for demote operations.
 */
class StoreCacheLarge : public StoreCache {
public:


private:
  SeqCache cache;

  bool logRequestFlag;

private:
  // Copy constructors - declared private and never defined

  StoreCacheLarge(const StoreCacheLarge&);
  StoreCacheLarge& operator=(const StoreCacheLarge&);

protected:
  virtual void BlockCache(const IORequest& inIOReq,
			  const Block::block_t& inBlock,
			  list<IORequest>& outIOReqs);

public:
  // Constructors and destructors

  /**
   * Create a simple block cache.
   *
   * @param inName A string name for the cache.
   * @param inNextStore A lower-level storage device, if any.
   * @param inBlockSize The size of each block, in bytes.
   * @param inSize The size of the cache, in blocks.
   * @param inEjectPolicy The cache ejection policy.
   * @param inDemotePolicy_t The cache demotion policy.
   */
  StoreCacheLarge(const char *inName,
		   Store *inNextStore,
		   uint64_t inBlockSize,
		   uint64_t inSize) :
    StoreCache(inName, inNextStore, inBlockSize, inSize),
    cache() { ; };

  /**
   * Create a simple block cache.
   *
   * @param inName A string name for the cache.
   * @param inBlockSize The size of each block, in bytes.
   * @param inSize The size of the cache, in blocks.
   * @param inEjectPolicy The cache ejection policy.
   * @param inDemotePolicy_t The cache demotion policy.
   */
  StoreCacheLarge(const char *inName,
		   uint64_t inBlockSize,
		   uint64_t inSize) :
    StoreCache(inName, inBlockSize, inSize),
    cache() { ; };

  /**
   * Destroy the cache.
   */
  ~StoreCacheLarge() { ; };

  // Statistics management

  virtual void statisticsShow() const;
  virtual bool isCached(const  Block::block_t& inBlock);
};

#endif /* _StoreCacheLarge_HH_ */
