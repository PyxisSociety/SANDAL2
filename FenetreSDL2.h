#ifndef _FENETRE_SDL2_BY_KLEVH_
#define _FENETRE_SDL2_BY_KLEVH_

#include <string.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

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
 * @struct FenetreSDL2
 * @brief SDL2TK window 
 */
typedef struct FenetreSDL2{
  int height;
  ///< current height of the window
  int width;
  ///< current width of the window
  int initHeight;
  ///< initial height of the window
  int initWidth;
  ///< initial width of the window
  int displayCode;
  ///< display code of the window
  int background[4];
  ///< background color of the window
  SDL_Window *window;
  ///< true SDL2 window
  SDL_Renderer *renderer;
  ///< SDL2 renderer
  struct ListElementSDL2 * liste;
  ///< elements in the window
  struct FenetreSDL2 * next;
  ///< next window
}FenetreSDL2;

/**
 * @struct ListFenetreSDL2
 * @brief list of windows
 */
typedef struct{
  FenetreSDL2 * first;
  FenetreSDL2 * last;
  FenetreSDL2 * current;
}ListFenetreSDL2;


/**
 * @brief list of windows
 *   WARNING : do not touch this variable, never ... trust me
 */
extern ListFenetreSDL2 * _windows_SDL2TK;

/* -------------------------------------------------------
 * Fenetre SDL2
 */
/**
 * @brief Resize the current window
 * @param width : new width of the current window
 * @param height : new height of the current window
 */
void resizeFenetreSDL2(unsigned width,unsigned height);
/**
 * @brief Change the display code of the current window
 * @param displayCode : new display code of the current window
 */
void changeDisplayFenetreSDL2(int displayCode);
/**
 * @brief Initialise the iterator of the windows' list
 * @return 0 if the iterator could not be initialised, 1 if it could
 */
int initIteratorFenetreSDL2();
/**
 * @brief Go to the next window
 * @return 1 if it was possible, 0 if not
 */
int nextFenetreSDL2();
/**
 * @brief Put the width of the current window in w (if not NULL) and its height in h (if not NULL)
 * @param w : where the width of the current window should be store
 * @param h : where the height of the current window should be store
 * @return 1 if there was an error, 0 if not
 */
int getDimensionFenetreSDL2(int * w,int * h);
/**
 * @brief Put the display code of the current window in d (if not NULL)
 * @param d : where the display code of the current window should be store
 * @return 1 if there was an error, 0 if not
 */
int getDisplayCodeFenetreSDL2(int * d);
/**
 * @brief Put the background color of the current window in color
 * @param color : where the background color of the current window should be store
 * @return 1 if there was an error, 0 if not
 */
int getColorFenetreSDL2(int color[4]);
/**
 * @brief Change the background color of the current window
 * @param color : new color of the background of the current window
 * @return 1 if there was an error, 0 if not
 */
int setColorFenetreSDL2(int color[4]);
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
