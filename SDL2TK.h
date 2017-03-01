#ifndef _MAIN_SDL2TK_KLEVH_
#define _MAIN_SDL2TK_KLEVH_

#include "ElementSDL2.h"
#include "FenetreSDL2.h"

/* -------------------------------------------------------
 * Initialisation et fermeture des outils SDL2
 */
/* initialise la SDL2 (retourne 1 si erreur d'init SDL, 2 si erreur d'init image, 3 si erreur d'init TTF, 0 sinon) a partir des formats d'images passe en parametre */
int initAllSDL2(int imageFlags);
/* ferme la SDL2, image et texte */
void closeAllSDL2();
/* initialisation de la SDL2 (seule)*/
int initSDL2();
/* initialisation du texte SDL2 */
int initImage(int imageFlags);
/* initialisation de l'image SDL2 */
int initTexte();
/* ferme ma SDL2 seule */
void closeSDL2();
/* ferme image */
void closeImage();
/* ferme texte */
void closeTexte();
/* ------------------------------------------------------- */

/* -------------------------------------------------------
 * Fenetre SDL2
 */
/* libere la fenetre */
void freeFenetreSDL2(FenetreSDL2 *fen);
/* initialise la fenetre */
FenetreSDL2* initFenetreSDL2(int width,int height,char *title,int SDLFlags,int background[4],int displayCode);
/* update les elements de la fenetre */
void updateFenetreSDL2(FenetreSDL2* fen);
/* actualise l'affichage de la fenetre passe en parametre */
void displayFenetreSDL2(FenetreSDL2*);
/* activation des evenements de clique de souris */
void clickFenetreSDL2(FenetreSDL2*,int x,int y);
/* activation des evenements d'appuie sur une touche du clavier */
void keyPressFenetreSDL2(FenetreSDL2*,char c);
/* activation des evenements au relachement d'une touche du clavier */
void keyReleasedFenetreSDL2(FenetreSDL2*,char c);
/* ------------------------------------------------------- */

#endif
