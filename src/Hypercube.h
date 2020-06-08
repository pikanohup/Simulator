#ifndef Hypercube_H
#define Hypercube_H

#include "HypercubeNode.h"

class HypercubeNode;

class Hypercube {
 private:
  int degree;
  HypercubeNode* head;

 public:
  Hypercube(int degree, int R1buffer, int R2buffer);
  ~Hypercube() {
    delete[] head;
  }

  HypercubeNode* operator[](int n);
  int getDegree();
  void clearAll();
};
#endif
