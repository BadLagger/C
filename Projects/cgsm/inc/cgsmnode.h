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
class Node{
protected:
    NodeState CurrentState;

    virtual bool advancedUpdate();
    virtual bool nodeOk();
    virtual bool nodeError();
    virtual bool nodeSuspend();
    virtual bool nodeWait();
public:
    Node();
    Node(int state);
    bool update();
};

#endif // CGSMNODE_H_INCLUDED
