/*
CT0442 Progetto virtual machine 2018-2019
Membri gruppo: Leonardo Mazzon 868445, Giulio Nicola 875297
*/
struct s_stack{
	int *vet;
	int pos;
};
typedef struct s_stack stack;
/* Firme funzioni */
int creazione_stack(const char *file, int *stack);
