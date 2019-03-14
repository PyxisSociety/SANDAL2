#ifndef DISPLAYCODE_SANDAL2_KLEVH
#define DISPLAYCODE_SANDAL2_KLEVH

#ifdef __cplusplus
extern "C" {
#endif
    
#include <stdio.h>
#include <stdlib.h>

/**
 * @file DisplayCode.h
 * @author Baptiste PRUNIER (KLEVH)
 * @brief Contains display code and list of display codes
 */

/**
 * @struct DisplayCode
 * @brief Display code containing the plan and a flag to indicate if it is displaied
 */
typedef struct DisplayCode{
  struct DisplayCode *next;
  /**< next DisplayCode*/
  int code;
  /**< display code*/
  int isDisplaied;
  /**< flag to tell whether or not the element should be displaied*/
  int plan;
  /**< plan linked to the display code*/
}DisplayCode;

/**
 * @struct ListDisplayCode
 * @brief List of display codes
 */
typedef struct{
  DisplayCode *first;
  /**< first element of the list*/
  unsigned size;
  /**< size of the list*/
}ListDisplayCode;

/* -------------------------------------------------------
 * Liste de code d'affichage
 */
/**
 * @brief Initialise an empty list of display codes
 * @return an empty list of display codes
 */
ListDisplayCode* initListDisplayCode();
/**
 * @brief Free the memory of a list of display codes
 * @param l : list of display codes 
 */
void freeListDisplayCode(ListDisplayCode* l);
/**
 * @brief Add of a display code to a list of display code
 * @param l : list of display codes
 * @param code : display code of the DisplayCode
 * @param isDisplaied : flag to tell if the element is displaied or not
 * @param plan : plan linked to the display code 
 * @return 1 if it could not be done, 0 if it could
 */
int addDisplayCode(ListDisplayCode* l,int code,int isDisplaied,int plan);
/**
 * @brief Remove a display code to a list of display code
 * @param l : list of display codes
 * @param code : display code to be removed
 * @return 0 if it succeeded, 1 if not
 */
int delDisplayCode(ListDisplayCode * l, int code);
/* ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif
    
#endif
