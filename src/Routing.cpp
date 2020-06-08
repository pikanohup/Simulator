#include <cassert>

#include "Routing.h"

/*******

  if ALGORITHM == 1, west-first
  if ALGORITHM == 2, dor-routing


  ***********/
extern int ALGORITHM;

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

  int curx = cur->x;
  int cury = cur->y;

  int dstx = dst->x;
  int dsty = dst->y;

  int xdis = dstx - curx;  // x方向的偏移
  int ydis = dsty - cury;  // y方向的偏移

  int bufferslc;  // 0 no buffer available, 1: select  x direction buffer,2 y
                  // direction, 3 z direction
  int var1;
  int var2;

  int vchx;  // virtual channel of x axis
  int vchy;

  if (xdis < 0)
    var1 = 0;
  else {
    if (xdis == 0)
      var1 = 1;
    else if (xdis > 0)
      var1 = 2;
  }

  if (xdis == 0) {
    if (ydis < 0)
      var2 = 0;
    else {
      if (ydis == 0)
        var2 = 1;
      else if (ydis > 0)
        var2 = 2;
    }
  } else {
    var2 = 1;  // xy路由算法：x方向的偏移不为0时,不能走y方向
  }

  Buffer* xlink[3] = {cur->bufferxneglink, NULL, cur->bufferxposlink};
  Buffer* ylink[3] = {cur->bufferyneglink, NULL, cur->bufferyposlink};

  int xlinknode[3] = {cur->linkxneg, -1, cur->linkxpos};
  int ylinknode[3] = {cur->linkyneg, -1, cur->linkypos};

  int virtualch[3] = {R2, 0, R1};

  /**********************************************


          ALGORITHM == 2   dor ROUTING 路由算法的实现，这里实现的xy

    *****************************************************/

  if (ALGORITHM == 2) {
    vchx = R1;  //无虚拟通道都使用r1
    vchy = R1;

    bufferslc = prefer(xlink[var1], ylink[var2], vchx, vchy, next->buff);
    switch (bufferslc) {
      case 0:
        next->node = -1;
        break;
      case 1:
        next->node = xlinknode[var1];
        next->channel = vchx;
        break;
      case 2:
        next->node = ylinknode[var2];
        next->channel = vchy;
        break;
    }
    return next;
  }
}
