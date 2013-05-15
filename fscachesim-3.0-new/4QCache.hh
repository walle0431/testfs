#ifndef _4QCACHE_HH_
#define _4QCACHE_HH_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif 

#include <list>
#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif 

#include "Block.hh"
#include "LocalBlock.hh" 
#include "BlockBuffer.hh"

class FQCache {

private:
   BlockBuffer *Q[4];
   uint64_t size;

public:
   FQCache(uint64_t inSize);

   int blockGetCascade(LocalBlock::local_block_t& inBlock);
   void blockPut(LocalBlock::local_block_t& inBlock, int inSeg);

   bool blockGet(LocalBlock::local_block_t& inBlock);

   uint64_t sizeGet() const {return size;};

  ~FQCache(); 


};


#endif /* _4QCACHE_HH_ */
