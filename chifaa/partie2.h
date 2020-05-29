#include "Liste_case.h"
#include "Entete_Fonctions.h"
#include "API_Grille_txt.h"
#include "API_Gene_instance.h"

typedef struct sommet Sommet;

typedef struct cellule_som{
    Sommet * sommet;
    struct cellule_som * suiv; 

    struct cellule_som * prec; /* sert uniquement dans l'exo 5 : pour l'implementation d'une file (parcours en largeur) */

} Cellule_som;

struct sommet {
   int num;                    /* Num de chaque sommet */
   int cl;                     /* Sa couleur d'origine */ 
   ListeCase cases;            /* Liste des cases du sommet*/
   int nbcase_som;             /* Nombre de cases de la liste cases */
   Cellule_som * sommet_adj;   /* Ensemble des aretes et pointeurs sur les sommets adjacents */


   int distance;                /* distance au noeud racine : sert uniquement dans l'exo 5 */
   Sommet * pere;               /* Pere du sommet dans l'arborescence du parcours en largeur : exo5 uniquement */
};


typedef struct graphe_zone {
    int dim;           /* Dimension de la matrice de couleurs */
    int nbsom;         /* Nombre de sommets dans le graphe */
    int nbcl;          /* nombre de couleurs */
    int *marque;        /* Tableau de marquage des sommets-zones : 0(Lzsg), 1(Bordure) ou 2(non-visite) */

    Cellule_som * Lzsg; /* Liste des sommets-zones appartenant a la zone superieure gauche*/
    int nb_som_zsg;     /* Nombre sommets-zones dans la Zsg : a mettre a jour*/

    Cellule_som ** B;  /* Tableau de listes de sommets-zones composant la bordure de la Zonz superieure gauche indicé sur les couleurs*/
    int *tailleB;      /* Taille de chacune des listes des sommets-zones composant la bordure : a maintenir a jour */

    Cellule_som * som;  /* Liste chainee des sommets-zones du graphe */

    Sommet *** mat;    /* Matrice de pointeurs sur les sommets indiquant a quel sommet appartient ue case (i, j) de la grille */
}Graphe_zone;
