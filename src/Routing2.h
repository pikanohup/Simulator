/*********
  Luo Wei ,12/5/2009

earthquake anniversary
clue with flow control

  *************/




#ifndef RT_2_H
#define RT_2_H

#include "HypercubeNode.h"
#include "Message.h"
#include "Allrouting.h"
class Hypercube;
class Message;
extern int flowalg; // flow control algorithm 



class Routing2:public Allrouting{

public:
	Routing2(Hypercube* hypercube1){
		hypercube = hypercube1;
		k = hypercube1->getNode();
		next = new NodeInfo();
		xtemp = new NodeInfo();
		ytemp = new NodeInfo();
	}
NodeInfo* xtemp;
NodeInfo* ytemp;

NodeInfo*	forward(Message&);//return the nextnode of the message takes;
NodeInfo* xdimension(const Message&); // check wether next hop could be along x dimension.
NodeInfo* ydimension(const Message&); // check wether next hop could be along y dimension.






};														  









#endif