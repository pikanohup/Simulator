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

int Routing::prefer(Buffer* buff1, Buffer* buff2, int& chn1, int& chn2,
                    Buffer*& record) {
  //检查是否有足够的缓存，链路是否可用
  if (buff1 != NULL && buff2 == NULL)
    if (checkBuffer(buff1, chn1, record))
      return 1;
    else
      return 0;

  if (buff1 != NULL && buff2 != NULL)
    if (checkBuffer(buff1, chn1, record))
      return 1;
    else
      return 0;

  if (buff1 == NULL && buff2 != NULL)
    if (checkBuffer(buff2, chn2, record))
      return 2;
    else
      return 0;

  if (buff1 == NULL && buff2 == NULL) return 0;
}

NodeInfo* Routing::noWrapLinkRoute(HypercubeNode* cur, HypercubeNode* dst) {
  assert(cur && dst && (cur != dst));
  // TODO
  return next;
}
