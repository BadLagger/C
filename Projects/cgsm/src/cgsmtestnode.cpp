#include "cgsmtestnode.h"

bool NodeTest::advancedUpdate(){
    switch(CurrentState.getState())
    {
      case NodeTestStates::TEST_BEGIN: return nodeTestBegin();
      case NodeTestStates::TEST_END:   return nodeTestEnd();
    }
    return false;
}

bool NodeTest::nodeTestBegin(){
#ifdef CGSM_TEST_NODE_DEBUG
    cout << "NodeTest debug: begin" << endl;
#endif
    CurrentState = NodeTestStates::TEST_END;
    return false;
}

bool NodeTest::nodeTestEnd(){
#ifdef CGSM_TEST_NODE_DEBUG
    cout << "NodeTest debug: end" << endl;
#endif
    CurrentState = NodeTestStates::TEST_BEGIN;
    return false;
}
/*NodeTest::NodeTest()
{
#ifdef CGSM_TEST_NODE_DEBUG
    cout << "NodeTest debug: constructor" << endl;
#endif
}*/

/*void GsmNodeTest::NodeBgn()
{
#ifdef CGSM_TEST_NODE_DEBUG
    cout << "NodeTest debug: bgn" << endl;
#endif
   setNodeState(TEST_WAIT);
}

void GsmNodeTest::NodeWait()
{
#ifdef CGSM_TEST_NODE_DEBUG
    cout << "NodeTest debug: wait" << endl;
#endif
   // Current = TEST_SUSPEND;
   setNodeState(TEST_SUSPEND);
}

void GsmNodeTest::NodeSuspend()
{
#ifdef CGSM_TEST_NODE_DEBUG
    cout << "NodeTest debug: suspend" << endl;
#endif
   // Current = TEST_OK;
}

void GsmNodeTest::NodeOk()
{
#ifdef CGSM_TEST_NODE_DEBUG
    cout << "NodeTest debug: ok" << endl;
#endif
   // Current = TEST_ERR;
}

void GsmNodeTest::NodeErr()
{
#ifdef CGSM_TEST_NODE_DEBUG
    cout << "NodeTest debug: err" << endl;
#endif
   // Current = TEST_BGN;
}    */
