#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

#include "estruturas.h"

int lerOpcaoMenu (int minimo, int maximo);

int menuPrincipal (int totalPortateis, int portateisDisponiveis, int totalRequisicoes, int requisicoesAtivas);

int menuPortatil (void);

int menuConsultar (int totalPortateis);
int submenuConsultarPortatil (void);
int submenuConsultarRequisicao (void);

int menuRequisicaoDevolucao (int totalPortateis);
int menuRequisicao (int *totalPortateis, int *portateisDisponiveis, int totalRequisicoes, int requisicoesAtivas);

int menuAvarias (int totalPortateis);

void menuEstatisticas (tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis, tipoRequisicao vetorRequisicoes[], int totalRequisicoes);

void menuInformacoes (void);

char menuSair (void);

#endif // MENUS_H_INCLUDED
