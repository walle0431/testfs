/*
  RCS:          $Header: /afs/cs.cmu.edu/user/tmwong/Cvs/fscachesim/StoreCacheSimple.cc,v 1.5 2002/02/18 00:23:45 tmwong Exp $
  Author:       T.M. Wong <tmwong+@cs.cmu.edu>
*/

#include <list>
#include <stdio.h> 
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif /* HAVE_STDLIB_H */

#include "Block.hh"
#include "IORequest.hh"
 
#include "StoreCacheSimpleCoop.hh"

using Block::block_t;
 



void
StoreCacheSimpleCoop::BlockCache(const IORequest& inIOReq,
			     const block_t& inBlock_t,
			     list<IORequest>& outIOReqs)
{
 


   if (inIOReq.opGet() == IORequest::Read)
   {
 
       if (!ReadFromCache(inIOReq, inBlock_t))
         if (cooperative.isCached(inBlock_t))
         {
             coopHitsPerOrig[inIOReq.origGet()]++; 
             cooperativeHits++;
         }
    }

   else if (inIOReq.opGet() == IORequest::Demote)
   {
       
       DemoteToCache (inIOReq, inBlock_t);
   }

}

