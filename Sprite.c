#include "Sprite.h"

/* -----------------------------------------------------
 * ListSprite
 */
ListSprite * initListSprite(){
  ListSprite * l = malloc(sizeof(*l));

  if(l){
    l->current = NULL;
    l->first = NULL;
    l->size = 0;
    l->sens = 0;
    l->wasChanged=0;
  }

  return l;
}

void freeListSprite(ListSprite * l){
  int i;
  Sprite * tmp;

  if(l){
    for(i = 0;i < l->size; ++i){
      tmp=l->first;
      l->first=l->first->next;
      free(tmp);
    }

    free(l);
  }
}

int addSprite(ListSprite * l,int x,int y,int width,int height,unsigned lifespan){
  Sprite *s;
  int error = 1;
  
  if(l){
    s=malloc(sizeof(*s));
    if(s){
      s->coords[0]=x;
      s->coords[1]=y;
      s->coords[2]=width;
      s->coords[3]=height;
      s->lifespan=lifespan;
      if(l->size){
	s->next=l->first;
	s->prev=l->first->prev;
	l->first->prev->next=s;
	l->first->prev=s;
      }else{
	s->next=s;
	s->prev=s;
	l->first=s;
	l->current=s;
	l->wasChanged=0;
      }
      l->size++;
      error = 0;
    }
  }

  return error;
}

int removeSprite(ListSprite * l,int x,int y,int width,int height){
  int i = 0;
  int error = 1;
  Sprite * s;

  if(l && l->size){
    s=l->first;
    while(i < l->size && (s->coords[0]!=x || s->coords[1]!=y || s->coords[2]!=width || s->coords[3]!=height)){
      ++i;
      s=s->next;
    }
    if(i<l->size){
      error = 0;
      s->prev->next=s->next;
      s->next->prev=s->prev;
      if(l->current == s){
	if(l->sens == -1){
	  l->current=s->prev;
	}else{
	  l->current=s->next;
	}
	l->wasChanged=0;
      }
      free(s);
      l->size--;
    }
  }
  
  return error;
}

int setLifeSpanSprite(ListSprite * l,int x,int y,int width,int height,unsigned lifespan){
  int i = 0;
  int error = 1;
  Sprite * s;

  if(l && l->size){
    s=l->first;
    while(i < l->size && (s->coords[0]!=x || s->coords[1]!=y || s->coords[2]!=width || s->coords[3]!=height)){
      ++i;
      s=s->next;
    }
    if(i<l->size){
      error = 0;
      s->lifespan = lifespan;
    }
  }
  
  return error;
}
/* ----------------------------------------------------- */
