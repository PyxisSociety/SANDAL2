#ifndef _HITBOX_SDL2TK_KLEVH_
#define _HITBOX_SDL2TK_KLEVH_

#include <math.h>
#include <stdlib.h>

/**
 * @file HitBox.h
 * @author Baptiste PRUNIER
 * @brief Generic hitboxes either polygonial, elliptic or a mixe of both
 */

/**
 * @struct LineSDL2
 * @brief Represente a line which delimitate a hittable surface from a none hittable one
 */
typedef struct LineSDL2{
  struct LineSDL2 * next;
  ///< next element
  float a;
  ///< a in the equation of the line ax+by=c
  float b;
  ///< b in the equation of the line ax+by=c
  float c;
  ///< c in the equation of the line ax+by=c
  int sens;
  ///< side of the line that is hittable (-1 : ax+by<c, 1 : ax+by>c)
}LineSDL2;

/**
 * @struct CircleSDL2
 * @brief Represente a hittable ellipse
 */
typedef struct CircleSDL2{
  struct CircleSDL2 * next;
  ///< next ellipse
  float x;
  ///< abscissa coordinate of the center of the ellipse
  float y;
  ///< ordinate coordinate of the center of the ellipse
  float rY;
  ///< size of the radius parallel to the ordinate axis
  float rX;
  ///< size of the radius parallel to the abscissa axis
  float theta;
  ///< degree of rotation
}CircleSDL2;

/**
 * @struct HitBox
 * @brief Represente a hit boxe which is a collection of LineSDL2 (defining a convexe polygon) and CircleSDL2
 */
typedef struct HitBox{
  LineSDL2 * firstL;
  ///< first element of the lines' list
  CircleSDL2 * firstC;
  ///< first element of the ellipses' list
  struct HitBox * next;
  ///< next hitbox
}HitBox;

/**
 * @struct ListHitBox
 * @brief Collection of hit boxes
 */
typedef struct{
  HitBox * first;
  HitBox * current;
}ListHitBox;

/* ----------------------------------------------------------
 * HitBox
 */
/**
 * @brief Generate an empty hitbox
 * @return return an empty hitbox
 */
HitBox * initHitBox();
/**
 * @brief add a line to the hitbox sens*(ax+by) > sens*c 
 * @param hb : hit boxe to which the line will be added
 * @param a : a in the equation of the line ax+by=c
 * @param b : b in the equation of the line ax+by=c
 * @param c : c in the equation of the line ax+by=c
 * @param sens : indicator of the side of the line which is hittable (-1 : ax+by<c, 1 : ax+by>c)
 * @return 0 if the line was correctly added, 1 in the other case
 */
int addLineSDL2(HitBox * hb,float a,float b,float c,int sens);
/**
 * @brief add an ellipse to the hitbox
 * @param hb : hit boxe to which the line will be added
 * @param x : abscissa coordinate of the center of the ellipse
 * @param y : ordinate coordinate of the center of the ellipse
 * @param rX : size of the radius parallel to the abscissa axis
 * @param rY : size of the radius parallel to the ordinate axis
 * @param theta : rotation of the ellipse (in degree)
 * @return 0 if the ellipse was correctly added, 1 in the other case
 */
int addCircleSDL2(HitBox * hb,float x,float y,float rX,float rY,float theta);
/**
 * @brief remove a line from the hitbox 
 * @param hb : hit boxe to which the line will be removed
 * @param a : a in the equation of the line ax+by=c
 * @param b : b in the equation of the line ax+by=c
 * @param c : c in the equation of the line ax+by=c
 * @param sens : indicator of the side of the line which is hittable (-1 : ax+by<c, 1 : ax+by>c)
 * @return 0 if the line was correctly removed, 1 in the other case
 */
int removeLineSDL2(HitBox * hb,float a,float b,float c,int sens);
/**
 * @brief remove an ellipse from the hitbox
 * @param hb : hit boxe to which the line will be removed
 * @param x : abscissa coordinate of the center of the ellipse
 * @param y : ordinate coordinate of the center of the ellipse
 * @param rX : size of the radius parallel to the abscissa axis
 * @param rY : size of the radius parallel to the ordinate axis
 * @param theta : rotation of the ellipse (in degree)
 * @return 0 if the ellipse was correctly removed, 1 in the other case
 */
int removeCircleSDL2(HitBox * hb,float x,float y,float rX,float rY,float theta);
/**
 * @brief tells if (x,y) touch the hitbox 
 * @param hb : hit boxe that you are trying to touch
 * @param x : abscissa coordinate of the point trying to touch the hit boxe
 * @param y : ordinate coordinate of the point trying to touch the hit boxe
 * @return 1 if the hit boxe is hit, 0 in the other case
 */
int hitHitBox(HitBox * hb,float x,float y);
/**
 * @brief generate a rectangulare shapped HitBox 
 * @param x1 : abscissa coordinate of the top left point of the rectangle
 * @param y1 : ordinate coordinate of the top left point of the rectangle
 * @param x2 : abscissa coordinate of the bottom right point of the rectangle
 * @param y2 : ordinate coordinate of the bottom right point of the rectangle
 * @return A rectangulare hit boxe defined by the points (x1,y1) and (x2,y2)
 */
HitBox * rectangleHitBox(float x1,float y1,float x2,float y2);
/**
 * @brief generate an ellipse shapped HitBox 
 * @param 
 * @param
 * @param
 * @param
 * @return
 */
HitBox * ellipseHitBox(float x,float y,float rX,float rY,float theta);
/* libere une hit box */
void freeHitBox(HitBox * hb);
/* ---------------------------------------------------------- */


/* ----------------------------------------------------------
 * ListHitBox
 */
/* libere la liste de hit box */
void freeListHitBox(ListHitBox * l);
/* initialise une liste de hit box vide */
ListHitBox * initListHitBox();
/* ajoute un element a la liste */
int addHitBox(ListHitBox * l,HitBox * hb);
/* supprime un element de la liste */
int removeHitBox(ListHitBox * l,HitBox * hb);
/* initialise l'iterateur de la liste */
int initIteratorListHitBox(ListHitBox * l);
/* retourne l'element courant et passe a l'element suivant */
HitBox * nextHitBox(ListHitBox * l);
/* tells if (x,y) touch one of the hitboxes */
int hitListHitBox(ListHitBox * l,float x,float y);
/* ---------------------------------------------------------- */

#endif
