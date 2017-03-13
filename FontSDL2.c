#include "FontSDL2.h"

/* -------------------------------------------------------
 * Police de caractere SDL2
 */
FontSDL2* createFontSDL2(char *fontPath,char *texte,int couleur[4]){
  FontSDL2 *f;
  SDL_Surface *s;
  SDL_Color c;

  if(_windows_SDL2TK && _windows_SDL2TK->current){
    f=malloc(sizeof(*f));
    if(f){
      f->font=TTF_OpenFont(fontPath,30);
      if(f->font){
	c.r=couleur[0];
	c.g=couleur[1];
	c.b=couleur[2];
	c.a=couleur[3];
	f->color=c;
	f->text=malloc((strlen(texte)+1)*sizeof(*(f->text)));
	if(f->text){
	  strcpy(f->text,texte);
	  s=TTF_RenderText_Solid(f->font,texte,c);
	  f->texture=SDL_CreateTextureFromSurface(_windows_SDL2TK->current->renderer,s);
	  SDL_FreeSurface(s);
	}else{
	  free(f);
	  f=NULL;
	}
      }else{
	free(f);
	f=NULL;
      }
    }
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

void actualizeTextFontSDL2(FontSDL2 *font,int isScripted){
  SDL_Surface *s = NULL;
  char *str;
  int size,i;
  
  if(_windows_SDL2TK && _windows_SDL2TK->current && font){
    if(isScripted){
      size=strlen(font->text);
      str=malloc((size+1)*sizeof(*str));
      if(str){
	for(i=0;i<size;++i){
	  if(font->text[i]!=' '){
	    str[i]='*';
	  }else{
	    str[i]=' ';
	  }
	}
	str[size]='\0';
	s=TTF_RenderText_Solid(font->font,str,font->color);
      }
    }else {
      s=TTF_RenderText_Solid(font->font,font->text,font->color);
    }
    if(s){
      if(font->texture){
	SDL_DestroyTexture(font->texture);
      }
      font->texture=SDL_CreateTextureFromSurface(_windows_SDL2TK->current->renderer,s);
      SDL_FreeSurface(s);
    }
  }
}

void changeTextFontSDL2(FontSDL2 *font,char *text){
  SDL_Surface *s;
  
  if(_windows_SDL2TK && _windows_SDL2TK->current && font && text){
    PFREE(font->text);
    font->text=malloc((strlen(text)+1)*sizeof(*(font->text)));
    if(font->text){
      strcpy(font->text,text);
      s=TTF_RenderText_Solid(font->font,text,font->color);
      if(font->texture){
	SDL_DestroyTexture(font->texture);
      }
      font->texture=SDL_CreateTextureFromSurface(_windows_SDL2TK->current->renderer,s);
      SDL_FreeSurface(s);
    }
  }
}

void changeColorFontSDL2(FontSDL2 *font,int color[4]){
  SDL_Surface *s;
  
  if(_windows_SDL2TK && _windows_SDL2TK->current && font){
    font->color.r=color[0];
    font->color.g=color[1];
    font->color.b=color[2];
    font->color.a=color[3];
    s=TTF_RenderText_Solid(font->font,font->text,font->color);
    if(s){
      if(font->texture){
	SDL_DestroyTexture(font->texture);
      }
      font->texture=SDL_CreateTextureFromSurface(_windows_SDL2TK->current->renderer,s);
      SDL_FreeSurface(s);
    }
  }
}
/* ------------------------------------------------------- */
