#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "API_Grille_txt.h"
#include "API_Gene_instance.h"
#include "Entete_Fonctions.h"
#include "Liste_case.h"
#include "Version_rapide.h"

int main(int argc,char**argv){

  clock_t temps_initial ; /* Temps initial en micro-secondes */
  clock_t temps_final ; /* Temps final en micro-secondes */
  double temps_cpu ; /* Temps total en secondes */

  int dim, nbcl, nivdif, graine, exo, aff;

  FILE* fichier = NULL ;

  // fichier = fopen("EXO1/vitesse_dim.txt", "r+");

  dim=5;
  nbcl=5;
  nivdif=3;
  graine=2;
  exo=1;
  aff=0;


  /* Allocation puis Generation de l'instance */
  while(dim<1001){
    temps_initial = clock () ;
    Grille *G;
    int i,j;
    int **M;
    M=(int **) malloc(sizeof(int*)*dim);
    for (i=0;i<dim;i++){
      M[i]=(int*) malloc(sizeof(int)*dim);
      if (M[i]==0) printf("Pas assez d'espace mémoire disponible\n");
    }
    Gene_instance_genere_matrice(dim, nbcl, nivdif, graine, M);



    if (aff==1){  /* Affichage de la grille */
      Grille_init(dim,nbcl, 500,&G);

      for (i=0;i<dim;i++)
      for (j=0;j<dim;j++){
        Grille_attribue_couleur_case(G,i,j,M[i][j]);
      }
    }

    temps_initial = clock ();
    sequence_aleatoire_rec(M, G, dim, nbcl, aff);

    temps_final = clock ();
    temps_cpu = (temps_final - temps_initial) * 1e-6;

    /* Desallocation de la matrice */
    for(i = 0; i< dim; i++) {
      if (M[i])
      free(M[i]);
    }
    if (M) free(M);

    if (aff==1){  /* Fermeture et désallocation de la grille */

      Grille_free(&G);
    }
    temps_final = clock () ;
    temps_cpu = (( double ) ( temps_final - temps_initial ) ) / CLOCKS_PER_SEC ;
     printf ("%d %f \n", dim , temps_cpu ) ;
		// fprintf (fichier, "%d %f \n", dim , temps_cpu ) ;
    dim=dim+5;
  }
  // fclose(fichier);
  return 0;
}
