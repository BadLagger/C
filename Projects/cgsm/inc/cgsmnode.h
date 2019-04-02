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
protected:
    map<NodeState, void (*)()> States;
    NodeState Current;
public:
    GsmNode();
    void addNodeState(NodeState, void (*)());
    void updateNode();
    void setNodeState(NodeState);
};

#endif // CGSMNODE_H_INCLUDED
