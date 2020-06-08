#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <fstream>

#include "Hypercube.h"
#include "Routing.h"
#include "Event.h"

void outtotest(vector<Message*>* vecmess, Hypercube* hcube);
void bufferleft(Hypercube* hcube, int knode);
void drain(vector<Message*>* vecmess, Hypercube* hcube, Event* s);

#endif
