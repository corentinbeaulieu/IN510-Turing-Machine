
#include "partie3.h"

int main (int argc, const char *argv[]) {
	if(argc != 3) {
		printf("[USAGE] : %s fichier_contenant_le_code_de_la_machine mot-entrée\n", argv[0]);
		return 1;
	}

	MT mt;
	mt = Init_MT(argv[1], argv[2]);
	Affiche_Bande(mt.tete);
//	Exec_Total(&mt);

	Desalloc_MT(&mt);

	return 0;

}
