/*
CT0442 Progetto virtual machine 2018-2019
Membri gruppo: Leonardo Mazzon 868445, Giulio Nicola 875297
*/

/* Compilazione: gcc -g3 -fsanitize=address -fsanitize=undefined -std=gnu89 -pedantic-errors -Wall -Wextra -o vm es_vm.c main_vm.c */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "es_vm.h"

int main(){

	const char *nome_file = "assembly.cvm";
	int *stack; /* Vettore 64 KB */
		
	return creazione_stack(nome_file, stack);
}
