#include "HypercubeNode.h"

// Share buffers are used first, when no share buffers, the separate buffers are
// used. So first we check the separate buffers whether used.
void Buffer::bufferMin(int chn, int n) {
  if (R1 == chn) {
    r1 -= n;
  } else {
    r2 -= n;
  }

  c -= 1;
  if (R2 == chn) {
    s++;
  }
}

void Buffer::bufferPlus(int chn, int n) {
  assert(chn == R1 || chn == R2);
  if (R1 == chn) {
    r1 += n;
  } else {
    r2 += n;
  }

  c += 1;
  if (R2 == chn) {
    s--;
  }
}

void HypercubeNode::setNode(int d, int _nodeid, Hypercube* _hypercube) {
  nodeid = _nodeid;
  hypercube = _hypercube;
}

void HypercubeNode::setBuffer(int d, int buff1, int buff2) {
  buffers.reserve(d);

  for (int i = 0; i < d; i++) {
    Buffer* buffer = new Buffer();

    buffer->linkused = false;
    buffer->r1 = buff1;
    buffer->r2 = buff2;
    buffer->c = (buff1 + buff2) / MESSLENGTH;
    buffer->s = 0;

    buffers.push_back(buffer);
  }
}

void HypercubeNode::setLinks(int d) {
  links.reserve(d);
  bufferLinks.reserve(d);

  for (int i = 0; i < d; i++) {
    int neighbour = nodeid ^ (0x01 << i);
    links.push_back(neighbour);
    bufferLinks.push_back(((*hypercube)[neighbour]->buffers)[i]);
  }
}

void HypercubeNode::bufferPlus(Buffer* buff, int chn, int n) {
  buff->bufferPlus(chn, n);
}

void HypercubeNode::bufferMin(Buffer* buff, int chn, int n) {
  buff->bufferMin(chn, n);
}

void HypercubeNode::clearBuffer() {
  for (vector<Buffer*>::iterator it = bufferLinks.begin(); it != bufferLinks.end(); it++) {
    (*it)->linkused = false;
  }
}
