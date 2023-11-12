#ifndef FUNCOES_FICHEIROS_H_INCLUDED
#define FUNCOES_FICHEIROS_H_INCLUDED

#include "funcoes_auxiliares.h"

void gravarFicheiroBinario (tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis, tipoRequisicao vetorRequisicoes[], int totalRequisicoes, int ultimaDevolucao);
tipoRequisicao *lerFicheiroBinario (tipoPortatil vetorPortateis[MAX_PORTATEIS], int *totalPortateis, tipoRequisicao vetorRequisicoes[], int *totalRequisicoes, int *ultimaDevolucao);
void gravarFicheiroAvariasBinario (tipoAvaria vetorAvarias[], int totalAvarias);
tipoAvaria *lerFicheiroAvariasBinario (tipoAvaria vetorAvarias[], int *totalAvarias);

void logRequisicao (tipoRequisicao requisicao, tipoPortatil portatil);
void logProlongarRequisicao (tipoRequisicao requisicao, tipoPortatil portatil, int diasAcrescentar);
void logDevolucao (tipoRequisicao requisicao, tipoPortatil portatil, int totalDias);

#endif // FUNCOES_FICHEIROS_H_INCLUDED
