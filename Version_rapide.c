#include<stdlib.h>
#include<stdio.h>
#include "Version_rapide.h"

/*Initialise la structure Zsg */
void init_Zsg (S_Zsg * Z, int dim, int nbcl){
  int i,j;
  Z->dim = dim;
  Z->nbcl = nbcl;

  ListeCase L = malloc(sizeof(ListeCase));
  L = NULL;
  Z->Lzsg=L;

  ListeCase * B = (ListeCase*)malloc(nbcl*sizeof(ListeCase));
  for (i=0; i<nbcl ; i++){
    B[i]=NULL;
  }
  Z->B=B;

  int **App;
  App=(int **) malloc(sizeof(int*)*dim);
  for (i=0;i<dim;i++){
    App[i]=(int*) malloc(sizeof(int)*dim);
    if (App[i]==0) printf("Pas assez d'espace mémoire disponible\n");
  }
  for (i=0;i<dim;i++){
    for (j=0;j<dim;j++){
      App[i][j]=-2;
    }
  }
  Z->App = App;
}

/* Ajoute une case dans la liste Lzsg */
void ajoute_Zsg (S_Zsg * Z, int i, int j){
  Elnt_liste *elnt;
  elnt=(Elnt_liste*) malloc(sizeof(Elnt_liste *));
  elnt->suiv=Z->Lzsg;
  elnt->i=i;
  elnt->j=j;
  Z->Lzsg=elnt;
}

/* Ajoute une case dans la bordure d'une couleur cl donnee */
void ajoute_Bordure(S_Zsg * Z, int i, int j, int cl){
  Elnt_liste *elnt;
  elnt=(Elnt_liste*) malloc(sizeof(Elnt_liste *));
  elnt->suiv=Z->B[cl];
  elnt->i=i;
  elnt->j=j;
  Z->B[cl]=elnt;
}

/* Renvoie vrai si la case est dans la Lzsg */
int appartient_Zsg (S_Zsg * Z, int i, int j){
  ListeCase tmp = Z->Lzsg;
  while(tmp){
    if(tmp->i==i && tmp->j==j){
      return 1;
    }
    tmp = tmp->suiv;
  }
  return 0;
}

/* Renvoie vrai si la case est dans la bordure de couleur cl donnee */
int appartient_Bordure (S_Zsg * Z, int i, int j, int cl){
  ListeCase tmp = Z->B[cl];
  while(tmp){
    if(tmp->i==i && tmp->j==j){
      return 1;
    }
    tmp = tmp->suiv;
  }
  return 0;
}

/* Met a jour les champs Lzsg et B d'une S_Zsg lorsqu'une case bascule de l'un a l'autre */
int agrandit_Zsg (int **M, S_Zsg *Z, int cl, int k, int l){

    ListeCase * p = ( ListeCase *) malloc ( sizeof ( ListeCase ));
    init_liste(p);
    ajoute_en_tete (p , k, l);
    int i = k;
    int j = l;
    int t = 0;
    ajoute_Zsg (Z,i,j);

    t++;

    while(!test_liste_vide(p)){

      enleve_en_tete(p, &i, &j);

      if(i+1<(Z->dim)){
        if(!present_liste(p, i+1, j)){
          if(cl==M[i+1][j]){
            if(!appartient_Zsg (Z, i+1, j)){
              ajoute_en_tete(p, i+1, j);
              ajoute_Zsg (Z,i+1, j);
              t++;
            }
          }else if(appartient_Bordure (Z, i+1,j,M[i+1][j])){
            ajoute_Bordure(Z, i+1, j, cl);
          }
        }
      }

      if(j+1<(Z->dim)){
        if(!present_liste(p, i, j+1)){
          if(cl==M[i][j+1]){
            if(!appartient_Zsg (Z, i, j+1)){
              ajoute_en_tete(p, i, j+1);
              ajoute_Zsg (Z,i, j+1);
              t++;
            }
          }else if(appartient_Bordure (Z, i,j+1,M[i+1][j])){
            ajoute_Bordure(Z, i, j+1, cl);
          }
        }
      }

      if(i-1>=0){
        if(!present_liste(p, i-1, j)){
          if(cl==M[i-1][j]){
            if(!appartient_Zsg (Z, i-1, j)){
              ajoute_en_tete(p, i-1, j);
              ajoute_Zsg (Z,i-1, j);
              t++;
            }
          }else if(appartient_Bordure (Z, i-1,j,M[i-1][j])){
            ajoute_Bordure(Z, i-1, j, cl);
          }
        }
      }

      if(j-1>=0){
        if(!present_liste(p, i, j-1)){
          if(cl==M[i][j-1]){
            if(!appartient_Zsg (Z, i, j-1)){
              ajoute_en_tete(p, i, j-1);
              ajoute_Zsg (Z,i, j-1);
              t++;
            }
          }else if(appartient_Bordure (Z, i,j-1,M[i-1][j])){
            ajoute_Bordure(Z, i, j-1, cl);
          }
        }
      }

    }
  detruit_liste(p);
  return t;
}

void sequence_aleatoire_rapide (int **M, Grille *G, int dim, int nbcl, int aff){
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
        trouve_zone_imp(M, dim, &taille, L);
        ListeCase tmp = *L;
        while(tmp){
          M[tmp->i][tmp->j]=c;
          tmp=tmp->suiv;
        }
      detruit_liste(L);
      }
      ListeCase * L = malloc(sizeof(ListeCase));
      init_liste(L);
      trouve_zone_imp(M, dim, &taille, L);
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
}
