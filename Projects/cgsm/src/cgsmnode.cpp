#include "cgsmnode.h"

template <class NodeState>
GsmNode<NodeState>::GsmNode(){
#ifdef CGSM_NODE_DEBUG
  cout<< "GsmNode dbg: call constructor" << endl;
#endif
}

template class GsmNode<NodeBaseStates>;
