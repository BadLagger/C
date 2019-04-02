#ifndef CGSMTESTNODE_H_INCLUDED
#define CGSMTESTNODE_H_INCLUDED

#include "cgsmnode.h"

#define CGSM_TEST_NODE_DEBUG

class GsmNodeTest : public GsmNode<NodeBaseStates>{
public:
    GsmNodeTest();
};

#endif // CGSMTESTNODE_H_INCLUDED
