#include <fstream>
#include <stdlib.h>
#include <new>
#include <algorithm>
#include <vector>       // std::vector
#include "grafo.h"
using namespace std;

int num_operacoes = 0;
int find_agend = 0; // variavel que percorre o vetor de entradas e busca pelos agendamentos

// struct que armazerna cada linha da entrada
struct tpTransacao{
	int tempo_chegada;
	int id;
	char op;
	char atributo;
};

int contaNumTransacoes(FILE * f){
    int count = 0;
    char c, aux_ant;

    if (f == NULL) {
        printf("Nao foi possivel ler a entrada.");
        return 0;
    }

		c = getc(f);
		aux_ant = c;
		for (; c != EOF; c = getc(f)){
				if ((c == '\n') && (aux_ant != '\n')) //não é linha em branco
						count++;
				aux_ant = c;
		}
		if (aux_ant != '\n') //última linha sem linha em branco
				count++;

    rewind(f);
    return(count);
}

void printaTransacoes(tpTransacao *t){
	puts("Lista de transacoes:");
	for (int i = 0 ; i < num_operacoes ; i++){
		printf("%d %d %c %c\n", t[i].tempo_chegada, t[i].id, t[i].op, t[i].atributo);
	}
}

tpTransacao *leEntrada(){
	FILE * f = stdin;
	int i = 0;

	num_operacoes = contaNumTransacoes(f);
	tpTransacao *t = (tpTransacao*) calloc(num_operacoes, sizeof(tpTransacao));
	if (!t){
		puts("Nao foi possivel alocar.");
		exit(0);
	}
	printf("num linhas: %d\n", num_operacoes);
	while (!feof(f)){
		fscanf(f, "%d", &t[i].tempo_chegada);

		//printf("tempo_chegada: %d\n", t.tempo_chegada);
		fscanf(f, "%d", &t[i].id);
		//printf("id: %d\n", t.id);
		getc(f); // pula espaco
		fscanf(f, "%c", &t[i].op);
		getc(f); // pula espaco
		//printf("op: %c\n", t.op);
		fscanf(f, "%c", &t[i].atributo);
		getc(f); // quebra de linha no arquivo
		//printf("atributo: %c\n", t.atributo);

		//printf("%d %d %c %c\n", t[i].tempo_chegada, t[i].id, t[i].op, t[i].atributo); // debug
		i++;
	}
	return t;
}

int transacaoEstaNoAgend(std::list<int> agendamento, int transacao){
	list<int>::iterator it = std::find(agendamento.begin(), agendamento.end(), transacao);

	if (it != agendamento.end())
		return 1;
	else
		return 0;
}

void printaAgend(std::list<int> agendamento){
	for (list<int>::iterator iter = agendamento.begin(); iter != agendamento.end(); iter++) {
	  if (iter != agendamento.begin()) cout << ",";
	  cout << *iter;
	}
	cout << " ";
}


// auxiliar para printar o agendamento ordenado
bool compare_nocase (int first, int second){

  return ( first < second );
}


// retorna true se eh seriavel quanto ao conflito
int ehSeriavelConflito(tpTransacao *t, std::list<int> agendamento){
	int i, j;
	Grafo g = Grafo(num_operacoes);
	list<int>::iterator it;

	for (i = 0 ; i < num_operacoes - 1 ; i++){
		for (j = i+1 ; j < num_operacoes ; j++){
			//printf("i: %d   j: %d\nT%d e T%d sao %c e %c\n", i,j,t[i].id, t[j].id, t[i].op, t[j].op);
			//printaAgend(agendamento);
			if (transacaoEstaNoAgend(agendamento, t[i].id) && transacaoEstaNoAgend(agendamento, t[j].id)){ // se transacoes estao no agendamento que estamos analisando
			//	puts("entra aqui");
				if ((((t[i].op == 'W') || (t[i].op == 'w')) && ((t[j].op == 'R') || (t[j].op == 'r'))) //Aresta Ti -> Tj para cada r(x) em Tj depois de w(x) em Ti
					|| (((t[i].op == 'R') || (t[i].op == 'r')) && ((t[j].op == 'W') || (t[j].op == 'w'))) // Aresta Ti -> Tj para cada w(x) em Tj depois de r(x) em Ti
					|| (((t[i].op == 'W') || (t[i].op == 'w')) && ((t[j].op == 'W') || (t[j].op == 'w')))){ // Aresta Ti -> Tj para cada w(x) em Tj depois de w(x) em Ti
						if ((t[i].id != t[j].id) && (t[i].atributo == t[j].atributo)){ // ambas as transacoes devem estar mexendo nas mesmas variaveis (e evita laco no grafo)
							g.adicionarAresta(t[i].id, t[j].id);
						//	printf("inseriu aresta T%d -> T%d", t[i].id, t[j].id);
						}
				}
			}
		}
	}

	return (!g.temCiclo());
}

