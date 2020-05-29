void trouve_zone_imp (int **M, int nbcase, int i, int j, int *taille, Liste Case *L ){
ListeCase P; 
int k, l; 
int cl=M[i][j]; 
M[i][j]=-1; 
ajoute_en_tete(L,i,j); 
*taille=0; 
init_liste (&P); 
ajoute_en_tete (&P ,i,j);

while (!test_liste_vide (&P)){ 
	enleve_en_tete (&P ,&k , &l); 
	(*taille) ++; 
 
	if ((k!=0) && (M[k-1][1]==cl)){ 
		M[k-1] [i]=-1; 
		ajoute_en_tete (L, k-1,1); 
		ajoute_en_tete (&P, k-1,1);
	} 
	if ((k!=nbcase -1) && (M[k+1][i]==cl)){ 
		M[k+1] [1]=-1; 
		ajoute_en_tete (L, k+1,1); 
		ajoute_en_tete (&P, k+1, 1); 
	} 
	if ((1 !=0) && (M[k][1-1] ==cl)){ 
		M[k] [1-1]=-1; 
		ajoute_en_tete (L,k,1-1); 
		ajoute_en_tete (&P,k,1-1);
	}
	if ((1!=nbcase-1)&&(M[k][1+1]==cl)) { 
		M[k] [1+1] =-1; 
		ajoute_en_tete (L,k,1+1); 
		ajoute_en_tete (&P,k,1+1); 
	}
}
}

int sequence aleatoire imp (int **M, Grille *G, int dim, int nbcl, int aff) { 
	int taille_zsg; 
	int i, j, cl; 
	ListeCase L; 
	Elnt-liste *cour; 
	int NBcase=dim*dim; 
	int cpt=0; 
	init_liste (&L); 
	do{ 
		taille_zsg=0; 
		detruit liste (&L); 
		trouve_zone_imp (M,dim ,0,0,& taille_zsg , &L); 
		if (taille_zsg==NBcase) return cpt; 
		cpt++;

		do{ 
			cl=rand %nbcl; 
		} while (cl==M[0][0]); 

		cour=L; 

		while (cour != NULL) { 
			M[cour->i][cour->j]=cl; 
			cour= cour ->suiv; 
		}

		if (aff == 1) { 
			cour=L; 
			while (cour !=NULL) { 
				Grille_attribue_couleur_case (G, cour->i, cour->j, cl); 
				cour= cour->suiv;
			} 
			Grille_attente_touche (); 
			Grille_redessine_Grille();

			printf ("%d: %d\n", cpt, taille_zsg); 
	}while (taille_zsg != NBcase); 
	return cpt; 
}
