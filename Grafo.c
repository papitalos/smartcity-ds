/** 
 
 * @file   Grafo.c
 * @brief  Fun��es de manipula��o e explora��o do grafo
 * 
 * @author italo
 * @date   May 2023
 
**/

#include "platform.h"
#include "Grafo.h"
#include "Caminho.h"
#include "Transporte.h"
#include "Localizacao.h"


#pragma region FUNC_DE_CRIACAO

//Fun��o para criar o grafo
Grafo* CriarGrafo(int nVert) {
	int i, j;

	//aloca espa�o para um grafo
	Grafo* graf = (Grafo*)malloc(sizeof(Grafo));
	if (graf == NULL) return NULL;
	
	// Aloca espaço para nVert vértices (não apenas 1 ponteiro!)
	graf->vert = (Vertice*)malloc(sizeof(Vertice) * nVert);
	if (graf->vert == NULL) {
		free(graf);
		return NULL;
	}

	//define o numero de vertices e come�a com 0 arestas
	graf->nVertices = nVert;
	graf->nArestas = 0;
	
	// Inicializa a matriz de adjacência
	for (i = 0; i < MAX_VERTICES; i++) {
		for (j = 0; j < MAX_VERTICES; j++) {
			graf->matrizAdj[i][j] = 0;
		}
	}
	
	for (i = 0; i < nVert; i++) {
		//define que cada adjacencia (1,2,3...)  de cada cabeca como nula
		graf->vert[i].cabeca = NULL;
		graf->vert[i].foiVisitado = false;
	}

	return graf;
}

// Fun��o para destruir o grafo
void DestruirGrafo(Grafo* graf) {
	if (graf == NULL) return;

	// Libera a mem�ria alocada para cada lista de adjac�ncias
	for (int i = 0; i < graf->nVertices; i++) {
		Adjacencia* atual = graf->vert[i].cabeca;
		while (atual != NULL) {
			Adjacencia* proximo = atual->prox;
			free(atual);
			atual = proximo;
		}
	}

	// Libera o array de vértices
	free(graf->vert);
	
	// Libera a mem�ria alocada para o grafo
	free(graf);
}

//Fun��o que cria uma adjacencia
Adjacencia* CriaAdjacencia(int v, float peso) {
	//aloca espa�o temporario para um n� da adjacencia
	Adjacencia* temp = (Adjacencia*)malloc(sizeof(Adjacencia));

	if (temp == NULL) return temp;

	//define os parametros dessa adjacencia temporaria
	temp->vertice = v; //vertice de destino
	temp->peso = peso; //peso da aresta sendo criada
	temp->prox = NULL; //define o proximo como nulo pra tirar o sujo
	return(temp);
}

//Fun��o para contar os vertices a partir da lista de localiza��es
int ContarVertices(Grafo* graf, ListaLocal* lista) {
	if (graf == NULL) {
		int contador = 0;
			ListaLocal* ultimo_nodo = lista;
			while (ultimo_nodo != NULL)
			{
				contador++;
				ultimo_nodo = ultimo_nodo->prox;
			}

			return contador;
	}
	return 1;
}

//Fun��o para endere�ar cada vertice com um local
int EnderecarLocal(Grafo* graf,ListaLocal* lista) {
	
	if (graf == NULL || lista == NULL) return -1;

	for (int i = 0; i < graf->nVertices; i++)
	{
		// Só tenta endereçar se há uma adjacência criada
		if (graf->vert[i].cabeca != NULL) {
			char* geocode = EncontrarLocal(lista, i);
			graf->vert[i].cabeca->local.geocode = geocode;
		}
	}
	return 1;
}

//Fun��o para endere�ar uma lista de transportes para um geocode especifico
int ListarTransportesPorVertice(Grafo* graf, ListaTransporte* lista) {

	if (graf == NULL || lista == NULL) return -1;

	for (int i = 0; i < graf->nVertices; i++)
	{
		// Só tenta endereçar se há uma adjacência criada
		if (graf->vert[i].cabeca != NULL) {
			graf->vert[i].cabeca->local.TransportesGeocode = ListarPorGeocode(lista, graf->vert[i].cabeca->local.geocode);
		}
	}
	return 1;
}

