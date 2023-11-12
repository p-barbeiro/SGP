#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes_estatisticas.h"
#include "funcoes_portateis.h"
#include "funcoes_requisicoes.h"
#include "funcoes_auxiliares.h"

// Percetangem de tipos de Processadores
void percentagemProcessadores (tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis, float *percetagemI3, float *percetagemI5, float *percetagemI7) {

	int indiceEstatisticas = 0, contadorI7 = 0, contadorI3 = 0, contadorI5 = 0;

	for (indiceEstatisticas = 0; indiceEstatisticas < totalPortateis; indiceEstatisticas++) {
		if (vetorPortateis[indiceEstatisticas].processador == PROCESSADOR_I3) {
			contadorI3++;
		} else {
			if (vetorPortateis[indiceEstatisticas].processador == PROCESSADOR_I5) {
				contadorI5++;
			} else {
				if (vetorPortateis[indiceEstatisticas].processador == PROCESSADOR_I7) {
					contadorI7++;
				}
			}
		}
	}
	*percetagemI3 = (float) (contadorI3 * 100) / totalPortateis;
	*percetagemI5 = (float) (contadorI5 * 100) / totalPortateis;
	*percetagemI7 = (float) (contadorI7 * 100) / totalPortateis;
}

// Tipo de utente com menor requisicao
void  tipoUtenteMenorRequisicao (tipoRequisicao vetorRequisicao[], int totalRequisicoes) {

	int indice = 0, contadorEstudante = 0, contadorDocente = 0, contadorAdmin = 0, menor = 0, auxiliar = 0;

	for (indice = 0; indice < totalRequisicoes; indice ++) {
		if (vetorRequisicao[indice].tipoUtente == TIPO_ESTUDANTE) {
			contadorEstudante++;
		} else {
			if (vetorRequisicao[indice].tipoUtente == TIPO_DOCENTE) {
				contadorDocente++;
			} else {
				if (vetorRequisicao[indice].tipoUtente == TIPO_ADMIN) {
					contadorAdmin++;
				}
			}
		}
	}

	if (contadorEstudante >= contadorDocente) {
		menor = contadorDocente;
	} else {
		menor = contadorEstudante;
	}
	if (menor >= contadorAdmin) {
		menor = contadorAdmin;
	}

	printf ("    Tipo(s) de utente(s) com a menor quantidade de requisicoes efetuadas  : ");
	if (contadorEstudante == menor) {
		printf ("Estudante (%d em %d)", menor, totalRequisicoes);
		auxiliar++;
	}
	if (auxiliar > 0) {
		printf ("\n                                                                            ");
		auxiliar = 0;
	}
	if (contadorDocente == menor) {
		printf ("Docente (%d em %d)", menor, totalRequisicoes);
		auxiliar ++;
	}
	if (auxiliar > 0) {
		printf ("\n                                                                            ");
		auxiliar = 0;
	}
	if (contadorAdmin == menor) {
		printf ("Tecnico Administrativo (%d em %d)", menor, totalRequisicoes);
	}
	printf ("\n\n");
}

// Custo medio de multas
void custoMedioMultas (tipoRequisicao vetorRequisicoes[], int totalRequisicoes, float *mediaMultas) {

	int indice = 0, requisicoesConcluidas = 0;
	float somaMultas = 0.00;

	for (indice = 0; indice < totalRequisicoes; indice ++) {
		if (vetorRequisicoes[indice].estadoRequisicao == REQUISICAO_CONCLUIDA) {
			requisicoesConcluidas++;
			somaMultas += vetorRequisicoes[indice].multa;
		}
	}

	if (requisicoesConcluidas != 0) {
		*mediaMultas = somaMultas / requisicoesConcluidas;
	}
}

void ultimasDevolucoes (tipoRequisicao vetorRequisicoes[], int totalRequisicoes) {

	// data mais recente é a data com o nr de dias maior;

	int indice, dataMaisRecente = 0, dataAuxiliar, dataComparacao;
	int contadorDevolucoes = 0;

	for (indice = 0; indice < totalRequisicoes; indice++) {
		if (vetorRequisicoes[indice].estadoRequisicao == REQUISICAO_CONCLUIDA) {
			contadorDevolucoes++;
		}
	}

    if(contadorDevolucoes==0){
        printf ("    Nenhum portatil foi devolvido ate ao momento!\n");
    }else{

	for (indice = 0; indice < totalRequisicoes; indice++) {
		if (vetorRequisicoes[indice].estadoRequisicao == REQUISICAO_CONCLUIDA) {
			dataAuxiliar = calcularNrDeDiasDesdeAnoRef (vetorRequisicoes[indice].dataDevolucao);
			if (dataAuxiliar > dataMaisRecente) {
				dataMaisRecente = dataAuxiliar;
			}
		}
	}

	for (indice = 0; indice < totalRequisicoes; indice++) {
		if (vetorRequisicoes[indice].estadoRequisicao == REQUISICAO_CONCLUIDA) {
			dataComparacao = calcularNrDeDiasDesdeAnoRef (vetorRequisicoes[indice].dataDevolucao);
			if (dataComparacao == dataMaisRecente) {
				printf ("    ID : %s | ID Portatil : %d | %s, ", vetorRequisicoes[indice].id, vetorRequisicoes[indice].idPortatil, vetorRequisicoes[indice].nomeUtente);
				if (vetorRequisicoes[indice].tipoUtente == TIPO_ESTUDANTE) {
					printf ("Estudante");
				} else {
					if (vetorRequisicoes[indice].tipoUtente == TIPO_DOCENTE) {
						printf ("Docente");
					} else {
						printf ("Tecnico Administrativo");
					}
				}
				printf (" | Data de devolucao : %02d/%02d/%04d\n", vetorRequisicoes[indice].dataDevolucao.dia, vetorRequisicoes[indice].dataDevolucao.mes, vetorRequisicoes[indice].dataDevolucao.ano);
			}
		}
	 }
   }
}
