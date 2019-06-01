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

void halt(){

	return;
}

void display(){

	return;
}

void print_stack(){
	
	return;
}

void push(){
	
	return;
}

void pop(){
	
	return;
}

void mov(){
	
	return;
}

void call(){
	
	return;
}

void ret(){
	
	return;
}

void jmp(){
	
	return;
}

void jz(){
	
	return;
}

void jpos(){
	
	return;
}

void jneg(){
	
	return;
}

void add(){
	
	return;
}

void sub(){
	
	return;
}

void mul(){
	
	return;
}

void div_reg(){
	
	return;
}

void interprete(int *vet_istruzioni, int dim_vet, s_stack stack){
	int indice_istruzione = 0;
	while(indice_istruzione < dim_vet){
		switch (vet_istruzioni[indice_istruzione]){
			case 0: halt();
					break;
			case 1: display();
					break;
			case 2: print_stack();
					break;
			case 10: push();
					break;
			case 11: pop();
					break;
			case 12: mov();
					break;
			case 20: call();
					break;
			case 21: ret();
					break;
			case 22: jmp();
					break;
			case 23: jz();
					break;
			case 24: jpos();
					break;
			case 25: jpos();
					break;
			case 30: add();
					break;
			case 31: sub();
					break;
			case 32: mul();
					break;
			case 33: div_reg();
					break;
			default: printf("Istruzione non trovata\n");
		}
		indice_istruzione++;
	}
	return;
}

int creazione_vettore(const char *file, int *vet_istruzioni, int *dim_vet){

	FILE *input;
	char *riga;
	size_t buffer_size = 0;
	int id_istruzione;
	int indice_istruzione= -1;
	
	/* Apertura del file, ritorna 0 in caso di errore. */
	input = fopen(file, "r");
	if(input){
	
		/* Lettura righe del file, se il primo carattere è un numero abbiamo trovato
			un istruzione/valore e andiamo a convertirla per intero. */
		while((getline(&riga, &buffer_size, input)) != -1){
			if(riga[0] >= '0' && riga[0] <= '9'){
				id_istruzione = atoi(strtok(riga,";"));
				
				/* Prima riga è la dimensione del vettore, indice a -1 per partire dalla
					prima posizione al ciclo successivo alla creazione. */	
				if(indice_istruzione == -1){
					vet_istruzioni = (int*)malloc(sizeof(int) * id_istruzione);
					/* Usiamo assert() per controllare le allocazioni in memoria */
					assert(vet_istruzioni);
					*dim_vet = id_istruzione;
					indice_istruzione++;
				}else{
					/* Inserimento delle istruzioni/valore nel vettore. */
					vet_istruzioni[indice_istruzione] = id_istruzione;
					indice_istruzione++;
				}
				
			}
			free(riga);
			riga = NULL;
		}
		
		free(riga);
		fclose(input);
		return 1;
		
	}else{
		return 0;
	}	
}
