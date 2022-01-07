
#ifndef PARTIE1_H_INCLUDED
#define PARTIE1_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef struct Bande {
	char contenu;
	struct Bande *prec;
	struct Bande *suiv;
} bande;

enum Deplacement {
	droite,
	gauche,
	place
};

//structure des deltas fonctions qui contiendront l'enum déplacement

typedef struct MachineTuring {
	char etatCourant;
	bande* tete;
	//Delta fonctions
} MT;


MT Init_MT (char *, char *);

void Exec_Pas (MT *);

void Exec_Total(MT *);

void Affiche_Bande (bande *);

void Ecriture_MT(MT *, char *);

void Desalloc_MT(MT *);

#endif
