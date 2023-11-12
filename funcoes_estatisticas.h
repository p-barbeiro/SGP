#ifndef FUNCOES_ESTATISTICAS_H_INCLUDED
#define FUNCOES_ESTATISTICAS_H_INCLUDED

#include "funcoes_requisicoes.h"

void percentagemProcessadores(tipoPortatil vetorPortateis[MAX_PORTATEIS],int totalPortateis, float *percetagemI3 , float *percetagemI5, float *percetagemI7);
void tipoUtenteMenorRequisicao(tipoRequisicao vetorRequisicoes[] ,int totalRequisicoes);
void custoMedioMultas (tipoRequisicao vetorRequisicoes[],int totalRequisicoes, float *mediaMultas);
void ultimasDevolucoes (tipoRequisicao vetorRequisicoes[], int totalRequisicoes);

#endif // FUNCOES_ESTATISTICAS_H_INCLUDED
