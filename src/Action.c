#include "Action.h"

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
        }
    }

    return a;
}

Action * setDataAction(Action * action, void * data){
    if(action){
        action->data = data;
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
        free(action->action);
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
            free(*action);
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
