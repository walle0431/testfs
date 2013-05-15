/*
  RCS:          $Header: /afs/cs.cmu.edu/user/tmwong/Cvs/fscachesim/Block.hh,v 1.5 2002/02/15 15:44:24 tmwong Exp $
  Author:       T.M. Wong <tmwong+@cs.cmu.edu>
*/

#ifndef _DEMOTEBLOCK_HH_
#define _DEMOTEBLOCK_HH_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include <map>
#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif /* HAVE_STDINT_H */

/**
 * block_t disk block type abstraction and utility functions.
 */
namespace DemoteBlock {


  typedef struct {

    uint64_t objID;
    uint64_t blockID;

    uint64_t demoteFreq; 
    uint64_t hitFreq;
 
    uint64_t r_d_dist[MAXDIS];
    uint64_t d_r_dist[MAXDIS];

    uint64_t demoteTime;
    uint64_t readTime;

    bool demoted;

    uint64_t l_r_d_dist;
    uint64_t l_d_r_dist;

  } demote_t;

};

#endif /* _DEMOTEBLOCK_HH_ */
