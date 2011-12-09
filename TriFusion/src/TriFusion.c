/*
 ============================================================================
 Nom         : TriFusion.c
 Auteur      : B3302, Robin Gicquel et Arnaud Mery de Montigny
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "TriFusion.h"

long nbComparaisons;
long nbPermutations;

liste * initialiser ( double r, liste *l )
{
	// A quoi sert r ???

	l = NULL;

	return l;
}

void supprimer_liste ( liste *l )
{
	liste * pList = l;
	liste * pSuivant;

	while (pList != NULL)
	{
		pSuivant = pList->suivant;
		free ( pList );
		pList = pSuivant;
	}
}

liste * separation ( liste * list )
{
	if ( list == NULL || list->suivant == NULL)
	{
		return NULL;
	}
	else
	{
		liste * list2 = list->suivant;
		list->suivant = list2->suivant;
		list2->suivant = separation ( list2->suivant );
		return list2;
	}
}

liste * fusion ( liste * list1, liste * list2 )
{
	if ( list1 == NULL)
	{
		return list2;
	}
	else if ( list2 == NULL)
	{
		return list1;
	}
	else if ( nbComparaisons++, list1->valeur <= list2->valeur )
	{
		list1->suivant = fusion ( list1->suivant, list2 );
		return list1;
	}
	else
	{
		list2->suivant = fusion ( list1, list2->suivant );
		nbPermutations++;
		return list2;
	}
}

liste * fusion_inverse ( liste * list1, liste * list2 )
{
	if ( list1 == NULL)
	{
		return list2;
	}
	else if ( list2 == NULL)
	{
		return list1;
	}
	else if ( list1->valeur >= list2->valeur )
	{
		list1->suivant = fusion_inverse ( list1->suivant, list2 );
		return list1;
	}
	else
	{
		list2->suivant = fusion_inverse ( list1, list2->suivant );
		return list2;
	}
}

liste * tri_fusion ( liste * list )
{
	if ( list != NULL && list->suivant != NULL)
	{
		liste * list2 = separation ( list );
		list = tri_fusion ( list );
		list2 = tri_fusion ( list2 );

		return fusion ( list, list2 );
	}
	return list;
}

liste * tri_fusion_inverse ( liste * list )
{
	if ( list != NULL && list->suivant != NULL)
	{
		liste * list2 = separation ( list );
		list = tri_fusion_inverse ( list );
		list2 = tri_fusion_inverse ( list2 );

		return fusion_inverse ( list, list2 );
	}
	return list;
}

void afficher ( liste * list )
{
	liste * pList = list;
	while (pList != NULL)
	{
		printf ( "%i ; ", pList->valeur );
		pList = pList->suivant;
	}
	putchar ( '\n' );
}

liste * generer_liste ( int * tab, int nbElem )
{
	liste * list = NULL;
	list = initialiser ( .0, list );

	if ( nbElem > 0 )
	{
		list = (liste *) (malloc ( sizeof(liste) ));
		list->valeur = tab[0];
		list->suivant = NULL;

		liste * pList = list;

		int i;
		for ( i = 1; i < nbElem; i++ )
		{
			pList->suivant = (liste *) (malloc ( sizeof(liste) ));
			pList = pList->suivant;
			pList->valeur = tab[i];
			pList->suivant = NULL;
		}
	}

	return list;
}

liste * generer_liste_aleatoire ( long nbElem, int min, int max )
{
	liste * list = NULL;
	list = initialiser ( .0, list );

	if ( nbElem > 0 )
	{
		list = (liste *) (malloc ( sizeof(liste) ));
		srand ( time ( NULL ) );
		list->valeur = rand ( ) % (max - min + 1) + min;
		list->suivant = NULL;

		liste * pList = list;

		long i;
		for ( i = 1; i < nbElem; i++ )
		{
			pList->suivant = (liste *) (malloc ( sizeof(liste) ));
			pList = pList->suivant;
			pList->valeur = rand ( ) % (max - min + 1) + min;
			pList->suivant = NULL;
		}
	}

	return list;
}

int egalite_liste ( liste * list1, liste * list2 )
{
	if ( list1 == NULL && list2 == NULL)
	{
		return 1;
	}

	while (list1 != NULL && list2 != NULL)
	{
		if ( list1->valeur != list2->valeur )
		{
			return 0;
		}
		list1 = list1->suivant;
		list2 = list2->suivant;
	}

	if ( list1 != NULL || list2 != NULL)
	{
		return 0;
	}

	return 1;
}

int main ( int argc, char *argv[] )
{
	if ( argc == 2 )
	{
		if ( strcmp ( argv[1], "1" ) == 0 )
		{
			//Test 1 vérifie la méthode separation
			{
				int tab[] = {
				        18, 8, 5, 11, 9, 7, 6, 15, 16 };
				liste * list = generer_liste ( tab, 9 );
				liste * list2 = separation ( list );
				int tabVerif[] = {
				        18, 5, 9, 6, 16 };
				int tabVerif2[] = {
				        8, 11, 7, 15 };
				liste * listVerif = generer_liste ( tabVerif, 5 );
				liste * listVerif2 = generer_liste ( tabVerif2, 4 );

				if ( egalite_liste ( list, listVerif ) != 0 )
				{
					if ( egalite_liste ( list2, listVerif2 ) != 0 )
					{
						puts ( "Test 1 validé (separation)" );
					}
					else
					{
						puts ( "Test 1 faux (separation)" );
					}
				}
				else
				{
					puts ( "Test 1 faux (separation)" );
				}

				supprimer_liste ( list );
				supprimer_liste ( list2 );
				supprimer_liste ( listVerif );
				supprimer_liste ( listVerif2 );
			}

			//Test 2 vérifie la méthode fusion
			{
				int tab1[] = {
				        5, 7, 9, 11, 20 };
				int tab2[] = {
				        4, 6, 10, 21 };
				int tabVerif[] = {
				        4, 5, 6, 7, 9, 10, 11, 20, 21 };
				liste * list1 = generer_liste ( tab1, 5 );
				liste * list2 = generer_liste ( tab2, 4 );
				liste * listVerif = generer_liste ( tabVerif, 9 );
				liste * listFusion = fusion ( list1, list2 );

				if ( egalite_liste ( listFusion, listVerif ) != 0 )
				{
					puts ( "Test 2 validé (fusion)" );
				}
				else
				{
					puts ( "Test 2 faux (fusion)" );
				}
			}

			//Test 3 vérifie la méthode tri_fusion
			{
				int tab[] = {
				        18, 8, 5, 11, 9, 7, 6, 15, 16 };
				liste * list = generer_liste ( tab, 9 );
				int tabVerif[] = {
				        5, 6, 7, 8, 9, 11, 15, 16, 18 };
				liste * listVerif = generer_liste ( tabVerif, 9 );

				nbComparaisons = 0;
				nbPermutations = 0;

				list = tri_fusion ( list );

				if ( egalite_liste ( list, listVerif ) != 0 )
				{
					puts ( "Test 3 validé (tri_fusion)" );
				}
				else
				{
					puts ( "Test 3 faux (tri_fusion)" );
				}
			}

			//Test 4 vérifie la méthode tri_fusion_inverse
			{
				int tab[] = {
				        18, 8, 5, 11, 9, 7, 6, 15, 16 };
				liste * list = generer_liste ( tab, 9 );
				int tabVerif[] = {
				        18, 16, 15, 11, 9, 8, 7, 6, 5 };
				liste * listVerif = generer_liste ( tabVerif, 9 );
				list = tri_fusion_inverse ( list );

				if ( egalite_liste ( list, listVerif ) != 0 )
				{
					puts ( "Test 4 validé (tri_fusion_inverse)" );
				}
				else
				{
					puts ( "Test 4 faux (tri_fusion_inverse)" );
				}
			}

			return 0;
		}
		else if ( strcmp ( argv[1], "2" ) == 0 )
		{
			srand ( time ( NULL ) );

			long clk_tck = CLOCKS_PER_SEC;
			clock_t t1, t2;

			liste * list;

			long i;

			FILE *f = fopen ( "valeurs.csv", "wb" );
			double temps;

			fprintf ( f, "NbElem;NbComp;NbPerm;TpsExec\n" );

			for ( i = 1; i <= 10000000; i += 1000 )
			{

				list = generer_liste_aleatoire ( i, -100000, 100000 );

				t1 = clock ( );
				nbComparaisons = 0;
				nbPermutations = 0;

				tri_fusion ( list );

				supprimer_liste ( list );

				t2 = clock ( );

				temps = (double) (t2 - t1) / (double) clk_tck;

				fprintf ( f, "%ld;%ld;%ld;%f\n", i, nbComparaisons,
				        nbPermutations, temps );
			}
			fclose ( f );

			return 0;
		}
		else if ( strcmp ( argv[1], "3" ) == 0 )
		{
			srand ( time ( NULL ) );

			long clk_tck = CLOCKS_PER_SEC;
			clock_t t1, t2;
			double temps;

			int nbListes = 1000;
			int nbElem = 20000;

			liste * tabListe[nbListes];

			int i;
			for ( i = 0; i < nbListes; i++ )
			{
				tabListe[i] = generer_liste_aleatoire ( nbElem, -100000,
				        100000 );
			}

			t1 = clock ( );

			for ( i = 0; i < nbListes; i++ )
			{
				tri_fusion ( tabListe[i] );
			}

			t2 = clock ( );

			temps = (double) (t2 - t1) / (double) clk_tck;

			printf (
			        "Temps d'exécution pour %d tris de listes aléatoires de %d éléments : %f secs\n",
			        nbListes, nbElem, temps );

			t1 = clock ( );

			for ( i = 0; i < nbListes; i++ )
			{
				tri_fusion ( tabListe[i] );
			}

			t2 = clock ( );

			temps = (double) (t2 - t1) / (double) clk_tck;

			printf (
			        "Temps d'exécution pour %d tris de listes déjà triées de %d éléments : %f secs\n",
			        nbListes, nbElem, temps );

			for ( i = 0; i < nbListes; i++ )
			{
				tabListe[i] = tri_fusion_inverse ( tabListe[i] );
			}

			t1 = clock ( );

			for ( i = 0; i < nbListes; i++ )
			{
				tri_fusion ( tabListe[i] );
			}

			t2 = clock ( );

			temps = (double) (t2 - t1) / (double) clk_tck;

			printf (
			        "Temps d'exécution pour %d tris de listes triées en sens inverse de %d éléments : %f secs\n",
			        nbListes, nbElem, temps );

			return 0;
		}
	}

	printf("Veuillez fournir un argument pour lancer les différents tests.\n\n");
	printf("Les arguments possibles sont :\n");
	printf("\t1 : Tests fonctionnels\n");
	printf("\t2 : Tests de performances avec un nombre d'éléments croissant, écriture des résultats dans le fichier valeurs.csv\n");
	printf("\t3 : Tests de performances sur des listes aléatoires, triées et triées en sens inverse\n");

	return 0;
}
