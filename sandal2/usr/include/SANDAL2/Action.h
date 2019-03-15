#ifndef ACTIONSDL2_SANDAL2_KLEVH
#define ACTIONSDL2_SANDAL2_KLEVH

#ifdef __cplusplus
extern "C" {
#endif

// macro to prevent auto tabulation
#if 1 < 0
}
#endif

/**
 * @file Action.h
 * @author Baptiste PRUNIER (KLEVH)
 * @brief Contains all structures related to actions on element
 */

struct Element;
typedef struct Action{
    float timing;
    /**< time for the action to be executed (in seconds), value inferior to 0 for infinite action */
    float timeSpent;
    /**< time already spent for the action (in seconds), it stays at 0 if timing is < 0 */
    void (*action)(struct Element *, void *, float);
    /**< action to be executed */
    void * data;
    /**< data of the action */
    int shouldBeFreed;
    /**< tells whether or not the data should be freed */
} Action;

typedef struct ListAction{
    struct ListAction * chained;
    /**< chained actions */
    struct ListAction * parallel;
    /**< parallel actions */
    Action * action;
    /**< action corresponding to this node of the action list architecture */
    int isParallel;
    /**< tells whether or not this list is the starting point of a parallel list */
} ListAction;





/* -------------------------------------------------------
 * Action functions
 */
/**
 * @brief Create an action based on its behavior and the time it should take
 * @param action : behavior of the action, takes 3 parameters : the element on which it will be applied, the data of the action and the total time elapsed since its beginning
 * @param timing : duration of the action, 0 is forbidden but a negative value makes the action infinite
 * @return the created action (NULL on failure)
 */
Action * initAction(void (*action)(struct Element *, void *, float), float timing);
/**
 * @brief Free the memory of an action
 * @param action : action to be freed
 */
void freeAction(Action * action);
/**
 * @brief Set the data bound to an action
 * @param action : action to bind data to
 * @param data : data to be bound to the action
 * @param shouldBeFreed : flag to tell whether or not the data should be freed
 * @return the action passed as first parameter
 */
Action * setDataAction(Action * action, void * data, int shouldBeFreed);
/* ------------------------------------------------------- */





/* -------------------------------------------------------
 * ListAction functions
 */
/**
 * @brief Create a list action from an action
 * @param action : action to be cast (do not free it yourself and use it only once)
 * @return the action casted as a list
 */
ListAction * actionAsList(Action * action);
/**
 * @brief Free the memory of a list action
 * @param action : list to be freed
 */
void freeListAction(ListAction * action);
/**
 * @brief Execute a list action and return the resulting list (after removing ended actions)
 * @param action : list to be executed
 * @param e : element to call actions on
 * @param time : time elapsed since last call of this function
 * @return the resulting list (after removing ended actions)
 */
ListAction * executeListAction(ListAction * action, struct Element * e, float time);
/**
 * @brief Generate a list of chained action (the nth action execute after the (n - 1)th ended)
 * @param action... : all list action of the list, needs to end by NULL. Passing the result of generateChainedAction() as one of its parameters will cause errors when executing them
 * @return the first action passed as parameter of action... after setting its chained actions
 */
ListAction * generateChainedAction(ListAction * action, ...);
/**
 * @brief Generate a list of parallel action
 * @param action... : all list action of the list, needs to end by NULL. Passing the result of generateParallelAction() as one of its parameters will cause errors when executing them
 * @return the first action passed as parameter of action... after setting its parallel actions
 */
ListAction * generateParallelAction(ListAction * action, ...);
/* ------------------------------------------------------- */





/* -------------------------------------------------------
 * Action pre made action functions
 */
/*
void moveByActionFunction(struct Element * e, void * data, float spentTime);
void moveToActionFunction(struct Element * e, void * data, float spentTime);
*/
// [max time, scale X, scale Y, original W, original H]
void scaleByActionFunction(struct Element * e, void * data, float spentTime);
/*
void scaleToActionFunction(struct Element * e, void * data, float spentTime);
void rotateByActionFunction(struct Element * e, void * data, float spentTime);
void rotateToActionFunction(struct Element * e, void * data, float spentTime);
void fadeInActionFunction(struct Element * e, void * data, float spentTime);
void fadeOutToActionFunction(struct Element * e, void * data, float spentTime);
*/
/* ------------------------------------------------------- */





/* -------------------------------------------------------
 * Action pre made actions
 */
/*
ListAction * moveByAction(struct Element * e, float x, float y, float time);
ListAction * moveToAction(struct Element * e, float x, float y, float time);
*/
ListAction * scaleByAction(struct Element * e, float x, float y, float time);
/*
ListAction * scaleToAction(struct Element * e, float x, float y, float time);
ListAction * rotateByAction(struct Element * e, float angle, float time);
ListAction * rotateToAction(struct Element * e, float angle, float time);
ListAction * fadeInAction(struct Element * e, float x, float y, float time);
ListAction * fadeOutToAction(struct Element * e, float x, float y, float time);
*/
/* ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif
