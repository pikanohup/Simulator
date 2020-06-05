/*********
  Luo Wei ,9/11/2007



  *************/




#ifndef ROUT_ING
#define ROUT_ING

#include "Allrouting.h"
#include "Message.h"
#include "HypercubeNode.h"
class Hypercube;

class Buffer;

class Routing:public Allrouting{

public:
	Routing(Hypercube* hypercube1){
		hypercube = hypercube1;
		k = hypercube1->getNode();
		next = new NodeInfo();
	}

int chkWrplnk(HypercubeNode* cur, HypercubeNode* dst);//check how many wrap links need from cur to dst.
bool			checkBuffer(Buffer *buff1 , int &chn, Buffer*& record);


NodeInfo*	forward(Message&);
NodeInfo*	forward(HypercubeNode* cur, HypercubeNode* dst);//return the nextnode of cur.
NodeInfo*	noWrapLinkrt(HypercubeNode* cur, HypercubeNode* dst);//from cur to do not need wraplink.
NodeInfo*	oneWrapLinkrt(HypercubeNode* cur, HypercubeNode* dst);//from cur to  need  one wraplink.
NodeInfo*	twoWrapLinkrt(HypercubeNode* cur, HypercubeNode* dst);//from cur to  need  two wraplink.


int		prefer(Buffer *buff1,Buffer *buff2,  int& chn1 , int& chn2, Buffer*& buff);

};









#endif