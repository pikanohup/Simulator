#include <cassert>

#include "Routing.h"

// extern int ALGORITHM;

NodeInfo* Routing::forward(Message& s) {
  return forward((*hypercube)[s.routpath[0].node], (*hypercube)[s.dst]);
}

NodeInfo* Routing::forward(HypercubeNode* cur, HypercubeNode* dst) {
  assert(cur && dst && (cur != dst));

  next->node = -1;
  next->buff = NULL;

  return noWrapLinkRoute(cur, dst);
}

/**********

                 check whether buff1 has enough buffer,
                 n	is the buffer number , if buff1 used, then record it:
                 chn is R1 or R2 used,and record is the buffer(such as
   bufferxneg)

                 ***********/

bool Routing::checkBuffer(Buffer* buff1, int& chn, Buffer*& record) {
  bool k = false;
  if (buff1->linkused == true) {
    return k;
  }

  if (chn == R1) {
    if (buff1->r1 >= MESSLENGTH) {
      k = true;
      buff1->linkused = true;
    }
  }
  if (k) {
    record = buff1;
    buff1->bufferMin(chn, MESSLENGTH);
  }
  return k;
}

// Algorithm: Minimal P-Cube Routing for Hypercubes
NodeInfo* Routing::noWrapLinkRoute(HypercubeNode* cur, HypercubeNode* dst) {
  assert(cur && dst && (cur != dst));

  int vch = R1;
  int curid = cur->nodeid;
  int dstid = dst->nodeid;

  // IF digit(Current, i) = 0 and digit(Dest, i) = 1 THEN
  // E0 := E0 + {i}
  // IF E0 != {} THEN
  // Channel := Select(E0)
  for (int i = 0; i < degree; i++) {
    if((curid & 0x01 << i) == 0 && (dstid & 0x01 << i) == 1) {
      int linkid = cur->links[i];
      Buffer* linkbuffer = cur->bufferLinks[i];
      if (checkBuffer(linkbuffer, vch, next->buff)) {
        next->node = linkid;
        next->channel = vch;
        return next;
      }
    }
  }

  // IF digit(Current, i) = 1 and digit(Dest, i) = 0 THEN
  // E1 := E1 + {i}
  // IF E0 = {} and E1 != {} THEN
  // Channel := Select(E1)
  for (int i = 0; i < degree; i++) {
    if((curid & 0x01 << i) == 1 && (dstid & 0x01 << i) == 0) {
      int linkid = cur->links[i];
      Buffer* linkbuffer = cur->bufferLinks[i];
      if (checkBuffer(linkbuffer, vch, next->buff)) {
        next->node = linkid;
        next->channel = vch;
        return next;
      }
    }
  }

  return next;
}
