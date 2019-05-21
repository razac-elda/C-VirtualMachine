/*
CT0442 Progetto virtual machine 2018-2019
Membri gruppo: Leonardo Mazzon 868445, Giulio Nicola 875297
*/

/* Compilazione: gcc -g3 -fsanitize=address -fsanitize=undefined -std=gnu89 -pedantic-errors -Wall -Wextra -o vm es_vm.c main_vm.c */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "es_vm.h"

/* 1-Successo 0-Errore N-Errore personalizzato*/
int creazione_stack(const char *file, int *stack){
	FILE *input;
	int lung_riga;
	size_t n = 0;
	char *riga;
	
	/* Lettura test del file */
	input = fopen(file, "r");	
	if(input){
		while((lung_riga = getline(&riga, &n, input)) != -1){
			printf("%s\n", riga);
			free(riga);
			riga = NULL;
		}
		free(riga);
		fclose(input);
		return 1;
	}else{
		printf("Errore apertura file\n");
		return 0;
	}
}
