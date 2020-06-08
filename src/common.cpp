#include "common.h"

int getsize(vector<Message*>* mess) {
  int size = 0;
  for (int i = 0; i < 10; i++) {
    if (!mess[i].empty()) size += mess[i].size();
  }
  return size;
}

void outtotest(vector<Message*>* allvecmess, Hypercube* hcube) {
  ofstream out = ofstream("test.txt");
  for (int i = 0; i < 10; i++) {
    vector<Message*>& vecmess = allvecmess[i];
    for (vector<Message*>::iterator it = vecmess.begin(); it != vecmess.end();
         it++) {
      out << "count: " << (*it)->count << "  src: ( " << (*hcube)[(*it)->src]->nodeid<< ") "
          << " dst: ( " << (*hcube)[(*it)->dst]->nodeid << ") "
          << " head:( " << (*hcube)[(*it)->routpath[0].node]->nodeid << ", R"
          << (*it)->routpath[0].channel << ")  "
          << " tail:( " << (*hcube)[(*it)->routpath[19].node]->nodeid << ") " << endl;
    }
  }
}

void drain(vector<Message*>* allvecmess, Hypercube* hcube, Event* s) {
  for (int i = 0; i < 10000; i++) {
    vector<Message*>& vecmess = allvecmess[i % 10];
    for (vector<Message*>::iterator it = vecmess.begin(); it != vecmess.end();
         it++) {
      // if the tail of a message shifts ,
      // the physical link the message  occupied should release.

      if ((*it)->releaselink == true) {
        assert((*it)->routpath[MESSLENGTH - 1].buff->linkused);
        (*it)->routpath[MESSLENGTH - 1].buff->linkused = false;
        (*it)->releaselink = false;
      }
    }

    for (vector<Message*>::iterator it = vecmess.begin();
         it != vecmess.end();) {
      if ((*it)->active == false ||
          (*it)->routpath[0].node ==
              (*it)->src) {  // when a message arrive at its destination, it is
                             // not active
        delete (*it);
        it = vecmess.erase(it);

      } else
        s->forwardMes(*(*it++));
    }
  }
}
