/*
CT0442 Progetto virtual machine 2018-2019
Membri gruppo: Leonardo Mazzon 868445, Giulio Nicola 875297
*/

/* Compilazione: gcc -g3 -fsanitize=address -fsanitize=undefined -std=gnu89 -pedantic-errors -Wall -Wextra -o vm_exe fun_vm.c main_vm.c */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fun_vm.h"
void halt(){		
}

void display(int registro){
	printf("%d", registro);
}

void print_stack(int n){

}

void push(){

}

void pop(){

}

void mov(){

}

void call(){

}

void ret(){

}

void jmp(){

}

void jz(){

}

void jpos(){

}

void jneg(){

}

void add(){

}

void sub(){

}

void mul(){

}

void div(){

}

void scelta(int num){
	switch case(num){
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
		casse 12: mov();
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
		case 33: div();
			break;
		default case: printf("Istruzione non trovata\n");

}

/* 1-Successo 0-Errore N-Errore personalizzato*/
int creazione_stack(const char *file, int *stack){
	FILE *input;
	int lung_riga;
	size_t n = 0;
	int *vet;
	char *riga;
	char *temp;
	int num;
	int i=0;
	/* Lettura test del file */
	input = fopen(file, "r");	
	if(input){
		while((lung_riga = getline(&riga, &n, input)) != -1){
			if(riga[0]>=48 && riga[0]<=57){
				temp=strtok(riga,";");
				num=atoi(temp);
				if(i==0){
					vet=(int*)malloc(sizeof(int)*num);
					if(vet!=NULL)
						i++;
				}else{
					vet[i-1]=num;
					i++;
				}
			}
			free(riga);
			riga = NULL;
		}
		free(riga);
		fclose(input);
		for(i=0;i<35;i++)
			printf("%d\n", vet[i]);
		free(vet);
		return 1;
	}else{
		printf("Errore apertura file\n");
		return 0;
	}
}
