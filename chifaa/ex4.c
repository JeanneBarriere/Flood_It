#include "partie2.h"
#include <stdio.h>
#include <stdlib.h>

/* ajouter un pointeur sur Sommet à une liste chaı̂née de Cellule som passée
en paramètre */
void ajoute_liste_sommet(Cellule_som ** pListe, Sommet * sommet){
	Cellule_som * nouv_sommet = (Cellule_som *) malloc(sizeof(Cellule_som));
	nouv_sommet->sommet = sommet;//on initialise 
	nouv_sommet->suiv = *pListe;
	*pListe = nouv_sommet;//on met en tete de pListe
}

/* détruire une liste chaı̂née de Cellule som SANS détruire les sommets
pointées par cette liste */

void detruit_liste_sommet(Cellule_som **pListe){
	Cellule_som * tmp1,tmp2; /* 2 tmp pour ne pas perdre le pointeur sur les cellules */
	tmp1=*pListe;

	//on parcourt la liste chainee
	while(tmp1){
		tmp2=tmp1;
		tmp1=tmp1->suiv;
		free(tmp2);//on desalloue la case Cellule_som sans desallouer la sommet ou il point
	}
}

/* mettre à jour deux sommet s1 et s2 en indiquant qu’ils
sont adjacents l’un de l’autre */
void ajoute_voisin(Sommet *s1, Sommet *s2){
	ajoute_liste_sommet(&(s1->sommet_adj),s2);//ajouter s2 a la liste des sommets adj de s1 
	ajoute_liste_sommet(&(s2->sommet_adj),s1);//ajouter s1 a la liste des sommets adj de s2
}

/* fonction booléenne qui renvoie vrai si et seulement si deux sommets sont adjacents */
int adjacent(Sommet *s1, Sommet *s2){

	if(s1==s2) return 0; // 2 sommets identiques ne sont pas adj

	Cellule_som *l1=s1->sommet_adj;
	//parcourir la liste des sommets adj de s1 
	while(l1){
		if(l1->sommet==s2) return 1;
		else
			l1=l1->suiv;
	}
	return 0;//non adj
}

/* créer le graphe tout entier */
Graphe_zone * cree_graphe_zone(int **M, int dim, int nbcl){

	/* Initialiser la structure de graphe */
	Graphe_zone *gz = (Graphe_zone *) malloc(sizeof(Graphe_zone));
	gz->nbsom=0;
	gz->som=NULL;
	/*la matrice mat contient le pointeur NULL pour chaque case*/
	int i,j;
	gz->mat = (Sommet ***)malloc(sizeof(Sommet **)*dim);
	for(i=0;i<dim;i++){
		gz->mat[i] = (Sommet **) malloc(sizeof(Sommet *)*dim);
		for(j=0;j<dim;j++) gz->mat[i][j] = NULL;
	}
	
	//Pour chaque case (i, j) de la grille
	for(i=0;i<dim;i++){
		for(j=0;j<dim;j++){	
			/* créer un sommet vide de cases */
			nouv_sommet = (Sommet *)malloc(sizeof(Sommet));
			nouv_sommet->num=gz->nbsom; //le nombre des sommmets
			nouv_sommet->cl = M[i][j];//couleur sur M
			nouv_sommet->sommet_adj=NULL;
			
			init_liste(&(nouv_sommet->cases));
			taille=0; //le nombre des case d'une zone
			//mettre la zone de (i,j) dans la cases de nouvelle sommet
			trouve_zone_rec(M,dim,i,j,&taille,&(nouv_sommet->cases));

			ListeCase lc=nouv_sommet->cases;
			for(lc!=NULL){
					gz->mat[lc->i][lc->j]=nouv_sommet; //on initialise le pointeur de mat avec la nouvelle sommet
					M[lc->i][lc->j]=nouv_sommet->cl; //on retourne la couleur de matrice
					lc=lc->suiv;
			}
			
			nouv_sommet->nbcase_som=taille;
			ajoute_liste_sommet(&(gz->som),nouv_sommet);//ajouter le sommet dans la graphe
			(gz->nbsom)++;//incrementer la nombre de sommets
		}
	}
	return gz;	
}