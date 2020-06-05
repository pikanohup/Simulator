#ifndef ALLROUTING_H
#define ALLROUTING_H

#include "Hypercube.h"
#include "Message.h"
class Message;
class Hypercube;
class NodeInfo;
class Allrouting{
public:
  NodeInfo* next;
	Hypercube* hypercube;
	int k;
	virtual NodeInfo*	forward(Message& s){return NULL;};
  // implemented by child
};


#endif