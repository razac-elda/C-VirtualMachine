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

void shift(char *s){
	if(s[0] != '\0'){
		s[0] = s[1];
		shift(s+1);
	}
}

void elimina_spazi(char *s){
	if(s[0] != '\0'){
		if(s[0] == ' ')
			shift(s);
		else s++;
		elimina_spazi(s);
	}
}

int creazione_vettore(const char *file, int **vet_istruzioni, int *num_istruzioni){

	FILE *input;
	char *riga;
	size_t buffer_size = 0;
	int id_istruzione;
	int ip = -1;
	int *vet_temp;
	/* Apertura del file, ritorna 0 in caso di errore. */
	input = fopen(file, "r");
	if(input){
	
		/* Lettura righe del file, se il primo carattere e' un numero abbiamo trovato
			un istruzione/valore e andiamo a convertirla per intero.
			Controlliamo anche di non sforare con le righe segnalate nel sorgente. */
		while((getline(&riga, &buffer_size, input)) != -1 && ip < *num_istruzioni){
			elimina_spazi(riga);
			if((riga[0] >= '0' && riga[0] <= '9') || (riga[0] == '-' && riga[1] >= '0' && riga[1] <= '9')){
				id_istruzione = atoi(strtok(riga, ";"));
				/* Prima riga è la dimensione del vettore temp, indice a -1 per partire dalla
				prima posizione al ciclo successivo alla creazione. */	
				if(ip == -1){ 
					vet_temp = (int*)malloc(sizeof(int) * id_istruzione);
					if(!vet_temp){
						free(riga);
						fclose(input);
						return -1;
					}
					*num_istruzioni = id_istruzione;
					ip++;
				}else{
					/* Inserimento delle istruzioni/valore nel vettore temp. */
					vet_temp[ip] = id_istruzione;
					ip++;
				}
				
			}
			free(riga);
			riga = NULL;
		}
		/* Associamo il vettore del main a quello temp. */
		*vet_istruzioni = vet_temp;
		free(riga);
		fclose(input);
		return 1;
		
	}else{
		return 0;
	}	
}

int main(int argc, char *argv[]){
	if(argc == 3){
		/* Parametri riga di comando. */
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
			/* Controlliamo quale comando e' stato scelto. */
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
