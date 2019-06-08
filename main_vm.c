/*
CT0442 Progetto virtual machine 2018-2019
Membri gruppo P1G129: Leonardo Mazzon 868445, Giulio Nicola 875297
*/

/* Compilazione: gcc -g3 -fsanitize=address -fsanitize=undefined -std=gnu89 -pedantic-errors -Wall -Wextra -o vm_exe fun_esegui_vm.c fun_stampa_vm.c main_vm.c */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fun_esegui_vm.h"
#include "fun_stampa_vm.h"

int main(int argc, char *argv[]){
	if(argc == 3){
		char *comando = argv[1];
		const char *nome_file = argv[2];
		/* Struct con vettore e stack pointer. */
		s_stack stack; 
		/* Vettore contenente le istruzioni e valori. */
		int *vet_istruzioni = NULL; 
		int num_istruzioni = 0;
		int successo_creazione, errore_interprete, errore_stampa;
		/* Errori aritmetici, allocazione o overflow/underflow terminano il programma. */
		successo_creazione = creazione_vettore(nome_file, &vet_istruzioni, &num_istruzioni);
		if(successo_creazione){
			if(strcmp(comando, "esegui") == 0){
				stack = getempty();
				if(stack.vet){
					errore_interprete = interprete(vet_istruzioni, num_istruzioni, &stack);
					if(errore_interprete)
						printf("Correggere il codice della macchina virtuale e riprovare.\n"); 
				}else{
					printf("\nErrore: allocazione stack non riuscita.\n");
				}
				free(stack.vet);
			}else{
				if(strcmp(comando, "stampa") == 0){
					errore_stampa = stampa(vet_istruzioni, num_istruzioni);
					if(errore_stampa)
						printf("Correggere il codice della macchina virtuale e riprovare.\n"); 
				}else{
					printf("\nErrore: comando non trovato.\n");
				}
			}
		}else{
			if(successo_creazione == 0)
				printf("\nErrore nell'apertura del file, controllare di aver inserito il nome corretto.\n");
			else
				printf("\nErrore: allocazione vettore non riuscita.\n");
		}
		free(vet_istruzioni);
	}else{
		printf("\nErrore: specificare il comando \"esegui\" oppure \"stampa\".\n");
	}
	printf("\n");
	return 0;
}
