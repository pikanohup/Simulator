#ifndef Hypercube_H
#define Hypercube_H

#include "HypercubeNode.h"

class HypercubeNode;
class Hypercube {
 public:
  Hypercube(int n, int R1buffer, int R2buffer); // n-dimension hypercube
  HypercubeNode* operator[](int n);

  void clearAll();
  ~Hypercube() { delete[] head; }
  int getNode() { return k; }

 private:
  int k;
  HypercubeNode* head;
};
#endif
