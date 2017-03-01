#include "FontSDL2.h"

/* -------------------------------------------------------
 * Police de caractere SDL2
 */
FontSDL2* createFontSDL2(FenetreSDL2 *fen,char *fontPath,char *texte,int couleur[4]){
  FontSDL2 *f=malloc(sizeof(*f));
  SDL_Surface *s;
  SDL_Color c;

  f->font=TTF_OpenFont(fontPath,30);
  if(f->font){
    c.r=couleur[0];
    c.g=couleur[1];
    c.b=couleur[2];
    c.a=couleur[3];
    f->color=c;
    f->text=malloc(strlen(texte)*sizeof(*(f->text)));
    strcpy(f->text,texte);
    s=TTF_RenderText_Solid(f->font,texte,c);
    f->texture=SDL_CreateTextureFromSurface(fen->renderer,s);
    SDL_FreeSurface(s);
  }else{
    free(f);
    f=NULL;
  }

  return f;
}

void freeFontSDL2(FontSDL2 *font){
  if(font){
    if(font->texture){
      SDL_DestroyTexture(font->texture);
    }
    if(font->font){
      TTF_CloseFont(font->font);
    }
    PFREE(font->text);
    free(font);
  }
}

void actualizeTextFontSDL2(FenetreSDL2 *f,FontSDL2 *font,int isScripted){
  SDL_Surface *s;
  char *str;
  int size,i;
  
  if(f && font){
    if(isScripted){
      size=strlen(font->text);
      str=malloc((size+1)*sizeof(*str));
      for(i=0;i<size;++i){
	if(font->text[i]!=' '){
	  str[i]='*';
	}else{
	  str[i]=' ';
	}
      }
      str[size]='\0';
      s=TTF_RenderText_Solid(font->font,str,font->color);
    }else {
      s=TTF_RenderText_Solid(font->font,font->text,font->color);
    }
    if(font->texture){
      SDL_DestroyTexture(font->texture);
    }
    font->texture=SDL_CreateTextureFromSurface(f->renderer,s);
    SDL_FreeSurface(s);
  }
}

void changeTextFontSDL2(FenetreSDL2 *f,FontSDL2 *font,char *text){
  SDL_Surface *s;
  
  if(f && font && text){
    PFREE(font->text);
    font->text=malloc((strlen(text)+1)*sizeof(*(font->text)));
    if(font->text){
      strcpy(font->text,text);
      s=TTF_RenderText_Solid(font->font,text,font->color);
      if(font->texture){
	SDL_DestroyTexture(font->texture);
      }
      font->texture=SDL_CreateTextureFromSurface(f->renderer,s);
      SDL_FreeSurface(s);
    }
  }
}

void changeColorFontSDL2(FenetreSDL2 *f,FontSDL2 *font,int color[4]){
  SDL_Surface *s;
  
  if(f && font){
    font->color.r=color[0];
    font->color.g=color[1];
    font->color.b=color[2];
    font->color.a=color[3];
    s=TTF_RenderText_Solid(font->font,font->text,font->color);
    if(s){
      if(font->texture){
	SDL_DestroyTexture(font->texture);
      }
      font->texture=SDL_CreateTextureFromSurface(f->renderer,s);
      SDL_FreeSurface(s);
    }
  }
}
/* ------------------------------------------------------- */
