/*
CT0442 Progetto virtual machine 2018-2019
Membri gruppo: Leonardo Mazzon 868445, Giulio Nicola 875297
*/

/* Compilazione: gcc -g3 -fsanitize=address -fsanitize=undefined -std=gnu89 -pedantic-errors -Wall -Wextra -o vm_exe fun_esegui_vm.c fun_stampa_vm.c main_vm.c */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fun_stampa_vm.h"

/* La funzione visualizzera' a schermo il file sorgente cvm interpretato.
Se non corrisponde a quello desiderato controllare che le istruzioni e i parametri siano corretti. */
int stampa(int *vet_istruzioni, int dim_vet){
	int i = 0;
	printf("\n");
	while(i < dim_vet){
		switch(vet_istruzioni[i]){
			case 0:
			
				printf("[ %d] HALT\n", i);
				i++;
				break;
				
			case 1:
			
				if(i+1 < dim_vet){
					printf("[ %d] DISPLAY R%d\n", i, vet_istruzioni[i+1]);
					i+=2;
					break;
				}else{
					printf("Errore: parametri insufficienti in posizione %d.\n", i);
					return 1;
				}
				
			case 2:
			
				if(i+1 < dim_vet){
					printf("[ %d] PRINT_STACK %d\n", i, vet_istruzioni[i+1]);
					i+=2;
					break;
				}else{
					printf("Errore: parametri insufficienti in posizione %d.\n", i);
					return 1;
				}
				
			case 10:
			
				if(i+1 < dim_vet){
					printf("[ %d] PUSH R%d\n", i, vet_istruzioni[i+1]);
					i+=2;
					break;
				}else{
					printf("Errore: parametri insufficienti in posizione %d.\n", i);
					return 1;
				}
				
			case 11:
			
				if(i+1 < dim_vet){
					printf("[ %d] POP R%d\n", i, vet_istruzioni[i+1]);
					i+=2;
					break;
				}else{
					printf("Errore: parametri insufficienti in posizione %d.\n", i);
					return 1;
				}
				
			case 12:
			
				if(i+1 < dim_vet && i+2 < dim_vet){
					printf("[ %d] MOV R%d %d\n", i, vet_istruzioni[i+1], vet_istruzioni[i+2]);
					i+=3;
					break;
				}else{
					printf("Errore: parametri insufficienti in posizione %d.\n", i);
					return 1;
				}
				
			case 20:
			
				if(i+1 < dim_vet){
					printf("[ %d] CALL %d\n", i, vet_istruzioni[i+1]);
					i+=2;
					break;
				}else{
					printf("Errore: parametri insufficienti in posizione %d.\n", i);
					return 1;
				}
				
			case 21:
				
				printf("[ %d] RET\n", i);
				i++;
				break;
				
			case 22:
			
				if(i+1 < dim_vet){
					printf("[ %d] JMP %d\n", i, vet_istruzioni[i+1]);
					i+=2;
					break;
				}else{
					printf("Errore: parametri insufficienti in posizione %d.\n", i);
					return 1;
				}
				
			case 23:
			
				if(i+1 < dim_vet){
					printf("[ %d] JZ %d\n", i, vet_istruzioni[i+1]);
					i+=2;
					break;
				}else{
					printf("Errore: parametri insufficienti in posizione %d.\n", i);
					return 1;
				}
				
			case 24:
			
				if(i+1 < dim_vet){
					printf("[ %d] JPOS %d\n", i, vet_istruzioni[i+1]);
					i+=2;
					break;
				}else{
					printf("Errore: parametri insufficienti in posizione %d.\n", i);
					return 1;
				}
				
			case 25:
			
				if(i+1 < dim_vet){
					printf("[ %d] JNEG %d\n", i, vet_istruzioni[i+1]);
					i+=2;
					break;
				}else{
					printf("Errore: parametri insufficienti in posizione %d.\n", i);
					return 1;
				}
				
			case 30:
				
				if(i+1 < dim_vet && i+2 < dim_vet){
					printf("[ %d] ADD R%d R%d\n", i, vet_istruzioni[i+1], vet_istruzioni[i+2]);
					i+=3;
					break;
				}else{
					printf("Errore: parametri insufficienti in posizione %d.\n", i);
					return 1;
				}
				
			case 31:
			
				if(i+1 < dim_vet && i+2 < dim_vet){
					printf("[ %d] SUB R%d R%d\n", i, vet_istruzioni[i+1], vet_istruzioni[i+2]);
					i+=3;
					break;
				}else{
					printf("Errore: parametri insufficienti in posizione %d.\n", i);
					return 1;
				}
				
			case 32:
			
				if(i+1 < dim_vet && i+2 < dim_vet){
					printf("[ %d] MUL R%d R%d\n", i, vet_istruzioni[i+1], vet_istruzioni[i+2]);
					i+=3;
					break;
				}else{
					printf("Errore: parametri insufficienti in posizione %d.\n", i);
					return 1;
				}
				
			case 33:
			
				if(i+1 < dim_vet && i+2 < dim_vet){
					printf("[ %d] DIV R%d R%d\n", i, vet_istruzioni[i+1], vet_istruzioni[i+2]);
					i+=3;
					break;
				}else{
					printf("Errore: parametri insufficienti in posizione %d.\n", i);
					return 1;
				}
				
			default:
				printf("Istruzione in posizione %d non trovata.\n", i);
				return 1;
		}
	}
	printf("\n");
	return 0;
}
