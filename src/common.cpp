#include "common.h"

int getsize(vector<Message*>* mess) {
  int size = 0;
  for (int i = 0; i < 10; i++) {
    if (!mess[i].empty()) size += mess[i].size();
  }
  return size;
}

void outtotest(vector<Message*>* allvecmess, Hypercube* hcube) {
  ofstream out = ofstream("test");
  for (int i = 0; i < 10; i++) {
    vector<Message*>& vecmess = allvecmess[i];
    for (vector<Message*>::iterator it = vecmess.begin(); it != vecmess.end();
         it++) {
      out << "count: " << (*it)->count << "  src: ( " << (*hcube)[(*it)->src]->x
          << " ," << (*hcube)[(*it)->src]->y << ") "
          << " dst: ( " << (*hcube)[(*it)->dst]->x << " ,"
          << (*hcube)[(*it)->dst]->y << ") "
          << " head:( " << (*hcube)[(*it)->routpath[0].node]->x << " ,"
          << (*hcube)[(*it)->routpath[0].node]->y << ", R"
          << (*it)->routpath[0].channel << ")  "
          << " tail:( " << (*hcube)[(*it)->routpath[19].node]->x << " ,"
          << (*hcube)[(*it)->routpath[19].node]->y << ") " << endl;
    }
  }
}

void bufferleft(Hypercube* hcube, int knode) {
  int star1 = 0, star2 = 0, flag = 0, star3 = 0, star4 = 0;
  for (int sta = 0; sta < knode * knode; sta++) {
    star1 += ((*hcube)[sta]->bufferxneg->c);
    star2 += ((*hcube)[sta]->bufferxpos->c);
    star3 += ((*hcube)[sta]->bufferyneg->c);
    star4 += ((*hcube)[sta]->bufferypos->c);
  }
  cout << "buffer left --->" << star1 << " " << star2 << " " << star3 << " "
       << " " << star4 << endl;
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
