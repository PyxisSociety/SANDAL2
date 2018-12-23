#include "../../Clickable.h"

#include "../LAssert/LAssert.h"

#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TEST_RANGE 10000

static float randrange(float min, float max){
    return (max - min) * ((float)rand() / RAND_MAX) + min;
}

TEST_SECTION(Clickable){
    static Clickable * click = NULL; // static to avoid reinitialization when a test case fail
    static Clickable * test = NULL;

    ONCE srand(time(0)); // initialize random seed only once
    
    TEST_CASE(autoCreationAndClick){
	test = rectangleClickable(0.f, 0.f, 10.f, 10.f);

	REQUIRE_NOT_NULL(test);
	REQUIRE_NOT_NULL(test->firstL);
	REQUIRE_NOT_NULL(test->firstL->next);
	REQUIRE_NOT_NULL(test->firstL->next->next);
	REQUIRE_NOT_NULL(test->firstL->next->next->next);
	REQUIRE(test->firstL->next->next->next->next == NULL);
	REQUIRE(test->firstC == NULL);
	REQUIRE(test->next == NULL);
	
	for(int i = 0; i < TEST_RANGE; ++i){
	    float x = randrange(-5, 15);
	    float y = randrange(-5, 15);
	    _Bool shouldHit = x >= 0 && x <= 10 && y >= 0 && y <= 10;

	    REQUIRE(!!hitClickable(test, x, y) == shouldHit);
	}

	freeClickable(test);


	
	test = ellipseClickable(2, 4, 1, 3, 27);
	
	REQUIRE_NOT_NULL(test);
	REQUIRE_NOT_NULL(test->firstC);
	REQUIRE(test->firstC->next == NULL);
	REQUIRE(test->firstL == NULL);
	REQUIRE(test->next == NULL);
	
	for(int i = 0; i < TEST_RANGE; ++i){
	    float x = randrange(-1, 1);
	    float y = randrange(-1, 1);
	    float cs = cosf(-M_PI * 27 / 180.f);
	    float sn = sinf(-M_PI * 27 / 180.f);
	    _Bool shouldHit = (((x * cs - y * sn - 2) * (x * cs - y * sn - 2)) / 1
			       + ((x * sn + y * cs - 4) * (x * sn + y * cs - 4)) / 9
			       <= 1);

	    REQUIRE(!!hitClickable(test, x, y) == shouldHit);
	}

	freeClickable(test);
	test = NULL;
    }

    if(test){
	freeClickable(test);
	test = NULL;
    }
    
    TEST_CASE(creation){
	click = initClickable();

	REQUIRE_NOT_NULL(click);
	REQUIRE(click->firstL == NULL);
	REQUIRE(click->firstC == NULL);
	REQUIRE(click->next == NULL);
    }

    // to avoid doing other test cases if click creation failed
    REQUIRE_NOT_NULL(click);

    TEST_CASE(line){
	REQUIRE(!addLine(click, 1, 2, 3, 1));
	REQUIRE_NOT_NULL(click->firstL);
	REQUIRE(click->firstL->a == 1, "add 1");
	REQUIRE(click->firstL->b == 2, "add 1");
	REQUIRE(click->firstL->c == 3, "add 1");
	REQUIRE(click->firstL->side == 1, "add 1");

	REQUIRE(!addLine(click, 1, 2, 4, 1));
	REQUIRE_NOT_NULL(click->firstL->next);
	REQUIRE(click->firstL->a == 1, "add 2");
	REQUIRE(click->firstL->b == 2, "add 2");
	REQUIRE(click->firstL->c == 4, "add 2");
	REQUIRE(click->firstL->side == 1, "add 2");

	REQUIRE(!delLine(click, 1, 2, 4, 1));
	REQUIRE_NOT_NULL(click->firstL);
	REQUIRE(click->firstL->next == NULL);
	REQUIRE(click->firstL->a == 1, "del 1");
	REQUIRE(click->firstL->b == 2, "del 1");
	REQUIRE(click->firstL->c == 3, "del 1");
	REQUIRE(click->firstL->side == 1, "del 1");
	REQUIRE(delLine(click, 1, 2, 4, 1));
	
	REQUIRE(!delLine(click, 1, 2, 3, 1));
	REQUIRE(click->firstL == NULL);
    }

    TEST_CASE(circle){
	REQUIRE(!addCircle(click, 1, 2, 3, 4, 1));
	REQUIRE_NOT_NULL(click->firstC);
	REQUIRE(click->firstC->x == 1, "add 1");
	REQUIRE(click->firstC->y == 2, "add 1");
	REQUIRE(click->firstC->rX == 3, "add 1");
	REQUIRE(click->firstC->rY == 4, "add 1");
	REQUIRE(click->firstC->theta == 1, "add 1");

	REQUIRE(!addCircle(click, 1, 2, 4, 3, 1));
	REQUIRE_NOT_NULL(click->firstC->next);
	REQUIRE(click->firstC->x == 1, "add 2");
	REQUIRE(click->firstC->y == 2, "add 2");
	REQUIRE(click->firstC->rX == 4, "add 2");
	REQUIRE(click->firstC->rY == 3, "add 2");
	REQUIRE(click->firstC->theta == 1, "add 2");

	REQUIRE(!delCircle(click, 1, 2, 4, 3, 1));
	REQUIRE_NOT_NULL(click->firstC);
	REQUIRE(click->firstC->next == NULL);
	REQUIRE(click->firstC->x == 1, "del 1");
	REQUIRE(click->firstC->y == 2, "del 1");
	REQUIRE(click->firstC->rX == 3, "del 1");
	REQUIRE(click->firstC->rY == 4, "del 1");
	REQUIRE(click->firstC->theta == 1, "del 1");
	REQUIRE(delCircle(click, 1, 2, 4, 3, 1));
	
	REQUIRE(!delCircle(click, 1, 2, 3, 4, 1));
	REQUIRE(click->firstC == NULL);
    }

    freeClickable(click);
}

