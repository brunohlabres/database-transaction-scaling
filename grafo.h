#ifndef __GRAFO__
#define __GRAFO__
#include <list>
#include <iostream>
#include <stack> // pilha para usar na DFS

class Grafo {
	int V; // número de vertices
	std::list<int> *adj;

public:
	Grafo(int V);
	void adicionarAresta(int v1, int v2);

	// faz uma DFS a partir de um vértice, retorna se achou ciclo ou não
	bool dfs(int v);

	// verifica se o grafo direcionado tem ciclo
	bool temCiclo();
};


#endif
