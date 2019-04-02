#include "cgsmnode.h"

template <class NodeState>
GsmNode<NodeState>::GsmNode(){
#ifdef CGSM_NODE_DEBUG
  cout<< "GsmNode dbg: call constructor" << endl;
#endif
}

template <class NodeState>
void GsmNode<NodeState>::addNodeState(NodeState state, void (*hndl)())
{
#ifdef CGSM_NODE_DEBUG
  cout<< "GsmNode dbg: call addNodeState" << endl;
#endif
  typename map<NodeState, void (*)()>::iterator check = States.find(state);
  if(check == States.end())
  {
      States.insert(pair<NodeState, void (*)()>(state, hndl));
  }
}

template <class NodeState>
void GsmNode<NodeState>::updateNode()
{
#ifdef CGSM_NODE_DEBUG
  cout<< "GsmNode dbg: call updateNode" << endl;
#endif
  typename map<NodeState, void (*)()>::iterator check = States.find(Current);

  if(check != States.end())
  {
      void (*hndl)() = *(check->second);
      hndl();
  }
}

template <class NodeState>
void GsmNode<NodeState>::setNodeState(NodeState state)
{
#ifdef CGSM_NODE_DEBUG
  cout<< "GsmNode dbg: call setNodeState 1" << endl;
#endif
  typename map<NodeState, void (*)()>::iterator check = States.find(state);
#ifdef CGSM_NODE_DEBUG
  cout<< "GsmNode dbg: call setNodeState 2" << endl;
#endif
  if(check != States.end())
  {
#ifdef CGSM_NODE_DEBUG
  cout<< "GsmNode dbg: call setNodeState check done" << endl;
#endif
      Current = check->first;
#ifdef CGSM_NODE_DEBUG
  cout<< "GsmNode dbg: call setNodeState set done" << endl;
#endif
  }
}

template class GsmNode<TestNodeStates>;