//Fun��o para criar uma aresta
int CriaAresta(Grafo* graf, int verIni, int verFin, float peso) {
	//Verifica se o grafo existe
	if (!graf) { return 2;}
	//Verifica se o numero de vertices nao sao negativos e se sao maiores do que o numero de vertices do graf
	if (verFin < 0 || verFin >= graf->nVertices) { return 3;}
	if (verIni < 0 || verFin >= graf->nVertices) { return 3;}
		
	//usa a fun��o de cima para criar a adjacencia com o vertice final(destino) e o peso
	Adjacencia* novaAdj = CriaAdjacencia(verFin, peso);

	//coloco a nova adjacencia linkada no vertice inicial da lista
	novaAdj->prox = graf->vert[verIni].cabeca; //o proximo elemento da lista passa receber a cabe�a da lista
	graf->vert[verIni].cabeca = novaAdj; // a nova adjacencia passa a ser a cabe�a da lista
	graf->nArestas++; //atualiza o numero de arestas
	return 1;
}

//Fun��o que liga os vertices as adjacencias a partir de um mapa matriz
int CriarMapaMatriz(Grafo* graf) {
	if (graf == NULL) return -1;
	
	//para cada linha e coluna dentro do numero max de vertices da matriz
	for (int i = 0; i < graf->nVertices && i < MAX_VERTICES; i++) {
		for (int j = 0; j < graf->nVertices && j < MAX_VERTICES; j++) {
			if (graf->matrizAdj[i][j] != 0) {
				//cria uma aresta no mapa, ligando i e j com o peso da matriz
				CriaAresta(graf, i, j, graf->matrizAdj[i][j]);
			}
		}
	}
	return 1;
}

//Fun��o para debugar o grafo
void DebugGrafo(Grafo* graf) {
	if (graf == NULL) {
		printf("Grafo é NULL!\n");
		return;
	}
	
	printf("\n---------------- Grafo ----------------\n");
	printf("Numero de vertices: %d\n", graf->nVertices);
	printf("Numero de arestas: %d\n", graf->nArestas);
	printf("Matriz de Adjacencia:\n");
	for (int i = 0; i < graf->nVertices && i < MAX_VERTICES; i++) {
		for (int j = 0; j < graf->nVertices && j < MAX_VERTICES; j++) {
			if (graf->matrizAdj[i][j] > 99) {
				printf("%.0f", graf->matrizAdj[i][j]);
			}
			else {
				printf(" %.0f ", graf->matrizAdj[i][j]);
			}	
		}
		printf("\n");
	}
	printf("Lista de Adjacencias:\n");
	for (int i = 0; i < graf->nVertices; i++) {
		printf("Vertice %d -> ", i);
		Adjacencia* adj = graf->vert[i].cabeca;
		while (adj != NULL) {
			printf("(%d, peso: %.1f) -> ", adj->vertice, adj->peso);
			adj = adj->prox;
		}
		printf("NULL\n");
	}
	printf("---------------------------------------\n");
}

#pragma endregion

