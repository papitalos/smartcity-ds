/**

 * @file   Gestor.h
 * @brief  informa��es dos gestores
 *
 * @author italo
 * @date   March 2023

**/

#include "platform.h"

#include "Consts.h"

#ifndef GESTOR_H
#define GESTOR_H

typedef struct Gestor Gestor;
typedef struct ListaGestor ListaGestor;

//assinaturas das fun��es
ListaGestor* EncontrarGestor(ListaGestor* lista, int id);

bool AdicionarGestor(ListaGestor** lista, Gestor gestorAtual);
bool RemoverGestor(ListaGestor** lista, ListaGestor* gestorAtual);
bool OrganizarGestorPorID(ListaGestor* lista);
bool EditarGestor(ListaGestor* lista, Gestor gestorEditado);
bool TrocarGestor(ListaGestor* gestor1, ListaGestor* gestor2);

int LerFileGestor(ListaGestor** lista);
int SalvarFileGestor(ListaGestor* lista);

//struct de dados
struct Gestor {
	int id;
	char nome[STRM];
	char email[STRG];
	char senha[STRP];
};

struct ListaGestor {
	Gestor gestor;
	ListaGestor* anter;
	ListaGestor* prox;
};

#endif
