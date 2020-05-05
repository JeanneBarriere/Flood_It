#include<stdio.h>
#include "Entete_Fonctions.h"

void trouve_zone_rec(int **M, int dim, int i, int j, int *taille, ListeCase *L){
  ajoute_en_tete(L, i, j);
  (*taille)++;
  if(i+1<dim){
    if(M[i][j]==M[i+1][j]){
      if(!present_liste(L, i+1, j)){
        trouve_zone_rec(M, dim, i+1, j, taille, L);
      }
    }
  }

  if(j+1<dim){
    if(M[i][j]==M[i][j+1]){
      if(!present_liste(L, i, j+1)){
        trouve_zone_rec(M, dim, i, j+1, taille, L);
      }
    }
  }

  if(i-1>=0){
    if(M[i][j]==M[i-1][j]){
      if(!present_liste(L, i-1, j)){
        trouve_zone_rec(M, dim, i-1, j, taille, L);
      }
    }
  }

  if(j-1>=0){
    if(M[i][j]==M[i][j-1]){
      if(!present_liste(L, i, j-1)){
        trouve_zone_rec(M, dim, i, j-1, taille, L);
      }
    }
  }
}


int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff){
  int cpt=0;
  int i;
  int j;
  int taille;

  Grille_init(dim,nbcl, 500,&G);

  while(taille<(dim*dim)){
    if (aff==1){  /* Affichage de la grille */
      printf("essai suivant : \n");

      for (i=0;i<dim;i++){
        for (j=0;j<dim;j++){
          Grille_attribue_couleur_case(G,i,j,M[i][j]);
        }
      }
      Grille_redessine_Grille(G);
    }

    int c=rand()%(nbcl);
    if (c!=M[0][0]){
      ListeCase * L = malloc(sizeof(ListeCase));
      init_liste(L);
      cpt++;
      int taille = 0;
      trouve_zone_rec(M, dim, 0, 0, &taille, L);
      ListeCase tmp = *L;
      while(tmp){
        M[tmp->i][tmp->j]=c;
        tmp=tmp->suiv;
      }
    detruit_liste(L);
    }
    ListeCase * L = malloc(sizeof(ListeCase));
    init_liste(L);
    trouve_zone_rec(M, dim, 0, 0, &taille, L);
    printf("taille 2 : %d\n", taille);
    detruit_liste(L);
  }

  for (i=0;i<dim;i++){
    for (j=0;j<dim;j++){
      Grille_attribue_couleur_case(G,i,j,M[i][j]);
    }
  }
  Grille_redessine_Grille(G);
  return cpt;
}
