#include "Action.h"
#include "Element.h"

#include <stdarg.h>
#include <stdlib.h>



/* -------------------------------------------------------
 * Action functions
 */
Action * initAction(void (*action)(struct Element *, void *, float), float timing){
    Action * a = NULL;

    if(timing){
        a = malloc(sizeof(*a));

        if(a){
            a->timing = timing;
            a->timeSpent = 0;
            a->action = action;
            a->data = NULL;
            a->shouldBeFreed = 0;
        }
    }

    return a;
}

void freeAction(Action * action){
    if(action){
        if(action->data && action->shouldBeFreed){
            free(action->data);
        }
        free(action);
    }
}

Action * setDataAction(Action * action, void * data, int shouldBeFreed){
    if(action){
        action->data = data;
        action->shouldBeFreed = shouldBeFreed;
    }
    return action;
}
/* ------------------------------------------------------- */





/* -------------------------------------------------------
 * Action generation functions
 */
ListAction * actionAsList(Action * action){
    ListAction * list = NULL;

    if(action){
        list = malloc(sizeof(*list));
        if(list){
            list->action = action;
            list->chained = NULL;
            list->parallel = NULL;
            list->isParallel = 0;
        }
    }

    return list;
}

void freeListAction(ListAction * action){
    ListAction * tmp;

    while(action){
        tmp = action->chained;
        freeAction(action->action);
        freeListAction(action->parallel);
        free(action);
        action = tmp;
    }
}

static void executeOneAction(Action ** action, struct Element * e, float time){
    // doing behavior, if any
    if((*action)->action){
        (*action)->action(e, (*action)->data, (*action)->timeSpent + time);
    }

    // incrementing time
    if((*action)->timing >= 0){
        (*action)->timeSpent += time;

        // if action finished
        if((*action)->timing <= (*action)->timeSpent){
            freeAction(*action);
            *action = NULL;
        }
    }
}

ListAction * executeListAction(ListAction * action, struct Element * e, float time){
    ListAction * tmp;
    
    if(action){
        if(action->action){
            executeOneAction(&(action->action), e, time);
        }

        action->parallel = executeListAction(action->parallel, e, time);

        if(!action->action){
            if(!action->parallel){
                tmp = action;
                action = action->chained;
                free(tmp);
            }else if(action->isParallel){
                tmp = action;
                action = action->chained;
                action->parallel = tmp->parallel;
                action->isParallel = 1;
                free(tmp);
            }
        }
    }

    return action;
}

ListAction * generateChainedAction(ListAction * action, ...){
    ListAction * result = action;
    ListAction * tmp    = NULL;
    va_list      vl;
    
    if(action){
        va_start(vl, action);
        while(action){
            tmp = va_arg(vl, ListAction*);
            action->chained = tmp;
            action = tmp;
        }
        va_end(vl);
    }

    return result;
}

ListAction * generateParallelAction(ListAction * action, ...){
    ListAction * result = action;
    ListAction * tmp;
    va_list      vl;
    
    if(action){
        action->isParallel = 1;
        
        va_start(vl, action);
        while(action){
            tmp = va_arg(vl, ListAction *);
            action->parallel = tmp;
            action = tmp;
        }
        va_end(vl);
    }

    return result;
}
/* ------------------------------------------------------- */





/* -------------------------------------------------------
 * Action pre made action functions
 */
/*
void moveByActionFunction(struct Element * e, void * data, float spentTime);
void moveToActionFunction(struct Element * e, void * data, float spentTime);
*/
void scaleByActionFunction(struct Element * e, void * data, float spentTime){
    float * infos = (float*)data;
    float   x;
    float   y;
    float   w;
    float   h;
    float   ratio;
    
    if(e && data){
        ratio = (infos[0] - (infos[0] - spentTime)) / infos[0];
        x     = infos[1];
        y     = infos[2];

        if(!infos[3] && !infos[4]){
            getDimensionElement(e, infos + 3, infos + 4);
        }
        
        w     = infos[3];
        h     = infos[4];

        if(x){
            setWidthElement(e, w + w * x * ratio);
        }
        if(y){
            setHeightElement(e, h + h * y * ratio);
        }
    }
}
/*
void scaleToActionFunction(struct Element * e, void * data, float spentTime);
void rotateByActionFunction(struct Element * e, void * data, float spentTime);
void rotateToActionFunction(struct Element * e, void * data, float spentTime);
*/
/* ------------------------------------------------------- */





/* -------------------------------------------------------
 * Action pre made actions
 */
/*
ListAction * moveByAction(float x, float y, float time);
ListAction * moveToAction(float x, float y, float time);
*/
ListAction * scaleByAction(float x, float y, float time){
    ListAction * result = NULL;
    float      * data   = malloc(5 * sizeof(*data));

    if(data){
        data[0] = time;
        data[1] = x;
        data[2] = y;
        data[3] = 0;
        data[4] = 0;
            
        result = actionAsList(setDataAction(initAction(scaleByActionFunction, time), data, 1));
        
        if(!result){
            free(data);
        }
    }

    return result;
}
/*
ListAction * scaleToAction(float x, float y, float time);
ListAction * rotateByAction(float angle, float time);
ListAction * rotateToAction(float angle, float time);
*/
/* ------------------------------------------------------- */
