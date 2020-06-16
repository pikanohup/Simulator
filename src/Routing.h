#ifndef ROUT_ING
#define ROUT_ING

#include "Allrouting.h"
#include "HypercubeNode.h"
#include "Message.h"

class Hypercube;
class Buffer;

class Routing : public Allrouting {
 public:
  Routing(Hypercube* _hypercube) {
    hypercube = _hypercube;
    degree = _hypercube->getDegree();
    next = new NodeInfo();
  }

  bool checkBuffer(Buffer* buff1, int& chn, Buffer*& record);

  NodeInfo* forward(Message&);
  NodeInfo* forward(HypercubeNode* cur, HypercubeNode* dst);
  NodeInfo* noWrapLinkRoute(HypercubeNode* cur, HypercubeNode* dst);  // from cur to do not need wraplink.
};

#endif
