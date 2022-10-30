#include "commun.h"
#include "histo.h"
#include "liste.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct gdata_s {
  SDL_Window *window;
  SDL_Renderer *renderer;
  TTF_Font *font;
  int width;
  int height;
} gdata_t;

void displayString(gdata_t g, char *chaine, int x, int y) {

  int iW, iH;
  SDL_Color couleur = {0, 0, 255, 255};
  SDL_Surface *surf = TTF_RenderText_Blended(g.font, chaine, couleur);
  SDL_Texture *text = SDL_CreateTextureFromSurface(g.renderer, surf);
  SDL_Rect rect;

  SDL_QueryTexture(text, NULL, NULL, &iW, &iH);

  rect.x = x;
  rect.y = y;
  rect.w = iW;
  rect.h = iH;

  SDL_RenderCopy(g.renderer, text, NULL, &rect);
}

void displayGraphicalHisto(gdata_t g, histogram_t h) {                          
    char chaine[255];
    int  maxx = 600;
    int  maxy = 400;
    int  i;   
    int  j = maxHisto(h);
  
    SDL_Rect r;
    SDL_SetRenderDrawColor(g.renderer, 255, 255, 255, 255);
    SDL_RenderClear(g.renderer);
    SDL_SetRenderDrawColor(g.renderer, 0, 0, 0, 255);

    for(i=0; i<HISTOSIZE; ++i) {
        r.x = (int)(maxx/22.0*(i+1));
        r.y = maxy-(int)(h[i]/(float)j*300.);
        r.w = 2;
        r.h = (int)(h[i]/(float)j*300.)+3;
        SDL_RenderFillRect(g.renderer, &r);
        
        sprintf(chaine, "%2d", i);
        displayString(g, chaine, (int)(maxx/22.0*(i+1)-4), 420);
        
        if (h[i]>0) {
            sprintf(chaine, "%d", h[i]);
            displayString(g, chaine, (int)(maxx/22.0*(i+1)-4), 75);
        }
        
    }
    
    strcpy(chaine, "Occurences");
    displayString(g, chaine, maxx-100, 50);
    sprintf(chaine, "Notes [%d]", countHisto(h));
    displayString(g, chaine, 10, 445);
    sprintf(chaine, "Moyenne : %f", meanHisto(h));
    displayString(g, chaine, 10, 470);

    SDL_RenderPresent(g.renderer);
}

void displayGraph(histogram_t h) {
  gdata_t g;
  int graphics = 1;
  int sortie = 0;
  SDL_Event event;

  g.window = 0;
  g.renderer = 0;
  g.font = 0;
  g.width = 600;
  g.height = 500;

  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    graphics = 0;
  } else {

    g.window = SDL_CreateWindow("Répartition des notes", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, g.width, g.height,
                                SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (g.window == 0) {
      fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n",
              SDL_GetError());
      graphics = 0;
    } else {
      g.renderer = SDL_CreateRenderer(
          g.window, -1,
          SDL_RENDERER_ACCELERATED); /* | SDL_RENDERER_PRESENTVSYNC */
      if (g.renderer == 0) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n",
                SDL_GetError());
        graphics = 0;
      } else {
        if (TTF_Init() != 0) {
          fprintf(stderr, "Erreur d'initialisation TTF : %s\n", TTF_GetError());
          graphics = 0;
        } else {
          g.font = TTF_OpenFont("Arial.ttf", 12);

          if (!g.font) {
            graphics = 0;
            fprintf(stderr, "La police ARIAL n'est pas chargee\n");
          }
        }
      }
    }
  }

  if (graphics == 0) {
    if (g.font != 0)
      TTF_CloseFont(g.font);
    if (g.renderer != 0)
      SDL_DestroyRenderer(g.renderer);
    if (g.window != 0)
      SDL_DestroyWindow(g.window);
    TTF_Quit();
    SDL_Quit();
    return;
  }

  while (!sortie) {

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_WINDOWEVENT:
        printf("window event\n");
        switch (event.window.event) {
        case SDL_WINDOWEVENT_CLOSE:
          printf("appui sur la croix\n");
          break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
          g.width = event.window.data1;
          g.height = event.window.data2;
          printf("Size : %d%d\n", g.width, g.height);
          break;
        default:
          displayGraphicalHisto(g, h);
          printf("evenenent window non pris en compte\n");
        }
        break;
      case SDL_MOUSEBUTTONDOWN:
        break;
      case SDL_QUIT:
        printf("on quitte\n");
        sortie = 1;
      }
    }
    SDL_Delay(1);
  }

  TTF_CloseFont(g.font);
  SDL_DestroyRenderer(g.renderer);
  SDL_DestroyWindow(g.window);
  TTF_Quit();
  SDL_Quit();
}

void displayText(histogram_t h) {
    displayHisto(h);
}

int main(int argc, char ** argv) {
    list_t list;
    histogram_t h;
    int text = 1;
    char * file = NULL;


    initList(&list); 

    if (argc<2) {
        printf("[HELP] %s file mode\n", argv[0]);
        printf("       where file is a text file containing the data to display\n");
        printf("       where mode belongs to text/graph\n\n");
    } else {
      /* first parameter is file */
      printf("%d\n", strcmp(argv[1],"text"));
      printf("%d\n", strcmp(argv[1],"text"));
      if (strcmp(argv[1], "text")  && strcmp(argv[1], "graph") ) {
	file = argv[1];
	if (argc>=3)
	  text = strcmp(argv[2], "graph");  
      } else {
	/* first parameter is text/graph */
	text = strcmp(argv[1], "graph");
	if (argc>=3)
	  file=argv[2];
      }

      if (file) {
	fprintf(stderr, "Reading external file not implemented\n\n");
	ERROR = ERROR_FILE;
      } else {

            printf("DEMO MODE -- dummy data");
      
            insert(&list, "un", 20);
            insert(&list, "deux", 10);
            insert(&list, "trois", 20);
            insert(&list, "quatre", 15);
            insert(&list, "cinq", 15);
            insert(&list, "six", 15);
            insert(&list, "sept", 0);
            insert(&list, "huit", 14);
            insert(&list, "neuf", 11);
            insert(&list, "dix", 7);
            displayByKey(list);
            displayByValue(list);
            computeHisto(h,list);

            if (text) {
                displayText(h);
            } else {
                displayGraph(h);
            }

            freeList(&list);	    
        }
    }

    return ERROR;
}   
