#include "flood.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

enum ETAT { INTRODUCTION = 0, JEU = 1, FIN = -1 };
typedef struct {
  SDL_Window *window;
  SDL_Renderer *rend;
  couleur_t *couleurs;
  int size;
  SDL_Rect rect;
  SDL_Texture *fondIntro;
  SDL_Texture *text;
  TTF_Font *font;
} graphique_t;

typedef struct {
  enum ETAT et;
  int tab[TAILLE][TAILLE];
  int running;
  int ancienneCouleur;
} moteur_t;

void initialiserMoteur(moteur_t *m) {
  m->running = 1;
  m->ancienneCouleur = -1;
  initialiser(m->tab);
  m->et = INTRODUCTION;
}

void initialiserSDL(graphique_t *g) {
  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
  }
}

void initialiserWindows(graphique_t *g) {
  g->window =
      SDL_CreateWindow("Flood", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       g->size, g->size, SDL_WINDOW_RESIZABLE);

  if (g->window == 0) {
    fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    /* on peut aussi utiliser SLD_Log() */
  }
}

void initialiserRenderer(graphique_t *g) {
  g->rend = SDL_CreateRenderer(
      g->window, -1, SDL_RENDERER_ACCELERATED); /*  SDL_RENDERER_SOFTWARE */

  if (g->rend == 0) {
    fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    /* faire ce qu'il faut pour quitter proprement */
  }
}

void initialiserImage(graphique_t *g) {
  int flags = IMG_INIT_JPG | IMG_INIT_PNG;
  int initted = 0;

  initted = IMG_Init(flags);

  if ((initted & flags) != flags) {
    printf("IMG_Init: Impossible d'initialiser le support des formats JPG et "
           "PNG requis!\n");
    printf("IMG_Init: %s\n", IMG_GetError());
  }

  SDL_Surface *surface = NULL;
  surface = IMG_Load("image.jpeg");
  if (!surface) {
    printf("IMG_Load: %s\n", IMG_GetError());
  }

  g->fondIntro = SDL_CreateTextureFromSurface(g->rend, surface);
  SDL_FreeSurface(surface);
}

void initialiserTexte(graphique_t *g) {
  if (TTF_Init() != 0) {
    fprintf(stderr, "Erreur d'initialisation TTF : %s\n", TTF_GetError());
  }
  SDL_Color couleur = {0, 150, 255, 255};
  g->font = TTF_OpenFont("chlorinar.regular.ttf", 80);
  SDL_Surface *surf =
      TTF_RenderText_Blended(g->font, "Appuyer pour jouer", couleur);
  g->text = SDL_CreateTextureFromSurface(g->rend, surf);
  SDL_FreeSurface(surf);
}
void initialiserGraphique(graphique_t *g) {
  g->size = 900;
  g->couleurs = aleaCouleur();

  initialiserSDL(g);
  initialiserWindows(g);
  initialiserRenderer(g);
  initialiserImage(g);
  initialiserTexte(g);
}

void afficherEcranJeu(moteur_t *m, graphique_t *g) {
  for (int i = 0; i < TAILLE; i++) {
    for (int j = 0; j < TAILLE; j++) {
      SDL_SetRenderDrawColor(g->rend, g->couleurs[m->tab[i][j]].r,
                             g->couleurs[m->tab[i][j]].g,
                             g->couleurs[m->tab[i][j]].b, 0);
      g->rect.x = g->size / TAILLE * j;
      g->rect.y = g->rect.h = g->size / TAILLE * i;
      g->rect.w = g->rect.h = g->size / TAILLE;
      SDL_RenderFillRect(g->rend, &g->rect);
      SDL_RenderPresent(g->rend);
    }
  }
}

void afficherEcranIntro(graphique_t *g) {

  int iW, iH;
  g->rect.x = 0;
  g->rect.y = 0;
  g->rect.w = g->rect.h = g->size;
  SDL_RenderCopy(g->rend, g->fondIntro, NULL, &(g->rect));
  SDL_RenderPresent(g->rend);

  SDL_QueryTexture(g->text, NULL, NULL, &iW, &iH);

  g->rect.x = (g->size) / 2 - iW / 2;
  g->rect.y = (g->size) / 2 - iH / 2;
  g->rect.w = iW;
  g->rect.h = iH;

  SDL_RenderCopy(g->rend, g->text, NULL, &(g->rect));
  SDL_RenderPresent(g->rend);
}

void afficherEcranFin(moteur_t *m, graphique_t *g) {}

void display(moteur_t *m, graphique_t *g) {
  switch (m->et) {
  case INTRODUCTION:
    afficherEcranIntro(g);
    break;
  case JEU:
    afficherEcranJeu(m, g);
    break;
  case FIN:
    afficherEcranFin(m, g);
    break;
  }
}

void actionJeu(SDL_Event event, moteur_t *m, graphique_t *g) {
  switch (event.type) {
  case SDL_MOUSEBUTTONDOWN:
    if (m->ancienneCouleur != m->tab[event.button.y * TAILLE / g->size]
                                    [event.button.x * TAILLE / g->size]) {
      remplir(m->tab, m->tab[0][0],
              m->tab[event.button.y * TAILLE / g->size]
                    [event.button.x * TAILLE / g->size],
              0, 0);
      afficherEcranJeu(m, g);
      afficherGrilleCouleur(m->tab);
      m->ancienneCouleur = m->tab[0][0];
    }
    break;
  }
}

void actionIntro(SDL_Event event, moteur_t *m, graphique_t *g) {
  switch (event.type) {
  case SDL_MOUSEBUTTONDOWN:
    m->et = JEU;
    display(m, g);
    break;
  }
}

void actionFin(SDL_Event event, moteur_t *m, graphique_t *g) {}

int main() {

  SDL_Event event;

  graphique_t *g = malloc(sizeof(graphique_t));
  moteur_t *m = malloc(sizeof(moteur_t));
  initialiserMoteur(m);
  initialiserGraphique(g);

  display(m, g);

  while (m->running) {

    while (SDL_PollEvent(&event) && m->running) {
      switch (event.type) {
      case SDL_WINDOWEVENT:
        switch (event.window.event) {
        case SDL_WINDOWEVENT_CLOSE:
          printf("appui sur la croix\n");
          m->running = 0;
          break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
          g->size = event.window.data1 < event.window.data2
                        ? event.window.data1
                        : event.window.data2;
          SDL_SetWindowSize(g->window, g->size, g->size);
          display(m, g);
          break;
        }
        break;
      case SDL_QUIT:
        printf("on quitte\n");
        m->running = 0;
        break;
      default:
        switch (m->et) {
        case INTRODUCTION:
          actionIntro(event, m, g);
          break;
        case JEU:
          actionJeu(event, m, g);
          break;
        case FIN:
          actionFin(event, m, g);
          break;
        }
      }
    }
    SDL_Delay(1); //  delai minimal
  }

  SDL_DestroyRenderer(g->rend);
  SDL_DestroyWindow(g->window);
  SDL_DestroyTexture(g->fondIntro);
  TTF_CloseFont(g->font);
  free(g);
  free(m);
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
  return 0;
}
