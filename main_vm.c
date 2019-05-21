/*
Progetto virtual machine 2018-2019
Membri gruppo: Leonardo Mazzon 868445, Giulio Nicola 875297
*/
#include "es_vm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){

	FILE *input;
	int lung_riga;
	size_t n = 0;
	char *riga;
	
	/* Lettura test del file assembly.cvm */
	input = fopen("assembly.cvm", "r");	
	if(input){
	
		while((lung_riga = getline(&riga, &n, input)) != -1){
			printf("%s\n", riga);
			free(riga);
			riga = NULL;
		}
		free(riga);
		fclose(input);
		
	}else{
		printf("Errore apertura file\n");
	}
	
	
	return 0;
}


