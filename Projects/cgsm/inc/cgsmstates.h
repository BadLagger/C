#ifndef CGSMSTATES_H_INCLUDED
#define CGSMSTATES_H_INCLUDED

#include <map>
/* Basic states for all NODES*/
class NodeBaseStates{
protected:
  int state;
  std::map<int, char*> states;

  void mapInit(){
    states.insert(std::pair<int, char*>((int)OK,      (char*)"OK"));
    states.insert(std::pair<int, char*>((int)ERROR,   (char*)"ERROR"));
    states.insert(std::pair<int, char*>((int)SUSPEND, (char*)"SUSPEND"));
    states.insert(std::pair<int, char*>((int)WAIT,    (char*)"WAIT"));
  }
public:
  static const int NULLST  = -1;
  static const int OK      = 0;
  static const int ERROR   = 1;
  static const int SUSPEND = 2;
  static const int WAIT    = 3;

  // constructors
  NodeBaseStates(){
   // states.insert(std::pair<int, char*>(1, "OK"));
    mapInit();
    state = SUSPEND;
  };

  NodeBaseStates(int state) {
    mapInit();
    std::map<int, char*>::iterator check = states.find(state);
    if(check != states.end())
      this->state = state;
    else
      this->state = SUSPEND;
  };

  // getter
  int getState(){
    return  state;
  };

  char* getTxtState(){
    std::map<int, char*>::iterator check = states.find(state);
    if(check != states.end())
    {
        return (char*)check->second;
    }
    return  (char*)"null state";
  };

  // operators
  NodeBaseStates operator=(NodeBaseStates state){
    this->state = state.getState();
    return *this;
  };

  NodeBaseStates operator=(int state){
    std::map<int, char*>::iterator check = states.find(state);
    if(check != states.end())
    {
      this->state = state;
    }
    return *this;
  };
};
/* States for test Node */
class NodeTestStates : public NodeBaseStates{
private:
    void mapTestInit(){
        states.insert(std::pair<int, char*>((int)TEST_BEGIN,    (char*)"TEST BEGIN"));
        states.insert(std::pair<int, char*>((int)TEST_END,      (char*)"TEST END"));
    }
public:
    static const int TEST_BEGIN    = 4;
    static const int TEST_END      = 5;

    NodeTestStates()
    {
        mapTestInit();
    }

    NodeTestStates(int state) : NodeBaseStates()
    {
        mapTestInit();
        std::map<int, char*>::iterator check = states.find(state);
        if(check != states.end())
          this->state = state;
        else
          this->state = SUSPEND;
    }
};



#endif // CGSMSTATES_H_INCLUDED
