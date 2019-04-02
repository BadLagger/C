#ifndef CGSMTESTNODE_H_INCLUDED
#define CGSMTESTNODE_H_INCLUDED

#include "cgsmnode.h"

#define CGSM_TEST_NODE_DEBUG

class NodeTest : public Node<NodeTestStates>{
protected:
    bool advancedUpdate();
    bool nodeTestBegin();
    bool nodeTestEnd();
public:
    NodeTest() :  Node(){};
    NodeTest(int state) :  Node(state){};
};

#endif // CGSMTESTNODE_H_INCLUDED
