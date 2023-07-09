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

#include "partie2.h"

int main (int argc, char *const argv[]) {


	// Gestion des options
	bool biinfinie; biinfinie = false;
	bool question6; question6 = false;
	bool question7; question7 = false;;

	char option;

	opterr = 0;
	while((option = getopt(argc, argv, "b67")) != -1) {
		switch(option) {
			case 'b':
				biinfinie = true;
				break;

			case '6':
				question6 = true;
				break;

			case '7':
				question7 = true;
				break;

			case '?':
				fprintf(stderr, "ERREUR: l'option -%c est inconnue\n", optopt);
				return ERR_USAGE;

			default: 
				return ERR_USAGE;
		}
	}

	// Vérification du bon usage
	if(question6 && question7) {
		fprintf(stderr, "ERREUR: l'option -6 est incompatible avec l'option -7\n");
		return ERR_USAGE;
	}

	MT mt;

	if(question6 || question7) {
		if((argc - optind) == 1) {
			if(question6) {
				mt = Question6(argv[optind]);
				Ecriture_MT(&mt, "sortieMT");
			}

			else {
				mt = Question7(argv[optind]);
				Ecriture_MT(&mt, "sortieMT");
			}
		} 

		else if((argc - optind) == 2) {
			if(question6) {
				mt = Question6(argv[optind]);
				Ecriture_MT(&mt, argv[optind+1]);
			}

			else {
				mt = Question7(argv[optind]);
				Ecriture_MT(&mt, argv[optind+1]);
			}
		}

		else {
			fprintf(stderr, "USAGE: %s [option] fichier_entree fichier_sortie", argv[0]);
			return ERR_USAGE;
		}
	}

	else if((argc - optind) != 2) {
		fprintf(stderr, "USAGE: %s [option] fichier mot_entrée\n", argv[0]); 
		return ERR_USAGE;
	}

	else {
		mt = Init_MT(argv[optind], argv[optind+1]);
		Exec_Total(&mt, biinfinie);
	}

	Desalloc_MT(&mt);

	return 0;

}