TEST_SECTION(ListClickable){
#   define RECTANGLE rectangleClickable(-0.5f, -0.5f, 0.5f, 0.5f)
#   define ELLIPSE ellipseClickable(0, 0, 1, 3, 27)
    static ListClickable * lc = NULL;
    
    TEST_CASE(creation){
	lc = initListClickable();
	REQUIRE_NOT_NULL(lc);
	REQUIRE(lc->first == NULL);
	REQUIRE(lc->current == NULL);
	REQUIRE(lc->firstBlock == NULL);
	REQUIRE(lc->currentBlock == NULL);
    }

    // to avoid doing other test cases if lc creation failed
    REQUIRE_NOT_NULL(lc);
    
    TEST_CASE(addDel){
	Clickable * c1 = NULL;
	Clickable * c2 = NULL;

	for(int i = 0; i < 2; ++i){
	    c1 = RECTANGLE;
	    REQUIRE_NOT_NULL(c1);
	    REQUIRE(!addClickable(lc, c1, i));
	    REQUIRE(delClickable(lc, c1, 1 - i));
	    if(!i){
		REQUIRE(lc->first == c1);
		REQUIRE(lc->first->next == NULL);
	    }else{
		REQUIRE(lc->firstBlock == c1);
		REQUIRE(lc->firstBlock->next == NULL);
	    }

	    c2 = ELLIPSE;
	    REQUIRE_NOT_NULL(c2);
	    REQUIRE(!addClickable(lc, c2, i));
	    REQUIRE(delClickable(lc, c2, 1 - i));
	    if(!i){
		REQUIRE(lc->first == c2);
		REQUIRE(lc->first->next == c1);
		REQUIRE(lc->first->next->next == NULL);
	    }else{
		REQUIRE(lc->firstBlock == c2);
		REQUIRE(lc->firstBlock->next == c1);
		REQUIRE(lc->firstBlock->next->next == NULL);
	    }

	    REQUIRE(!delClickable(lc, c2, i));
	    if(!i){
		REQUIRE(lc->first == c1);
		REQUIRE(lc->first->next == NULL);
	    }else{
		REQUIRE(lc->firstBlock == c1);
		REQUIRE(lc->firstBlock->next == NULL);
	    }
	    REQUIRE(delClickable(lc, c2, i));
	
	    REQUIRE(!delClickable(lc, c1, i));
	    if(!i){
		REQUIRE(lc->first == NULL);
	    }else{
		REQUIRE(lc->firstBlock == NULL);
	    }
	    REQUIRE(delClickable(lc, c1, i));
	}
    }
    
    TEST_CASE(iterate){
	int (*init[])(ListClickable *) = {
	    initIteratorListClickable,
	    initIteratorListClickableBlocking
	};
	Clickable * (*next[])(ListClickable *) = {
	    nextClickable,
	    nextClickableBlocking
	};
	
	Clickable * c1[2];
	c1[0] = RECTANGLE;
	c1[1] = RECTANGLE;
	Clickable * c2[2];
	c2[0] = ELLIPSE;
	c2[1] = ELLIPSE;

	REQUIRE(!addClickable(lc, *c1, 0));
	REQUIRE(!addClickable(lc, *c2, 0));
	REQUIRE(!addClickable(lc, c1[1], 1));
	REQUIRE(!addClickable(lc, c2[1], 1));

	for(int i = 0; i < 2; ++i){
	    REQUIRE(init[i](lc));
	    REQUIRE(next[i](lc) == c2[i]);
	    REQUIRE(next[i](lc) == c1[i]);
	    REQUIRE(next[i](lc) == NULL);
	}

	REQUIRE(!delClickable(lc, *c1, 0));
	REQUIRE(!delClickable(lc, *c2, 0));
	REQUIRE(!delClickable(lc, c1[1], 1));
	REQUIRE(!delClickable(lc, c2[1], 1));
    }
    
    TEST_CASE(hit){
	Clickable * e = ELLIPSE;
	Clickable * r = RECTANGLE;
	REQUIRE(!addClickable(lc, r, 1));
	REQUIRE(!addClickable(lc, e, 0));

	for(int i = 0; i < TEST_RANGE; ++i){
	    float x = randrange(-1, 1);
	    float y = randrange(-1, 1);
	    float cs = cosf(-M_PI * 27 / 180.f);
	    float sn = sinf(-M_PI * 27 / 180.f);
	    _Bool shouldHitE = hitClickable(e, x, y);
	    _Bool shouldHitR = hitClickable(r, x, y);

	    REQUIRE(hitListClickable(lc, x, y) == (!shouldHitR && shouldHitE),
		    "shouldIt(R: %d, E: %d) - (x,y)==(%f,%f)\n",
		    shouldHitR, shouldHitE, x, y);
	}
    }

    freeListClickable(lc);
#   undef RECTANGLE
#   undef ELLIPSE
}