#pragma region FUNC_SUPORTE

	//Fun��o que cria um caminhao
	int CriarCaminhao(Coletor* novoColetor) {
		//Aloca espa�o para o caminh�o
		novoColetor = (Coletor*)malloc(sizeof(Coletor*));

		//Verifica se alocou espa�o corretamente
		if (novoColetor == NULL) return -1; 

		//Define o peso atual do caminh�o como 0
		novoColetor->pesoAtual = 0;

		/*Espa�o para caso venha adicionar coisas extras para o caminh�o*/

		return 1;
	}

	//Fun��o que cria um NodoPath para a lista da solu��o atual
	Trajeto CriarNodoPath(Adjacencia* adjacencia) {
		
		//Cria um novo nodoPath
		Trajeto newNodoPath = {0};

		//Define suas variaveis como as variaveis da adjacencia atual
		newNodoPath.peso = adjacencia->peso;
		newNodoPath.vertice = adjacencia->vertice;

		return newNodoPath;
	}

	//Fun��o que adiciona o NodoPath na lista de uma solu��o
	int AdicionarNodoPath(Solucao** path, Trajeto trajeto) {

		//Aloca espa�o para o novo nodo da solu��o
		Solucao* novoNodo = (Solucao*)malloc(sizeof(Solucao));

		//Verifica se a aloca��o funcionou
		if (novoNodo == NULL) return -1;

		//Define as variaveis do novo nodo 
		novoNodo->TrajetoParcial = trajeto;
		novoNodo->prox = NULL;

		//Verifica se � o primeiro nodo a adicionar a lista da solu��o
		if (*path == NULL) {
			*path = novoNodo;
		}

		//Percorre a lista
		else {
			Solucao* ultimo_nodo = *path;
			while (ultimo_nodo->prox != NULL) {
				ultimo_nodo = ultimo_nodo->prox;
			}
			//Define o ultimo nodo como o novo nodo
			ultimo_nodo->prox = novoNodo;
		}

		//Atualiza o tamanho e distancia do trajeto existente na lista
		Solucao* nodo_atual = *path;
		int tamanho = 0;
		float distanciaTotal = 0;
		//Percorre a lista novamente (agora com o novo nodo adicionado)
		while (nodo_atual != NULL) {
			tamanho++;
			distanciaTotal += nodo_atual->TrajetoParcial.peso;
			nodo_atual = nodo_atual->prox;
		}
		novoNodo->tamanho = tamanho;
		novoNodo->distanciaTotal = distanciaTotal;
		return 1;
	}

	//Fun��o que remove o ultimo NodoPath da lista de uma solu��o
	int RemoverUltimoNodoPath(Solucao** path) {

		//Verifica se existe algum nodo na lista da solu��o
		if (*path == NULL) {
			return 1; //N�o h� nada para remover
		}

		Solucao* nodoRemover = *path;
		Solucao* nodoAnterior = NULL;

		//Percorre a lista at� chegar ao �ltimo n�
		while (nodoRemover->prox != NULL) {
			nodoAnterior = nodoRemover;
			nodoRemover = nodoRemover->prox;
		}

		//Atualiza o tamanho do caminho atual
		(*path)->tamanho--;

		//Remove o �ltimo n� do caminho atual
		if (nodoAnterior == NULL) {
			*path = NULL; //O caminho ficou vazio
		}
		else {
			nodoAnterior->prox = NULL;
			free(nodoRemover);
		}
		return 1;
	}

	//Fun��o que calcula a distancia total de qualquer solu��o
	int CalcularDistanciaTotal(Solucao* solCalc) {

		if (solCalc == NULL) return -1; //Verifica se a solucao existe

		Solucao* ultimo_nodoA = solCalc;
		float distancia = 0;
		while (ultimo_nodoA != NULL) {
			distancia += ultimo_nodoA->TrajetoParcial.peso;
			ultimo_nodoA = ultimo_nodoA->prox;
		}
		return distancia;
	}

	//Fun��o que calcula a melhor solu��o de todas de acordo com a distancia
	Solucao* CalcularMelhorSolucao(Solucao* solAtual, Solucao* solMelhor) {
		 
		//Caso seja Nulo, ou seja a primeira vez
		Solucao* solProvisoria;
		if (solMelhor == NULL) {
			solProvisoria = NULL;
			while (solAtual != NULL) {
				AdicionarNodoPath(&solProvisoria, solAtual->TrajetoParcial);
				solAtual = solAtual->prox;
			}

			return solProvisoria;
		}

		//Calcula as distancias totais
		int distSolMelhor = CalcularDistanciaTotal(solMelhor); 
		int distSolAtual = CalcularDistanciaTotal(solAtual);

		// Verifica se a dist�ncia total do trajeto atual � menor que a da melhor solu��o
		if (distSolAtual < distSolMelhor) {
			solProvisoria = NULL;
			while (solAtual != NULL) {	
				AdicionarNodoPath(&solProvisoria, solAtual->TrajetoParcial);
				solAtual = solAtual->prox;
			}
			solMelhor = solProvisoria;
		}
		//ImprimirSolucao(solMelhor);//Imprime a melhor solu��o percorrida
		return solMelhor;
	}

	//Fun��o para debugar os caminhos de todas solu��es percorridas
	void ImprimirCaminho(Solucao* solucao) {
		if (solucao == NULL) {
			printf("Caminho vazio.\n");
			return;
		}

		Solucao* nodo_atual = solucao;
		while (nodo_atual != NULL) {
			printf("\nVertice: %d, Peso: %.2f", nodo_atual->TrajetoParcial.vertice, nodo_atual->TrajetoParcial.peso);
			nodo_atual = nodo_atual->prox;
		}
		printf("\n");
	}

	//Fun��o para debugar o melhor caminho de todas as solu��es percorridas
	void ImprimirSolucao(Solucao* solucao) {
		if (solucao == NULL) {
			printf("Caminho vazio.\n");
			return;
		}

		Solucao* nodo_atual = solucao;
		printf("\nMelhor solucao ate agora:");
		while (nodo_atual != NULL) {
			printf("\nVertice: %d, Peso: %.2f", nodo_atual->TrajetoParcial.vertice, nodo_atual->TrajetoParcial.peso);
			nodo_atual = nodo_atual->prox;
		}
		printf("\n");
	}

#pragma endregion

