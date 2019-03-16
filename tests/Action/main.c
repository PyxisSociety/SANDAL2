#include "Action.h"
#include "Element.h"

#include "../LAssert/LAssert.h"



TEST_SECTION(Action){
    // init action
    Action * a = initAction(NULL, 30);
    REQUIRE_NOT_NULL(a);
    REQUIRE(a->timing == 30);
    REQUIRE(a->timeSpent == 0);
    REQUIRE(a->action == NULL);
    REQUIRE(a->data == NULL);
    REQUIRE(a->shouldBeFreed == 0);

    // set data
    REQUIRE(a == setDataAction(a, (void*)1, 1));
    REQUIRE(a->shouldBeFreed == 1);
    REQUIRE(a->data == (void*)1);

    // free action
    a->shouldBeFreed = 0;
    freeAction(a);
}




TEST_SECTION(ListAction){
    // action as list
    Action a;
    ListAction * pla = actionAsList(&a);
    REQUIRE_NOT_NULL(pla);
    REQUIRE(pla->action == &a);
    REQUIRE(pla->chained == NULL);
    REQUIRE(pla->parallel == NULL);
    REQUIRE(pla->isParallel == 0);
    pla->action = NULL;
    freeListAction(pla);
    pla = NULL;

    // generate chained action
    ListAction la1 = {0}, la2, la3;
    pla = generateChainedAction(&la1, &la2, &la3, NULL);
    REQUIRE(pla == &la1);
    REQUIRE(la1.chained == &la2);
    REQUIRE(la1.parallel == NULL);
    REQUIRE(la2.chained == &la3);
    REQUIRE(la3.chained == NULL);

    // generate parallel action
    pla = generateParallelAction(&la1, &la2, &la3, NULL);
    REQUIRE(pla == &la1);
    REQUIRE(la1.parallel == &la2);
    REQUIRE(la2.parallel == &la3);
    REQUIRE(la3.parallel == NULL);
}




TEST_SECTION(PreMadeAction){
    ListAction * pla;
#define TEST_ACTION(name, ...)                                  \
    pla = name##Action(__VA_ARGS__);                            \
    REQUIRE_NOT_NULL(pla);                                      \
    REQUIRE_NOT_NULL(pla->action);                              \
    REQUIRE_NOT_NULL(pla->action->data);                        \
    REQUIRE(pla->action->action == name##ActionFunction);       \
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
