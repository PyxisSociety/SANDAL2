#include "Action.h"
#include "Element.h"

#include "../LAssert/LAssert.h"



TEST_SECTION(Action){
    // init action
    ListAction * la = initAction(NULL, 30);
    REQUIRE_NOT_NULL(la);
    REQUIRE_NOT_NULL(la->first);
    REQUIRE(la->first->isList == 0);
    Action a = la->first->action.action;
    REQUIRE(a.timing == 30);
    REQUIRE(a.timing == 30);
    REQUIRE(a.timeSpent == 0);
    REQUIRE(a.action == NULL);
    REQUIRE(a.data == NULL);
    REQUIRE(a.shouldBeFreed == 0);

    // set data
    REQUIRE(la == setDataAction(la, (void*)1, 1));
    REQUIRE(la->first->action.action.shouldBeFreed == 1);
    REQUIRE(la->first->action.action.data == (void*)1);

    // set forever
    REQUIRE(la == setForeverAction(la, 1));
    REQUIRE(la->isForever == 1);

    // free action
    la->first->action.action.shouldBeFreed = 0;
    freeListAction(la);
}




TEST_SECTION(ListAction){
    // generate chained action
    ListAction la1 = {0}, la2 = {0}, la3 = {0};
    ListAction * pla = generateChainedAction(&la1, &la2, &la3, NULL);
    REQUIRE_NOT_NULL(pla);
    REQUIRE_NOT_NULL(pla->first);
    REQUIRE_NOT_NULL(pla->first->next);
    REQUIRE_NOT_NULL(pla->first->next->next);
    REQUIRE(pla->first->next->next->next == NULL);
    REQUIRE(pla->isParallel == 0);
    freeListAction(pla);


    TEST_CASE(Parallel){
        // list creation
        ListAction * pla = generateParallelAction(moveByAction(10, 10, 1), scaleByAction(10, 10, 1), scaleToAction(10, 10, 2), NULL);
        REQUIRE_NOT_NULL(pla);
        REQUIRE(pla->isParallel);
        REQUIRE(!pla->isForever);
        REQUIRE_NOT_NULL(pla->first);
        REQUIRE_NOT_NULL(pla->first->next);
        REQUIRE_NOT_NULL(pla->first->next->next);
        REQUIRE(pla->first->next->next->next == NULL);

        // list execution
        Element e = {0};
        REQUIRE(!executeListAction(pla, &e, 1));
        REQUIRE(pla->first->isFinished);
        REQUIRE(pla->first->next->isFinished);
        REQUIRE(!pla->first->next->next->isFinished);
        
        REQUIRE(executeListAction(pla, &e, 1));
        REQUIRE(pla->first->isFinished);
        REQUIRE(pla->first->next->isFinished);
        REQUIRE(pla->first->next->next->isFinished);

        // freeing list
        freeListAction(pla);
    }

    TEST_CASE(Chained){
        // list creation
        ListAction * pla = generateChainedAction(moveByAction(10, 10, 1), scaleByAction(10, 10, 1), scaleToAction(10, 10, 2), NULL);
        REQUIRE_NOT_NULL(pla);
        REQUIRE(!pla->isParallel);
        REQUIRE(!pla->isForever);
        REQUIRE_NOT_NULL(pla->first);
        REQUIRE_NOT_NULL(pla->first->next);
        REQUIRE_NOT_NULL(pla->first->next->next);
        REQUIRE(pla->first->next->next->next == NULL);

        // list execution
        Element e = {0};
        REQUIRE(!executeListAction(pla, &e, 1));
        REQUIRE(pla->first->isFinished);
        REQUIRE(!pla->first->next->isFinished);
        REQUIRE(!pla->first->next->next->isFinished);
        
        REQUIRE(!executeListAction(pla, &e, 1));
        REQUIRE(pla->first->isFinished);
        REQUIRE(pla->first->next->isFinished);
        REQUIRE(!pla->first->next->next->isFinished);
        
        REQUIRE(executeListAction(pla, &e, 2));
        REQUIRE(pla->first->isFinished);
        REQUIRE(pla->first->next->isFinished);
        REQUIRE(pla->first->next->next->isFinished);

        // freeing list
        freeListAction(pla);
    }
}




