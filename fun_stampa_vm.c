/*
CT0442 Progetto virtual machine 2018-2019
Membri gruppo: Leonardo Mazzon 868445, Giulio Nicola 875297
*/

/* Compilazione: gcc -g3 -fsanitize=address -fsanitize=undefined -std=gnu89 -pedantic-errors -Wall -Wextra -o vm_exe fun_esegui_vm.c fun_stampa_vm.c main_vm.c */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fun_stampa_vm.h"

void stampa(int *vet_istruzioni, int dim_vet){
	int i = 0;
	while(i < dim_vet){
		switch(vet_istruzioni[i]){
			case 0:
				printf("[ %d] HALT\n", i);
				i++;
				break;
			case 1:
				printf("[ %d] DISPLAY R%d\n", i, vet_istruzioni[i+1]);
				i+=2;
				break;
			case 2:
				printf("[ %d] PRINT_STACK %d\n", i, vet_istruzioni[i+1]);
				i+=2;
				break;
			case 10:
				printf("[ %d] PUSH R%d\n", i, vet_istruzioni[i+1]);
				i+=2;
				break;
			case 11:
				printf("[ %d] POP R%d\n", i, vet_istruzioni[i+1]);
				i+=2;
				break;
			case 12:
				printf("[ %d] MOV R%d %d\n", i, vet_istruzioni[i+1], vet_istruzioni[i+2]);
				i+=3;
				break;
			case 20:
				printf("[ %d] CALL %d\n", i, vet_istruzioni[i+1]);
				i+=2;
				break;
			case 21:
				printf("[ %d] RET\n", i);
				i++;
				break;
			case 22:
				printf("[ %d] JMP %d\n", i, vet_istruzioni[i+1]);
				i+=2;
				break;
			case 23:
				printf("[ %d] JZ %d\n", i, vet_istruzioni[i+1]);
				i+=2;
				break;
			case 24:
				printf("[ %d] JPOS %d\n", i, vet_istruzioni[i+1]);
				i+=2;
				break;
			case 25:
				printf("[ %d] JNEG %d\n", i, vet_istruzioni[i+1]);
				i+=2;
				break;
			case 30:
				printf("[ %d] ADD R%d R%d\n", i, vet_istruzioni[i+1], vet_istruzioni[i+2]);
				i+=3;
				break;
			case 31:
				printf("[ %d] SUB R%d R%d\n", i, vet_istruzioni[i+1], vet_istruzioni[i+2]);
				i+=3;
				break;
			case 32:
				printf("[ %d] MUL R%d R%d\n", i, vet_istruzioni[i+1], vet_istruzioni[i+2]);
				i+=3;
				break;
			case 33:
				printf("[ %d] DIV R%d R%d\n", i, vet_istruzioni[i+1], vet_istruzioni[i+2]);
				i+=3;
				break;
			default:
				printf("Istruzione in posizione %d non trovata.\n", i);
				i++;
		}
	}
	return;
}
