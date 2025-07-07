/** 
 
 * @file   Cliente.h
 * @brief  informa��es dos clientes
 * 
 * @author italo
 * @date   March 2023
 
**/

#include "platform.h"

#include "Consts.h"

#ifndef CLIENTE_H
#define CLIENTE_H

	typedef struct Cliente Cliente;
	typedef struct ListaCliente ListaCliente;

	//assinaturas das fun��es
	ListaCliente* EncontrarCliente(ListaCliente* lista, int id);

	bool AdicionarCliente(ListaCliente** lista, Cliente clienteAtual);
	bool RemoverCliente(ListaCliente** lista, ListaCliente* clienteAtual);
	bool OrganizarClientePorID(ListaCliente* lista);
	bool EditarCliente(ListaCliente* lista, Cliente clienteEditado);
	bool TrocarCliente(ListaCliente* cliente1, ListaCliente* cliente2);

	int LerFileCliente(ListaCliente** lista);
	int SalvarFileCliente(ListaCliente* lista);

	//struct de dados
	struct Cliente {
		int id;
		char nome[STRM];
		char nif[STRP];
		char endereco[STRG];
		float saldo;
	};

	struct ListaCliente {
		Cliente cliente;
		ListaCliente* anter;
		ListaCliente* prox;
	};

#endif