TEST_SECTION(PreMadeAction){
    ListAction * pla;
#define TEST_ACTION(name, ...)                                          \
    pla = name##Action(__VA_ARGS__);                                    \
    REQUIRE_NOT_NULL(pla);                                              \
    REQUIRE_NOT_NULL(pla->first);                                       \
    REQUIRE_NOT_NULL(pla->first->action.action.data);                   \
    REQUIRE(pla->first->action.action.action == name##ActionFunction);  \
    freeListAction(pla)
#define P3 0, 0, 2
#define P2 0, 2

    TEST_ACTION(moveBy, P3);
    TEST_ACTION(moveTo, P3);
    TEST_ACTION(scaleBy, P3);
    TEST_ACTION(scaleTo, P3);
    TEST_ACTION(rotateBy, P2);
    TEST_ACTION(rotateTo, P2);
    TEST_ACTION(fadeIn, P2);
    TEST_ACTION(fadeOut, P2);
    
#undef P2
#undef P3
#undef TEST_ACTION
}




TEST_SECTION(PreMadeActionFunction){
    Element e = {0};
    float data[] = {2, 0, 0, 0, 0};
    e.coulBlock[0] = -1;

    // move by
    e.x = 10;
    e.y = 10;
    data[1] = 10;
    data[2] = -10;
    data[3] = 0;
    data[4] = 0;
    moveByActionFunction(&e, (void*)data, 0.5f);
    EQ(data[3], 10);
    EQ(data[4], 10);
    EQ(e.x, 12.5f);
    EQ(e.y, 7.5f);
    
    // move to
    e.x = 10;
    e.y = 10;
    data[1] = 20;
    data[2] = -10;
    data[3] = 0;
    data[4] = 0;
    moveToActionFunction(&e, (void*)data, 0.5f);
    EQ(data[3], 10);
    EQ(data[4], 10);
    EQ(e.x, 12.5f);
    EQ(e.y, 5.f);

    // scale by
    e.width = 10;
    e.height = 10;
    data[1] = 1.f;
    data[2] = -1.f;
    data[3] = 0;
    data[4] = 0;
    scaleByActionFunction(&e, (void*)data, 0.5f);
    EQ(data[3], 10);
    EQ(data[4], 10);
    EQ(e.width, 12.5f);
    EQ(e.height, 7.5f);

    // scale to
    e.width = 10;
    e.height = 10;
    data[1] = 14.f;
    data[2] = 6.f;
    data[3] = 0;
    data[4] = 0;
    scaleToActionFunction(&e, (void*)data, 0.5f);
    EQ(data[3], 10);
    EQ(data[4], 10);
    EQ(e.width, 11);
    EQ(e.height, 9);

    // rotate by
    e.rotation = 30;
    data[1] = 10;
    data[2] = 0;
    rotateByActionFunction(&e, (void*)data, 0.5f);
    EQ(data[2], 30);
    EQ(e.rotation, 32.5f);

    // rotate to
    e.rotation = 30;
    data[1] = 10;
    data[2] = 0;
    rotateToActionFunction(&e, (void*)data, 0.5f);
    EQ(data[2], 30);
    EQ(e.rotation, 25.f);

    // fade in
    e.coulBlock[3] = 20;
    data[1] = 20;
    data[2] = -1;
    fadeInActionFunction(&e, (void*)data, 0.5f);
    EQ(data[2], 20);
    REQUIRE(e.coulBlock[3] == 15);

    // fade out
    e.coulBlock[3] = 20;
    data[1] = 20;
    data[2] = -1;
    fadeOutActionFunction(&e, (void*)data, 0.5f);
    EQ(data[2], 20);
    REQUIRE(e.coulBlock[3] == 25);
}
