/*
  RCS:          $Header: /afs/cs.cmu.edu/user/tmwong/Cvs/fscachesim/StoreCacheSeg.hh,v 1.3 2002/02/15 18:17:30 tmwong Exp $
  Author:       T.M. Wong <tmwong+@cs.cmu.edu>
*/

#ifndef _STORECACHESEGCOOP_HH_
#define _STORECACHESEGCOOP_HH_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include <list>
#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif /* HAVE_STDINT_H */

#include "Block.hh"
#include "FreqBlock.hh"
#include "StoreCacheSimpleCoop.hh"

/**
 * Segmented LRU cache with an adaptive cache-insertion policy
 * [Wong2002]. Incoming {read, demote} blocks are "cached" in a {read,
 * demote} ghost cache before being insterted in the actual cache. The
 * relative hit rates in the ghosts determine into which segment the
 * incoming block will be inserted.
 *
 * @warning As implemented, segmented caches are terminal storage devices:
 * no lower-level devices can be connected to them.
 */
class StoreCacheSegCoop : public StoreCacheSimpleCoop {

private:


  typedef map<Block::block_t,
	      list<FreqBlock::history_t>::iterator,
	      Block::LessThan> HistoryIndex;

private:

 // history  and index
  list<FreqBlock::history_t> history;
 
  HistoryIndex historyIndex;


  /**
   * The cache segments.
   */
  Cache **cacheSegs;
  
  /**
   * The number of cache segments.
   */
  int cacheSegCount;



  /**
   * The number of hits in each segment.
   */
  uint64_t *segHits;

private:
  // Copy constructors - declared private and never defined

  StoreCacheSegCoop(const StoreCacheSegCoop&);
  StoreCacheSegCoop& operator=(const StoreCacheSegCoop&);

  int blockGetCascade(const Block::block_t& inBlock);
  void blockPutAtSegCascade(const Block::block_t& inBlock,
			    int inSeg);

  void blockDemote(const Block::block_t& inBlock);
  void blockRead(const Block::block_t& inBlock);
  int posGet(const Block::block_t& inBlock);

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
   * @param inSegCount The number of segments.
   * @param inNormalizeFlag If true, normalize the ghost cache probabilities.
   */
  StoreCacheSegCoop(const char *inName,
		uint64_t inBlockSize,
		uint64_t inSize,
		int inSegCount);

  /**
   * Create a segmented adaptive cache with exponential size segments.  The
   * next segment is inSegMultiplier times the size of the previous
   * segment. The tail segment (the eject-me-last end) is the largest.
   *
   * @param inName A string name for the cache.
   * @param inNextStore A lower-level storage device (can be NULL).
   * @param inBlockSize The size of each block, in bytes.
   * @param inSize The size of the total cache, in blocks.
   * @param inSegCount The number of segments.
   * @param inSegMultiplier The multipler for segment sizes. 
   * @param inNormalizeFlag If true, normalize the ghost cache probabilities.
   */
  StoreCacheSegCoop(const char *inName,
		uint64_t inBlockSize,
		uint64_t inSize,
		int inSegCount,
		int inSegMultiplier);

  /**
   * Destroy the cache.
   */
  ~StoreCacheSegCoop();

  // Statistics management

  virtual void statisticsReset();

  virtual void statisticsShow() const;
};

#endif /* _STORECACHESEGCOOP_HH_ */
