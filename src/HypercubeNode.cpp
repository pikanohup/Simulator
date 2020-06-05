#include "HypercubeNode.h"

void Buffer::bufferMin (int chn , int n) {       //share buffers are used first,when no share buffers ,

		if(R1 == chn){								//	the separate buffers are used.So first we check the
												// separate buffers whether used.
		  r1 -= n;
		}
		else {
		  r2 -= n;
		}
/*

   the following is for flow control
  */
        c -= 1;
	 if(R2 == chn)
		 s++;



}

void	Buffer::bufferPlus (int chn ,int n) {
		assert( chn == R1 || chn == R2 );
		if(R1 == chn){
		 r1 += n;
		}
		else {
		 r2 += n;
		}
/*

   the following is for flow control
  */
        c += 1;
	 if(R2 == chn)
		 s--;

}



void	HypercubeNode::setCoordinate(int _nodeid ,int _x, int _y){
				nodeid = _nodeid;
				x = _x;
				y = _y;

				}


void	HypercubeNode::setbuffer( int buff1, int buff2)            //   num is the share buffer number
	{


	 bufferxneg = new Buffer();
	 bufferxpos = new Buffer();
	 bufferyneg = new Buffer();
	 bufferypos = new Buffer();

		clearBuffer();


	 bufferxneg->r1  = buff1;
	 bufferxpos->r1  = buff1;
	 bufferyneg->r1  = buff1;
	 bufferypos->r1  = buff1;


	 bufferxneg->r2  = buff2;
	 bufferxpos->r2  = buff2;
	 bufferyneg->r2  = buff2;
	 bufferypos->r2  = buff2;


/*

   the following is for flow control
  */
	 bufferxneg->c  = (buff1 + buff2) / MESSLENGTH;
	 bufferxpos->c  = (buff1 + buff2) / MESSLENGTH;
	 bufferyneg->c  = (buff1 + buff2) / MESSLENGTH;
	 bufferypos->c  = (buff1 + buff2) / MESSLENGTH;


	 bufferxneg->s  = 0;
	 bufferxpos->s  = 0;
	 bufferyneg->s  = 0;
	 bufferypos->s  = 0;


	}

void	HypercubeNode::setLinkBuffer(int x1, int x2, int y1, int y2)
	{
		linkxneg = x1;
		linkxpos = x2;
		linkyneg = y1;
		linkypos = y2;


		if (linkxneg != -1) bufferxneglink = (*hypercube)[linkxneg]->bufferxpos;
		else bufferxneglink = NULL;
		if (linkxpos != -1) bufferxposlink = (*hypercube)[linkxpos]->bufferxneg;
		else bufferxposlink = NULL;

		if (linkyneg != -1) bufferyneglink = (*hypercube)[linkyneg]->bufferypos;
		else bufferyneglink = NULL;
	    if (linkypos != -1) bufferyposlink = (*hypercube)[linkypos]->bufferyneg;
		else bufferyposlink = NULL;


	}

void	HypercubeNode::bufferPlus(Buffer* buff, int chn , int n)
	  {
			buff->bufferPlus(chn,n);
	  }

void	 HypercubeNode::bufferMin(Buffer* buff, int chn,int n)
	  {
			buff->bufferMin(chn,n);
	  }

void	HypercubeNode::clearBuffer(){
	  		bufferxneg->linkused  = false;
			bufferxpos->linkused  = false;
			bufferyneg->linkused  = false;
			bufferypos->linkused  = false;


	  }

void    HypercubeNode::sethypercube(Hypercube * hypercube){
		this->hypercube = hypercube;
}