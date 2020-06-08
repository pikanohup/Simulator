#ifndef HypercubeNode_H
#define HypercubeNode_H

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "Hypercube.h"

#define R1 1
#define R2 2
using namespace std;
#define MESSLENGTH 16

class Hypercube;
class Buffer {  // R1 and R2 reserve some buffers separately,they can also use
                // sharebuffer.
 public:
  bool linkused;  // in a physical circle ,check whether physical link is used ,
                  // only one flit is allowed to pass the link in a circle
  int r1;
  int r2;
  void bufferMin(int chn, int n);
  void bufferPlus(int chn, int n);

  int c;  // flow control buffer
  int s;  // flow control special buffer
};

/**************************************************
  this class define the info of a flit in the hypercube node
  including nodeid, buffer
  ************************************************/
class NodeInfo {
 public:  // nextnode is the node to be routed, and vchannel is the virtual
          // channel(R1 or R2) used.
  int node;
  int channel;   // which is used : R1 or R2
  Buffer* buff;  // point to the buffer occupy ,such as bufferxneg......
  NodeInfo() : node(-1) {}
};

class HypercubeNode {
 private:
  int nodeid;

 public:
  vector<Buffer*> buffers;
  vector<int> links;
  vector<Buffer*> bufferLinks;

  Hypercube* hypercube;

  ~HypercubeNode() {
    for (vector<Buffer*>::iterator it = buffers.begin(); it != buffers.end(); it++) {
      delete (*it);
    }
  }
  void setNode(int d, int _nodeid, Hypercube* _hypercube);
  void setBuffer(int d, int buff1, int buff2);
  void setLinks(int d);
  void bufferPlus(Buffer* buff, int chn, int n);
  void bufferMin(Buffer* buff, int chn, int n);
  void clearBuffer();
};

#endif
