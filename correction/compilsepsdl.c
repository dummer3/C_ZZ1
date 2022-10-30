#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/*
 * strucure cle (nom), valeur (note)
 */

int ERROR = 0;

#define ERROR_OK          0
#define ERROR_LIST_ALLOC  1
#define ERROR_FILE        1

typedef struct cell_s {
    char key[30];
    int  value;
    struct cell_s * nk, *nv;
} cell_t;

typedef struct list_s {
    cell_t * key;
    cell_t * value;
} list_t;


typedef struct gdata_s {
    SDL_Window   * window;
    SDL_Renderer * renderer;
    TTF_Font     * font;       
    int            width;
    int            height;
} gdata_t;

#define HISTOSIZE 21

/* #define DEBUG */

#ifdef DEBUG
    #define LOG(A) printf A
#else
    #define LOG(A) 
#endif

typedef int histogram_t[HISTOSIZE];

void initList(list_t * plist) {
    plist->key = plist->value = 0;
}

int insert(list_t * plist, char * nom, int note) {
    int ret = 0;
    cell_t * prec = 0, *cour =0;
    cell_t * cell = (cell_t * )malloc(sizeof(cell_t));

    if (cell) {
        strcpy(cell->key, nom);
        cell->value = note;
        cell->nk = cell->nv = 0;
        LOG(("** INSERT %s %d\n", cell->key, cell->value));

        prec = 0;
        cour = plist->key;
        while (cour &&  strcmp(cell->key, cour->key)>0) {
            prec = cour;
            cour = cour->nk;
        }
        if (prec) {
            cell->nk = prec->nk; 
            prec->nk = cell;
        } else {
            cell->nk = plist->key;
            plist->key = cell;
        }
        prec = 0;
        cour = plist->value;
        while (cour &&  cell->value < cour->value) {
            prec = cour;
            cour = cour->nv;
        }
        if (prec) {
            cell->nv = prec->nv; 
            prec->nv = cell;
        } else {
            cell->nv = plist->value;
            plist->value = cell;
        }
        ret = 1;
    } else ERROR = ERROR_LIST_ALLOC;
    
    return ret;
}

void displayByKey(list_t list) {
    cell_t * cour = list.key;
    
    printf("by key\n");
    while (cour) {
        printf("%s %d\n", cour->key, cour->value);
        cour = cour->nk;
    }
}

void displayByValue(list_t list) {
    cell_t * cour = list.value;
    
    printf("by value\n");
    while (cour) {
        printf("%s %d\n", cour->key, cour->value);
       cour = cour->nv;
    }
}

void freeList(list_t *plist) {
    plist-> key = plist-> value = NULL;
}

void computeHisto(histogram_t h, list_t l) {
    int i = 0;
    int j = 0;
    cell_t * cour = l.key;

    for (i=0; i < HISTOSIZE ; ++i)
        h[i] = 0.0;

    while (cour) {
        ++h[cour->value];
        cour = cour->nk;
        ++j;
    }
} 

void displayHisto(histogram_t h) {
    int i = 0;
    
    for (i=0; i < HISTOSIZE ; ++i)
        printf("[%2d] : %3d\n", i, h[i] );
}

int maxHisto(histogram_t h) {
    int i, max = h[0];
    
    for(i=1; i< HISTOSIZE; ++i)
        if (h[i]>max) max=h[i];
    
    return max;
}

float meanHisto(histogram_t h) {
    float som =0.;
    int   tot = 0, i;
    
    for (i=0; i< HISTOSIZE; ++i) {
        som  = h[i] * i;
        tot += h[i];
    }
    LOG(("MEAN %f / %d\n", som, tot));
    
    return som/(float)tot;
}

int countHisto(histogram_t h) {
    int   tot = 0, i;
    for (i=0; i< HISTOSIZE; ++i) {
        tot += h[i];
    }
    LOG(("TOT %d\n", tot));
  
    return tot;
}

void displayString(gdata_t g, char * chaine, int x, int y) {

    int iW, iH;
    SDL_Color     couleur  = {0, 0, 255, 255};
    SDL_Surface * surf     = TTF_RenderText_Blended(g.font, chaine, couleur);
    SDL_Texture * text     = SDL_CreateTextureFromSurface(g.renderer, surf);
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
    gdata_t        g;
    int graphics = 1;
    int sortie   = 0;
    SDL_Event      event;

    g.window     = 0;
    g.renderer   = 0;
    g.font       = 0;
    g.width      = 600;
    g.height     = 500;


    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
        graphics = 0;
    } else {

        g.window = SDL_CreateWindow("Répartition des notes", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                    g.width, g.height, SDL_WINDOW_SHOWN |  SDL_WINDOW_RESIZABLE); 
    
        if (g.window == 0) {
            fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
            graphics = 0; 
        } else {
            g.renderer = SDL_CreateRenderer(g.window, -1, SDL_RENDERER_ACCELERATED ); /* | SDL_RENDERER_PRESENTVSYNC */
            if (g.renderer == 0) {
                fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
                graphics = 0;
            } else {
                if (TTF_Init() != 0){
                    fprintf(stderr, "Erreur d'initialisation TTF : %s\n", TTF_GetError()); 
                    graphics = 0;
                } else {
                    g.font = TTF_OpenFont("Arial.ttf", 12 );  

                    if (!g.font) { 
                    	graphics = 0;
                    	fprintf(stderr, "La police ARIAL n'est pas chargee\n"); 
                    } 
                }
            }
        }
    }

    if (graphics==0) {
        if (g.font     != 0) TTF_CloseFont(g.font);
        if (g.renderer != 0) SDL_DestroyRenderer(g.renderer);
        if (g.window   != 0) SDL_DestroyWindow(g.window);
        TTF_Quit();
        SDL_Quit();
        return;
    }    

    while (!sortie) {

        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_WINDOWEVENT:
                    printf("window event\n");
                    switch (event.window.event)  {
                        case SDL_WINDOWEVENT_CLOSE:  
                            printf("appui sur la croix\n");
                            break;
                        case SDL_WINDOWEVENT_SIZE_CHANGED:
                            g.width  = event.window.data1;
                            g.height = event.window.data2;
                            printf("Size : %d%d\n", g.width, g.height);
                        default:
                            displayGraphicalHisto(g, h);
                            printf("evenenent window non pris en compte\n");
                    }   
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    break;
                case SDL_QUIT : 
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

int main(int argc, char **argv) {
  list_t list;
  histogram_t h;
  int text = 1;
  char *file = NULL;

  initList(&list);

  if (argc < 2) {
    printf("[HELP] %s file mode\n", argv[0]);
    printf("       where file is a text file containing the data to display\n");
    printf("       where mode belongs to text/graph\n\n");
  } else {
    /* first parameter is file */
    if (strcmp(argv[1], "text") && strcmp(argv[1], "graph")) {
      file = argv[1];
      if (argc >= 3)
        text = strcmp(argv[2], "graph");
    } else {
      /* first parameter is text/graph */
      text = strcmp(argv[1], "graph");
      if (argc >= 3)
        file = argv[2];
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
      computeHisto(h, list);

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
