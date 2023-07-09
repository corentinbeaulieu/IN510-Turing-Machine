/* Copyright (c) 2022 Corentin Beaulieu, Victor Schweisthal 

 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), to deal 
 * in the Software without restriction, including without limitation the rights 
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
 * copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions: 

 * The above copyright notice and this permission notice shall be included in all 
 * copies or substantial portions of the Software. 

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
 * SOFTWARE. */


#include "partie1.h"

// Fonction créant un structure bande à partir d'un mot
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
			fprintf(stderr, "ERREUR : Echec d'allocation d'une case de la bande\n");
			exit(ERR_ALLOC);
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

// Fonction parsant un fichier contenant le code d'une machine de Turing pour en extraire les informations dans les différentes structures
/* Les restrictions du langage :
 *	- Le premier caractère est un majuscule qui représente l'état final
 *  - Les deltas transitions sont écrites sur une unique ligne avec des virgules comme séparateur
 *  - Les retours à la ligne servent à séparer deux deltas transitions
 *  - La moindre faute dans le fichier par rapport à cela produit une erreur
 */
delta *Init_Delta(const char *fichier, uint16_t *nbDeltas, char etatFinal[8]) {
	FILE *file;
	file = fopen (fichier, "r");

	if (!file) {
		fprintf(stderr, "\nErreur : le fichier %s n'a pas pu être ouvert.\n\n", fichier);
		exit(ERR_OUV_FICHIER);
	}

	char buff[255];
	char delim[2] = ",";

	//On calcule le nombre de transitions (nombre de lignes - la ligne d'état final)
	*nbDeltas = -1;

	while (fgets(buff, 255, file)) (*nbDeltas)++;
	rewind(file);

	delta *transitions = malloc(sizeof(delta) * (*nbDeltas));

	//On récupère l'état final (première ligne)
	fgets(buff, 255, file);
	strncpy(etatFinal, buff, 7);
	etatFinal[7] ='\0';
	int j;
	for(j = 0; j < 8; j++) {
		if(etatFinal[j] == '\n') {
			etatFinal[j] = '\0';
			break;
		}
		else if(etatFinal[j] == '\0') break;
	}


	//Puis les transitions
	int i = 0;
	while (fgets(buff, 255, file)) {
		char *token = strtok(buff, delim);
		strcpy(transitions[i].etatDepart, token);

		token = strtok(NULL, delim);
		transitions[i].lettreLue = token[0];

		token = strtok(NULL, delim);
		strcpy(transitions[i].etatArrivee, token);

		token = strtok(NULL, delim);
		transitions[i].lettreEc = token[0];


		token = strtok(NULL, delim);
		switch(token[0]) {
			case '<':
				transitions[i].dep = gauche;
				break;

			case '>':
				transitions[i].dep = droite;
				break;

			case '-':
				transitions[i].dep = place;
				break;

			default:
				fprintf(stderr, "ERREUR: %c n'est pas un déplacment valide", token[0]);
				free(transitions);
				exit(ERR_USAGE);
				break;
		}
		i++;
	}

	fclose(file);

	return transitions;
}

// Fonction renvoyant une structure de machine à partir d'un fichier contenant son code et un mot d'entrée
MT Init_MT(const char *fichier, const char *mot) {
	MT mt;
	strcpy(mt.etatCourant, "A");
	mt.tete = Init_Bande(mot);
	mt.transitions = Init_Delta(fichier, &(mt.nbDeltas), mt.etatFinal);

	return mt;
}

// Fonction ajoutant une case vide à la fin d'une' bande
void Ajout_Case_Suiv(bande *b) {
	b->suiv = malloc(sizeof(bande));
	if(b->suiv == NULL) {
		fprintf(stderr, "ERREUR : Echec d'allocation d'une case de la bande\n");
		exit(ERR_ALLOC);
	}

	b->suiv->contenu = '_';
	b->suiv->suiv = NULL;
	b->suiv->prec = b;
}

// Fonction ajoutant une case vide au début d'une bande
void Ajout_Case_Prec(bande *b) {
	b->prec = malloc(sizeof(bande));
	if(b->prec == NULL) {
		fprintf(stderr, "ERREUR : Echec d'allocation d'une case de la bande\n");
		exit(ERR_ALLOC);
	}

	b->prec->contenu = '_';
	b->prec->suiv = b;
	b->prec->prec = NULL;
}

// Fonction supprimant une case vide à la fin d'une bande
void Suppr_Case_Suiv(bande *b) {
	if(b->suiv->contenu == '_' && b->suiv->suiv == NULL) {
		free(b->suiv);
		b->suiv = NULL;
	}
}

// Fonction supprimant une case vide au début de la bande
void Suppr_Case_Prec(bande *b) {
	if(b->prec->contenu == '_' && b->prec->prec == NULL) {
		free(b->prec);
		b->prec = NULL;
	}
}

