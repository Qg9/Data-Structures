#include <stdlib.h>
#include <stdio.h>

struct Pile {
	int value;
	struct Pile* next;
};

typedef struct Pile pile;

pile* empile(int value, pile* source) {
	pile* l = malloc(sizeof(pile));
	l->next = source;
	l->value = value;
	return l;
}

int main() {
	pile* p	= empile(3, empile( 2,  
		empile(1, NULL)));

	while(p != NULL) {
		int v = p->value;
		printf("%i \n", v);
		p = p->next;
	}
}


