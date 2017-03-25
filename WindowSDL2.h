#ifndef _FENETRE_SDL2_BY_KLEVH_
#define _FENETRE_SDL2_BY_KLEVH_

#include <string.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

/**
 * @file WindowSDL2.h
 * @author Baptiste PRUNIER (KLEVH)
 * @brief Contains all structures related to windows but only those unrelated to Elements.
 */

/**
 * @brief Get the absolute value of a variable
 */
#define absolu(a) ((a>0)?a:-a)
/**
 * @brief free p if it is not NULL
 */
#define PFREE(p){				\
    if(p){					\
      free(p);					\
    }						\
  }

struct ListElementSDL2;

/**
 * @struct WindowSDL2
 * @brief SANDAL2 window 
 */
typedef struct WindowSDL2{
  int height;
  /**< current height of the window*/
  int width;
  /**< current width of the window*/
  int initHeight;
  /**< initial height of the window*/
  int initWidth;
  /**< initial width of the window*/
  int displayCode;
  /**< display code of the window*/
  int background[4];
  /**< background color of the window*/
  SDL_Window *window;
  /**< true SDL2 window*/
  SDL_Renderer *renderer;
  /**< SDL2 renderer*/
  struct ListElementSDL2 * liste;
  /**< elements in the window*/
  struct WindowSDL2 * next;
  /**< next window*/
  unsigned toDelete;
  /**< number of element to be deleted by the cleaner*/
}WindowSDL2;

/**
 * @struct ListWindowSDL2
 * @brief list of windows
 */
typedef struct{
  WindowSDL2 * first;
  /**<First WindowSDL2 of the list*/
  WindowSDL2 * last;
  /**<Last WindowSDL2 of the list*/
  WindowSDL2 * current;
  /**<current WindowSDL2 of the list*/
}ListWindowSDL2;


/**
 * @brief list of windows
 *   WARNING : do not touch this variable, never ... trust me
 */
extern ListWindowSDL2 * _windows_SDL2TK;

/* -------------------------------------------------------
 * Window SDL2
 */
/**
 * @brief Resize the current window
 * @param width : new width of the current window
 * @param height : new height of the current window
 */
void resizeWindowSDL2(unsigned width,unsigned height);
/**
 * @brief Change the display code of the current window
 * @param displayCode : new display code of the current window
 */
void changeDisplayWindowSDL2(int displayCode);
/**
 * @brief Initialise the iterator of the windows' list
 * @return 0 if the iterator could not be initialised, 1 if it could
 */
int initIteratorWindowSDL2();
/**
 * @brief Go to the next window
 * @return 1 if it was possible, 0 if not
 */
int nextWindowSDL2();
/**
 * @brief Put the width of the current window in w (if not NULL) and its height in h (if not NULL)
 * @param w : where the width of the current window should be store
 * @param h : where the height of the current window should be store
 * @return 1 if there was an error, 0 if not
 */
int getDimensionWindowSDL2(int * w,int * h);
/**
 * @brief Put the display code of the current window in d (if not NULL)
 * @param d : where the display code of the current window should be store
 * @return 1 if there was an error, 0 if not
 */
int getDisplayCodeWindowSDL2(int * d);
/**
 * @brief Put the background color of the current window in color
 * @param color : where the background color of the current window should be store
 * @return 1 if there was an error, 0 if not
 */
int getColorWindowSDL2(int color[4]);
/**
 * @brief Change the background color of the current window
 * @param color : new color of the background of the current window
 * @return 1 if there was an error, 0 if not
 */
int setColorWindowSDL2(int color[4]);
/**
 * @brief Getter for the current window position
 * @param x : where the abscissa coordinate of the window will be store
 * @param y : where the ordinate coordinate of the window will be store
 * @return 1 if there was an error, 0 if not
 */
int getCoordWindowSDL2(int *x,int *y);
/**
 * @brief Set for the current window position
 * @param x : new abscissa coordinate of the window
 * @param y : new ordinate coordinate of the window
 * @return 1 if there was an error, 0 if not
 */
int setCoordWindowSDL2(int x,int y);
/**
 * @brief Getter for the real dimension of the current window (do not use this function to calculate elements' size or coordinates, use getDimensionWindowSDL2 instead)
 * @param width : where the real width of the window will be store
 * @param height : where the real height of the window will be store
 * @return 1 if there was an error, 0 if not
 */
int getRealDimensionWindowSDL2(int *width,int *height);
/**
 * @brief Getter for the curent window ID
 * @param ID : where to store the ID
 * @return 1 if there was an error, 0 if not
 */
int getIDWindowSDL2(Uint32 *ID);
/* ------------------------------------------------------- */

/* -------------------------------------------------------
 * Other functions
 */
/**
 * @brief Compare two static arrays of size 4
 * @param c1 : first array to be compared
 * @param c2 : second array to be compared
 * @return 1 if both arrays are equal, 0 if not
 */
int cmpCoul(int c1[4],int c2[4]);
/**
 * @brief Copy a static array of size 4 in another
 * @param to : where the second array will be copied
 * @param from : array to copy
 */
void copyColor(int to[4],int from[4]);
/* ------------------------------------------------------- */

#endif
