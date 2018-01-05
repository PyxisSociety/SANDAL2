#ifndef SPRITE_SANDAL2_KLEVH
#define SPRITE_SANDAL2_KLEVH

#ifdef __cplusplus
extern "C" {
#endif
    
#include <stdlib.h>

/**
 * @file Sprite.h
 * @author Baptiste PRUNIER (KLEVH)
 * @brief Sprite manager for SANDAL2
 */

/**
 * @struct Sprite
 * @brief informations about a step of an animation
 */
typedef struct Sprite{
  struct Sprite * next;
  /**< next step of the animation*/
  struct Sprite * prev;
  /**< previous step of the animation*/
  int coords[4];
  /**< [0] and [1] for the coordinates of the top left corner and [2] and [3] respectively for the width and the height*/
  unsigned lifespan;
  /**< number of time minus one the Sprite should be displaied before going to the next*/
  int code;
  /**< identifier of the Sprite */
}Sprite;

/**
 * @struct ListSprite
 * @brief all steps of an animation
 */
typedef struct ListSprite{
  Sprite * first;
  /**< first step of the animation*/
  Sprite * current;
  /**< current step of the animation*/
  unsigned size;
  /**< number of steps in the animation*/
  int sens;
  /**< tells whether to go forward (1), backward (-1) or not to move (0)*/
  unsigned wasChanged;
  /**< tells how many time the current sprite was displaied*/
  int code;
  /**< identifier of the animation*/
  struct ListSprite * next;
  /**< next animation*/
  struct ListSprite * prev;
  /**< previous animation*/
}ListSprite;

/**
 * @struct ListAnimation
 * @brief a list of animations
 */
typedef struct{
  ListSprite * first;
  /**< first animation*/
  ListSprite * current;
  /**< current animation*/
  unsigned size;
  /**< number of animations*/
}ListAnimation;

/* -----------------------------------------------------
 * ListSprite
 */
/**
 * @brief create an empty list of sprite
 * @return the empty list of sprite
 */
ListSprite * initListSprite(int code);
/**
 * @brief free the memory of a list of sprite
 * @param l : list to be freed
 */
void freeListSprite(ListSprite * l);
/**
 * @brief add a Sprite to the list
 * @param l : list of sprite
 * @param x : abscissa coordinate of the top left corner of the sprite in its image
 * @param y : ordinate coordinate of the top left corner of the sprite in its image
 * @param width : width of the sprite in its image
 * @param height : height of the sprite in its image
 * @param lifespan : number of time the sprite should be displaied before going to the next sprite
 * @param code : identifier of the Sprite to add
 * @return 0 if the sprite was correctly added, 1 if not
 */
int addSprite(ListSprite * l,int x,int y,int width,int height,unsigned lifespan,int code);
/**
 * @brief remove a Sprite to the list
 * @param l : list of sprite
 * @param code : code of the sprite to be removed
 * @return 0 if the sprite was correctly removed, 1 if not
 */
int delSprite(ListSprite * l,int code);
/**
 * @brief set the lifespan of a sprite
 * @param l : list of sprite
 * @param code : code of the sprite to be changed
 * @param lifespan : new number of time the sprite should be displaied before going to the next sprite
 * @return 0 if the lifespan could be set, 1 if not
 */
int setLifeSpanSprite(ListSprite * l,int code,unsigned lifespan);
/**
 * @brief change the current sprite in a given list of sprite
 * @param l : list of sprite
 * @param code : code of the sprite to be set
 * @return 0 if the sprite could be set, 1 if not
 */
int setSprite(ListSprite * l,int code);
/* ----------------------------------------------------- */

/* -----------------------------------------------------
 * ListAnimation
 */
/**
 * @brief create an empty list of animation
 * @return the empty list of animation
 */
ListAnimation * initListAnimation();
/**
 * @brief free the memory of a list of animation
 * @param l : list to be freed
 */
void freeListAnimation(ListAnimation *l);
/**
 * @brief add an empty animation to the list
 * @param l : list of animation
 * @param code : code of the new animation
 * @return 0 if the animation could be added, 1 if not
 */
int createAnimation(ListAnimation *l,int code);
/**
 * @brief remove an empty animation from the list
 * @param l : list of animation
 * @param code : code of the animation to be removed
 * @return 0 if the animation could be removed, 1 if not
 */
int delAnimation(ListAnimation *l,int code);
/**
 * @brief add a Sprite to an animation
 * @param l : list of animations
 * @param code : code of the animation to add the sprite
 * @param x : abscissa coordinate of the top left corner of the sprite in its image
 * @param y : ordinate coordinate of the top left corner of the sprite in its image
 * @param width : width of the sprite in its image
 * @param height : height of the sprite in its image
 * @param lifespan : number of time the sprite should be displaied before going to the next sprite
 * @param codeS : code of the Sprite to be added
 * @return 0 if the sprite was correctly added, 1 if not
 */
int addSpriteAnimation(ListAnimation *l,int code,int x,int y,int width,int height,unsigned lifespan,int codeS);
/**
 * @brief remove a Sprite to an animation
 * @param l : list of animations
 * @param code : code of the animation to remove the sprite
 * @param codeS : code of the sprite to be removed
 * @return 0 if the sprite was correctly removed, 1 if not
 */
int delSpriteAnimation(ListAnimation *l,int code,int codeS);
/**
 * @brief set the lifespan of a sprite
 * @param l : list of animations
 * @param code : code of the animation to set the sprite
 * @param codeS : code of the sprite to be modified
 * @param lifespan : new number of time the sprite should be displaied before going to the next sprite
 * @return 0 if the lifespan could be set, 1 if not
 */
int setLifeSpanSpriteAnimation(ListAnimation *l,int code,int codeS,unsigned lifespan);
/**
 * @brief set the current animation of a list of animations
 * @param l : list of animations
 * @param code : code of the animation to be set as current
 * @return 0 if the animation could be set as current, 1 if not
 */
int setAnimation(ListAnimation *l,int code);
/**
 * @brief change the current sprite in the current list of sprite in a given list of animation
 * @param l : list of animation
 * @param codeS : code of the sprite to be set
 * @return 0 if the sprite could be set, 1 if not
 */
int setSpriteAnimation(ListAnimation *l,int codeS);
/* ----------------------------------------------------- */

#ifdef __cplusplus
}
#endif
    
#endif
