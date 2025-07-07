/**

 * @file   Transporte.h
 * @brief  informa��es dos transportes
 *
 * @author italo
 * @date   March 2023

**/

#include "platform.h"

#include "Consts.h"

#ifndef LOCALIZACAO_H
#define LOCALIZACAO_H


typedef struct Localizacao Local;
typedef struct ListaLocalizacao ListaLocal;

//Assinaturas das fun��es
char* EncontrarLocal(ListaLocal* lista, int id);

bool AdicionarLocal(ListaLocal** lista, Local localAtual);
bool AdicionarLocalPorGeocode(ListaLocal** lista, char* geocode, int id);
bool RemoverLocal(ListaLocal** lista, ListaLocal* localAtual);
bool TrocarLocal(ListaLocal* transporte1, ListaLocal* transporte2);
bool EditarLocal(ListaLocal* lista, Local transporteEditado);
bool OrganizarLocalPorID(ListaLocal* lista);

int LerFileLocal(ListaLocal** lista);
int SalvarFileLocal(ListaLocal* lista);

//Struct de dados
struct Localizacao {
	int id;
	char geocode[STRG];
	char nome[STRG];
};

struct ListaLocalizacao {
	Local local;
	ListaLocal* anter;
	ListaLocal* prox;
};

#endif
