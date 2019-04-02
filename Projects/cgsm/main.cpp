#include "cgsmtestnode.h"
#include <stdio.h>
/*using namespace std;

static void testSuspend(){
    cout << "test suspend" << endl;
}

static void testOk(){
    cout << "test ok" << endl;
}

static void testErr(){
    cout << "test err" << endl;
}

static void testWait(){
    cout << "test wait" << endl;
}

typedef enum
{
    TEST_SUSPEND = 0,
    TEST_OK,
    TEST_ERR,
    TEST_WAIT
}TestNodeStates;*/


int main()
{
    NodeBaseStates state(NodeTestStates::ERROR);
    NodeBaseStates newState = state;
    cout << "State: "     << state.getTxtState() << endl;
    cout << "New State: " << newState.getTxtState() << endl;
    newState = NodeBaseStates::OK;
    cout << "New State Ok: " << newState.getTxtState() << endl;

    NodeTestStates testState(NodeTestStates::TEST_BEGIN);
    cout << "State test: "     << testState.getTxtState() << endl;

    Node<NodeBaseStates> BasicNode(NodeBaseStates::ERROR);
    BasicNode.update();
    BasicNode.update();
    BasicNode.update();
    BasicNode.update();
    BasicNode.update();
    BasicNode.update();
    BasicNode.update();
    BasicNode.update();
    BasicNode.update();
    BasicNode.update();

    NodeTest test(NodeTestStates::TEST_BEGIN);
    test.update();
    test.update();
    test.update();
    test.update();
    test.update();
    test.update();
   // cout << "New State: " << newState.state << endl;
    //GsmNodeTest test;
  //  printf("Current test state: %d\r\n", test.getNodeState());
   // cout << "Current test state: " << test.getState() << endl;
   // test.setNodeState(static NodeBaseStates.SUSPEND);
   // cout << "Current test state: " << test.getNodeState() << endl;
    /*test.updateNode();
    test.updateNode();
    test.updateNode();
    test.updateNode();
    test.updateNode();
    test.updateNode();
    test.updateNode();*/

    /*GsmNode<TestNodeStates> Test(TEST_BGN);

    Test.addNodeState(TEST_BGN,     testNodeBgn);
    Test.addNodeState(TEST_WAIT,    testNodeWait);
    Test.addNodeState(TEST_SUSPEND, testNodeSuspend);
    Test.addNodeState(TEST_OK,      testNodeOk);
    Test.addNodeState(TEST_ERR,     testNodeErr);

    Test.updateNode();
    Test.setNodeState(TEST_OK);
    Test.updateNode();*/

    /*TestNodeStates currentState = TEST_SUSPEND;
    map<TestNodeStates, void (*)()> TestNode;

    TestNode.insert(pair<TestNodeStates, void (*)()>(TEST_SUSPEND, testSuspend));
    TestNode.insert(pair<TestNodeStates, void (*)()>(TEST_OK,      testOk));
    TestNode.insert(pair<TestNodeStates, void (*)()>(TEST_ERR,     testErr));
    TestNode.insert(pair<TestNodeStates, void (*)()>(TEST_WAIT,    testWait));

    map<TestNodeStates, void (*)()>::iterator foo = TestNode.find(currentState);
    void (*hndl)() = 0;

    if(foo != TestNode.end()){
        hndl = *foo->second;
        hndl();
    }

    currentState = TEST_OK;
    foo = TestNode.find(currentState);

    if(foo != TestNode.end()){
        hndl = *foo->second;
        hndl();
    }*/

    return 0;
}