// retorna true se eh seriavel quanto ao conflito
int ehEquivalenteVisao(tpTransacao *t, std::list<int> agendamento){
	int i, j;
	Grafo g = Grafo(num_operacoes);
	list<int>::iterator it;

	for (i = 0 ; i < num_operacoes - 1 ; i++){
		for (j = i+1 ; j < num_operacoes ; j++){
			//printf("i: %d   j: %d\nT%d e T%d sao %c e %c\n", i,j,t[i].id, t[j].id, t[i].op, t[j].op);
			//printaAgend(agendamento);
			if (transacaoEstaNoAgend(agendamento, t[i].id) && transacaoEstaNoAgend(agendamento, t[j].id)){ // se transacoes estao no agendamento que estamos analisando
			//	puts("entra aqui");
				if (((t[i].op == 'W') || (t[i].op == 'w')) && ((t[j].op == 'R') || (t[j].op == 'r'))) { //Aresta Ti -> Tj para cada r(x) em Tj depois de w(x) em Ti
						if ((t[i].id != t[j].id) && (t[i].atributo == t[j].atributo)){ // ambas as transacoes devem estar mexendo nas mesmas variaveis (e evita laco no grafo)
							g.adicionarAresta(t[i].id, t[j].id);
						//	printf("inseriu aresta T%d -> T%d", t[i].id, t[j].id);
						}
				}
				else if (((t[i].op == 'R') || (t[i].op == 'r')) && ((t[j].op == 'W') || (t[j].op == 'w'))){
					if ((t[i].id != t[j].id) && (t[i].atributo == t[j].atributo)){ // ambas as transacoes devem estar mexendo nas mesmas variaveis (e evita laco no grafo)
						g.adicionarAresta(t[i].id, t[j].id);
					//	printf("inseriu aresta T%d -> T%d", t[i].id, t[j].id);
					}
				}
			}
		}
	}

	return (!g.temCiclo());
}

void printaLista(list<int> lista){
	cout << "Lista:\n";
	for (list<int>::iterator it = lista.begin(); it != lista.end(); ++it)
    	cout << *it << endl;
}

// encontra agendamento no vetor de tptransacao
std::list<int> encontraProxAgendamento(tpTransacao *t){
	std::list<int> agendamento; // transacoes paralelas
	std::list<int> agendamento_max; // guarda agendamento


	// inicializa agendamento
	while ((t[find_agend].op == 'C') || (t[find_agend].op == 'c')){ // encontra a primeira transacao que nao commita
		find_agend++;
	}
	agendamento.push_back(t[find_agend].id);
	agendamento_max.push_back(t[find_agend].id);

	while (!agendamento.empty()){

		if ((t[find_agend].op != 'C') && (t[find_agend].op != 'c')){
			if ((std::find(agendamento.begin(),agendamento.end(),t[find_agend].id)) == agendamento.end()){ // nao tem no vetor
				agendamento.push_back(t[find_agend].id);
				agendamento_max.push_back(t[find_agend].id);
			}
		}
		else{ // se commitou
			agendamento.remove(t[find_agend].id);
		}
		find_agend++;
	}
	//printaLista(agendamento_max);
	return agendamento_max;

}

int main(){
	tpTransacao *t;
	std::list<int> agendamento; // transacoes paralelas

	int num_agend = 0;

	t = leEntrada();
	//printaTransacoes(t);

	while (find_agend < num_operacoes){
		agendamento = encontraProxAgendamento(t);
		num_agend++;

		//printando para a saida do trabalho
		printf("%d ", num_agend); //printa o num do agendamento atual
		agendamento.sort(compare_nocase); // ordena o agendamento
		printaAgend(agendamento);
		if (ehSeriavelConflito(t, agendamento)){ //printa se eh ou nao seriavel por conflito
			printf("SS ");
		}
		else{
			printf("NS ");
		}
		if (ehEquivalenteVisao(t, agendamento)){ //printa se eh ou nao seriavel por conflito
			printf("SV\n");
		}
		else{
			printf("NV\n");
		}
	}
}
