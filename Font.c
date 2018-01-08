#include "Font.h"

/* -------------------------------------------------------
 * Text 
 */
Font* createFont(const char *fontPath,const char *texte,int couleur[4],int quality){
  Font *f = NULL;
  SDL_Surface *s;
  SDL_Color c,c2;

  if(_windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current->renderer){
    f=(Font*)malloc(sizeof(*f));
    if(f){
      f->font=TTF_OpenFont(fontPath,30);
      if(f->font){
	c.r=couleur[0];
	c.g=couleur[1];
	c.b=couleur[2];
	c.a=couleur[3];
	f->color=c;
	f->text=(char*)malloc((strlen(texte)+1)*sizeof(*(f->text)));
	f->texture=NULL;
	if(f->text){
	  strcpy(f->text,texte);
	  f->quality=quality;
	  switch(quality){
	  case 1:
	    c2.r=_windows_SANDAL2->current->background[0];
	    c2.g=_windows_SANDAL2->current->background[1];
	    c2.b=_windows_SANDAL2->current->background[2];
	    c2.a=_windows_SANDAL2->current->background[3];
	    s=TTF_RenderText_Shaded(f->font,texte,c,c2);
	    break;
	  case 2:
	    s=TTF_RenderText_Blended(f->font,texte,c);
	    break;
	  default:
	    s=TTF_RenderText_Solid(f->font,texte,c);
	  }
	  if(s){
	    f->texture=SDL_CreateTextureFromSurface(_windows_SANDAL2->current->renderer,s);
	    if(!f->texture){
		freeFont(f);
		f=NULL;
	    }
	    SDL_FreeSurface(s);
	  }else if(f){
	    freeFont(f);
	    f=NULL;
	  }
	}else{
	  TTF_CloseFont(f->font);
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

void freeFont(Font *font){
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
int actualizeTextFont(Font *font,int isScripted){
  SDL_Surface *s = NULL;
  char *str;
  int size,i,error=1;
  SDL_Color c2;
  
  if(_windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current->renderer && font && font->font){
    if(isScripted){
      size=strlen(font->text);
      str=(char*)malloc((size+1)*sizeof(*str));
      if(str){
	for(i=0;i<size;++i){
	  if(font->text[i]!=' '){
	    str[i]='*';
	  }else{
	    str[i]=' ';
	  }
	}
	str[size]='\0';
	switch(font->quality){
	case 1:
	  c2.r=_windows_SANDAL2->current->background[0];
	  c2.g=_windows_SANDAL2->current->background[1];
	  c2.b=_windows_SANDAL2->current->background[2];
	  c2.a=_windows_SANDAL2->current->background[3];
	  s=TTF_RenderText_Shaded(font->font,str,font->color,c2);
	  break;
	case 2:
	  s=TTF_RenderText_Blended(font->font,str,font->color);
	  break;
	default:
	  s=TTF_RenderText_Solid(font->font,str,font->color);
	}
      }
    }else{
      switch(font->quality){
      case 1:
	c2.r=_windows_SANDAL2->current->background[0];
	c2.g=_windows_SANDAL2->current->background[1];
	c2.b=_windows_SANDAL2->current->background[2];
	c2.a=_windows_SANDAL2->current->background[3];
	s=TTF_RenderText_Shaded(font->font,font->text,font->color,c2);
	break;
      case 2:
	s=TTF_RenderText_Blended(font->font,font->text,font->color);
	break;
      default:
	s=TTF_RenderText_Solid(font->font,font->text,font->color);
      }
    }
    if(s){
      if(font->texture){
	SDL_DestroyTexture(font->texture);
      }
      font->texture=SDL_CreateTextureFromSurface(_windows_SANDAL2->current->renderer,s);
      SDL_FreeSurface(s);
      if(font->texture){
	error=0;
      }
    }
  }

  return error;
}

int setTextFont(Font *font,const char *text){
  SDL_Surface *s;
  int error = 1;
  SDL_Color c2;
  
  if(_windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current->renderer && font && text && font->font){
    PFREE(font->text);
    font->text=(char*)malloc((strlen(text)+1)*sizeof(*(font->text)));
    if(font->text){
      strcpy(font->text,text);
      switch(font->quality){
      case 1:
	c2.r=_windows_SANDAL2->current->background[0];
	c2.g=_windows_SANDAL2->current->background[1];
	c2.b=_windows_SANDAL2->current->background[2];
	c2.a=_windows_SANDAL2->current->background[3];
	s=TTF_RenderText_Shaded(font->font,text,font->color,c2);
	break;
      case 2:
	s=TTF_RenderText_Blended(font->font,text,font->color);
	break;
      default:
	s=TTF_RenderText_Solid(font->font,text,font->color);
      }
      if(font->texture){
	SDL_DestroyTexture(font->texture);
      }
      font->texture=SDL_CreateTextureFromSurface(_windows_SANDAL2->current->renderer,s);
      SDL_FreeSurface(s);
      if(font->texture){
	error = 0;
      }
    }
  }

  return error;
}

int setColorFont(Font *font,int color[4]){
  SDL_Surface *s;
  int error = 1;
  SDL_Color c2;

  if(_windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current->renderer && font){
    font->color.r=color[0];
    font->color.g=color[1];
    font->color.b=color[2];
    font->color.a=color[3];
    switch(font->quality){
    case 1:
      c2.r=_windows_SANDAL2->current->background[0];
      c2.g=_windows_SANDAL2->current->background[1];
      c2.b=_windows_SANDAL2->current->background[2];
      c2.a=_windows_SANDAL2->current->background[3];
      s=TTF_RenderText_Shaded(font->font,font->text,font->color,c2);
      break;
    case 2:
      s=TTF_RenderText_Blended(font->font,font->text,font->color);
      break;
    default:
      s=TTF_RenderText_Solid(font->font,font->text,font->color);
    }
    if(s){
      if(font->texture){
	SDL_DestroyTexture(font->texture);
      }
      font->texture=SDL_CreateTextureFromSurface(_windows_SANDAL2->current->renderer,s);
      SDL_FreeSurface(s);
      if(font->texture){
	error = 0;
      }
    }
  }

  return error;
}

int setStyleFont(Font *font,int style){
  SDL_Surface *s;
  int error = 1;
  SDL_Color c2;

  if(_windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current->renderer && font && font->font){
    TTF_SetFontStyle(font->font,style);
    switch(font->quality){
    case 1:
      c2.r=_windows_SANDAL2->current->background[0];
      c2.g=_windows_SANDAL2->current->background[1];
      c2.b=_windows_SANDAL2->current->background[2];
      c2.a=_windows_SANDAL2->current->background[3];
      s=TTF_RenderText_Shaded(font->font,font->text,font->color,c2);
      break;
    case 2:
      s=TTF_RenderText_Blended(font->font,font->text,font->color);
      break;
    default:
      s=TTF_RenderText_Solid(font->font,font->text,font->color);
    }
    if(s){
      if(font->texture){
	SDL_DestroyTexture(font->texture);
      }
      font->texture=SDL_CreateTextureFromSurface(_windows_SANDAL2->current->renderer,s);
      SDL_FreeSurface(s);
      if(font->texture){
	error = 0;
      }
    }
  }

  return error;
}

int getStyleFont(Font *font,int * style){
  int error = 1;

  if(_windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current->renderer && font && font->font){
    error = 0;
    if(style){
      *style=TTF_GetFontStyle(font->font);
    }
  }

  return error;
}
/* ------------------------------------------------------- */
