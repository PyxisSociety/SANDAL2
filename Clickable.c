#include "Clickable.h"


/* ----------------------------------------------------------
 * Clickables
 */

Clickable * initClickable(){
  Clickable * hb = (Clickable*)malloc(sizeof(*hb));

  if(hb){
    hb->firstC = NULL;
    hb->firstL = NULL;
    hb->next = NULL;
  }

  return hb;
}

int addLine(Clickable * hb,float a,float b,float c,int sens){
  Line * l;
  int error = 1;

  if(hb){
    l=(Line*)malloc(sizeof(*l));
    if(l){
      l->next=hb->firstL;
      l->a=a;
      l->b=b;
      l->c=c;
      l->sens=sens;
      hb->firstL=l;
      error = 0;
    }
  }

  return error;
}

int addCircle(Clickable * hb,float x,float y,float rX,float rY,float theta){
  Circle *c;
  int error = 1;

  if(hb){
    c=(Circle*)malloc(sizeof(*c));
    if(c){
      c->next=hb->firstC;
      c->x=x;
      c->y=y;
      c->rX=rX;
      c->rY=rY;
      c->theta=theta*(x!=y);
      hb->firstC=c;
      error=0;
    }
  }

  return error;
}

int delLine(Clickable * hb,float a,float b,float c,int sens){
  int error = 1;
  Line ** l, *tmp;

  if(hb){
    l=&(hb->firstL);
    while(*l && !((*l)->a==a && (*l)->b==b && (*l)->c==c && (*l)->sens==sens)){
      l=&((*l)->next);
    }
    if(*l){
      tmp=*l;
      *l=(*l)->next;
      free(tmp);
      error=0;
    }
  }

  return error;
}

int delCircle(Clickable * hb,float x,float y,float rX,float rY,float theta){
  int error = 1;
  Circle ** c, *tmp;

  if(hb){
    c=&(hb->firstC);
    while(*c && !((*c)->x==x && (*c)->y==y && (*c)->rX==rX && (*c)->rY==rY && (*c)->theta==theta)){
      c=&((*c)->next);
    }
    if(*c){
      tmp=*c;
      *c=(*c)->next;
      free(tmp);
      error=0;
    }
  }

  return error;
}

int hitClickable(Clickable * hb,float x,float y){
  int h = 0;
  Line * l;
  Circle * c;
  float cs,sn;
  
  if(hb){
    l=hb->firstL;
    if(l){
      do{
	h = (l->sens*(l->a*x + l->b*y) > l->sens*l->c);
	l=l->next;
      }while(l && h);
    }
    if(!l || h){
      c=hb->firstC;
      if(c){
	do{
	  if(c->theta!=0.f){
	    cs=cosf(-M_PI*c->theta/180.f);
	    sn=sinf(-M_PI*c->theta/180.f);
	  }else{
	    cs=1.f;
	    sn=0.f;
	  }
	  h = (((x*cs-y*sn-c->x)*(x*cs-y*sn-c->x))/(c->rX*c->rX) + ((x*sn+y*cs-c->y)*(x*sn+y*cs-c->y))/(c->rY*c->rY) <= 1);
	  c=c->next;
	}while(c && h);
      }
    }
  }

  return h;
}

Clickable * rectangleClickable(float x1,float y1,float x2,float y2){
  Clickable * hb = initClickable();
  float tmp;

  if(hb){
    if(x1 > x2){
      tmp=x1;
      x1=x2;
      x2=tmp;
    }
    if(y1 > y2){
      tmp=y1;
      y1=y2;
      y2=tmp;
    }
    if(!addLine(hb,0.f,1.f,y2,-1)){
      if(!addLine(hb,0.f,1.f,y1,1)){
	if(!addLine(hb,1.f,0.f,x1,1)){
	  if(addLine(hb,1.f,0.f,x2,-1)){
	    freeClickable(hb);
	    hb=NULL;
	  }
	}else{
	  freeClickable(hb);
	  hb=NULL;
	}
      }else{
	freeClickable(hb);
	hb=NULL;
      }
    }else{
      free(hb);
      hb=NULL;
    }
  }

  return hb;
}

Clickable * ellipseClickable(float x,float y,float rX,float rY,float theta){
  Clickable * hb=initClickable();

  if(hb){
    if(addCircle(hb,x,y,rX,rY,theta)){
      free(hb);
      hb=NULL;
    }
  }

  return hb;
}

void freeClickable(Clickable * hb){
  Circle * c, * ctmp;
  Line * l, * ltmp;
  if(hb){
    l=hb->firstL;
    while(l){
      ltmp=l->next;
      free(l);
      l=ltmp;
    }
    c=hb->firstC;
    while(c){
      ctmp=c->next;
      free(c);
      c=ctmp;
    }
    free(hb);
  }
}
/* ---------------------------------------------------------- */



/* ----------------------------------------------------------
 * ListClickable
 */
void freeListClickable(ListClickable * l){
  Clickable * hb, * tmp;

  if(l){
    hb=l->first;
    while(hb){
      tmp=hb->next;
      free(hb);
      hb=tmp;
    }
    free(l);
  }
}

ListClickable * initListClickable(){
  ListClickable * l = malloc(sizeof(*l));

  if(l){
    l->first=NULL;
    l->current=NULL;
    l->firstBlock=NULL;
    l->currentBlock=NULL;
  }

  return l;
}

int addClickable(ListClickable * l,Clickable * hb,int blocking){
  int error = 1;

  if(l && hb){
    if(blocking){
      hb->next=l->firstBlock;
      l->firstBlock=hb;
    }else{
      hb->next=l->first;
      l->first=hb;
    }
    error = 0;
  }

  return error;
}

int delClickable(ListClickable * l,Clickable * hb){
  int error = 1;
  Clickable ** h, *tmp;
  
  if(l && hb){
    h=&(l->first);
    while(*h && *h!=hb){
      h=&((*h)->next);
    }
    if(*h){
      tmp=*h;
      *h=(*h)->next;
      freeClickable(tmp);
      error = 0;
    }
  }

  return error;
}

int initIteratorListClickable(ListClickable * l){
  int succes = 0;

  if(l && l->first){
    l->current=l->first;
    succes = 1;
  }

  return succes;
}

Clickable * nextClickable(ListClickable * l){
  Clickable * hb=NULL;

  if(l && l->current){
    hb=l->current;
    l->current=l->current->next;
  }

  return hb;
}

int hitListClickable(ListClickable * l,float x,float y){
  Clickable * hb;
  int hit = 0;

  if(l && l->first){
    hb=l->first;
    do{
      hit = hitClickable(hb,x,y);
      hb=hb->next;
    }while(hb && !hit);
    if(l->firstBlock){
      hb=l->firstBlock;
      do{
	hit = !hitClickable(hb,x,y);
	hb=hb->next;
      }while(hb && hit);
    }
  }

  return hit;
}
/* ---------------------------------------------------------- */
