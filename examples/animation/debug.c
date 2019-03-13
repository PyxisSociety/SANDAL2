#include <stdio.h>

#include "../../SANDAL2.h"

void touch(Element *this, int button){
    (void)button;
    
    nextAnimationElement(this);
    setFlipStateElement(this,SANDAL2_FLIP_NONE);
}

void endJump(Element *this,int code){
    if(code==1){
	setAnimationElement(this,0);
	setFlipStateElement(this,SANDAL2_FLIP_VER);
    }
}

void moveWindow(SDL_Keycode c){
    int x = 0, y = 0;
    int * val;
    const int pas = 3;

    getOriginWindow(&x,&y);

    switch(c){
    case 'z':
	y -= pas;
	break;
    case 's':
	y += pas;
	break;
    case 'q':
	x -= pas;
	break;
    case 'd':
	x += pas;
	break;
    case 27:
	if(!getDataWindow((void **)&val) && val)
	    *val = 0;
	break;
    case 'f':
	toggleFullScreenWindow();
	break;
    }

    setOriginWindow(x,y);
}

int main(){
    Element * objet;
    int run = 1;
    int tps = 0, ticks = 0;
    int noir[4] = {0,0,0,255};
    int rouge[4] = {255,0,0,255};
    int i;
  
    if(initAllSANDAL2(IMG_INIT_JPG)){
	fprintf(stderr,"Erreur d'initialisation de la bibliotheque graphique.\n");
	exit(-1);
    }

    /* initialisation de la fenetre */
    if(!createWindow(400,400,"test",SDL_WINDOW_RESIZABLE,noir,1)){
	closeAllSANDAL2();
	fprintf(stderr,"Erreur d'ouverture de la fenetre.\n");
	exit(-1);
    }
    setKeyPressedWindow(moveWindow);
    setOriginWindow(0,0);
    setDataWindow(&run);
    
    objet=createText(150.f,100.f,50.f,50.f,100.f,"arial.ttf","OK",rouge,2,1,-1);
    setTextStyleElement(objet,SANDAL2_STRIKETHROUGH);

    objet = createImage(150.f,100.f,100.f,200.f,"spritesheet.jpg",1,0);
    addClickableElement(objet,rectangleClickable(0.f,0.f,1.f,1.f),0);
  
    addAnimationElement(objet,0);
    for(i=0;i<4;++i)
	if(addSpriteAnimationElement(objet,0,55*i,0,55,75,10,i))
	    printf("Error adding sprite %d to animation 0\n",i);
    setWaySpriteAnimationElement(objet,0,1);

    addAnimationElement(objet,1);
    for(i=0;i<4;++i)
	if(addSpriteAnimationElement(objet,1,259+i*72,0,72,75,10,i))
	    printf("Error adding sprite %d to animation 1\n",i);
    setWaySpriteAnimationElement(objet,1,1);
  
    addRotationSpeedElement(objet,1.f);

    setOnClickElement(objet,touch);

    setEndSpriteElement(objet,endJump);
    
    /* display de la fenetre */
    while(run){
	tps = SDL_GetTicks();
	/* gestion d'evenement */
	run=!PollEvent(NULL) && run;

	/* update de la fenetre */
	updateWindow();
	/* affichage de la fenetre */
	displayWindow();
	/* delai pour 60 frames/secondes */
	ticks = 16 - SDL_GetTicks() + tps;
	if(ticks>0)
	    SDL_Delay(ticks);
    }

    closeAllWindow();
    closeAllSANDAL2();

    return 0;
}
