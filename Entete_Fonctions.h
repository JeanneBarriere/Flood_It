#ifndef __ENTETE_FONCTIONS__
#define __ENTETE_FONCTIONS__

#include "API_Grille_txt.h"
#include "Liste_case.h"

/* Retourne dans L la liste des cases de meme couleur que la case i,j
(fonction imperative) */
void trouve_zone_rec(int **M, int nbcase,int i, int j, int *taille, ListeCase *L);

/* Algorithme tirant au sort une couleur: il utilise la fonction recursive pour determiner la Zsg */
int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff);

/* Retourne dans L la liste des cases de meme couleur que la case i,j
  (fonction imperative) */
void trouve_zone_imp(int **M, int dim, int *taille, ListeCase *L);

/* Algorithme tirant au sort une couleur: il utilise la fonction imperative pour determiner la Zsg */
int sequence_aleatoire_imp(int **M, Grille *G, int dim, int nbcl, int aff);



#endif  /* __ENTETE_FONCTIONS__ */
