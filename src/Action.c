#include "Action.h"
#include "Element.h"

#include <stdarg.h>
#include <stdlib.h>



/* -------------------------------------------------------
 * Action functions
 */
ListAction * initAction(void (*action)(struct Element *, void *, float), float timing){
    ListAction * la = NULL;
    ActionNode * an = NULL;

    if(timing > 0){
        la = malloc(sizeof(*la));

        if(la){
            an = malloc(sizeof(*an));

            if(an){
                la->first = an;
                la->isParallel = 0;
                la->isForever = 0;

                an->isList = 0;
                an->next = NULL;
                an->isFinished = 0;
                
                an->action.action.timing = timing;
                an->action.action.timeSpent = 0;
                an->action.action.action = action;
                an->action.action.data = NULL;
                an->action.action.shouldBeFreed = 0;
            }else{
                free(la);
                la = NULL;
            }
        }
    }

    return la;
}

static void freeAction(Action * action){
    if(action){
        if(action->data && action->shouldBeFreed){
            free(action->data);
        }
        free(action);
    }
}

static void freeActionNode(ActionNode * actionNode){
    ActionNode * tmp = NULL;
    
    while(actionNode){
        if(actionNode->isList){
            freeActionNode(actionNode->action.list.first);
        }else if(actionNode->action.action.shouldBeFreed){
            free(actionNode->action.action.data);
        }

        tmp = actionNode->next;
        free(actionNode);
        actionNode = tmp;
    }
}

ListAction * setDataAction(ListAction * action, void * data, int shouldBeFreed){
    if(action && action->first && !action->first->next && !action->first->isList){
        action->first->action.action.data = data;
        action->first->action.action.shouldBeFreed = shouldBeFreed;
    }
    return action;
}
/* ------------------------------------------------------- */





/* -------------------------------------------------------
 * Action generation functions
 */

void freeListAction(ListAction * action){
    if(action){
        freeActionNode(action->first);
        free(action);
    }
}

static int executeOneAction(Action * action, struct Element * e, float time){
    // doing behavior, if any
    if(action->action){
        action->action(e, action->data, action->timeSpent + time);
    }

    // incrementing time
    action->timeSpent += time;

    return action->timing <= action->timeSpent;
}

static void rewindListAction(ListAction * action){
    ActionNode * node = action->first;

    while(node){
        node->isFinished = 0;

        if(node->isList){
            rewindListAction(&(node->action.list));
        }

        node = node->next;
    }
}

int executeListAction(ListAction * action, struct Element * e, float time){
    ActionNode * node;
    int          isFinished = 1;
    
    if(action){
        node = action->first;

        if(node){
            if(action->isParallel){
                do{
                    if(!node->isFinished){
                        if(node->isList){
                            node->isFinished = executeListAction(&(node->action.list), e, time);
                        }else{
                            node->isFinished = executeOneAction(&(node->action.action), e, time);
                        }

                        isFinished = isFinished && node->isFinished;
                    }

                    node = node->next;
                }while(node);
            }else{
                isFinished = 0; 
                while(node && node->isFinished){
                    node = node->next;
                }

                if(node){
                    if(node->isList){
                        node->isFinished = executeListAction(&(node->action.list), e, time);
                    }else{
                        node->isFinished = executeOneAction(&(node->action.action), e, time);
                    }
                    isFinished = node->isFinished && !node->next;
                }else{
                    isFinished = 1;
                }
            }
        }

        if(isFinished && action->isForever){
            rewindListAction(action);
            isFinished = 0;
        }
    }

    return isFinished;
}

static int goThroughParameters(ListAction * action, ActionNode * node, va_list vl){
    int error = 0;
    
    do{
        node->isList = 1;
        node->isFinished = 0;

        node->action.list.first      = action->first;
        node->action.list.isParallel = action->isParallel;
        node->action.list.isForever  = action->isForever;
        node->next = NULL;
#ifndef DEBUG_SDL2_NO_VIDEO
        free(action);
#endif

        action = va_arg(vl, ListAction *);
        if(action){
            node->next = malloc(sizeof(*(node->next)));
            node = node->next;
            error = !node;
        }
    }while(action && !error);

    if(error && action){
        freeListAction(action);
        error = 2;
    }

    return error;
}

static ListAction * genericGenerateAction(ListAction * action, int isParallel, va_list vl){
    ListAction * result = NULL;
    ActionNode * node   = NULL;
    int          error  = 0;
    
    if(action){
        result = malloc(sizeof(*result));

        if(result){
            node = malloc(sizeof(*node));

            if(node){
                result->first = node;
                result->isParallel = isParallel;
                result->isForever = 0;

                // going through parameters
                error = goThroughParameters(action, node, vl);

                // if an allocation failed
                if(error){
                    freeListAction(result);
                    result = NULL;

                    if(error == 2){
                        action = va_arg(vl, ListAction *);
                        while(action){
                            freeListAction(action);
                            action = va_arg(vl, ListAction *);
                        }
                    }

                    error = 0;
                }
            }else{
                // if first node allocation failed
                free(result);
                result = NULL;

                error = 1;
            }
        }else{
            error = 1;
        }

        if(error){
            do{
                freeListAction(action);
                action = va_arg(vl, ListAction *);
            }while(action && !error);
        }
    }

    return result;
}

ListAction * generateChainedAction(ListAction * action, ...){
    ListAction * result;
    va_list      vl;

    va_start(vl, action);
    result = genericGenerateAction(action, 0, vl);
    va_end(vl);

    return result;
}

ListAction * generateParallelAction(ListAction * action, ...){
    ListAction * result;
    va_list      vl;

    va_start(vl, action);
    result = genericGenerateAction(action, 1, vl);
    va_end(vl);

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

        if(infos[2] < 0){
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

        if(infos[2] < 0){
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
            
        result = setDataAction(initAction(moveByActionFunction, time), data, 1);
        
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
            
        result = setDataAction(initAction(moveToActionFunction, time), data, 1);
        
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
            
        result = setDataAction(initAction(scaleByActionFunction, time), data, 1);
        
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
            
        result = setDataAction(initAction(scaleToActionFunction, time), data, 1);
        
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
            
        result = setDataAction(initAction(rotateByActionFunction, time), data, 1);
        
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
            
        result = setDataAction(initAction(rotateToActionFunction, time), data, 1);
        
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
        data[2] = -1;
            
        result = setDataAction(initAction(fadeInActionFunction, time), data, 1);
        
        if(!result){
            free(data);
        }
    }

    return result;
}

ListAction * fadeOutAction(int alpha, float time){
    ListAction * result = NULL;
    float      * data   = malloc(3 * sizeof(*data));

    if(data){
        data[0] = time;
        data[1] = (float)alpha;
        data[2] = -1;
            
        result = setDataAction(initAction(fadeOutActionFunction, time), data, 1);
        
        if(!result){
            free(data);
        }
    }

    return result;
}
/* ------------------------------------------------------- */
