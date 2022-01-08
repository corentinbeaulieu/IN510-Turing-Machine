
#ifndef PARTIE1_H_INCLUDED
#define PARTIE1_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

enum ERREUR {
	ERR_USAGE=1,
	ERR_OUV_FICHIER,
	ERR_ALLOC,
	ERR_TRANS_IMP,
	ERR_HORS_BANDE
};


typedef struct Bande {
	char contenu;
	struct Bande *prec;
	struct Bande *suiv;
} bande;

typedef struct Delta {
	char etatDepart[8];
	char lettreLue;
	char etatArrivee[8];
	char lettreEc;
	enum Deplacement {
		droite,
		gauche,
		place
	} dep;
} delta;

typedef struct MachineTuring {
	char etatCourant[8];
	bande* tete;
	uint16_t nbDeltas;
	delta *transitions;
	char etatFinal[8];
} MT;


MT Init_MT (const char *,const char *);

void Exec_Total(MT *, bool);

void Affiche_Bande (bande *);

void Ecriture_MT(MT *, const char *);

void Desalloc_MT(MT *);

#endif
