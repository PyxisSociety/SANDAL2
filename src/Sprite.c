#include "Sprite.h"

/* -----------------------------------------------------
 * ListSprite
 */
ListSprite * initListSprite(int code){
    ListSprite * l = (ListSprite*)malloc(sizeof(*l));

    if(l){
	l->current = NULL;
	l->first = NULL;
	l->size = 0;
	l->side = 0;
	l->wasChanged=0;
	l->next=NULL;
	l->prev=NULL;
	l->code=code;
    }

    return l;
}

void freeListSprite(ListSprite * l){
    unsigned i;
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

int addSprite(ListSprite * l,int x,int y,int width,int height,unsigned lifespan,int code){
    Sprite *s;
    int error = 1;
    unsigned i = 0;
  
    if(l){
	s = l->first;
	while(i < l->size && s->code != code){
	    s = s->next;
	    ++i;
	}
	if(!s || s->code != code){
	    s=(Sprite*)malloc(sizeof(*s));
	    if(s){
		s->coords[0]=x;
		s->coords[1]=y;
		s->coords[2]=width;
		s->coords[3]=height;
		s->lifespan=lifespan;
		s->code=code;
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
    }

    return error;
}

int delSprite(ListSprite * l,int code){
    unsigned i = 0;
    int error = 1;
    Sprite * s;

    if(l && l->size){
	s=l->first;
	while(i < l->size && s->code!=code){
	    ++i;
	    s=s->next;
	}
	if(i<l->size){
	    error = 0;
	    s->prev->next=s->next;
	    s->next->prev=s->prev;
	    if(l->current == s){
		if(l->side == -1){
		    l->current=s->prev;
		}else{
		    l->current=s->next;
		}
		l->wasChanged=0;
	    }
	    if(s == l->first){
		l->first = s->next;
	    }
	    free(s);
	    l->size--;
	    if(!l->size){
		l->first = NULL;
		l->current = NULL;
	    }
	}
    }
  
    return error;
}

int setLifeSpanSprite(ListSprite * l,int code,unsigned lifespan){
    unsigned i = 0;
    int error = 1;
    Sprite * s;

    if(l && l->size){
	s=l->first;
	while(i < l->size && s->code!=code){
	    ++i;
	    s=s->next;
	}
	if(i<l->size && s->code==code){
	    error = 0;
	    s->lifespan = lifespan;
	}
    }
  
    return error;
}

int setSprite(ListSprite * l,int code){
    unsigned i = 0;
    int error = 1;
    Sprite *s;

    if(l){
	s=l->first;
	while(i < l->size && s->code!=code){
	    s=s->next;
	    ++i;
	}
	if(i < l->size && s->code==code){
	    l->current=s;
	    error = 0;
	}
    }
    return error;
}
/* ----------------------------------------------------- */



/* -----------------------------------------------------
 * ListAnimation
 */
ListAnimation * initListAnimation(){
    ListAnimation * l = (ListAnimation*)malloc(sizeof(*l));

    if(l){
	l->first=NULL;
	l->current=NULL;
	l->size=0;
    }

    return l;
}

void freeListAnimation(ListAnimation *l){
    ListSprite *ls;
    unsigned i;

    if(l){
	i=0;
	while(i<l->size){
	    ls=l->first;
	    l->first=l->first->next;
	    freeListSprite(ls);
	    ++i;
	}
	free(l);
    }
}

int createAnimation(ListAnimation *l,int code){
    ListSprite *ls;
    int error = 1;
    unsigned i = 0;

    if(l){
	ls = l->first;
	while(i < l->size && ls->code != code){
	    ls = ls->next;
	    ++i;
	}
	if(!ls || ls->code != code){
	    ls=initListSprite(code);
	    if(ls){
		error=0;
		if(l->size){
		    ls->next=l->first;
		    ls->prev=l->first->prev;
		    l->first->prev->next=ls;
		    l->first->prev=ls;
		}else{
		    ls->next=ls;
		    ls->prev=ls;
		    l->first=ls;
		    l->current=ls;
		}
		l->size++;
	    }
	}
    }

    return error;
}

int delAnimation(ListAnimation *l,int code){
    ListSprite *ls;
    int error = 1;
    unsigned i = 0;

    if(l){
	ls = l->first;
	while(i < l->size && ls->code != code){
	    ls = ls->next;
	    ++i;
	}
	if(ls && ls->code == code){
	    error = 0;
	    ls->next->prev = ls->prev;
	    ls->prev->next = ls->next;
	    l->size--;
	    if(l->size == 0){
		l->first = NULL;
		l->current = NULL;
	    }else{
		if(l->current == ls){
		    l->current = l->current->next;
		}
		if(l->first == ls){
		    l->first = l->first->next;
		}
	    }
	    freeListSprite(ls);
	}
    }

    return error;
}

int addSpriteAnimation(ListAnimation *l,int code,int x,int y,int width,int height,unsigned lifespan,int codeS){
    ListSprite *ls;
    int error = 1;
    unsigned i = 0;

    if(l){
	ls = l->first;
	while(i < l->size && ls->code != code){
	    ls = ls->next;
	    ++i;
	}
	if(ls && ls->code == code){
	    error = addSprite(ls,x,y,width,height,lifespan,codeS);
	}
    }

    return error;
}

int delSpriteAnimation(ListAnimation *l,int code,int codeS){
    ListSprite *ls;
    int error = 1;
    unsigned i = 0;

    if(l){
	ls=l->first;
	while(i < l->size && ls->code != code){
	    ls = ls->next;
	    ++i;
	}
	if(ls && ls->code == code){
	    error = delSprite(ls,codeS);
	}
    }

    return error;
}

int setLifeSpanSpriteAnimation(ListAnimation *l,int code,int codeS,unsigned lifespan){
    ListSprite *ls;
    int error = 1;
    unsigned i = 0;

    if(l){
	ls=l->first;
	while(i<l->size && ls->code!=code){
	    ls=ls->next;
	    ++i;
	}
	if(i<l->size){
	    error=setLifeSpanSprite(ls,codeS,lifespan);
	}
    }

    return error;
}

int setAnimation(ListAnimation *l,int code){
    ListSprite *ls;
    int error = 1;
    unsigned i = 0;

    if(l){
	ls=l->first;
	while(i<l->size && ls->code!=code){
	    ls=ls->next;
	    ++i;
	}
	if(i<l->size){
	    l->current=ls;
	    error=0;
	}
    }

    return error;
}

int setSpriteAnimation(ListAnimation *l,int codeS){
    int error = 0;

    if(l){
	error=setSprite(l->current,codeS);
    }

    return error;
}
/* ----------------------------------------------------- */
