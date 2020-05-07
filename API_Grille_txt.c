#include "API_Grille_txt.h"

#include<string.h>


void Grille_init(int dim, int nbcl, int taille_pixel,Grille **G){
  int i,j,cl;
  unsigned int genecl = 10101;

  (*G)=(Grille*) malloc(sizeof(Grille));

  (*G)->dim=dim;
  (*G)->nbcl=nbcl;



  (*G)->Tab=(char**) malloc(sizeof(char*)*dim);
  for (i=0;i<dim;i++)
    (*G)->Tab[i]=(char*) malloc(sizeof(char)*dim);

  (*G)->T_coul=(char**) malloc(sizeof(char*)*nbcl);
  for (i=0;i<nbcl;i++)
    (*G)->T_coul[i]=(char*) malloc(sizeof(char)*30);

  char ch[8]="\033[3";
  char ch2[8]="\033[4";
  char coul[4];

  cl=0;
  i=0;
  while (i<8 && cl<nbcl){
    strcat((*G)->T_coul[cl],ch);
    sprintf(coul, "%d",i);
    strcat((*G)->T_coul[cl],coul);
    strcat((*G)->T_coul[cl],"m");

    strcat((*G)->T_coul[cl],ch2);
    sprintf(coul, "%d",i);
    strcat((*G)->T_coul[cl],coul);
    strcat((*G)->T_coul[cl],"m\0");
    cl++;
    i++;
  }

  i=0;
  while (i<8 && cl<nbcl){
    j=0;
    while (j<8 && cl<nbcl){
      if (i!=j){
	strcat((*G)->T_coul[cl],ch);
	sprintf(coul, "%d",i);
	strcat((*G)->T_coul[cl],coul);
	strcat((*G)->T_coul[cl],"m");

	strcat((*G)->T_coul[cl],ch2);
	sprintf(coul, "%d",j);
	strcat((*G)->T_coul[cl],coul);
	strcat((*G)->T_coul[cl],"m\0");
	cl++;
      }
      j++;
    }
    i++;
  }
}

void Grille_free(Grille **G){
  int i;

  for(i=0;i<(*G)->dim;i++) free((*G)->Tab[i]);
  free((*G)->Tab);

  for (i=0;i<(*G)->nbcl;i++) free((*G)->T_coul[i]);
  free((*G)->T_coul);
  free(*G);

}

void Grille_ouvre_fenetre(Grille *G){
  /* Fonction vide dans le cas mode texte */
}


void Grille_ferme_fenetre()
{
  /* Fonction vide dans le cas mode texte */
}


void Grille_attribue_couleur_case(Grille *G, int i, int j, int c){

  G->Tab[i][j]=c%49;

}

void Grille_redessine_Grille(Grille *G){
  int i,j;
  printf("\033[H\033[2J");
  for (i=0;i<G->dim;i++){
    for (j=0;j<G->dim;j++){
      //     printf("\033[34;01m%c\033[00m",'0');  //,G->Tab[i][j]);
      //couleur_char(G->T_coul[G->Tab[i][j]]);
      printf("%s00", G->T_coul[G->Tab[i][j]]);
    }
    printf("\033[00m\n");
  }

}

 void Grille_attente_touche(){

  /* Attente touche est remplace par un delai d'attente */

  int i;

  for (i=0;i<100000;i++){}

}
