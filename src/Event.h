#ifndef EVEN_T
#define EVEN_T

#include "Hypercube.h"
#include "HypercubeNode.h"
#include "Message.h"
#include "Routing.h"

class Event {
 public:
  int consumed;
  double totalcir;  // total circle all the messages take;
  int messarrive;   // how many message arrived
  Allrouting* rout;
  Hypercube* hcube;
  int k;  // k * k *k hypercube

  Message* genMes();          // generate a message
  void forwardMes(Message&);  // forward a message
  // void        consumeMes(Message&);
  Event(Allrouting*);
};

#endif
