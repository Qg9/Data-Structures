#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct Pile {
	int value;
	struct Pile* next;
};

typedef struct Pile* pile;

void empile(int value, pile* source) {
	pile l = malloc(sizeof(pile));
	l->next = *source;
	l->value = value;
	*source = l;
}

int depile(pile* source) {
	pile curr = *source;
	pile next = curr->next;
	int v = curr->value;
	free(curr);
	*source = next;
	return v;
}

struct graph {
	int size;
	pile* vectors;
	int* degrees;
};

typedef struct graph graph;

graph* createempty(int size) {
	graph* g = malloc(sizeof(graph));
	g->size = size;
	g->degrees = malloc(sizeof(int)*size);
	g->vectors = malloc(sizeof(pile*)*size);
	
	for(int i = 0; i < size; i++){
		g->degrees[i] = 0;
		g->vectors[i] = NULL;
	}
	return g;
}

void addvector(graph* g, int source, int target) {
	g->degrees[source]+=1;
	empile(target, &g->vectors[source]);
}

bool* dfs(graph* g, int source) {
	bool* visited = malloc(sizeof(bool)*g->size);
	for(int i = 0; i < g->size; i++)visited[i] = false;
	visited[source] = true;
	
	pile cache = NULL;
	empile(source, &cache);
	
	while(cache != NULL) {
		int curr = depile(&cache);
		pile nexts = g->vectors[curr];
		
		while(nexts != NULL) {
			int next = depile(&nexts);
			if(visited[next])continue;
			visited[next] = true;
			empile(next, &cache);
		}
	}
	return visited;
}

void print_array(bool* array, int size) {
	for(int i = 0; i < size; i++) {
		printf("%i ", array[i]);
	}
	printf("\n");
}

int main() {
	graph* g = createempty(5);
	addvector(g, 3, 4);
	addvector(g, 4, 2);
	addvector(g, 0, 4);
	addvector(g, 1, 5);
	addvector(g, 0, 3);

	bool* p = dfs(g, 0);
	print_array(p, 5);
}


