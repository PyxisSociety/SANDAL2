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
/**
 * @brief function used by moveByAction() and left public to be used in self made action functions
 * @param e : element on which the action is called
 * @param data : a float* array of size 5 casted to void*. It MUST have the following format:
 *               [the duration of the action, the x delta, the y delta, 0, 0]
 *               the last two values MUST be set to 0 before the first call, they will be modified inside the function
 *               those modifications NEEDS to be saved for the following calls
 * @param spentTime : total spent time since the beginning of the action
 */
void moveByActionFunction(struct Element * e, void * data, float spentTime);
/**
 * @brief function used by moveToAction() and left public to be used in self made action functions
 * @param e : element on which the action is called
 * @param data : a float* array of size 5 casted to void*. It MUST have the following format:
 *               [the duration of the action, the x new value, the y new value, 0, 0]
 *               the last two values MUST be set to 0 before the first call, they will be modified inside the function
 *               those modifications NEEDS to be saved for the following calls
 * @param spentTime : total spent time since the beginning of the action
 */
void moveToActionFunction(struct Element * e, void * data, float spentTime);
/**
 * @brief function used by scaleByAction() and left public to be used in self made action functions
 * @param e : element on which the action is called
 * @param data : a float* array of size 5 casted to void*. It MUST have the following format:
 *               [the duration of the action, the x scale value, the y scale value, 0, 0]
 *               the last two values MUST be set to 0 before the first call, they will be modified inside the function
 *               those modifications NEEDS to be saved for the following calls
 * @param spentTime : total spent time since the beginning of the action
 */
void scaleByActionFunction(struct Element * e, void * data, float spentTime);
/**
 * @brief function used by scaleToAction() and left public to be used in self made action functions
 * @param e : element on which the action is called
 * @param data : a float* array of size 5 casted to void*. It MUST have the following format:
 *               [the duration of the action, the x scale value, the y scale value, 0, 0]
 *               the last two values MUST be set to 0 before the first call, they will be modified inside the function
 *               those modifications NEEDS to be saved for the following calls
 * @param spentTime : total spent time since the beginning of the action
 */
void scaleToActionFunction(struct Element * e, void * data, float spentTime);
/**
 * @brief function used by rotateByAction() and left public to be used in self made action functions
 * @param e : element on which the action is called
 * @param data : a float* array of size 3 casted to void*. It MUST have the following format:
 *               [the duration of the action, the angle delta, 0]
 *               the last value MUST be set to 0 before the first call, it will be modified inside the function
 *               those modifications NEEDS to be saved for the following calls
 * @param spentTime : total spent time since the beginning of the action
 */
void rotateByActionFunction(struct Element * e, void * data, float spentTime);
/**
 * @brief function used by rotateToAction() and left public to be used in self made action functions
 * @param e : element on which the action is called
 * @param data : a float* array of size 3 casted to void*. It MUST have the following format:
 *               [the duration of the action, the new angle, 0]
 *               the last value MUST be set to 0 before the first call, it will be modified inside the function
 *               those modifications NEEDS to be saved for the following calls
 * @param spentTime : total spent time since the beginning of the action
 */
void rotateToActionFunction(struct Element * e, void * data, float spentTime);
/**
 * @brief function used by fadeInAction() and left public to be used in self made action functions
 * @param e : element on which the action is called
 * @param data : a float* array of size 3 casted to void*. It MUST have the following format:
 *               [the duration of the action, the delta to decrement alpha with, 0]
 *               the last value MUST be set to 0 before the first call, it will be modified inside the function
 *               those modifications NEEDS to be saved for the following calls
 * @param spentTime : total spent time since the beginning of the action
 */
void fadeInActionFunction(struct Element * e, void * data, float spentTime);
/**
 * @brief function used by fadeOutAction() and left public to be used in self made action functions
 * @param e : element on which the action is called
 * @param data : a float* array of size 3 casted to void*. It MUST have the following format:
 *               [the duration of the action, the delta to increment alpha with, 0]
 *               the last value MUST be set to 0 before the first call, it will be modified inside the function
 *               those modifications NEEDS to be saved for the following calls
 * @param spentTime : total spent time since the beginning of the action
 */
void fadeOutActionFunction(struct Element * e, void * data, float spentTime);
/* ------------------------------------------------------- */





/* -------------------------------------------------------
 * Action pre made actions
 */
ListAction * moveByAction(float x, float y, float time);
ListAction * moveToAction(float x, float y, float time);
/**
 * @brief Generate a ListAction doing a scale XY (only X if y == 0, only Y if x == 0) during a given time
 * @param x : scale value of x (percentage of modification with 1.0 == +100%)
 * @param y : scale value of y (percentage of modification with 1.0 == +100%)
 * @param time : duration of the action
 * @return the list action generated
 */
ListAction * scaleByAction(float x, float y, float time);
ListAction * scaleToAction(float w, float h, float time);
ListAction * rotateByAction(float angle, float time);
ListAction * rotateToAction(float angle, float time);
ListAction * fadeInAction(int alpha, float time);
ListAction * fadeOutAction(int alpha, float time);
/* ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif
