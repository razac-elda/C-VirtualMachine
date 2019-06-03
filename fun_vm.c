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

/* Registri */
int r0=0,r1=0,r2=0,r3=0,r4=0,r5=0,r6=0,r7=0,r8=0,r9=0,r10=0,
	r11=0,r12=0,r13=0,r14=0,r15=0,r16=0,r17=0,r18=0,r19=0,r20=0,
	r21=0,r22=0,r23=0,r24=0,r25=0,r26=0,r27=0,r28=0,r29=0,r30=0,r31=0;

int* indirizzo_registro(int nome_registro){
	switch(nome_registro){
		case 0: return &r0;
		case 1: return &r1;
		case 2: return &r2;
		case 3: return &r3;
		case 4: return &r4;
		case 5: return &r5;
		case 6: return &r6;
		case 7: return &r7;
		case 8: return &r8;
		case 9: return &r9;
		case 10: return &r10;
		case 11: return &r11;
		case 12: return &r12;
		case 13: return &r13;
		case 14: return &r14;
		case 15: return &r15;
		case 16: return &r16;
		case 17: return &r17;
		case 18: return &r18;
		case 19: return &r19;
		case 20: return &r20;
		case 21: return &r21;
		case 22: return &r22;
		case 23: return &r23;
		case 24: return &r24;
		case 25: return &r25;
		case 26: return &r26;
		case 27: return &r27;
		case 28: return &r28;
		case 29: return &r29;
		case 30: return &r30;
		case 31: return &r31;
	}
	return NULL;
}

