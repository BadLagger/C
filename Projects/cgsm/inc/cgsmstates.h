#ifndef CGSMSTATES_H_INCLUDED
#define CGSMSTATES_H_INCLUDED

#include <map>

class NodeBaseStates{
  int state;

  void NodeStatesInit(){

  }
public:
  static map<int, char*> states;
  static const int OK      = 0;
  static const int ERROR   = 1;
  static const int SUSPEND = 2;
  static const int WAIT    = 3;

  // constructors
  NodeBaseStates(){
    state = SUSPEND;
  };

  NodeBaseStates(int state) {
    this->state = state;
  };

  // getter
  int getState(){
    return  state;
  };

  // operators
  NodeBaseStates operator=(NodeBaseStates state){
    this->state = state.getState();
    return *this;
  };
};

#endif // CGSMSTATES_H_INCLUDED
