/** 
 
 * @file   Main.c
 * @brief  arquivo principal de chamada de fun��es
 * 
 * @author italo
 * @date   March 2023
 
**/

#include "platform.h"
#include "Cliente.h"
#include "Gestor.h"
#include "Transporte.h"
#include "Caminho.h"
#include "Grafo.h"
#include "Localizacao.h"

/**
 * no caso da leitura e escrita de arquivos e listas
 * (1 - funcionou! ; 2 - foi problema do ficheiro! ; 3 - foi problema do sscanf ou sprintf; 4 - se a lista estiver vazia).
 * no caso dos grafos
 * (1 - funcionou! ; -1 - n�o funcionou; -2 - erro no arquivo).
 */

int main() {

	//FASE 1
	//Inicializar listas como NULL
	ListaCliente* listaClientes = NULL; 
	ListaGestor* listaGestores = NULL; 
	ListaTransporte* listaTransportes = NULL; 

	//Leitura de arquivos em printf para verificar funcionamento
	printf("\n %d", LerFileCliente(&listaClientes));
	printf("\n %d", LerFileGestor(&listaGestores));
	printf("\n %d", LerFileTransporte(&listaTransportes));

	//Cria um exemplo pra remover cliente
	ListaCliente* exemplo = EncontrarCliente(listaClientes, 2);
	RemoverCliente(&listaClientes, exemplo);

	//Testa o restante das fun��es
	TrocarCliente(EncontrarCliente(listaClientes, 1), EncontrarCliente(listaClientes, 4));

	OrganizarTransportePorBateria(listaTransportes);
	ContarTransportesPoucaBateria(listaTransportes, "///orgao.nossa.alma", 2);

	OrganizarClientePorID(listaClientes);
	OrganizarTransportePorID(listaTransportes);

	

	//EXTRAS DE LISTA
	//Cria a lista com todas as localiza��es existentes
	ListaLocal* listaLocal = NULL;
	//L� o arquivo das localiza��es
	printf("\n %d", LerFileLocal(&listaLocal));
	OrganizarLocalPorID(listaLocal);

	//FASE 2
	//Inicializa��o das variaveis do grafo
	Grafo* graf = NULL;	
	Coletor* caminhao = NULL;
	Solucao* melhorSol = NULL;

	//Leio o arquivo binario do grafo
	graf = LerGrafoBinario("Data/grafo.bin", listaLocal);

	//Conta a quantidade de locais e define o grafo com essa quantidade
	if (graf == NULL)
	{
		int contador = ContarVertices(NULL, listaLocal); // Passa NULL em vez de graf
		graf = CriarGrafo(contador);//Cria o grafo com o n�mero de vertices que existe no arquivo txt
	}

	//Cria liga��es do Grafo (apenas se o grafo foi criado com sucesso)
	if (graf != NULL) {
		printf("\n %d", CriarMapaMatriz(graf));
		DebugGrafo(graf);

		//Endere�a cada nodo do grafo com um local e uma lista de transportes daquele local
		printf("\n %d", EnderecarLocal(graf, listaLocal));
		printf("\n %d", ListarTransportesPorVertice(graf, listaTransportes));
		
		//Salvo o Grafo
		printf("\n %d", SalvarGrafoBinario(graf,"Data/grafo.bin"));
	} else {
		printf("\nErro: Não foi possível criar o grafo!");
	}

	
	//Cria uma solu��o DFS do melhor caminho a percorrer
	// melhorSol = DFS(graf, 0, melhorSol); // Comentado: tipos incompatíveis

	return 0;
}