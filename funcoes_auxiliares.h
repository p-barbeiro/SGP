#ifndef FUNCOES_AUXILIARES_H_INCLUDED
#define FUNCOES_AUXILIARES_H_INCLUDED

#include "constantes.h"
#include "estruturas.h"

char lerCaracter (void);
int lerInteiro (char mensagem[MAX_STRING], int minimo, int maximo);
float lerFloat (char mensagem[MAX_STRING], float minimo, float maximo);
void lerString (char mensagem[MAX_STRING], char vetorCaracteres[MAX_STRING], int maximoCaracteres);
void limpaBufferStdin (void);
int lerInteiroPositivo (void);
void enterParaContinuar (void);
void limparEcra (void);

tipoData lerData (void);
int calcularNrDiasEntreDatas (tipoData dataInicial, tipoData dataFinal);
int calcularNrDeDiasDesdeAnoRef (tipoData data);
int calcularMaximoDiasPorAno (int ano);
int calcularMaximoDiasPorMes (int mes, int ano);
tipoData calcularDataAtravesDosDias (int totalDeDias);
tipoData calcularDataAposXDias (tipoData data, int dia);

#endif // FUNCOES_AUXILIARES_H_INCLUDED
