#ifndef _MAIN_SANDAL2_KLEVH_
#define _MAIN_SANDAL2_KLEVH_

#include "ElementSDL2.h"

/**
 * @file SANDAL2.h
 * @author Baptiste PRUNIER (KLEVH)
 * @version 1.0.1
 * @brief File to include which includes everything else.
 *  Compilation flags to use :
 *    -lSDL2 -lSDL2_ttf -lSDL2_image -lm
 */

/**
 * @brief list of windows
 *   WARNING : do not touch this variable, never ... trust me
 */
extern ListWindowSDL2 * _windows_SANDAL2;

/* -------------------------------------------------------
 * Initialisation et fermeture des outils SDL2
 */
/**
 * @brief Initialisation of SDL2, its image and fonts (return 1 if SDL2 initialisation error, 2 if image initialisation error, 3 if font initialisation error, 0 if not) using SDL2's image flags
 * @param imageFlags : SDL2's image flags
 * @return error code
 */
int initAllSDL2(int imageFlags);
/**
 * @brief Close SDL2, images and font
 */
void closeAllSDL2();
/**
 * @brief Initialisation of SDL2 alone
 * @return 0 if success, 1 if failed
 */
int initSDL2();
/**
 * @brief Initialisation of images alone
 * @param imageFlags : SDL2's image flags
 * @return 0 if success, 1 if failed
 */
int initImage(int imageFlags);
/**
 * @brief Initialisation of text alone
 * @return 0 if success, 1 if failed
 */
int initTexte();
/**
 * @brief Close SDL2
 */
void closeSDL2();
/**
 * @brief Close images
 */
void closeImage();
/**
 * @brief Close font
 */
void closeTexte();
/* ------------------------------------------------------- */

/* -------------------------------------------------------
 * Fenetre SDL2
 */
/**
 * @brief Free a window's memory
 */
void freeWindowSDL2(WindowSDL2 *fen);
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
int initWindowSDL2(int width,int height,char *title,int SDLFlags,int background[4],int displayCode);
/**
 * @brief update all the elements of the current window
 * @return 1 if it failed, 0 if not
 */
int updateWindowSDL2();
/**
 * @brief actualise the display of the current window 
 * @return 1 if it failed, 0 if not
 */
int displayWindowSDL2();
/**
 * @brief activation of click events on the current window
 * @param x : abscissa coordinate of the mouse during the click
 * @param y : ordinate coordinate of the mouse during the click
 * @return 1 if it failed, 0 if not
 */
int clickWindowSDL2(int x,int y);
/**
 * @brief activation of unclick events on the current window
 * @param x : abscissa coordinate of the mouse during the unclick
 * @param y : ordinate coordinate of the mouse during the unclick
 * @return 1 if it failed, 0 if not
 */
int unclickWindowSDL2(int x,int y);
/**
 * @brief activation of the key pressed events on the current window
 * @param c : key which was pressed
 * @return 1 if it failed, 0 if not
 */
int keyPressedWindowSDL2(char c);
/**
 * @brief activation of the key released events on the current window
 * @param c : key which was released
 * @return 1 if it failed, 0 if not
 */
int keyReleasedWindowSDL2(char c);
/**
 * @brief update all the elements of all the windows
 * @return 1 if it failed, 0 if not
 */
int updateAllWindowSDL2();
/**
 * @brief actualise the display of all the windows 
 * @return 0 if it succeeded, a binary code telling which window failed (example : 100101 tells that the second and the fifth window failed, the first bit on the rigth only tells that there was an error), if you have more window than bits for int, you will not be able to tell which of the window failed in those which have a bigger number than the number of bit minus one
 */
int displayAllWindowSDL2();
/**
 * @brief activation of click events on all the windows
 * @param x : abscissa coordinate of the mouse during the click
 * @param y : ordinate coordinate of the mouse during the click
 * @return 0 if it succeeded, a binary code telling which window failed (example : 100101 tells that the second and the fifth window failed, the first bit on the rigth only tells that there was an error), if you have more window than bits for int, you will not be able to tell which of the window failed in those which have a bigger number than the number of bit minus one
 */
int clickAllWindowSDL2(int x,int y);
/**
 * @brief activation of unclick events on all the windows
 * @param x : abscissa coordinate of the mouse during the unclick
 * @param y : ordinate coordinate of the mouse during the unclick
 * @return 0 if it succeeded, a binary code telling which window failed (example : 100101 tells that the second and the fifth window failed, the first bit on the rigth only tells that there was an error), if you have more window than bits for int, you will not be able to tell which of the window failed in those which have a bigger number than the number of bit minus one
 */
int unclickAllWindowSDL2(int x,int y);
/**
 * @brief activation of the key pressed events on all windows
 * @param c : key which was pressed
 * @return 0 if it succeeded, a binary code telling which window failed (example : 100101 tells that the second and the fifth window failed, the first bit on the rigth only tells that there was an error), if you have more window than bits for int, you will not be able to tell which of the window failed in those which have a bigger number than the number of bit minus one
 */
int keyPressedAllWindowSDL2(char c);
/**
 * @brief activation of the key released events on all windows
 * @param c : key which was released
 * @return 0 if it succeeded, a binary code telling which window failed (example : 100101 tells that the second and the fifth window failed, the first bit on the rigth only tells that there was an error), if you have more window than bits for int, you will not be able to tell which of the window failed in those which have a bigger number than the number of bit minus one
 */
int keyReleasedAllWindowSDL2(char c);
/**
 * @brief close the current windows and go to the next
 * @return 1 if it failed, 0 if not
 */
int closeWindowSDL2();
/**
 * @brief close all windows
 * @return 1 if it failed, 0 if not
 */
int closeAllWindowSDL2();
/* ------------------------------------------------------- */

/* ------------------------------------------------------- 
 * Gestion d'evenement
 */
/**
 * @brief Get the event (if there is one) and apply the corresponding functions
 * @param error: where to store the error flag (0 if it succeeded, a binary code telling which window failed (example : 100101 tells that the second and the fifth window failed, the first bit on the rigth only tells that there was an error), if you have more window than bits for int, you will not be able to tell which of the window failed in those which have a bigger number than the number of bit minus one)
 * @return 1 if the user asked to close the window, 0 if not
 */
int PollEventSDL2(int * error);
/* ------------------------------------------------------- */

#endif
