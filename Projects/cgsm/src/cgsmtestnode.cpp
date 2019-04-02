#include "cgsmtestnode.h"

GsmNodeTest::GsmNodeTest()
{
#ifdef CGSM_TEST_NODE_DEBUG
    cout << "NodeTest debug: constructor" << endl;
#endif
    addNodeState(TEST_BGN,     (void (*)())&NodeBgn);
    addNodeState(TEST_WAIT,    (void (*)())&NodeWait);
    addNodeState(TEST_SUSPEND, (void (*)())&NodeSuspend);
    addNodeState(TEST_OK,      (void (*)())&NodeOk);
    addNodeState(TEST_ERR,     (void (*)())&NodeErr);
    setNodeState(TEST_BGN);
}

void GsmNodeTest::NodeBgn()
{
#ifdef CGSM_TEST_NODE_DEBUG
    cout << "NodeTest debug: bgn" << endl;
#endif
   // Current = TEST_WAIT;
   setNodeState(TEST_WAIT);
#ifdef CGSM_TEST_NODE_DEBUG
    cout << "NodeTest debug: bgn return" << endl;
#endif
}

void GsmNodeTest::NodeWait()
{
#ifdef CGSM_TEST_NODE_DEBUG
    cout << "NodeTest debug: wait" << endl;
#endif
   // Current = TEST_SUSPEND;
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
}
