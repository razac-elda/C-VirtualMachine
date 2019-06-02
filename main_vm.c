/*
CT0442 Progetto virtual machine 2018-2019
Membri gruppo: Leonardo Mazzon 868445, Giulio Nicola 875297
*/

/* Compilazione: gcc -g3 -fsanitize=address -fsanitize=undefined -std=gnu89 -pedantic-errors -Wall -Wextra -o vm_exe fun_vm.c main_vm.c */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "fun_vm.h"

int main(){

	const char *nome_file = "assembly.cvm";
	/* Struct con vettore 64 KB e stack pointer. */
	s_stack stack; 
	/* Vettore contenente le istruzioni e valori. */
	int *vet_istruzioni = NULL; 
	int num_istruzioni;
	int successo;
	
	/* Implementare un menu? */
	/* Errori aritmetici, allocazione o overflow/underflow terminano il programma. */
	successo = creazione_vettore(nome_file, &vet_istruzioni, &num_istruzioni);
	if(successo){
		stack = getempty();
		interprete(vet_istruzioni, num_istruzioni, &stack);
	}else{
		printf("Errore nell'apertura del file, controllare di aver inserito il nome corretto.\n");
	}
	free(vet_istruzioni);
	free(stack.vet);
	return 0;
}
