#include<stdlib.h>
#include<stdio.h>
#include "Version_rapide.h"

/*Initialise la structure Zsg */
void init_Zsg (S_Zsg * Z, int dim, int nbcl){
  int i,j;
  Z->dim = dim;
  Z->nbcl = nbcl;

  init_liste(&(Z->Lzsg));

  Z->B=(ListeCase*)malloc(nbcl*sizeof(ListeCase));
  for (i=0; i<nbcl ; i++){
    Z->B[i]=NULL;
  }

  Z->App =(int **) malloc(sizeof(int*)*dim);
  for (i=0;i<dim;i++){
    Z->App[i]=(int*) malloc(sizeof(int)*dim);
    if (Z->App[i]==0) printf("Pas assez d'espace mémoire disponible\n");
  }
  for (i=0;i<dim;i++){
    for (j=0;j<dim;j++){
      Z->App[i][j]=-2;
    }
  }
}

void detruit_Zsg (S_Zsg * Z){
  detruit_liste(&(Z->Lzsg));
  free(Z->Lzsg);
  int i;
  for (i=0; i<Z->nbcl ; i++){
    detruit_liste(&(Z->B[i]));
    free(Z->B[i]);
  }
  free(Z->B);

  for (i=0; i<Z->dim ; i++){
    free(Z->App[i]);
  }
  free(Z->App);
  free(Z);
}

/* Ajoute une case dans la liste Lzsg */
void ajoute_Zsg (S_Zsg * Z, int i, int j){
  Elnt_liste *elnt;
  elnt=(Elnt_liste*) malloc(sizeof(Elnt_liste));
  elnt->suiv=Z->Lzsg;
  elnt->i=i;
  elnt->j=j;
  Z->Lzsg=elnt;
  Z->App[i][j]=-1;
}

/* Ajoute une case dans la bordure d'une couleur cl donnee */
void ajoute_Bordure(S_Zsg * Z, int i, int j, int cl){
  Elnt_liste *elnt;
  elnt=(Elnt_liste*) malloc(sizeof(Elnt_liste ));
  elnt->suiv=Z->B[cl];
  elnt->i=i;
  elnt->j=j;
  Z->B[cl]=elnt;
  Z->App[i][j]=cl;
}

/* Renvoie vrai si la case est dans la Lzsg */
int appartient_Zsg (S_Zsg * Z, int i, int j){
  return (Z->App[i][j]==-1);
}

/* Renvoie vrai si la case est dans la bordure de couleur cl donnee */
int appartient_Bordure (S_Zsg * Z, int i, int j, int cl){
  return (Z->App[i][j]==cl);
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
          if((!appartient_Zsg (Z, i+1, j))&&!(appartient_Bordure(Z, i+1,j,M[i+1][j]))){
            ajoute_en_tete(p, i+1, j);
            ajoute_Zsg (Z,i+1, j);
            t++;
          }
        }else if(!(appartient_Bordure (Z, i+1,j,M[i+1][j]))){
          ajoute_Bordure(Z, i+1, j, M[i+1][j]);
        }
      }
    }

    if(j+1<(Z->dim)){
      if(!present_liste(p, i, j+1)){
        if(cl==M[i][j+1]){
          if((!appartient_Zsg (Z, i, j+1))&&!(appartient_Bordure(Z, i,j+1,M[i][j+1]))){
            ajoute_en_tete(p, i, j+1);
            ajoute_Zsg (Z,i, j+1);
            t++;
          }
        }else if(!(appartient_Bordure (Z, i,j+1,M[i][j+1]))){
          ajoute_Bordure(Z, i, j+1, M[i][j+1]);
        }
      }
    }


    if(i-1>=0){
      if(!present_liste(p, i-1, j)){
        if(cl==M[i-1][j]){
          if((!appartient_Zsg (Z, i-1, j))&&!(appartient_Bordure(Z, i-1,j,M[i-1][j]))){
            ajoute_en_tete(p, i-1, j);
            ajoute_Zsg (Z,i-1, j);
            t++;
          }
        }else if(!(appartient_Bordure (Z, i-1,j,M[i-1][j]))){
          ajoute_Bordure(Z, i-1, j, M[i-1][j]);
        }
      }
    }

    if(j-1>=0){
      if(!present_liste(p, i, j-1)){
        if(cl==M[i][j-1]){
          if((!appartient_Zsg (Z, i, j-1))&&!(appartient_Bordure(Z, i,j-1,M[i][j-1]))){
            ajoute_en_tete(p, i, j-1);
            ajoute_Zsg (Z,i, j-1);
            t++;
          }
        }else if(!(appartient_Bordure (Z, i,j-1,M[i][j-1]))){
          ajoute_Bordure(Z, i, j-1, M[i][j-1]);
        }
      }
    }
  }
  detruit_liste(p);
  free(p);
  return t;
}

/* Algorithme tirant au sort une couleur: il utilise la fonction precedente pour agrandir la Zsg */
int sequence_aleatoire_rapide (int **M, Grille *G, int dim, int nbcl, int aff){
  int cpt=0;
  int i;
  int j;
  int cl = 0;
  int taille = 0;

  S_Zsg * Z = (S_Zsg*) malloc(sizeof(S_Zsg));
  init_Zsg(Z, dim, nbcl);
  taille = taille + agrandit_Zsg( M, Z, M[0][0], 0, 0);

  while(taille<(dim*dim)){
    cl=rand()%(nbcl);
    if (cl!=M[0][0]){
      cpt++;
      ListeCase tmp = Z->Lzsg;

      while(tmp){
        M[tmp->i][tmp->j]=cl;
        tmp=tmp->suiv;
      }

      tmp = Z->B[cl];
      while(tmp){
        taille = taille + agrandit_Zsg(M , Z, cl, tmp->i, tmp->j);
        tmp=tmp->suiv;
      }
      detruit_liste(&(Z->B[cl]));
      Z->B[cl]=NULL;
      detruit_liste(&tmp);

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
  detruit_Zsg (Z);
  return cpt;
}
