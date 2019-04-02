#ifndef CGSMNODE_H_INCLUDED
#define CGSMNODE_H_INCLUDED

#define CGSM_NODE_DEBUG

#ifdef CGSM_NODE_DEBUG
  #include <iostream>
#endif

#include "cgsmstates.h"
#include <map>

using namespace std;

template <class NodeState>
class GsmNode{
    NodeState currentState;
public:
    GsmNode();
};

#endif // CGSMNODE_H_INCLUDED
