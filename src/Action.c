#include "Action.h"
#include "Element.h"

#include <stdarg.h>
#include <stdlib.h>



/* -------------------------------------------------------
 * Action functions
 */
ListAction * initAction(void (*action)(struct Element *, void *, double), double timing){
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

static int executeOneAction(Action * action, struct Element * e, double time){
    double ratio;
    
    // incrementing time
    action->timeSpent += time;
    if(action->timeSpent > action->timing){
        action->timeSpent = action->timing;
    }

    // calculating the ratio
    if(action->timeSpent + 1e-7 >= action->timing){
        ratio = 1;
    }else{
        ratio = (action->timing - (action->timing - action->timeSpent)) / action->timing;
    }
    
    // doing behavior, if any
    if(action->action){
        action->action(e, action->data, ratio);
    }

    return ratio >= 1;
}

static void rewindListAction(ListAction * action){
    ActionNode * node = action->first;

    while(node){
        node->isFinished = 0;

        if(node->isList){
            rewindListAction(&(node->action.list));
        }else{
            node->action.action.timeSpent = 0.f;
        }

        node = node->next;
    }
}

int executeListAction(ListAction * action, struct Element * e, double time){
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

ListAction * setForeverAction(ListAction * action, int isForever){
    if(action){
        action->isForever = isForever;
    }

    return action;
}

long long addActionAtEndAction(ListAction * action, ListAction * toAdd){
    long long     index = -1;
    ActionNode ** node;
    ActionNode  * newNode;
    
    if(action && toAdd){
        newNode = malloc(sizeof(*newNode));

        if(newNode){
            newNode->isList = 1;
            newNode->isFinished = 0;

            newNode->action.list.first      = toAdd->first;
            newNode->action.list.isParallel = toAdd->isParallel;
            newNode->action.list.isForever  = toAdd->isForever;
            newNode->next = NULL;
#ifndef DEBUG_SDL2_NO_VIDEO
            free(toAdd);
#endif
        
            index = 0;
            node = &(action->first);
            while(*node){
                ++index;
                node = &((*node)->next);
            }

            *node = newNode;
        }
    }

    return index;
}

int delActionToAction(ListAction * action, long long index){
    ActionNode ** node;
    ActionNode  * tmp;
    int           succeeded = 0;

    if(action && index >= 0){
        node = &(action->first);
        while(*node && index){
            --index;
            node = &((*node)->next);
        }

        if(*node){
            succeeded = 1;
            tmp = *node;
            *node = (*node)->next;
            tmp->next = NULL;
            if(tmp->isList){
                freeActionNode(tmp->action.list.first);
            }else if(tmp->action.action.shouldBeFreed && tmp->action.action.data){
                free(tmp->action.action.data);
            }
            free(tmp);
        }
    }

    return !succeeded;
}
/* ------------------------------------------------------- */





/* -------------------------------------------------------
 * Action pre made action functions
 */
void moveByActionFunction(struct Element * e, void * data, double spentTime){
    double * infos = (double*)data;
    double moveX, moveY;
    double x, y;
    
    if(e && data){
        if(!infos[2] && !infos[3]){
            getCoordElement(e, infos + 2, infos + 3);
        }
        getCoordElement(e, &x, &y);

        moveX = infos[0] * (spentTime - infos[6]);
        moveY = infos[1] * (spentTime - infos[6]);

        if((infos[4] < infos[2] + infos[0] && moveX + infos[4] >= infos[2] + infos[0])
            || (infos[4] > infos[2] + infos[0] && moveX + infos[4] <= infos[2] + infos[0])){
            moveX = infos[2] + infos[0];
        }
        if((infos[5] < infos[3] + infos[1] && moveX + infos[5] >= infos[3] + infos[1])
            || (infos[5] > infos[3] + infos[1] && moveX + infos[5] <= infos[3] + infos[1])){
            moveY = infos[3] + infos[1];
        }
        
        if(moveX){
            setCoordXElement(e, x + moveX);
        }
        if(moveY){
            setCoordYElement(e, y + moveY);
        }

        infos[4] += moveX;
        infos[5] += moveY;

        infos[6] = spentTime;
    }
}

void moveToActionFunction(struct Element * e, void * data, double spentTime){
    double * infos = (double*)data;
    double   newX;
    double   newY;
    double   oldX;
    double   oldY;
    
    if(e && data){
        newX  = infos[0];
        newY  = infos[1];

        if(!infos[2] && !infos[3]){
            getCoordElement(e, infos + 2, infos + 3);
        }
        
        oldX  = infos[2];
        oldY  = infos[3];

        if(newX){
            setCoordXElement(e, oldX + (newX - oldX) * spentTime);
        }
        if(newY){
            setCoordYElement(e, oldY + (newY - oldY) * spentTime);
        }
    }
}

void scaleByActionFunction(struct Element * e, void * data, double spentTime){
    double * infos = (double*)data;
    double   x;
    double   y;
    double   w;
    double   h;
    
    if(e && data){
        x     = infos[0];
        y     = infos[1];

        if(!infos[2] && !infos[3]){
            getDimensionElement(e, infos + 2, infos + 3);
        }
        
        w     = infos[2];
        h     = infos[3];

        if(x){
            setWidthElement(e, w + w * x * spentTime);
        }
        if(y){
            setHeightElement(e, h + h * y * spentTime);
        }
    }
}

void scaleToActionFunction(struct Element * e, void * data, double spentTime){
    double * infos = (double*)data;
    double   newW;
    double   newH;
    double   oldW;
    double   oldH;
    
    if(e && data){
        newW  = infos[0];
        newH  = infos[1];

        if(!infos[2] && !infos[3]){
            getDimensionElement(e, infos + 2, infos + 3);
        }
        
        oldW  = infos[2];
        oldH  = infos[3];

        if(newW){
            setWidthElement(e, oldW + (newW - oldW) * spentTime);
        }
        if(newH){
            setHeightElement(e, oldH + (newH - oldH) * spentTime);
        }
    }
}

void rotateByActionFunction(struct Element * e, void * data, double spentTime){
    double * infos = (double*)data;
    double   toAdd;
    double   angle;
    
    if(e && data){
        if(!infos[1]){
            getAngleElement(e, infos + 1);
        }
        getAngleElement(e, &angle);

        toAdd = infos[0] * (spentTime - infos[3]);

        if((infos[2] < infos[0] && toAdd + infos[2] > infos[0])
           || (infos[2] > infos[0] && toAdd + infos[2] < infos[1])){
            toAdd = infos[0] + infos[2];
        }
        
        setAngleElement(e, angle + toAdd);

        infos[2] += toAdd;
        infos[3] = spentTime;
    }
}

void rotateToActionFunction(struct Element * e, void * data, double spentTime){
    double * infos = (double*)data;
    double   newAngle;
    double   oldAngle;
    
    if(e && data){
        newAngle = infos[0];

        if(!infos[1]){
            getAngleElement(e, infos + 1);
        }
        
        oldAngle = infos[1];

        setAngleElement(e, oldAngle + (newAngle - oldAngle) * spentTime);
    }
}
void fadeInActionFunction(struct Element * e, void * data, double spentTime){
    double * infos = (double*)data;
    int     oldAlpha;
    int     newAlpha;
    
    if(e && data){
        newAlpha = (int)infos[0];

        if(infos[1] < 0){
            getAlphaElement(e, &oldAlpha);
            infos[1] = (double)oldAlpha;
        }else{        
            oldAlpha = infos[1];
        }

        setAlphaElement(e, oldAlpha - newAlpha * spentTime);
    }
}
void fadeOutActionFunction(struct Element * e, void * data, double spentTime){
    double * infos = (double*)data;
    int     oldAlpha;
    int     newAlpha;
    
    if(e && data){
        newAlpha = (int)infos[0];

        if(infos[1] < 0){
            getAlphaElement(e, &oldAlpha);
            infos[1] = (double)oldAlpha;
        }else{        
            oldAlpha = infos[1];
        }
        
        setAlphaElement(e, oldAlpha + newAlpha * spentTime);
    }
}
/* ------------------------------------------------------- */





/* -------------------------------------------------------
 * Action pre made actions
 */
ListAction * moveByAction(double x, double y, double time){
    ListAction * result = NULL;
    double      * data   = malloc(7 * sizeof(*data));

    if(data){
        data[0] = x;
        data[1] = y;
        data[2] = 0;
        data[3] = 0;
        data[4] = 0;
        data[5] = 0;
        data[6] = 0;
            
        result = setDataAction(initAction(moveByActionFunction, time), data, 1);
        
        if(!result){
            free(data);
        }
    }

    return result;
}

ListAction * moveToAction(double x, double y, double time){
    ListAction * result = NULL;
    double      * data   = malloc(4 * sizeof(*data));

    if(data){
        data[0] = x;
        data[1] = y;
        data[2] = 0;
        data[3] = 0;
            
        result = setDataAction(initAction(moveToActionFunction, time), data, 1);
        
        if(!result){
            free(data);
        }
    }

    return result;
}

ListAction * scaleByAction(double x, double y, double time){
    ListAction * result = NULL;
    double      * data   = malloc(4 * sizeof(*data));

    if(data){
        data[0] = x;
        data[1] = y;
        data[2] = 0;
        data[3] = 0;
            
        result = setDataAction(initAction(scaleByActionFunction, time), data, 1);
        
        if(!result){
            free(data);
        }
    }

    return result;
}

ListAction * scaleToAction(double w, double h, double time){
    ListAction * result = NULL;
    double      * data   = malloc(4 * sizeof(*data));

    if(data){
        data[0] = w;
        data[1] = h;
        data[2] = 0;
        data[3] = 0;
            
        result = setDataAction(initAction(scaleToActionFunction, time), data, 1);
        
        if(!result){
            free(data);
        }
    }

    return result;
}

ListAction * rotateByAction(double angle, double time){
    ListAction * result = NULL;
    double      * data   = malloc(4 * sizeof(*data));

    if(data){
        data[0] = angle;
        data[1] = 0;
        data[2] = 0;
        data[3] = 0;
            
        result = setDataAction(initAction(rotateByActionFunction, time), data, 1);
        
        if(!result){
            free(data);
        }
    }

    return result;
}

ListAction * rotateToAction(double angle, double time){
    ListAction * result = NULL;
    double      * data   = malloc(2 * sizeof(*data));

    if(data){
        data[0] = angle;
        data[1] = 0;
            
        result = setDataAction(initAction(rotateToActionFunction, time), data, 1);
        
        if(!result){
            free(data);
        }
    }

    return result;
}

ListAction * fadeInAction(int alpha, double time){
    ListAction * result = NULL;
    double      * data   = malloc(3 * sizeof(*data));

    if(data){
        data[0] = (double)alpha;
        data[1] = -1;
            
        result = setDataAction(initAction(fadeInActionFunction, time), data, 1);
        
        if(!result){
            free(data);
        }
    }

    return result;
}

ListAction * fadeOutAction(int alpha, double time){
    ListAction * result = NULL;
    double      * data   = malloc(3 * sizeof(*data));

    if(data){
        data[0] = (double)alpha;
        data[1] = -1;
            
        result = setDataAction(initAction(fadeOutActionFunction, time), data, 1);
        
        if(!result){
            free(data);
        }
    }

    return result;
}
/* ------------------------------------------------------- */
