#include "SDL2TK.h"

int main()
{
  int noir[4] = {0,0,0,0};
  int blanc[4] = {255,255,255,0};
  FenetreSDL2 * fen;
  ElementSDL2 * e1, * e2;

  if(!initAllSDL2(IMG_INIT_JPG)){
    fen = initFenetreSDL2(100,100,"Plop",1,0,noir,0);
    e1=createBlock(fen,0.f,0.f,50.f,50.f,blanc,0,NULL,NULL,NULL,NULL,NULL);
    e2=createBlock(fen,50.f,50.f,50.f,50.f,blanc,0,NULL,NULL,NULL,NULL,NULL);
    addElementToElementSDL2(e2,e1);
    delElementToElementSDL2(e2,e1);
    addElementSDL2(fen,e1);
    addElementSDL2(fen,e2);
    freeElementSDL2(e1);
    freeFenetreSDL2(fen);
    
    closeAllSDL2();
  }
  
  return 0;
}
