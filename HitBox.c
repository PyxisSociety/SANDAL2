#include "HitBox.h"


/* ----------------------------------------------------------
 * HitBoxs
 */

HitBox * initHitBox(){
  HitBox * hb = malloc(sizeof(*hb));

  if(hb){
    hb->firstC = NULL;
    hb->firstL = NULL;
  }

  return hb;
}

int addLineSDL2(HitBox * hb,float a,float b,float c,int sens){
  LineSDL2 * l;
  int error = 1;

  if(hb){
    l=malloc(sizeof(*l));
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

int addCircleSDL2(HitBox * hb,float x,float y,float rX,float rY,float theta){
  CircleSDL2 *c;
  int error = 1;

  if(hb){
    c=malloc(sizeof(*c));
    if(c){
      c->next=hb->firstC;
      c->x=x;
      c->y=y;
      c->rX=rX;
      c->rY=rY;
      c->theta=theta;
      hb->firstC=c;
      error=0;
    }
  }

  return error;
}

int removeLineSDL2(HitBox * hb,float a,float b,float c,int sens){
  int error = 1;
  LineSDL2 ** l, *tmp;

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
}

int removeCircleSDL2(HitBox * hb,float x,float y,float rX,float rY,float theta){
  int error = 1;
  CircleSDL2 ** c, *tmp;

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

int hitHitBox(HitBox * hb,float x,float y){
  int h = 0;
  LineSDL2 * l;
  CircleSDL2 * c;
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
	  printf("%f - %f\n",cs,sn);
	  printf("%f - %f\n",((x*cs-y*sn-c->x)*(x*cs-y*sn-c->x))/(c->rX*c->rX),((x*sn+y*cs-c->y)*(x*sn+y*cs-c->y))/(c->rY*c->rY));
	  h = (((x*cs-y*sn-c->x)*(x*cs-y*sn-c->x))/(c->rX*c->rX) + ((x*sn+y*cs-c->y)*(x*sn+y*cs-c->y))/(c->rY*c->rY) <= 1);
	  c=c->next;
	}while(c && h);
      }
    }
  }

  return h;
}

HitBox * rectangleHitBox(float x1,float y1,float x2,float y2){
  HitBox * hb = initHitBox();
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
    if(!addLineSDL2(hb,0.f,1.f,y2,-1)){
      if(!addLineSDL2(hb,0.f,1.f,y1,1)){
	if(!addLineSDL2(hb,1.f,0.f,x1,1)){
	  if(addLineSDL2(hb,1.f,0.f,x2,-1)){
	    freeHitBox(hb);
	    hb=NULL;
	  }
	}else{
	  freeHitBox(hb);
	  hb=NULL;
	}
      }else{
	freeHitBox(hb);
	hb=NULL;
      }
    }else{
      free(hb);
      hb=NULL;
    }
  }

  return hb;
}

HitBox * ellipseHitBox(float x,float y,float rX,float rY,float theta){
  HitBox * hb=initHitBox();

  if(hb){
    if(addCircleSDL2(hb,x,y,rX,rY,theta)){
      free(hb);
      hb=NULL;
    }
  }

  return hb;
}

void freeHitBox(HitBox * hb){
  CircleSDL2 * c, * ctmp;
  LineSDL2 * l, * ltmp;
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