// Fonction simulant un pas de calcul d'une machine sur une bande infinié à droite
void Exec_Pas_Semiinfinie (MT *mt) {
	int i;
	delta del;
	for(i = 0; i < mt->nbDeltas; i++) {
		del = mt->transitions[i];
		if(!strcmp(del.etatDepart, mt->etatCourant) && del.lettreLue == mt->tete->contenu) 
			break;
	}

	if(i >= mt->nbDeltas) {
		fprintf(stderr, "ERREUR : Transition impossible\n");
		exit(ERR_TRANS_IMP);
	}

	strcpy(mt->etatCourant, del.etatArrivee);
	mt->tete->contenu = del.lettreEc;

	switch(del.dep) {
		case droite: 
			if(mt->tete->suiv == NULL) {
				Ajout_Case_Suiv(mt->tete);
			}
			mt->tete = mt->tete->suiv;
			break;

		case gauche:
			if(mt->tete->prec == NULL) {
				break;
			}
			mt->tete = mt->tete->prec;
			Suppr_Case_Suiv(mt->tete);
			break;

		case place:
			break;
	}
}

// Fonction simulant un pas de calcul d'une machine sur un bande bi infinie
void Exec_Pas_Biinfinie (MT *mt) {
	int i;
	delta del;
	for(i = 0; i < mt->nbDeltas; i++) {
		del = mt->transitions[i];
		if(!strcmp(del.etatDepart, mt->etatCourant) && del.lettreLue == mt->tete->contenu) 
			break;
	}

	if(i >= mt->nbDeltas) {
		fprintf(stderr, "ERREUR : Transition impossible\n");
		exit(ERR_TRANS_IMP);
	}

	strcpy(mt->etatCourant, del.etatArrivee);
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

// Fonction simulant toute l'exécution d'un machine 
void Exec_Total(MT *mt, bool biinfinie) {
	uint64_t iter;
	iter = 1;
	if(biinfinie) {
		while(strcmp(mt->etatCourant, mt->etatFinal)) {
			printf("Etape %lu :\n", iter);
			printf("Etat courant : %s\n", mt->etatCourant);
			Affiche_Bande(mt->tete);
			Exec_Pas_Biinfinie(mt);
			iter++;
		}
	}

	else {
		while(strcmp(mt->etatCourant, mt->etatFinal)) {
			printf("Etape %lu :\n", iter);
			printf("Etat courant : %s\n", mt->etatCourant);
			Affiche_Bande(mt->tete);
			Exec_Pas_Semiinfinie(mt);
			iter++;
		}
	}

	printf("Fin du calcul en %lu étapes\n", iter);
	printf("Etat courant : %s\n", mt->etatCourant);
	Affiche_Bande(mt->tete);
}

// Fonction affichant l'état courant de la bande
void Affiche_Bande(bande *b) {
	bande *ecr;
	ecr = b;
	while(ecr->prec != NULL) ecr = ecr->prec;

	while(ecr->suiv != NULL) {
		if(ecr == b) printf(" >%c<  ", ecr->contenu);
		else printf("%c ", ecr->contenu);

		ecr = ecr->suiv;
	}
	if(ecr == b) printf(" >%c<\n\n", ecr->contenu);
	else printf("%c\n\n", ecr->contenu);
}

// Fonction qui écrit le code d'une machine dans un fichier
void Ecriture_MT(MT *mt, const char *chemin) {
	FILE *file;
	file = fopen (chemin, "w");

	if (!file) {
		fprintf(stderr, "\nErreur : le fichier %s n'a pas pu être ouvert.\n\n", chemin);
		exit(ERR_OUV_FICHIER);
	}

	fprintf(file, "%s\n", mt->etatFinal);
	uint16_t i;
	for(i=0; i< mt->nbDeltas; i++) {
		fprintf(file, "%s,%c,%s,%c,", mt->transitions[i].etatDepart, mt->transitions[i].lettreLue, mt->transitions[i].etatArrivee, mt->transitions[i].lettreEc);
		switch(mt->transitions[i].dep) {
			case droite:
				fprintf(file, ">\n");
				break;

			case gauche:
				fprintf(file, "<\n");
				break;

			case place:
				fprintf(file, "-\n");
				break;
		}
	}

	fclose(file);
}

// Fonction qui désalloue une structure de bande
void Desalloc_Bande(bande *b) {
	while(b->prec != NULL) b = b->prec;

	bande *suiv;
	while(b->suiv != NULL) {
		suiv = b->suiv;
		free(b);
		b = suiv;
	}
	free(b);
}

// Fonction qui désalloue une structure de machine
void Desalloc_MT(MT *mt) {
	Desalloc_Bande(mt->tete);
	mt->tete = NULL;
	free(mt->transitions);
	mt->transitions = NULL;
}
