#ifndef ROUT_ING
#define ROUT_ING

#include "Allrouting.h"
#include "HypercubeNode.h"
#include "Message.h"

class Hypercube;
class Buffer;

class Routing : public Allrouting {
 public:
  Routing(Hypercube* hypercube1) {
    hypercube = hypercube1;
    k = hypercube1->getNode();
    next = new NodeInfo();
  }

  bool checkBuffer(Buffer* buff1, int& chn, Buffer*& record);

  NodeInfo* forward(Message&);
  NodeInfo* forward(HypercubeNode* cur, HypercubeNode* dst);
  NodeInfo* noWrapLinkRoute(HypercubeNode* cur, HypercubeNode* dst);  // from cur to do not need wraplink.

  int prefer(Buffer* buff1, Buffer* buff2, int& chn1, int& chn2, Buffer*& buff);
};

#endif
