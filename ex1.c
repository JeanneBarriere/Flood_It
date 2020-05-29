void trouve_zonerec (int **M, int nbcase, int i, int j, int *taille, Liste Case *L ){ 
	int coul=M[i][j];
	M[i][j]=-1; 
	(*taille) ++; 
	ajoute_en_tete (L,i,j);

	if ((i !=nbcase -1) && (M[i+1] [i]==coul)){
		trouve_zone_rec (M, nbcase ,i+1, 3, taille , L);
	}

	if ((i !=0) && (M[i-1] [j] ==coul)){
		trouve_zone_rec (M, nbcase ,i-1, j, taille ,L);
	} 

	if (( j!=0) && (M[i][j-1]==coul)){
		trouve_zone_rec (M, nbcase ,i,j-1, taille ,L); 
	}

	if ((j!=nbcase-1) && (M[i][j+1] == coul)){ 
		trouve_zone_rec (M,nbcase ,i,j+1, taille ,L);
	}
} 


int sequence_aleatoire_rec (int **M, Grille *G, int dim, int nbcl, int aff){ 

	int taille_zsg;
	int i, j, cl;
	int NBcase=dim*dim; 
	int cpt =0;
	ListeCase L; 
	Elnt_liste *cour; 
	init_liste (&L);

	do{

		taille_zsg=0; 
		detruit_liste (&L); 
		trouve_zone_rec (M, dim ,0,0,& taille_zsg , &L);

		if (taille_zsg== NBcase) return cpt; 
		cpt++; 

		do{ 
			cl=rand (%nbcl); 
		} while (cl==M [O] [0]); 
		
		cour=L; 

		while (cour != NULL) { 
			M[cour->i][cour->j]=cl;
			cour= cour ->suiv;
		}
		
		if (aff == 1) { 
			cour=L; 
			while (cour !=NULL){ 
				Grille_attribue_couleur_case (G, cour->i, cour->j,cl); 
				cour= cour->suiv; 
			}
			Grille attente_touche();
			Grille redessine_Grille(); 
		}

		printf ("%d: -%d\n", cpt, taille_zsg); 
	} while (taille_zsg!= NBcase); 
	return cpt;
}