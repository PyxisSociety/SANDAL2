#include "../../DisplayCode.h"

#include "../LAssert/LAssert.h"



TEST_SECTION(DisplayCodeList){
    static ListDisplayCode * ldc = NULL; // static to be initialized only once
    
    TEST_CASE(creation){
	ldc = initListDisplayCode();

	REQUIRE_NOT_NULL(ldc);
	REQUIRE(ldc->size == 0);
	REQUIRE(ldc->first == NULL);
    }

    // not to do other test cases if font failed to be initialized
    REQUIRE_NOT_NULL(ldc);

    TEST_CASE(add){
	REQUIRE(!addDisplayCode(ldc, 0, 1, 1));
	REQUIRE(ldc->size == 1);
	REQUIRE_NOT_NULL(ldc->first);
	DisplayCode * dc1 = ldc->first;
	REQUIRE(dc1->next == NULL);
	REQUIRE(dc1->code == 0);
	REQUIRE(dc1->isDisplaied == 1);
	REQUIRE(dc1->plan == 1);
	
	REQUIRE(!addDisplayCode(ldc, 1, 1, 1));
	REQUIRE(ldc->size == 2);
	REQUIRE_NOT_NULL(ldc->first->next);
	DisplayCode * dc2 = ldc->first->next;
	REQUIRE(dc1->next == dc2);
	REQUIRE(dc2->code == 1);
	REQUIRE(dc2->isDisplaied == 1);
	REQUIRE(dc2->plan == 1);

	REQUIRE(!addDisplayCode(ldc, 1, 0, 3));
	REQUIRE(ldc->size == 2);
	REQUIRE_NOT_NULL(ldc->first->next);
	REQUIRE(ldc->first->next == dc2);
	REQUIRE(dc2->code == 1);
	REQUIRE(dc2->isDisplaied == 0);
	REQUIRE(dc2->plan == 3);
    }

    TEST_CASE(del){
	REQUIRE_NOT_NULL(ldc->first);
	REQUIRE_NOT_NULL(ldc->first->next);
	DisplayCode * dc = ldc->first->next;
	
	REQUIRE(!delDisplayCode(ldc, 0));
	REQUIRE(ldc->size == 1);
	REQUIRE(ldc->first == dc);
	REQUIRE(dc->next == NULL);
	REQUIRE(delDisplayCode(ldc, 0));

	REQUIRE(!delDisplayCode(ldc, 1));
	REQUIRE(ldc->size == 0);
	REQUIRE(ldc->first == NULL);
	REQUIRE(delDisplayCode(ldc, 1));
    }

    freeListDisplayCode(ldc);
}
