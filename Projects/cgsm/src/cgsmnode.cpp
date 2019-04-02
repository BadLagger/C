#include "cgsmnode.h"

template <class NodeState>
Node<NodeState>::Node(){
#ifdef CGSM_NODE_DEBUG
  cout<< "Node dbg: call default constructor " << CurrentState.getTxtState()<<endl;
#endif

}

template <class NodeState>
Node<NodeState>::Node(int state){
#ifdef CGSM_NODE_DEBUG
  cout<< "Node dbg: call state constructor" <<endl;
#endif
  CurrentState = state;
#ifdef CGSM_NODE_DEBUG
  cout<< "Node dbg: state is "<< CurrentState.getTxtState() <<endl;
#endif
}

template <class NodeState>
bool Node<NodeState>::update(){

    switch(CurrentState.getState())
    {
      case NodeState::OK:      return nodeOk();
      case NodeState::ERROR:   return nodeError();
      case NodeState::SUSPEND: return nodeSuspend();
      case NodeState::WAIT:    return nodeWait();
      default:                 return advancedUpdate();
    }
}

template <class NodeState>
bool Node<NodeState>::advancedUpdate(){
#ifdef CGSM_NODE_DEBUG
  cout<< "Node dbg: advanced update" <<endl;
#endif
    return false;
}

template <class NodeState>
bool Node<NodeState>::nodeOk(){
#ifdef CGSM_NODE_DEBUG
  cout<< "Node dbg: ok update" <<endl;
#endif
    CurrentState = NodeState::ERROR;
    return true;
}

template <class NodeState>
bool Node<NodeState>::nodeError(){
#ifdef CGSM_NODE_DEBUG
  cout<< "Node dbg: error update" <<endl;
#endif
    CurrentState = NodeState::SUSPEND;
    return false;
}

template <class NodeState>
bool Node<NodeState>::nodeSuspend(){
#ifdef CGSM_NODE_DEBUG
  cout<< "Node dbg: suspend update" <<endl;
#endif
    CurrentState = NodeState::WAIT;
    return true;;
}

template <class NodeState>
bool Node<NodeState>::nodeWait(){
#ifdef CGSM_NODE_DEBUG
  cout<< "Node dbg: wait update" <<endl;
#endif
    CurrentState = NodeState::OK;
    return false;
}

template class Node<NodeBaseStates>;
template class Node<NodeTestStates>;
