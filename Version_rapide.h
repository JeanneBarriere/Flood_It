#ifndef __VERSION_RAPIDE__
#define __VERSION_RAPIDE__

#include "API_Grille_txt.h"
#include "Liste_case.h"
#include "Entete_Fonctions.h"

typedef struct s_Zsg {
  int dim ; /* dimension de la grille */
  int nbcl ; /* nombre de couleurs */

  ListeCase Lzsg ; /* Liste des cases de la zone Zsg */
  ListeCase *B ; /* Tableau de listes de cases de la bordure */
  int **App ; /* Tableau a double entree des appartenances */

} S_Zsg ;

/*Initialise la structure Zsg */
void init_Zsg (S_Zsg * Z, int dim, int nbcl);

/*Detruit la structure Zsg */
void detruit_Zsg (S_Zsg * Z);

/* Ajoute une case dans la liste Lzsg */
void ajoute_Zsg (S_Zsg * Z, int i, int j);

/* Ajoute une case dans la bordure d'une couleur cl donnee */
void ajoute_Bordure(S_Zsg * Z, int i, int j, int cl);

/* Renvoie vrai si la case est dans la Lzsg */
int appartient_Zsg (S_Zsg * Z, int i, int j);

/* Renvoie vrai si la case est dans la bordure de couleur cl donnee */
int appartient_Bordure (S_Zsg * Z, int i, int j, int cl);

/* Met a jour les champs Lzsg et B d'une S_Zsg lorsqu'une case bascule de l'un a l'autre */
int agrandit_Zsg (int **M, S_Zsg *Z, int cl, int K, int l);

/* Algorithme tirant au sort une couleur: il utilise la fonction precedente pour agrandir la Zsg */
int sequence_aleatoire_rapide (int **M, Grille *G, int dim, int nbcl, int aff);

#endif  /* __VERSION_RAPIDE__ */
