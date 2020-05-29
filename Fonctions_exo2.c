#include<stdio.h>
#include "Entete_Fonctions.h"

void trouve_zone_imp(int **M, int dim, int *taille, ListeCase *L){

  ListeCase * p = ( ListeCase *) malloc ( sizeof ( ListeCase ));
  init_liste(p);
  ajoute_en_tete (p , 0, 0);
  int i;
  int j;
  int t = 0;
  int cl = M[0][0];
  ajoute_en_tete(L, 0, 0);
  t++;

  while(!test_liste_vide(p)){
    enleve_en_tete(p, &i, &j);
    M[i][j]=-1;

    if(i+1<dim){
      if(cl==M[i+1][j]){
        ajoute_en_tete(p, i+1, j);
        ajoute_en_tete(L, i+1, j);
        M[i+1][j]=-1;
        t++;
      }
    }

    if(j+1<dim){
      if(cl==M[i][j+1]){
        ajoute_en_tete(p, i, j+1);
        ajoute_en_tete(L, i, j+1);
        M[i][j+1]=-1;
        t++;
      }
    }

    if(i-1>=0){
      if(cl==M[i-1][j]){
        ajoute_en_tete(p, i-1, j);
        ajoute_en_tete(L, i-1, j);
        M[i-1][j]=-1;
        t++;
      }
    }

    if(j-1>=0){
      if(cl==M[i][j-1]){
        ajoute_en_tete(p, i, j-1);
        ajoute_en_tete(L, i, j-1);
        M[i][j-1]=-1;
        t++;
      }
    }

  }
*taille = t;
detruit_liste(p);
free(p);
}


int sequence_aleatoire_imp(int **M, Grille *G, int dim, int nbcl, int aff){
  int cpt=0;
  int i;
  int j;
  int taille = 0;

  ListeCase * L = malloc(sizeof(ListeCase));
  init_liste(L);

  while(taille<(dim*dim)){

    int c=rand()%(nbcl);
    if (c!=M[0][0]){//si la couleur n'est pas celle de (0,0) on colore la Zsg */
      cpt++;
      trouve_zone_imp(M, dim, &taille, L);
      ListeCase tmp = *L;
      while(tmp){
        M[tmp->i][tmp->j]=c;
        tmp=tmp->suiv;
      }
      detruit_liste(L);
      taille=0;
      trouve_zone_imp(M, dim, &taille, L);
      tmp = *L;
      while(tmp){
        M[tmp->i][tmp->j]=c;
        tmp=tmp->suiv;
      }
      if (aff==1){  /* Affichage de la grille */
        printf("essai suivant : \n");
        for (i=0;i<dim;i++){
          for (j=0;j<dim;j++){
            Grille_attribue_couleur_case(G,i,j,M[i][j]);
          }
        }
        Grille_redessine_Grille(G);
      }
    }
  }
  detruit_liste(L);
  free(L);
  return cpt;
}
