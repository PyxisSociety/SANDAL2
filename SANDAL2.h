#ifndef MAIN_SANDAL2_KLEVH
#define MAIN_SANDAL2_KLEVH

#ifdef __cplusplus
extern "C" {
#endif
    
#include "Element.h"

/**
 * @file SANDAL2.h
 * @author Baptiste PRUNIER (KLEVH)
 * @version 1.1.0
 * @brief File to include which includes everything else.
 *  Compilation flags to use :
 *    -lSDL2 -lSDL2_ttf -lSDL2_image -lm
 */

/**
 * @brief list of windows
 *   WARNING : do not touch this variable, never ... trust me
 */
  extern ListWindow * _windows_SANDAL2;

/* -------------------------------------------------------
 * Initialisation et fermeture des outils 
 */
/**
 * @brief Initialisation of SANDAL2, its image and fonts (return 1 if  initialisation error, 2 if image initialisation error, 3 if font initialisation error, 0 if not) using SDL2's image flags
 * @param imageFlags : SDL2's image flags
 * @return error code
 */
int initAllSANDAL2(int imageFlags);
/**
 * @brief Close SANDAL2, images and font
 */
void closeAllSANDAL2(void);
/**
 * @brief Initialisation of SANDAL2 alone
 * @return 0 if success, 1 if failed
 */
int initSANDAL2(void);
/**
 * @brief Initialisation of images alone
 * @param imageFlags : SDL2's image flags
 * @return 0 if success, 1 if failed
 */
int initImageSANDAL2(int imageFlags);
/**
 * @brief Initialisation of text alone
 * @return 0 if success, 1 if failed
 */
int initTextSANDAL2(void);
/**
 * @brief Close SDL2
 */
void closeSANDAL2(void);
/**
 * @brief Close images
 */
void closeImageSANDAL2(void);
/**
 * @brief Close font
 */
void closeTextSANDAL2(void);
/* ------------------------------------------------------- */

/* ------------------------------------------------------- 
 * Creation, modification et suppression des fenetres
 */
/**
 * @brief Add a window to the list of windows
 * @param width : width of the window
 * @param height : height of the window
 * @param title : title of the window
 * @param SDLFlags : flags of SDL2
 * @param background : color of the background
 * @param displayCode : display code of the window
 * @return 1 if it failed, 0 if not
 */
int createWindow(int width,int height,const char *title,int SDLFlags,int background[4],int displayCode);
/**
 * @brief close the current windows and go to the next, do not use this one in elements' or windows' binded functions, use shouldCloseWindow() instead
 * @return 1 if it failed, 0 if not
 */
int closeWindow(void);
/**
 * @brief tells that the current window should be closed, do not use this one in functions that are not binded to windows or elements, use closeWindow() instead
 * @return 1 if it failed, 0 if not
 */
int shouldCloseWindow(void);
/**
 * @brief close all windows
 * @return 1 if it failed, 0 if not
 */
int closeAllWindow(void);
/**
 * @brief Toggle the full screen mode of the current window
 * @return 0 if succeeded, 1 if not
 */
int toggleFullScreenWindow(void);
/**
 * @brief Tells whether or not the window is in full screen mode
 * @return 1 if the current window is in full screen mode, 0 if not or if there is no current window
 */
int isFullScreenWindow(void);
/* ------------------------------------------------------- */

/* -------------------------------------------------------
 * Gestion des Fenetres 
 */
/**
 * @brief update all the elements of the current window
 * @return 1 if it failed, 0 if not
 */
int updateWindow(void);
/**
 * @brief actualise the display of the current window 
 * @return 1 if it failed, 0 if not
 */
  int displayWindow(void);
/**
 * @brief activation of click events on the current window
 * @param x : abscissa coordinate of the mouse during the click
 * @param y : ordinate coordinate of the mouse during the click
 * @return 1 if it failed, 0 if not
 */
int clickWindow(SDL_MouseButtonEvent button);
/**
 * @brief activation of unclick events on the current window
 * @param x : abscissa coordinate of the mouse during the unclick
 * @param y : ordinate coordinate of the mouse during the unclick
 * @return 1 if it failed, 0 if not
 */
int unclickWindow(SDL_MouseButtonEvent button);
/**
 * @brief activation of the key pressed events on the current window
 * @param c : key which was pressed
 * @return 1 if it failed, 0 if not
 */
int keyPressedWindow(int c);
/**
 * @brief activation of the key released events on the current window
 * @param c : key which was released
 * @return 1 if it failed, 0 if not
 */
int keyReleasedWindow(int c);
/**
 * @brief update all the elements of all the windows
 * @return 1 if it failed, 0 if not
 */
unsigned long updateAllWindow(void);
/**
 * @brief actualise the display of all the windows 
 * @return 0 if it succeeded, a binary code telling which window failed (example : 100101 tells that the second and the fifth window failed, the first bit on the rigth only tells that there was an error), if you have more window than bits for int, you will not be able to tell which of the window failed in those which have a bigger number than the number of bit minus one
 */
unsigned long displayAllWindow(void);
/**
 * @brief activation of click events on all the windows
 * @param x : abscissa coordinate of the mouse during the click
 * @param y : ordinate coordinate of the mouse during the click
 * @return 0 if it succeeded, a binary code telling which window failed (example : 100101 tells that the second and the fifth window failed, the first bit on the rigth only tells that there was an error), if you have more window than bits for int, you will not be able to tell which of the window failed in those which have a bigger number than the number of bit minus one
 */
unsigned long clickAllWindow(SDL_MouseButtonEvent event);
/**
 * @brief activation of unclick events on all the windows
 * @param x : abscissa coordinate of the mouse during the unclick
 * @param y : ordinate coordinate of the mouse during the unclick
 * @return 0 if it succeeded, a binary code telling which window failed (example : 100101 tells that the second and the fifth window failed, the first bit on the rigth only tells that there was an error), if you have more window than bits for int, you will not be able to tell which of the window failed in those which have a bigger number than the number of bit minus one
 */
unsigned long unclickAllWindow(SDL_MouseButtonEvent);
/**
 * @brief activation of the key pressed events on all windows
 * @param c : key which was pressed
 * @return 0 if it succeeded, a binary code telling which window failed (example : 100101 tells that the second and the fifth window failed, the first bit on the rigth only tells that there was an error), if you have more window than bits for int, you will not be able to tell which of the window failed in those which have a bigger number than the number of bit minus one
 */
unsigned long keyPressedAllWindow(char c);
/**
 * @brief activation of the key released events on all windows
 * @param c : key which was released
 * @return 0 if it succeeded, a binary code telling which window failed (example : 100101 tells that the second and the fifth window failed, the first bit on the rigth only tells that there was an error), if you have more window than bits for int, you will not be able to tell which of the window failed in those which have a bigger number than the number of bit minus one
 */
unsigned long keyReleasedAllWindow(char c);
unsigned long wheelWindow(int y);
/* ------------------------------------------------------- */

/* ------------------------------------------------------- 
 * Gestion d'evenement
 */
/**
 * @brief Get the event (if there is one) and apply the corresponding functions
 * @param error: where to store the error flag (0 if it succeeded, a binary code telling which window failed (example : 100101 tells that the second and the fifth window failed, the first bit on the rigth only tells that there was an error), if you have more window than bits for int, you will not be able to tell which of the window failed in those which have a bigger number than the number of bit minus one)
 * @return 1 if the user asked to close the window, 0 if not
 */
int PollEvent(unsigned long * error);
/* ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif
    
#endif
