// 3 dimension hypercube network .Written by Luo Wei in 3/20/2009.


#ifndef Hypercube_H
#define Hypercube_H
#include "HypercubeNode.h"
class HypercubeNode;
class Hypercube{
public:
	Hypercube(int n,  int R1buffer, int R2buffer);//n*n 2Dhypercube,
	HypercubeNode* operator [](int n);
	void clearAll();
	~Hypercube()
	{
		
		delete [] head;
	
	}
	int getNode(){return k;}
private:
	 int k;
	HypercubeNode* head;
};
#endif