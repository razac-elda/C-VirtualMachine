/*
CT0442 Progetto virtual machine 2018-2019
Membri gruppo: Leonardo Mazzon 868445, Giulio Nicola 875297
*/

/* Compilazione: gcc -g3 -fsanitize=address -fsanitize=undefined -std=gnu89 -pedantic-errors -Wall -Wextra -o vm_exe fun_esegui_vm.c fun_stampa_vm.c main_vm.c */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fun_esegui_vm.h"

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
	
		/* Lettura righe del file, se il primo carattere è un numero abbiamo trovato
			un istruzione/valore e andiamo a convertirla per intero. */
		while((getline(&riga, &buffer_size, input)) != -1){
			elimina_spazi(riga);
			if(riga[0] >= '0' && riga[0] <= '9'){
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

s_stack getempty(){
	s_stack ris;
	/* Allocazione 65536 Bytes(64KB). */
	ris.vet = (int*)malloc(65536);
	if(ris.vet){
		/* Numero di interi contenibili(dim max) */
		ris.dim = 65536 / sizeof(int);
		/* Stack pointer a 0. */
		ris.sp = 0;
	}
	return ris;
}

int isempty(s_stack stack){
	return (stack.sp == 0);
}

void display(int registro, int *valore){
	printf("Registro R%d: %d\n", registro, *valore);
	return;
}

int print_stack(s_stack *stack, int n){
	int lifo = stack->sp - 1;
	while(lifo >= 0 && n > 0){
		printf("Posizione %d: %d\n", lifo, (stack->vet)[lifo]);
		lifo--;
		n--;
	}
	/* Ritorno dimensione stack. */
	return stack->sp;
}

int push(s_stack *stack, int registro){
	if(stack->sp < stack->dim){
		(stack->vet)[stack->sp] = registro;
		(stack->sp)++;
		return 0;
	}else{
		return 1;	
	}
}

int pop(s_stack *stack, int *registro){
	if(!isempty(*stack)){
		(stack->sp)--;
		*registro = (stack->vet)[stack->sp];
		return 0;
	}else{
		return 1;
	}
}

void mov(int *registro, int numero){
	*registro = numero;
	return;
}

int add(int *registro1, int *registro2, s_stack *stack){
	int ris, of = 0;
	ris = (*registro1) + (*registro2);
	of = push(stack, ris);
	return of;
}

int sub(int *registro1, int *registro2, s_stack *stack){
	int ris, of = 0;
	ris = (*registro1) - (*registro2);
	of = push(stack, ris);
	return of;
}

int mul(int *registro1, int *registro2, s_stack *stack){
	int ris, of = 0;
	ris = (*registro1) * (*registro2);
	of = push(stack, ris);
	return of;
}

int div_reg(int *registro1, int *registro2, s_stack *stack){
	int ris, of = 0;
	ris = (*registro1) / (*registro2);
	of = push(stack, ris);
	return of;
}

int interprete(int *vet_istruzioni, int num_istruzioni, s_stack *stack){
	/* Flag overflow e underflow */
	int of = 0, uf = 0;
	/* Instruction Pointer */
	int ip = 0;
	/* Parametro 1 e 2 sono i nomi dei registri o il numero. */
	int p1, p2;
	/* Val 1 e 2 conterrano, quando necessario, gli indirizzi dei registri corrispondenti a P1 e P2.
		Dereferenziare per il valore. */
	int *val1, *val2;
	/* Variabili per gestire lo stack. */
	int stack_dim;
	int stack_val;
	/* Se un istruzione non è corretta o ci sono errori torno al main segnalando il tipo di errore. */
	printf("\n");
	while(ip < num_istruzioni){
		switch (vet_istruzioni[ip]){
			case 0:	/* HALT */
				return 0;
			case 1:	/* DISPLAY */
			
				ip++;
				if(ip >= num_istruzioni){
					printf("Errore: parametri insufficienti in posizione %d.\n", ip-1);
					return 1;
				}
				p1 = vet_istruzioni[ip];
				if(p1 >= 0 && p1 <= 31){
					/* Ottengo l'indirizzo del registro. */
					val1 = indirizzo_registro(p1);
					display(p1, val1);
				}else{
					printf("Registro R%d non valido in posizione %d.\n", p1, ip-1);
					return 1;
				}
				break;
				
			case 2:	/* PRINT */
				
				ip++;
				if(ip >= num_istruzioni){
					printf("Errore: parametri insufficienti in posizione %d.\n", ip-1);
					return 1;
				}
				p1 = vet_istruzioni[ip];
				printf("====STACK LAST====\n");
				stack_dim = print_stack(stack, p1);
				printf("====STACK FIRST====\n");
				if(stack_dim == p1){
					printf("Tutto lo stack e' stato stampato(%d posizione/i).\n\n", p1);
				}else{
					if(stack_dim < p1){
						if(stack_dim == 0)
							printf("Lo stack e' vuoto.\n\n");
						else
							printf("E' stato possibile stampare solo %d posizione/i.\n\n", stack_dim);
					}else{
						printf("%d posizione/i stampata/e.\n\n", p1);
					}
				}
				break;
				
			case 10:	/* PUSH */
			
				ip++;
				if(ip >= num_istruzioni){
					printf("Errore: parametri insufficienti in posizione %d.\n", ip-1);
					return 1;
				}
				p1 = vet_istruzioni[ip];
				if(p1 >= 0 && p1 <= 31){
					val1 = indirizzo_registro(p1);
					of = push(stack, *val1);
					if(of){
						printf("Errore: stack overflow\n");
						return 1;	
					}
				}else{
					printf("Registro R%d non valido in posizione %d.\n", p1, ip-1);
					return 1;
				}
				break;
				
			case 11:	/* POP */
			
				ip++;
				if(ip >= num_istruzioni){
					printf("Errore: parametri insufficienti in posizione %d.\n", ip-1);
					return 1;
				}
				p1 = vet_istruzioni[ip];
				if(p1 >= 0 && p1 <= 31){
					val1 = indirizzo_registro(p1);
					uf = pop(stack, val1);
					if(uf){
						printf("Errore: stack underflow\n");
						return 1;	
					}
				}else{
					printf("Registro R%d non valido in posizione %d.\n", p1, ip-1);
					return 1;
				}
				break;
				
			case 12:	/* MOV */
			
				ip++;
				if(ip >= num_istruzioni){
					printf("Errore: parametri insufficienti in posizione %d.\n", ip-1);
					return 1;
				}
				p1 = vet_istruzioni[ip];
				if(p1 >= 0 && p1 <= 31){
					val1 = indirizzo_registro(p1);
					ip++;
					if(ip >= num_istruzioni){
						printf("Errore: parametri insufficienti in posizione %d.\n", ip-2);
						return 1;
					}
					p2 = vet_istruzioni[ip];
					mov(val1, p2);
				}else{
					printf("Registro R%d non valido in posizione %d.\n", p1, ip-2);
					return 1;
				}
				break;
				
			case 20:	/* CALL */
			
				ip++;
				if(ip >= num_istruzioni){
					printf("Errore: parametri insufficienti in posizione %d.\n", ip-1);
					return 1;
				}
				p1 = vet_istruzioni[ip];
				if(p1 >= 0 && p1 < num_istruzioni){
					ip++;
					if(ip >= num_istruzioni){
						printf("Errore: parametri insufficienti in posizione %d.\n", ip-2);
						return 1;
					}
					of = push(stack, ip);
					if(of){
						printf("Errore: stack overflow\n");
						return 1;	
					} 
					ip = p1 - 1;
				}else{
					printf("Errore: call a %d salta ad un indirizzo non valido\n", ip-1);
					return 1;
				}
				break;
				
			case 21:	/* RET */
			
				uf = pop(stack, &ip);
				if(uf){
					printf("Errore: stack underflow\n");
					return 1;	
				}
				ip--;
				break;
				
			case 22:	/* JMP */
				
				ip++;
				if(ip >= num_istruzioni){
					printf("Errore: parametri insufficienti in posizione %d.\n", ip-1);
					return 1;
				}
				p1 = vet_istruzioni[ip];
				if(p1 > 0 && p1 < num_istruzioni){
					ip = p1 - 1;
				}else{
					printf("Errore: il jump a %d salta ad un indirizzo non valido\n", ip-1);
					return 1;
				}
				break;
				
			case 23:	/* JZ */
			
				uf = pop(stack, &stack_val);
				if(uf){
					printf("Errore: stack underflow\n");
					return 1;	
				}
				ip++;
				if(ip >= num_istruzioni){
					printf("Errore: parametri insufficienti in posizione %d.\n", ip-1);
					return 1;
				}
				if(stack_val == 0){
					p1 = vet_istruzioni[ip];
					if(p1 > 0 && p1 < num_istruzioni){
						ip = p1 - 1;
					}else{
						printf("Errore: il jump a %d salta ad un indirizzo non valido\n", ip-1);
						return 1;
					}
				}
				break;
				
			case 24:	/* JPOS */
			
				uf = pop(stack, &stack_val);
				if(uf){
					printf("Errore: stack underflow\n");
					return 1;	
				}
				ip++;
				if(ip >= num_istruzioni){
					printf("Errore: parametri insufficienti in posizione %d.\n", ip-1);
					return 1;
				}
				if(stack_val > 0){
					p1 = vet_istruzioni[ip];
					if(p1 > 0 && p1 < num_istruzioni){
						ip = p1 - 1;
					}else{
						printf("Errore: il jump a %d salta ad un indirizzo non valido\n", ip-1);
						return 1;
					}
				}
				break;
				
			case 25:	/* JNEG */
			
				uf = pop(stack, &stack_val);
				if(uf){
					printf("Errore: stack underflow\n");
					return 1;	
				}
				ip++;
				if(ip >= num_istruzioni){
					printf("Errore: parametri insufficienti in posizione %d.\n", ip-1);
					return 1;
				}
				if(stack_val < 0){
					p1 = vet_istruzioni[ip];
					if(p1 > 0 && p1 < num_istruzioni){
						ip = p1 - 1;
					}else{
						printf("Errore: il jump a %d salta ad un indirizzo non valido\n", ip-1);
						return 1;
					}
				}
				break;
				
			case 30:	/* ADD */
			
				ip++;
				if(ip >= num_istruzioni){
					printf("Errore: parametri insufficienti in posizione %d.\n", ip-1);
					return 1;
				}
				p1 = vet_istruzioni[ip];
				ip++;
				if(ip >= num_istruzioni){
					printf("Errore: parametri insufficienti in posizione %d.\n", ip-2);
					return 1;
				}
				p2 = vet_istruzioni[ip];
				if((p1 >= 0 && p1 <= 31) && (p2 >= 0 && p2 <= 31)){
					val1 = indirizzo_registro(p1);
					val2 = indirizzo_registro(p2);
					of = add(val1, val2, stack);
					if(of){
						printf("Errore: stack overflow\n");
						return 1;	
					}
				}else{
					/* Trovo il o i registri errati da segnalare. */
					if(p1 >= 0 && p1 <= 31){
						printf("Registro R%d non valido in posizione %d.\n", p2, ip-2);
					}else{
						if(p2 >= 0 && p2 <= 31)
							printf("Registro R%d non valido in posizione %d.\n", p1, ip-2);
						else
							printf("Registri R%d e R%d non validi in posizione %d.\n", p1, p2, ip-2);
					}
					return 1;
				}
				break;
				
			case 31:	/* SUB */
			
				ip++;
				if(ip >= num_istruzioni){
					printf("Errore: parametri insufficienti in posizione %d.\n", ip-1);
					return 1;
				}
				p1 = vet_istruzioni[ip];
				ip++;
				if(ip >= num_istruzioni){
					printf("Errore: parametri insufficienti in posizione %d.\n", ip-2);
					return 1;
				}
				p2 = vet_istruzioni[ip];
				if((p1 >= 0 && p1 <= 31) && (p2 >= 0 && p2 <= 31)){
					val1 = indirizzo_registro(p1);
					val2 = indirizzo_registro(p2);
					of = sub(val1, val2, stack);
					if(of){
						printf("Errore: stack overflow\n");
						return 1;	
					}
				}else{
					/* Trovo il o i registri errati da segnalare. */
					if(p1 >= 0 && p1 <= 31){
						printf("Registro R%d non valido in posizione %d.\n", p2, ip-2);
					}else{
						if(p2 >= 0 && p2 <= 31)
							printf("Registro R%d non valido in posizione %d.\n", p1, ip-2);
						else
							printf("Registri R%d e R%d non validi in posizione %d.\n", p1, p2, ip-2);
					}
					return 1;
				}
				break;
				
			case 32:	/* MUL */
			
				ip++;
				if(ip >= num_istruzioni){
					printf("Errore: parametri insufficienti in posizione %d.\n", ip-1);
					return 1;
				}
				p1 = vet_istruzioni[ip];
				ip++;
				if(ip >= num_istruzioni){
					printf("Errore: parametri insufficienti in posizione %d.\n", ip-2);
					return 1;
				}
				p2 = vet_istruzioni[ip];
				if((p1 >= 0 && p1 <= 31) && (p2 >= 0 && p2 <= 31)){
					val1 = indirizzo_registro(p1);
					val2 = indirizzo_registro(p2);
					of = mul(val1, val2, stack);
					if(of){
						printf("Errore: stack overflow\n");
						return 1;	
					}
				}else{
					/* Trovo il o i registri errati da segnalare. */
					if(p1 >= 0 && p1 <= 31){
						printf("Registro R%d non valido in posizione %d.\n", p2, ip-2);
					}else{
						if(p2 >= 0 && p2 <= 31)
							printf("Registro R%d non valido in posizione %d.\n", p1, ip-2);
						else
							printf("Registri R%d e R%d non validi in posizione %d.\n", p1, p2, ip-2);
					}
					return 1;
				}
				break;
				
			case 33:	/* DIV */
			
				ip++;
				if(ip >= num_istruzioni){
					printf("Errore: parametri insufficienti in posizione %d.\n", ip-1);
					return 1;
				}
				p1 = vet_istruzioni[ip];
				ip++;
				if(ip >= num_istruzioni){
					printf("Errore: parametri insufficienti in posizione %d.\n", ip-2);
					return 1;
				}
				p2 = vet_istruzioni[ip];
				if((p1 >= 0 && p1 <= 31) && (p2 >= 0 && p2 <= 31)){
					val1 = indirizzo_registro(p1);
					val2 = indirizzo_registro(p2);
					if(val2 == 0){
						printf("Errore: divisione per zero in posizione %d.\n", ip-2);
						return 1;
					}
					of = div_reg(val1, val2, stack);
					if(of){
						printf("Errore: stack overflow\n");
						return 1;	
					}
				}else{
					/* Trovo il o i registri errati da segnalare. */
					if(p1 >= 0 && p1 <= 31){
						printf("Registro R%d non valido in posizione %d.\n", p2, ip-2);
					}else{
						if(p2 >= 0 && p2 <= 31)
							printf("Registro R%d non valido in posizione %d.\n", p1, ip-2);
						else
							printf("Registri R%d e R%d non validi in posizione %d.\n", p1, p2, ip-2);
					}
					return 1;
				}
				break;
				
			default:	/* ISTRUZIONE NON TROVATA */
				printf("Istruzione in posizione %d non trovata.\n", ip);
				return 1;
		}
		ip++;
	}
	return 0;
}
