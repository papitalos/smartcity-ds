/** 
 
 * @file   Cliente.c
 * @brief  arquivo de manipula��o de dados de clientes
 * 
 * @author italo
 * @date   March 2023
 
**/

#include "platform.h"
#include "Cliente.h"

bool AdicionarCliente(ListaCliente** lista, Cliente clienteAtual) {

	//aloca espa�o para um novo n� para a lista de clientes e verifica se funcionou
	ListaCliente* newCliente = (ListaCliente*)malloc(sizeof(ListaCliente));
	if (newCliente == NULL) {
		free(newCliente);
		return false;
	}

	//coloca esse novo n� com o cliente atual e inicializa o cliente proximo e anterior como nulo
	newCliente->cliente = clienteAtual;
	newCliente->anter = NULL;
	newCliente->prox = NULL;

	//verifica se a lista est� nula (o que significa q � a primeira vez q estamos adicionando a lista)
	if (*lista == NULL) {
		//a lista passa a ser o novo e unico cliente
		*lista = newCliente;
		return true;
	}

	//percorre a lista para encadear no ultimo n�
	ListaCliente* ultimo_cliente = *lista;
	while (ultimo_cliente->prox != NULL) {
		ultimo_cliente = ultimo_cliente->prox;
	}

	//proximo depois do ultimo passa a ser o novo cliente
	ultimo_cliente->prox = newCliente;

	//anterior depois do novo cliente passa a ser o ultimo
	ultimo_cliente->prox->anter = ultimo_cliente;

	return true;
}
bool RemoverCliente(ListaCliente** lista, ListaCliente* clienteAtual) {

	//se cliente atual nao existe retorna falso pois nao existe cliente pra remover
	if (clienteAtual == NULL) return false;

	//se for o primeiro elemento da lista
	if (*lista == clienteAtual) {
		//lista passa a come�ar pelo proximo 
		*lista = clienteAtual->prox;
		//anterior fica nulo
		(*lista)->anter = NULL;
	}
	else {
		//ajusta as liga��es dos n�s todas
		if (clienteAtual->anter != NULL) {
			clienteAtual->anter->prox = clienteAtual->prox;
		}		
		if (clienteAtual->prox != NULL) {
			clienteAtual->prox->anter = clienteAtual->anter;
		}
			
	}

	//libera a memoria do cliente a remover
	free(clienteAtual);

	return true;
}
bool TrocarCliente(ListaCliente* cliente1, ListaCliente* cliente2) {
	//cria um cliente auxiliar
	Cliente aux = cliente1->cliente;

	//espa�o na memoria onde armazena cliente1 passa a armazenar cliente2
	cliente1->cliente = cliente2->cliente;

	//cliente2 recebe auxiliar
	cliente2->cliente = aux;

	return 1;
}
bool EditarCliente(ListaCliente* lista, Cliente clienteEditado) {

	//verifica se lista � nula, se for, significa que o n� fornecido � invalido
	if (lista == NULL) return false;


	//se a lista for n�o for nula, faz a troca do cliente pelo clienteEditado
	lista->cliente = clienteEditado;

	return true;
}
bool OrganizarClientePorID(ListaCliente* lista) {

	//verifica se lista � nula, se for, significa que o n� fornecido � invalido
	if (lista == NULL) return false;

	//cria��o de uma variavel de controle e a lista a percorrer
	bool terminou = false;
	ListaCliente* listaAtual = NULL;

	//enquanto n�o terminar de trocar os clientes
	while (!terminou)
	{
		//inicializa a lista
		listaAtual = lista;

		//percorre ate o penultimo elemento da lista
		while (listaAtual->prox != NULL)
		{
			//se o id do cliente atual for maior que o id do proximo cliente
			if (listaAtual->cliente.id > listaAtual->prox->cliente.id) {
				//usa a fun��o trocar clientes
				TrocarCliente(listaAtual, listaAtual->prox);
				terminou = false;
			}
			//passa pro proximo da lista
			listaAtual = listaAtual->prox;
		}
		//termina
		terminou = true;
	}
	return true;
}

ListaCliente* EncontrarCliente(ListaCliente* lista, int id) {

	//verifica se a lista esta vazia se sim retorna vazio
	if (lista == NULL) return NULL;

	//inicializa a lista
	ListaCliente* listaAtual = lista;

	//percorre a lista
	while (listaAtual != NULL)
	{
		//se o cliente for o com o id desejado retorna cliente
		if (listaAtual->cliente.id == id) return listaAtual;

		//se nao, vai ao proximo da lista
		listaAtual = listaAtual->prox;
	}

	return NULL;
}

int LerFileCliente(ListaCliente** lista) {

	//cria um cliente vazio temporario e um apontador pro arquivo
	Cliente tempCliente = { 0 };
	FILE* file;

	//abre o arquivo no endere�o de memoria de file da localiza��o fornecida no modo r = read
	file = fopen("Data/cliente.txt", "r");

	//se file for nulo significa que nao existe o arquivo
	if (file == NULL) return 2;


	//cria um buffer para receber informa��o linha a linha
	char buffer[256];

	//enquanto a fun��o fgets (que pega informa��o linha a linah do file e armazena no buffer) for =! nula
	while (fgets(buffer, sizeof(buffer), file) != NULL)
	{
		//sscanf passa as informa�oes do buffer pra o cliente
		if (sscanf(buffer, "%d;%[^;];%[^;];%[^;];%f\n",
			&tempCliente.id, tempCliente.nome, tempCliente.nif, tempCliente.endereco, &tempCliente.saldo) != 5)
			return 3;

		//senao, adiciona cliente
		AdicionarCliente(lista, tempCliente);
	}

	fclose(file);
	return 1;
}
int SalvarFileCliente(ListaCliente* lista) {
	//se lista for nula retorna 4 (lista vazia)
	if (lista == NULL) return 4;

	//inicializa apontadores para os clientes da lista e para o file
	ListaCliente* tempCliente = lista;
	FILE* file;

	//abre o arquivo com o modo wb = write bin
	file = fopen("Data/cliente.bin", "wb");

	//retorna 2 se o arquivo nao existir
	if (file == NULL) return 2;

	//faz um primeiro save e depois passa a percorrer a lista
	do
	{
		fwrite(&(tempCliente->cliente), sizeof(ListaCliente), 1, file);//escreve no arquivo binario

		tempCliente = tempCliente->prox;

	} while (tempCliente != NULL); //enquanto o cliente for diferente de nulo

	fclose(file);
	return 1;
}