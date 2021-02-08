/*
CT0442 Progetto virtual machine 2018-2019
Membri gruppo P1G129: Leonardo Mazzon 868445, Giulio Nicola 875297
*/

/* Compilazione: gcc -g3 -fsanitize=address -fsanitize=undefined -std=gnu89 -pedantic-errors -Wall -Wextra -o vm_exe fun_esegui_vm.c fun_stampa_vm.c main_vm.c -lm*/

/* Librerie */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "fun_esegui_vm.h"

/* Registri. */
int r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,
	r11,r12,r13,r14,r15,r16,r17,r18,r19,r20,
	r21,r22,r23,r24,r25,r26,r27,r28,r29,r30,r31;

/* Tramite gli indirizzi possiamo lavorare sui registri. */
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

/* Ritorna 1 in caso di overflow. */
int push(s_stack *stack, int registro){
	if(stack->sp < stack->dim){
		(stack->vet)[stack->sp] = registro;
		(stack->sp)++;
		return 0;
	}else{
		return 1;	
	}
}

/* Ritorna 1 in caso di underflow. */
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

/* Le funzioni che svolgono operazioni aritmetiche ritornano 1 in caso di stack overflow. */
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

/* Il compito della funzione "interprete" e' quello di rilevare le istruzioni con i rispettivi parametri
ed eseguirle, gestendo il flusso del programma(jump e call), vengono anche implementati i controlli necessari. */
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
	
	printf("\n");
	/* Se un istruzione non è corretta o ci sono errori torno al main segnalando il tipo di errore. */
	while(ip < num_istruzioni){
		/* Ad ogni istruzione rilevata andiamo a leggere le posizioni successive a seconda 
		del numero di parametri dell'istruzione. Sono presenti controlli per verificare che i parametri
		successivi siano dei registri(se specificato dall'istruzione). Si i parametri sforassero con le righe
		si verifica un errore di parametri insufficienti. */
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
					val1 = indirizzo_registro(p1);
					display(p1, val1);
				}else{
					printf("Registro R%d non valido in posizione %d.\n", p1, ip-1);
					return 1;
				}
				break;
				
			case 2:	/* PRINT_STACK */
				
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
						printf("Errore: stack overflow.\n");
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
						printf("Errore: stack underflow.\n");
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
						printf("Errore: stack overflow.\n");
						return 1;	
					}
					/* Effettuato un salto parto dalla posizione precedente, 
					perche' alla fine del while la posizione aumenta. */
					ip = p1 - 1;
				}else{
					printf("Errore: call a %d salta ad un indirizzo non valido.\n", ip-1);
					return 1;
				}
				break;
				
			case 21:	/* RET */
			
				uf = pop(stack, &ip);
				if(uf){
					printf("Errore: stack underflow.\n");
					return 1;	
				}
				/* Effettuato un ritorno parto dalla posizione precedente, 
				perche' alla fine del while la posizione aumenta. */
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
					printf("Errore: il jump a %d salta ad un indirizzo non valido.\n", ip-1);
					return 1;
				}
				break;
				
			case 23:	/* JZ */
			
				uf = pop(stack, &stack_val);
				if(uf){
					printf("Errore: stack underflow.\n");
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
						printf("Errore: il jump a %d salta ad un indirizzo non valido.\n", ip-1);
						return 1;
					}
				}
				break;
				
			case 24:	/* JPOS */
			
				uf = pop(stack, &stack_val);
				if(uf){
					printf("Errore: stack underflow.\n");
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
						printf("Errore: il jump a %d salta ad un indirizzo non valido.\n", ip-1);
						return 1;
					}
				}
				break;
				
			case 25:	/* JNEG */
			
				uf = pop(stack, &stack_val);
				if(uf){
					printf("Errore: stack underflow.\n");
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
						printf("Errore: il jump a %d salta ad un indirizzo non valido.\n", ip-1);
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
					/* Controllo int overflow tramite limits.h. */
					if((*val2 > 0 && *val1 > INT_MAX - *val2) || (*val2 < 0 && *val1 < INT_MIN - *val2)){
						printf("Errore: la somma a riga %d causa overflow.\n", ip-2);
						return 1;	
					}
					of = add(val1, val2, stack);
					if(of){
						printf("Errore: stack overflow.\n");
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
					/* Controllo int underflow tramite limits.h. */
					if((*val2 > 0 && *val1 < INT_MIN + *val2) || (*val2 < 0 && *val1 > INT_MAX + *val2)){
						printf("Errore: la sottrazione a riga %d causa underflow.\n", ip-2);
						return 1;	
					}
					of = sub(val1, val2, stack);
					if(of){
						printf("Errore: stack overflow.\n");
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
					/* Mantengo il formato (+) * (+) o (+) * (-).
					I risultato rimangono invariati per le regole dei segni.*/
					if(*val1 < 0){
						*val1*=-1;
						*val2*=-1;
					}
					/* Controllo int overflow tramite limits.h.*/
					if((*val2 > 0 && *val1 > INT_MAX / *val2) || (*val2 < 0 && *val1 > INT_MIN / *val2)){
						printf("Errore: la moltiplicazione a riga %d causa overflow.\n", ip-2);
						return 1;	
					}
					of = mul(val1, val2, stack);
					if(of){
						printf("Errore: stack overflow.\n");
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
					/* Divisiore deve essere diverso da 0. */
					if(*val2 == 0){
						printf("Errore: divisione per zero in posizione %d.\n", ip-2);
						return 1;
					}
					/* Controllo int overflow tramite limits.h. La divisone causa overflow
					se divisiamo il valore piu' piccolo per -1. */
					if(*val1 == INT_MIN && *val2 == -1){
						printf("Errore: la divisione a riga %d causa overflow.\n", ip-2);
						return 1;	
					}
					of = div_reg(val1, val2, stack);
					if(of){
						printf("Errore: stack overflow.\n");
						return 1;	
					}
				}else{
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
