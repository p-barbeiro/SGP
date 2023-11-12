#ifndef FUNCOES_REQUISOES_H_INCLUDED
#define FUNCOES_REQUISOES_H_INCLUDED

#include "estruturas.h"

tipoRequisicao lerDadosRequisicao (tipoPortatil portatil, int nrRequisicao);
int lerTipoUtente (void);
int procurarRequisicao (tipoRequisicao vetorRequisicoes[], int totalRequisicoes);
int updateRequisicoesAtivas (tipoRequisicao vetorRequisicoes[], int totalRequisicoes);

tipoRequisicao* adicionarRequisicao (tipoRequisicao vetorRequisicoes[], int *reservasEfetuadas, tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis, int *nrRequisicao);
void prolongarRequisicao (tipoRequisicao vetorRequisicoes[], int totalRequisicoes, tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis);
int adicionarDevolucao (tipoRequisicao vetorRequisicoes[], int *totalRequisicoes, tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis);

void listarRequisicoes (tipoRequisicao vetorRequisicoes[], int totalRequisicoes);
void listarRequisicoesDetalhe (tipoRequisicao vetorRequisicoes[], int totalRequisicoes, tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis);
void listarRequisicoesAtivas (tipoRequisicao vetorRequisicoes[], int totalRequisicoes);
void mostrarRequisicao (tipoRequisicao requisicao);
void mostrarResumoRequisicao (tipoRequisicao requisicao);

#endif // FUNCOES_REQUISOES_H_INCLUDED
