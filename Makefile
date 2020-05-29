all: Flood-It_Partie1

test: Flood-It_Partie1_test.o Liste_case.o  API_Grille_txt.o API_Gene_instance.o Fonctions_exo1.o Fonctions_exo2.o Version_rapide.o
	gcc -g -o Test Flood-It_Partie1_test.o Liste_case.o API_Grille_txt.o API_Gene_instance.o Fonctions_exo1.o Fonctions_exo2.o Version_rapide.o

API_Gene_instance.o: API_Gene_instance.c API_Gene_instance.h
	gcc -c API_Gene_instance.c

API_Grille_txt.o: API_Grille_txt.c API_Grille_txt.h
	gcc -c API_Grille_txt.c

Liste_case.o: Liste_case.c Liste_case.h
	gcc -c Liste_case.c

Version_rapide.o: Version_rapide.c Version_rapide.h
	gcc -c Version_rapide.c

Fonctions_exo1.o: Fonctions_exo1.c Entete_Fonctions.h Liste_case.h
	gcc -c Fonctions_exo1.c

Fonctions_exo2.o: Fonctions_exo2.c Entete_Fonctions.h Liste_case.h
	gcc -c Fonctions_exo2.c

Flood-It_Partie1.o: Flood-It_Partie1.c
	gcc -c Flood-It_Partie1.c

Flood-It_Partie1: Flood-It_Partie1.o Liste_case.o  API_Grille_txt.o API_Gene_instance.o Fonctions_exo1.o Fonctions_exo2.o Version_rapide.o
	gcc -o Flood-It_Partie1 Flood-It_Partie1.o Liste_case.o API_Grille_txt.o API_Gene_instance.o Fonctions_exo1.o Fonctions_exo2.o Version_rapide.o

clean:
	rm -f *.o Flood-It_Partie1 Test
