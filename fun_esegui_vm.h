/*
CT0442 Progetto virtual machine 2018-2019
Membri gruppo P1G129: Leonardo Mazzon 868445, Giulio Nicola 875297
*/

struct s_stack{
	int *vet;
	int sp;
	int dim;
};
typedef struct s_stack s_stack;

/* Firme funzioni */
int interprete(int *vet_istruzioni, int num_istruzioni, s_stack* stack);
s_stack getempty();
