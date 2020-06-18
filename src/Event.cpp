#include <cmath>

#include "Event.h"
#include "Message.h"

Event::Event(Allrouting* rout) : consumed(0), totalcir(0), messarrive(0), rout(rout), hcube(rout->hypercube) {
}

Message* Event::genMes() {
  Hypercube* hypercube = NULL;
  if (rout != NULL) hypercube = rout->hypercube;

  // GENERATETYPE === 1
  int num = pow(2, rout->degree);
  int tempRand = abs(rand()) % num;
  int src = tempRand;
  while (1) {
    tempRand = abs(rand()) % num;
    if (tempRand != src) {
      int dest = tempRand;
      return new Message(src, dest);
    }
  }
}

void Event::forwardMes(Message& s) {
  if (s.begintrans <= 0) s.count++;
  if (s.routpath[0].node == s.src) {
    if (s.begintrans > 0)
      s.begintrans--;  // check whether process time
    else {
      s.begintrans--;
      NodeInfo* next;
      assert(rout != NULL);
      next = rout->forward(s);
      if (next->node == -1) {
        s.timeout++;
      } else {
        s.timeout = 0;
        assert(s.routpath[0].node != next->node);
        s.routpath[0] = *next;
      }
    }
  } else {
    if (s.routpath[0].node != s.dst) {
      NodeInfo* next = NULL;
      if (rout != NULL)
        next = rout->forward(s);  //调用Allrouting.h中的forward()函数，得到header
                                  //flit下一跳的节点
      if (next->node == -1) {
        int i;
        for (i = 1; i < MESSLENGTH && s.routpath[i].node == s.routpath[0].node;
             i++)
          ;  // if blocked insert the flits until all are inserted
        if (i < MESSLENGTH) {
          NodeInfo temp1, temp2;  // all the flits forward one step
          temp2 = s.routpath[i - 1];
          while (i < MESSLENGTH) {
            temp1 = s.routpath[i];
            s.routpath[i] = temp2;
            temp2 = temp1;
            i++;
          }
          if (temp2.node != s.routpath[MESSLENGTH - 1].node) {
            assert(s.routpath[MESSLENGTH - 1].buff->linkused);
            s.releaselink = true;
          }
          if (temp2.buff != NULL &&
              temp2.node != s.routpath[MESSLENGTH - 1].node)
            temp2.buff->bufferPlus(temp2.channel, MESSLENGTH);
        }
        s.timeout++;
      } else {
        s.timeout = 0;
        NodeInfo temp1, temp2;  // all the flits forward one step
        temp2 = s.routpath[0];
        int i = 1;
        while (i < MESSLENGTH) {
          temp1 = s.routpath[i];
          s.routpath[i] = temp2;
          temp2 = temp1;
          i++;
        }
        if (temp2.node != s.routpath[MESSLENGTH - 1].node) {
          assert(s.routpath[MESSLENGTH - 1].buff->linkused ||
                 s.routpath[MESSLENGTH - 1].buff->linkused);
          s.releaselink = true;  // the tail shift, release the physical link
        }
        if (temp2.buff != NULL &&
            temp2.node !=
                s.routpath[MESSLENGTH - 1].node)  // maybe the last flit do not
                                                  // insert into the network
          temp2.buff->bufferPlus(temp2.channel, MESSLENGTH);

        s.routpath[0] = *next;
      }
    }

    else {
      NodeInfo temp1, temp2;  // all the flits forward one step
      temp2 = s.routpath[0];
      int i;
      for (i = 1; i < MESSLENGTH && s.routpath[i].node == s.routpath[0].node;
           i++)
        ;
      if (i == MESSLENGTH) {
        s.routpath[i - 1].buff->bufferPlus(s.routpath[i - 1].channel,
                                           MESSLENGTH);  // add buffer
        s.active = false;
        totalcir += s.count;
        messarrive++;
        return;
      }
      while (i < MESSLENGTH) {
        temp1 = s.routpath[i];
        s.routpath[i] = temp2;
        temp2 = temp1;
        i++;
      }
      if (temp2.node != s.routpath[MESSLENGTH - 1].node)
        s.releaselink = true;  // the tail shift, release the physical link

      if (temp2.buff != NULL &&
          temp2.node != s.routpath[MESSLENGTH - 1]
                            .node)  // maybe the last flit do not insert
        temp2.buff->bufferPlus(temp2.channel, MESSLENGTH);
    }
  }
}
