/*
 ============================================================================
 Nom         : TriFusion.c
 Auteur      : B3302, Robin Gicquel et Arnaud Mery de Montigny
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "TriFusion.h"

liste * Separation ( liste * list )
{
	if ( list == NULL || list->suivant == NULL)
	{
		return NULL;
	}
	else
	{
		liste * list2 = list->suivant;
		list->suivant = list2->suivant;
		list2->suivant = Separation ( list2->suivant );
		return list2;
	}
}

liste * Fusion ( liste * list1, liste * list2 )
{
	if ( list1 == NULL)
	{
		return list2;
	}
	else if ( list2 == NULL)
	{
		return list1;
	}
	else if ( list1->valeur <= list2->valeur )
	{
		list1->suivant = Fusion ( list1->suivant, list2 );
		return list1;
	}
	else
	{
		list2->suivant = Fusion ( list1, list2->suivant );
		return list2;
	}
}

liste * TriFusion ( liste * list )
{
	if (list != NULL && list->suivant != NULL) {
		liste * list2 = Separation(list);
		list = TriFusion(list);
		list2 = TriFusion(list2);
		return Fusion(list, list2);
	}
	return list;
}

void AfficherListe (liste * list) {
	liste * pList = list;
	while (pList != NULL) {
		printf("%i ; ", pList->valeur);
		pList = pList->suivant;
	}
	putchar('\n');
}

liste * genererListe(int * tab, int nbElem) {
	liste * list = NULL;

	if (nbElem > 0) {
		list = (liste *)(malloc(sizeof(liste)));
		list->valeur = tab[0];
		list->suivant = NULL;

		liste * pList = list;

		int i;
		for (i = 1; i < nbElem; i++) {
			pList->suivant = (liste *)(malloc(sizeof(liste)));
			pList = pList->suivant;
			pList->valeur = tab[i];
			pList->suivant = NULL;
		}
	}

	return list;
}

liste * genererListeAleatoire(int nbElem, int min, int max) {
	liste * list = NULL;

	if (nbElem > 0) {
		list = (liste *)(malloc(sizeof(liste)));
		srand(time(NULL));
		list->valeur = rand()%(max-min+1)+min;
		list->suivant = NULL;

		liste * pList = list;

		int i;
		for (i = 1; i < nbElem; i++) {
			pList->suivant = (liste *)(malloc(sizeof(liste)));
			pList = pList->suivant;
			pList->valeur = rand()%(max-min+1)+min;
			pList->suivant = NULL;
		}
	}

	return list;
}

int main ( void )
{
//	int tab[] = {18, 8, 5, 11, 9, 7, 6, 15, 16};
//
//	liste * list = genererListe(tab, 9);

	liste * list = genererListeAleatoire(10000, -RAND_MAX/2, RAND_MAX/2);

	AfficherListe(list);

	time_t debut = clock();

	list = TriFusion(list);

	time_t fin = clock();

	AfficherListe(list);

	printf("Teamps d'exécution : %i\n", (int)difftime(fin, debut));

	return 0;
}
