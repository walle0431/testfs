#ifndef _ARC_HH_
#define _ARC_HH_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif 

#include <list>
#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif 

#include "Block.hh"
#include "Cache.hh"
#include "LocalBlock.hh"
#include "BlockBuffer.hh"

class ARC {

private:
   Cache *Q[4];
   uint64_t size;

bool Adaption(uint64_t blockSeg);

public:
   ARC(uint64_t inSize);

   int blockGetCascade(const Block::block_t& inBlock);
   void blockPut(const Block::block_t& inBlock, int inSeg);

   bool blockGet(const Block::block_t& inBlock);

   uint64_t sizeGet() const {return size;};

  ~ARC(); 

};


#endif /* _ARC_HH_ */
