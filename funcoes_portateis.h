#ifndef FUNCOES_PORTATEIS_H_INCLUDED
#define FUNCOES_PORTATEIS_H_INCLUDED

#include "funcoes_requisicoes.h"

int updatePortateisDisponiveis (tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis);

void adicionarPortatil (tipoPortatil vetorPortateis[MAX_PORTATEIS], int *totalPortateis);
void alterarLocalizacaoPortatil (tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis);
void lerLocalizacao (char mensagem [MAX_STRING], char vetorCaracteres[MAX_STRING]);
char repetirAdicionarPortatil (void);
int lerProcessador (void);

int procuraPortatil (tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis, int idPortatil);

void listarPortateis (tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis);
void listarPortateisPorEstado (char mensagem[MAX_STRING],tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis, int estado);
void listarPortatilDetalhe (tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis, tipoRequisicao vetorRequisicoes[], int totalRequisicoes);
void mostrarPortatil (tipoPortatil portatil);

#endif // FUNCOES_PORTATEIS_H_INCLUDED
