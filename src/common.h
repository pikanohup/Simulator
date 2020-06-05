#ifndef CO_MM_O1
#define CO_MM_O1

#include "Hypercube.h"
#include "Routing.h"
#include "Event.h"
#include <vector>
#include <fstream>

void outtotest(vector<Message*>* vecmess, Hypercube* hcube);
void bufferleft(Hypercube* hcube, int knode);
void drain(vector<Message*>* vecmess, Hypercube* hcube, Event* s);

#endif