int creazione_vettore(const char *file, int **vet_istruzioni, int *num_istruzioni){

	FILE *input;
	char *riga;
	size_t buffer_size = 0;
	int id_istruzione;
	int ip= -1;
	int *vet_temp;
	/* Apertura del file, ritorna 0 in caso di errore. */
	input = fopen(file, "r");
	if(input){
	
		/* Lettura righe del file, se il primo carattere è un numero abbiamo trovato
			un istruzione/valore e andiamo a convertirla per intero. */
		while((getline(&riga, &buffer_size, input)) != -1){
			if(riga[0] >= '0' && riga[0] <= '9'){
				id_istruzione = atoi(strtok(riga,";"));
				
				/* Prima riga è la dimensione del vettore temp, indice a -1 per partire dalla
					prima posizione al ciclo successivo alla creazione. */	
				if(ip == -1){
					vet_temp = (int*)malloc(sizeof(int) * id_istruzione);
					/* Usiamo assert() per controllare le allocazioni in memoria. */
					assert(vet_temp && "Errore: allocazione vettore istruzioni non riuscita!");
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

s_stack getempty(){
	s_stack ris;
	/* Allocazione 65536 Bytes(64KB). */
	ris.vet = (int*)malloc(65536);
	assert(ris.vet && "Errore: allocazione stack non riuscita!");
	/* Numero di interi contenibili(dim max) */
	ris.dim = 65536/sizeof(int);
	/* Stack pointer a 0. */
	ris.sp = 0;
	return ris;
}

int isempty(s_stack stack){
	return (stack.sp == 0);
}

void display(int registro, int *valore){
	printf("Registro R%d: %d.\n", registro, *valore);
	return;
}

void print_stack(){
	
	return;
}

int push(s_stack *stack, int registro){
	if(stack->sp < stack->dim){
		(stack->vet)[stack->sp] = registro;
		(stack->sp)++;
		return 1;
	}else{
		return 0;	
	}
}

int pop(s_stack *stack, int *registro){
	if(!isempty(*stack)){
		(stack->sp)--;
		*registro = (stack->vet)[stack->sp];
		return 1;
	}else{
		return 0;
	}
}

void mov(int *registro, int numero){
	*registro = numero;
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

void add(int *registro1, int *registro2, s_stack *stack){
	int ris, of;
	ris = (*registro1) + (*registro2);
	of = push(stack, ris);
	assert(of && "Errore: stackoverflow.com!");
	return;
}

void sub(int *registro1, int *registro2, s_stack *stack){
	int ris, of;
	ris = (*registro1) - (*registro2);
	of = push(stack, ris);
	assert(of && "Errore: stackoverflow.com!");
	return;
}

void mul(int *registro1, int *registro2, s_stack *stack){
	int ris, of;
	ris = (*registro1) * (*registro2);
	of = push(stack, ris);
	assert(of && "Errore: stackoverflow.com!");
	return;
}

void div_reg(int *registro1, int *registro2, s_stack *stack){
	int ris, of;
	ris = (*registro1) / (*registro2);
	of = push(stack, ris);
	assert(of && "Errore: stackoverflow.com!");
	return;
}

void interprete(int *vet_istruzioni, int num_istruzioni, s_stack *stack){
	/* Instruction Pointer */
	int ip = 0;
	/* Parametro 1 e 2 sono i nomi dei registri o il numero. */
	int p1, p2;
	/* Val 1 e 2 conterrano, quando necessario, gli indirizzi dei registri corrispondenti a P1 e P2.
		Dereferenziare per il valore. */
	int *val1, *val2;
	/* Test */
	int registro;
	int i;
	/* Se un istruzione non è corretta esco. */
	while(ip < num_istruzioni){
		switch (vet_istruzioni[ip]){
			case 0:	/* HALT */
				return;
			case 1:	/* DISPLAY */
			
				ip++;
				/* Unico parametro di display. */
				p1 = vet_istruzioni[ip];
				if(p1 >= 0 && p1 <= 31){
					/* Ottengo l'indirizzo del registro. */
					val1 = indirizzo_registro(p1);
					display(p1, val1);
				}else{
					printf("Registro R%d non valido a riga %d.\n", p1, ip-1);
					ip = num_istruzioni;
				}
				break;
				
			case 2:	/* PRINT */
				print_stack();
				break;
			case 10:	/* PUSH */
				i=push(stack, registro);
				break;
			case 11:	/* POP */
				i=pop(stack, &registro);
				break;
			case 12:	/* MOV */
				ip++;
				p1 = vet_istruzioni[ip];
				if(p1 >= 0 && p1 <= 31){
					val1 = indirizzo_registro(p1);
					ip++;
					p2 = vet_istruzioni[ip];
					mov(val1, p2);
				}else{
					printf("Registro R%d non valido a riga %d.\n", p1, ip-2);
					ip = num_istruzioni;
				}
				break;
			case 20:	/* CALL */
				call();
				break;
			case 21:	/* RET */
				ret();
				break;
			case 22:	/* JMP */
				jmp();
				break;
			case 23:	/* JZ */
				jz();
				break;
			case 24:	/* JPOS */
				jpos();
				break;
			case 25:	/* JNEG */
				jneg();
				break;
				
			case 30:	/* ADD */
			
				ip++;
				p1 = vet_istruzioni[ip];
				ip++;
				p2 = vet_istruzioni[ip];
				if((p1 >= 0 && p1 <= 31) && (p2 >= 0 && p2 <= 31)){
					val1 = indirizzo_registro(p1);
					val2 = indirizzo_registro(p2);
					add(val1, val2, stack);
				}else{
					/* Trovo il o i registri errati da segnalare. */
					if(p1 >= 0 && p1 <= 31){
						printf("Registro R%d non valido a riga %d.\n", p2, ip-2);
					}else{
						if(p2 >= 0 && p2 <= 31)
							printf("Registro R%d non valido a riga %d.\n", p1, ip-2);
						else
							printf("Registri R%d e R%d non validi a riga %d.\n", p1, p2, ip-2);
					}
					ip = num_istruzioni;
				}
				break;
				
			case 31:	/* SUB */
			
				ip++;
				p1 = vet_istruzioni[ip];
				ip++;
				p2 = vet_istruzioni[ip];
				if((p1 >= 0 && p1 <= 31) && (p2 >= 0 && p2 <= 31)){
					val1 = indirizzo_registro(p1);
					val2 = indirizzo_registro(p2);
					sub(val1, val2, stack);
				}else{
					/* Trovo il o i registri errati da segnalare. */
					if(p1 >= 0 && p1 <= 31){
						printf("Registro R%d non valido a riga %d.\n", p2, ip-2);
					}else{
						if(p2 >= 0 && p2 <= 31)
							printf("Registro R%d non valido a riga %d.\n", p1, ip-2);
						else
							printf("Registri R%d e R%d non validi a riga %d.\n", p1, p2, ip-2);
					}
					ip = num_istruzioni;
				}
				break;
				
			case 32:	/* MUL */
			
				ip++;
				p1 = vet_istruzioni[ip];
				ip++;
				p2 = vet_istruzioni[ip];
				if((p1 >= 0 && p1 <= 31) && (p2 >= 0 && p2 <= 31)){
					val1 = indirizzo_registro(p1);
					val2 = indirizzo_registro(p2);
					mul(val1, val2, stack);
				}else{
					/* Trovo il o i registri errati da segnalare. */
					if(p1 >= 0 && p1 <= 31){
						printf("Registro R%d non valido a riga %d.\n", p2, ip-2);
					}else{
						if(p2 >= 0 && p2 <= 31)
							printf("Registro R%d non valido a riga %d.\n", p1, ip-2);
						else
							printf("Registri R%d e R%d non validi a riga %d.\n", p1, p2, ip-2);
					}
					ip = num_istruzioni;
				}
				break;
				
			case 33:	/* DIV */
			
				ip++;
				p1 = vet_istruzioni[ip];
				ip++;
				p2 = vet_istruzioni[ip];
				if((p1 >= 0 && p1 <= 31) && (p2 >= 0 && p2 <= 31)){
					val1 = indirizzo_registro(0);
					val2 = indirizzo_registro(1);
					assert(*val2 && "Errore: divisione per zero!");
					div_reg(val1, val2, stack);
				}else{
					/* Trovo il o i registri errati da segnalare. */
					if(p1 >= 0 && p1 <= 31){
						printf("Registro R%d non valido a riga %d.\n", p2, ip-2);
					}else{
						if(p2 >= 0 && p2 <= 31)
							printf("Registro R%d non valido a riga %d.\n", p1, ip-2);
						else
							printf("Registri R%d e R%d non validi a riga %d.\n", p1, p2, ip-2);
					}
					ip = num_istruzioni;
				}
				break;
				
			default:
				printf("Istruzione a riga %d non trovata.\n", ip);
				ip = num_istruzioni;
		}
		ip++;
	}
	return;
}
