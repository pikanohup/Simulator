#include <cassert>
#include <cmath>

#include "Hypercube.h"

Hypercube::Hypercube(int degree, int R1buffer, int R2buffer) : degree(degree) {
  int n = pow(2, degree);

  head = new HypercubeNode[n];
  assert(head);

  for (int i = 0; i < n; i++) {
    (head + i)->setNode(degree, i, this);
    (head + i)->setBuffer(degree, R1buffer, R2buffer);
  }

  for (int i = 0; i < n; i++) {
    (head + i)->setLinks(degree);
  }
}

HypercubeNode* Hypercube::operator[](int n) {
	return (head + n);
}

int Hypercube::getDegree() {
  return degree;
}

void Hypercube::clearAll() {
  int n = pow(2, degree);

  for (int i = 0; i < n; i++) {
    (head + i)->clearBuffer();
  }
}