#pragma region FUNC_DE_SEARCH
	//Fun��o DFS
	int DFS(Grafo* graf, int vertAtual, Solucao* solAtual) {

		//Verifica��es das variaveis
		if (graf == NULL || vertAtual < 0) return -1;

		//Cria uma suposta melhor solu��o com valor est�tico
		static Solucao* solMelhor;

		//Marca o v�rtice atual como visitado
		graf->vert[vertAtual].foiVisitado = true;
		
		//Percorre as adjac�ncias do v�rtice atual
		Adjacencia* adj = graf->vert[vertAtual].cabeca;
		while (adj != NULL) {
			int proxVertice = adj->vertice;

			//Se o vertice n�o foi visitado e tem adjacencia com o vertice atual
			if (!graf->vert[proxVertice].foiVisitado && graf->matrizAdj[vertAtual][proxVertice] != 0) {

				//Adiciona ao caminho atual
				Trajeto nodoPath = CriarNodoPath(adj);
				AdicionarNodoPath(&solAtual, nodoPath);

				//Chama a recursividade
				DFS(graf, proxVertice, solAtual);
			}

			//Senao vai para o proximo vertice adjacente do vertice atual
			adj = adj->prox;
		}

		//Ao percorrer tudo calcula a melhor solu��o e imprime o caminho percorrido
		if (adj == NULL) {
			//ImprimirCaminho(solAtual); //Imprime todos os caminhos percorridos
			solMelhor = CalcularMelhorSolucao(solAtual, solMelhor);
	
		}
		
		//Desmarca o v�rtice atual como visitado e remove do caminho atual
		graf->vert[vertAtual].foiVisitado = false;
		RemoverUltimoNodoPath(&solAtual);

		
		
		return 1;
	}

#pragma endregion

#pragma region FUNC_FILES

	//Fun��o para salvar o grafo em um arquivo bin�rio
	int SalvarGrafoBinario(Grafo* graf, char* fileName) {
		//Verifica se o grafo existe
		if (graf == NULL) return -1;
		
		//Abre o arquivo bin�rio em modo de escrita
		FILE* file = fopen(fileName, "wb");
		if (file == NULL) return -1;

		//Escreve o n�mero de v�rtices e o n�mero de arestas no arquivo
		fwrite(&(graf->nVertices), sizeof(int), 1, file);
		fwrite(&(graf->nArestas), sizeof(int), 1, file);

		for (int i = 0; i < graf->nVertices; i++) {
			for (int j = 0; j < graf->nVertices; j++) {
				fwrite(&(graf->matrizAdj[i][j]), sizeof(int), 1, file);
			}
		}
		// Escreve os v�rtices e suas adjac�ncias no arquivo
		for (int i = 0; i < graf->nVertices; i++) {
			Adjacencia* adj = graf->vert[i].cabeca;
			while (adj != NULL) {
				AdjFile adjFile = { 0 };
				adjFile.origem = i;
				adjFile.destino = adj->vertice;
				adjFile.peso = adj->peso;
				adjFile.geocode = adj->local.geocode;
				fwrite(&adjFile, sizeof(AdjFile), 1, file);

				adj = adj->prox;
			}
		}
		//Fecha o arquivo
		fclose(file);
		//Destroi o grafo
		DestruirGrafo(graf);
		return 1;
	}

	// Fun��o para ler o grafo de um arquivo bin�rio
	Grafo* LerGrafoBinario(char* fileName, ListaLocal* lista) {
		// Abre o arquivo bin�rio em modo de leitura
		FILE* file = fopen(fileName, "rb");
		if (file == NULL) return NULL;

		// L� o n�mero de v�rtices e o n�mero de arestas do arquivo
		int nVertices = 0, nArestas = 0;
		fread(&nVertices, sizeof(int), 1, file);
		fread(&nArestas, sizeof(int), 1, file);

		// Cria o grafo com o n�mero de v�rtices lido do arquivo
		Grafo * graf = CriarGrafo(nVertices);


		// L� a matriz de adjac�ncia do arquivo
		float tempMatriz[MAX_VERTICES][MAX_VERTICES] = { 0 };
		for (int i = 0; i < nVertices; i++) {
			for (int j = 0; j < nVertices; j++) {
				fread(&(tempMatriz[i][j]), sizeof(int), 1, file);
				graf->matrizAdj[i][j] = tempMatriz[i][j];
			}
		}


		//Inicializo fora para usar em outra logica
		char* geocode = NULL;

		for (int i = 0; i < nVertices; i++)
		{
			char* geocodeEncontrado = EncontrarLocal(lista, i);
			Adjacencia* adj = graf->vert[i].cabeca;
			while (adj != NULL) {
				if (adj->vertice == i) {
					adj->local.geocode = geocodeEncontrado;
					break;
				}
				adj = adj->prox;
			}

			if (EncontrarLocal(lista, i) == NULL) {
				// Cria uma nova localiza��o e adiciona � lista
				AdicionarLocalPorGeocode(&lista, geocode, i);
			}
		}

		// Fecha o arquivo
		fclose(file);

		return graf;
	}

#pragma endregion
