
#include "partie1.h"

bande *Init_Bande(const char *mot) {
	bande *b, *prec;
	b = NULL;

	char lu;
	uint16_t i;
	i = 0;
	lu = mot[i];
	while(lu != '\0') {
		prec = b;
		b = malloc(sizeof(bande));
		if(!b) {
			//ERREUR
			exit(1);
		}
		b->contenu = lu;
		b->prec = prec;
		b->suiv = NULL;

		if(prec != NULL) prec->suiv = b;

		i++;
		lu = mot[i];
	}

	while(prec != NULL) {
		b = prec;
		prec = b->prec;
	}

	return b;
}


/* Les restrictions du langage :
 *	- Le premier caractère est un majuscule qui représente l'état final
 *  - Les deltas transitions sont écrites sur une unique ligne avec des virgules comme séparateur
 *  - Les retours à la ligne servent à séparer deux deltas transitions
 *  - La moindre faute dans le fichier par rapport à cela produit une erreur
 */
delta *Init_Delta(const char *fichier, uint16_t *nbDeltas, char *etatFinal) {
	// A Implémenter

	delta *transitions;
	return transitions;
}


MT Init_MT(const char *fichier, const char *mot) {
	MT mt;
	mt.etatCourant = 'A';
	mt.tete = Init_Bande(mot);
	mt.transitions = Init_Delta(fichier, &(mt.nbDeltas), &(mt.etatFinal));

	return mt;
}

void Ajout_Case_Suiv(bande *b) {
	b->suiv = malloc(sizeof(bande));
	if(b->suiv == NULL) {
		// Gestion de l'erreur
		exit(1);
	}

	b->suiv->contenu = '_';
	b->suiv->suiv = NULL;
	b->suiv->prec = b;
}

void Ajout_Case_Prec(bande *b) {
	b->suiv = malloc(sizeof(bande));
	if(b->prec == NULL) {
		// Gestion de l'erreur
		exit(1);
	}

	b->prec->contenu = '_';
	b->prec->suiv = b;
	b->prec->prec = NULL;
}

void Suppr_Case_Suiv(bande *b) {
	if(b->suiv->contenu == '_' && b->suiv->suiv == NULL) {
		free(b->suiv);
		b->suiv = NULL;
	}
}

void Suppr_Case_Prec(bande *b) {
	if(b->prec->contenu == '_' && b->prec->prec == NULL) {
		free(b->prec);
		b->prec = NULL;
	}
}



void Exec_Pas (MT *mt) {
	// Que faire si la MT est non déterministe ?

	int i;
	delta del;
	for(i = 0; i < mt->nbDeltas; i++) {
		del = mt->transitions[i];
		if(del.etatDepart == mt->etatCourant && del.lettreLue == mt->tete->contenu) 
			break;
	}

	if(i >= mt->nbDeltas) {
		//Rejetter
		// Plutôt une erreur car on a que des machines qui calculenT
	}

	mt->etatCourant = del.etatArrivee;
	mt->tete->contenu = del.lettreEc;

	switch(del.dep) {
		case droite: 
			if(mt->tete->suiv == NULL) {
				Ajout_Case_Suiv(mt->tete);
			}
			mt->tete = mt->tete->suiv;
			Suppr_Case_Prec(mt->tete);
			break;

		case gauche:
			if(mt->tete->prec == NULL) {
				Ajout_Case_Prec(mt->tete);
			}
			mt->tete = mt->tete->prec;
			Suppr_Case_Suiv(mt->tete);
			break;

		case place:
			break;
	}
}

void Exec_Total(MT *mt) {
	uint64_t iter;
	iter = 1;
	while(mt->etatCourant != mt->etatFinal) {
		printf("Etape %u :\n", iter);
		Exec_Pas(mt);
		Affiche_Bande(mt->tete);
	}
}



void Affiche_Bande(bande *b) {
	bande *ecr;
	ecr = b;
	while(ecr->prec != NULL) ecr = ecr->prec;

	while(ecr->suiv != NULL) {
		if(ecr == b) printf(">%c< ", ecr->contenu);
		else printf("%c ", ecr->contenu);

		ecr = ecr->suiv;
	}
}



void Desalloc_Bande(bande *b) {
	while(b->prec != NULL) b = b->prec;

	bande *suiv;
	while(b->suiv != NULL) {
		suiv = b->suiv;
		free(b);
		b = suiv;
	}
}


void Desalloc_MT(MT *mt) {
	Desalloc_Bande(mt->tete);
	mt->tete = NULL;
	free(mt->transitions);
	mt->transitions = NULL;
}

