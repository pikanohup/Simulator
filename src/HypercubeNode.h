#ifndef HypercubeNode_H
#define HypercubeNode_H

#include <cassert>
#include <iostream>
#include <string>
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
  Buffer* bufferxneg;  // the buffer of x axis negative direction
  Buffer* bufferxpos;  // the buffer of x axis positive direction
  Buffer* bufferyneg;
  Buffer* bufferypos;

  int linkxneg;  // the node to x axis negative direction link
  int linkxpos;
  int linkyneg;
  int linkypos;

  Hypercube* hypercube;

  Buffer* bufferxneglink;
  Buffer* bufferxposlink;  // the buffer x positive direction link to, it is the
                           // buffer of neighbor node
  Buffer* bufferyneglink;  // ...
  Buffer* bufferyposlink;

  int x;  // x coordinate
  int y;  // y coordinate

  void setCoordinate(int _nodeid, int _x, int _y);
  void setBuffer(int buff1, int buff2);  // num is the share buffer number
  void setLinkBuffer(int x1, int x2, int y1, int y2);
  void setHypercube(Hypercube* hypercube);
  void bufferPlus(Buffer* buff, int chn, int n);
  void bufferMin(Buffer* buff, int chn, int n);
  void clearBuffer();

  ~HypercubeNode() {
    delete bufferxneg;
    delete bufferyneg;
    delete bufferxpos;
    delete bufferypos;
  }
};

#endif
