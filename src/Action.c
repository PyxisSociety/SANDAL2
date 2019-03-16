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
        va_start(vl, action);
        while(action){
            tmp = va_arg(vl, ListAction *);
            action->parallel = tmp;
            action->isParallel = 1;
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

void moveByActionFunction(struct Element * e, void * data, float spentTime){
    float * infos = (float*)data;
    float   moveX;
    float   moveY;
    float   x;
    float   y;
    float   ratio;
    
    if(e && data){
        ratio = (infos[0] - (infos[0] - spentTime)) / infos[0];
        moveX = infos[1];
        moveY = infos[2];

        if(!infos[3] && !infos[4]){
            getCoordElement(e, infos + 3, infos + 4);
        }
        
        x     = infos[3];
        y     = infos[4];

        if(moveX){
            setCoordXElement(e, x + moveX * ratio);
        }
        if(moveY){
            setCoordYElement(e, y + moveY * ratio);
        }
    }
}

void moveToActionFunction(struct Element * e, void * data, float spentTime){
    float * infos = (float*)data;
    float   newX;
    float   newY;
    float   oldX;
    float   oldY;
    float   ratio;
    
    if(e && data){
        ratio = (infos[0] - (infos[0] - spentTime)) / infos[0];
        newX  = infos[1];
        newY  = infos[2];

        if(!infos[3] && !infos[4]){
            getCoordElement(e, infos + 3, infos + 4);
        }
        
        oldX  = infos[3];
        oldY  = infos[4];

        if(newX){
            setCoordXElement(e, oldX + (newX - oldX) * ratio);
        }
        if(newY){
            setCoordYElement(e, oldY + (newY - oldY) * ratio);
        }
    }
}

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

void scaleToActionFunction(struct Element * e, void * data, float spentTime){
    float * infos = (float*)data;
    float   newW;
    float   newH;
    float   oldW;
    float   oldH;
    float   ratio;
    
    if(e && data){
        ratio = (infos[0] - (infos[0] - spentTime)) / infos[0];
        newW  = infos[1];
        newH  = infos[2];

        if(!infos[3] && !infos[4]){
            getDimensionElement(e, infos + 3, infos + 4);
        }
        
        oldW  = infos[3];
        oldH  = infos[4];

        if(newW){
            setWidthElement(e, oldW + (newW - oldW) * ratio);
        }
        if(newH){
            setHeightElement(e, oldH + (newH - oldH) * ratio);
        }
    }
}

void rotateByActionFunction(struct Element * e, void * data, float spentTime){
    float * infos = (float*)data;
    float   toAdd;
    float   angle;
    float   ratio;
    
    if(e && data){
        ratio = (infos[0] - (infos[0] - spentTime)) / infos[0];
        toAdd = infos[1];

        if(!infos[2]){
            getAngleElement(e, infos + 2);
        }

        angle = infos[2];

        setAngleElement(e, angle + toAdd * ratio);
    }
}

void rotateToActionFunction(struct Element * e, void * data, float spentTime){
    float * infos = (float*)data;
    float   newAngle;
    float   oldAngle;
    float   ratio;
    
    if(e && data){
        ratio    = (infos[0] - (infos[0] - spentTime)) / infos[0];
        newAngle = infos[1];

        if(!infos[2]){
            getAngleElement(e, infos + 2);
        }
        
        oldAngle = infos[2];

        setAngleElement(e, oldAngle + (newAngle - oldAngle) * ratio);
    }
}
void fadeInActionFunction(struct Element * e, void * data, float spentTime){
    float * infos = (float*)data;
    int     oldAlpha;
    int     newAlpha;
    float   ratio;
    
    if(e && data){
        ratio    = (infos[0] - (infos[0] - spentTime)) / infos[0];
        newAlpha = (int)infos[1];

        if(!infos[2]){
            getAlphaElement(e, &oldAlpha);
            infos[2] = (float)oldAlpha;
        }else{        
            oldAlpha = infos[2];
        }
        
        setAlphaElement(e, oldAlpha - newAlpha * ratio);
    }
}
void fadeOutActionFunction(struct Element * e, void * data, float spentTime){
    float * infos = (float*)data;
    int     oldAlpha;
    int     newAlpha;
    float   ratio;
    
    if(e && data){
        ratio    = (infos[0] - (infos[0] - spentTime)) / infos[0];
        newAlpha = (int)infos[1];

        if(!infos[2]){
            getAlphaElement(e, &oldAlpha);
            infos[2] = (float)oldAlpha;
        }else{        
            oldAlpha = infos[2];
        }
        
        setAlphaElement(e, oldAlpha + newAlpha * ratio);
    }
}
/* ------------------------------------------------------- */





/* -------------------------------------------------------
 * Action pre made actions
 */
ListAction * moveByAction(float x, float y, float time){
    ListAction * result = NULL;
    float      * data   = malloc(5 * sizeof(*data));

    if(data){
        data[0] = time;
        data[1] = x;
        data[2] = y;
        data[3] = 0;
        data[4] = 0;
            
        result = actionAsList(setDataAction(initAction(moveByActionFunction, time), data, 1));
        
        if(!result){
            free(data);
        }
    }

    return result;
}

ListAction * moveToAction(float x, float y, float time){
    ListAction * result = NULL;
    float      * data   = malloc(5 * sizeof(*data));

    if(data){
        data[0] = time;
        data[1] = x;
        data[2] = y;
        data[3] = 0;
        data[4] = 0;
            
        result = actionAsList(setDataAction(initAction(moveToActionFunction, time), data, 1));
        
        if(!result){
            free(data);
        }
    }

    return result;
}

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

ListAction * scaleToAction(float w, float h, float time){
    ListAction * result = NULL;
    float      * data   = malloc(5 * sizeof(*data));

    if(data){
        data[0] = time;
        data[1] = w;
        data[2] = h;
        data[3] = 0;
        data[4] = 0;
            
        result = actionAsList(setDataAction(initAction(scaleToActionFunction, time), data, 1));
        
        if(!result){
            free(data);
        }
    }

    return result;
}

ListAction * rotateByAction(float angle, float time){
    ListAction * result = NULL;
    float      * data   = malloc(3 * sizeof(*data));

    if(data){
        data[0] = time;
        data[1] = angle;
        data[2] = 0;
            
        result = actionAsList(setDataAction(initAction(rotateByActionFunction, time), data, 1));
        
        if(!result){
            free(data);
        }
    }

    return result;
}

ListAction * rotateToAction(float angle, float time){
    ListAction * result = NULL;
    float      * data   = malloc(3 * sizeof(*data));

    if(data){
        data[0] = time;
        data[1] = angle;
        data[2] = 0;
            
        result = actionAsList(setDataAction(initAction(rotateToActionFunction, time), data, 1));
        
        if(!result){
            free(data);
        }
    }

    return result;
}

ListAction * fadeInAction(int alpha, float time){
    ListAction * result = NULL;
    float      * data   = malloc(3 * sizeof(*data));

    if(data){
        data[0] = time;
        data[1] = (float)alpha;
        data[2] = 0;
            
        result = actionAsList(setDataAction(initAction(fadeInActionFunction, time), data, 1));
        
        if(!result){
            free(data);
        }
    }

    return result;
}

ListAction * fadeOutToAction(int alpha, float time){
    ListAction * result = NULL;
    float      * data   = malloc(3 * sizeof(*data));

    if(data){
        data[0] = time;
        data[1] = (float)alpha;
        data[2] = 0;
            
        result = actionAsList(setDataAction(initAction(fadeOutActionFunction, time), data, 1));
        
        if(!result){
            free(data);
        }
    }

    return result;
}
/* ------------------------------------------------------- */
