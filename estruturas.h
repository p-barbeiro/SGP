#ifndef SGP_ESTRUTURAS_H_INCLUDED
#define SGP_ESTRUTURAS_H_INCLUDED

#include "constantes.h"

typedef struct {
	int dia;
	int mes;
	int ano;
} tipoData;

typedef struct {
	int tipo; // 0 - Temporaria / 1 - Permanente
	int idPortatil;
	tipoData dataAvaria;
	tipoData dataReparacao;
	int duracao;
} tipoAvaria;

typedef struct {
	int id; // ID tipo 22XXX
	char designacao[MAX_STRING];
	int processador;
	int ram;
	int estado; // 0 - Disponivel / 1 - Reservado / 2 - Avariado / 3 - Avariado Permanente
	char localizacao[MAX_STRING];
	tipoData dataAquisicao;
	float valor;
	int contadorRequisicoes;
	int contadorAvarias;
	int contadorDias;
} tipoPortatil;

typedef struct {
	// REQUISICAO
	char id[MAX_STRING];             // ID tipo REQXXX
	int idPortatil;                     // ID tipo 22XXX
	char nomeUtente[MAX_STRING];     // Nome do utente
	int tipoUtente;                     // 1 - Estudante / 2 - Docente / 3 - Tecnico administrativo
	tipoData dataRequisicao;            // AAAA/MM/DD
	int prazoRequisicao;                // Max 30 dias + Renovacao 7 em 7 dias
	int estadoRequisicao;               // 0 - Concluida / 1 - Ativa
	// DEVOLUCAO
	tipoData dataDevolucao;             // AAAA/MM/DD
	char localizacao[MAX_STRING];    // Residencias / Campus1 / Campus2 / Campus5
	float multa;                        // 0.00 EUR
} tipoRequisicao;

#endif // SGP_ESTRUTURAS_H_INCLUDED
