#include "DisplayCode.h"

/* -------------------------------------------------------
 * Liste de code d'affichage
 */
ListDisplayCode* initListDisplayCode(){
  ListDisplayCode *l=(ListDisplayCode*)malloc(sizeof(*l));

  if(l){
    l->first=NULL;
    l->size=0;
  }
  
  return l;
}

void freeListDisplayCode(ListDisplayCode *l){
  DisplayCode *d,*tmp;

  if(l){
    d=l->first;
    while (d) {
      tmp=d->next;
      free(d);
      d=tmp;
    }
    free(l);
  }
}

int addDisplayCode(ListDisplayCode* l,int code,int isDisplaied,int plan){
  DisplayCode **d, *new;
  int error = 1;

  if(l){
    d=&(l->first);
    while(*d && (*d)->code<code){
      d=&((*d)->next);
    }
    if(*d && (*d)->code==code){
      (*d)->isDisplaied=isDisplaied;
      (*d)->plan=plan;
      error = 0;
    }else{
      new=(DisplayCode*)malloc(sizeof(*new));
      if(new){
	new->code=code;
	new->next=*d;
	new->isDisplaied=isDisplaied;
	new->plan=plan;
	*d=new;
	l->size++;
	error = 0;
      }
    }
  }

  return error;
}

int delDisplayCode(ListDisplayCode * l, int code){
    int error = 1;
    DisplayCode ** d, * dtmp;
    
    if(l){
	d = &(l->first);
	while(*d && (*d)->code < code)
	    d = &((*d)->next);
	if(*d && (*d)->code == code){
	    error = 0;
	    dtmp = *d;
	    *d = dtmp->next;
	    free(dtmp);
	    --l->size;
	}
    }
    
    return error;
}
/* ------------------------------------------------------- */
