#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "funcoes_avarias.h"
#include "funcoes_auxiliares.h"
#include "funcoes_requisicoes.h"
#include "funcoes_portateis.h"

int lerTipoAvaria (char mensagem [MAX_STRING]) {

	int opcao;

	printf ("%s", mensagem);
	printf ("\t\t[1] Avaria temporaria\n");
	printf ("\t\t[2] Avaria permanente\n");
	opcao = lerInteiro ("\t\t\tIntroduza a opcao -> ", 1, 2);

	return opcao;
}

tipoAvaria *adicionarAvaria (tipoAvaria vetorAvarias[], int *totalAvarias,
                             tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis) {

	tipoAvaria *ponteiroAuxiliar;
	int idPortatil = 0, posicaoVetorPortateis = 0;
	int portateisDisponiveis = 0;

    portateisDisponiveis = updatePortateisDisponiveis (vetorPortateis, totalPortateis);

	if (totalPortateis == 0) {
		printf ("\tNao existem portateis no sistema.\n");
		printf ("\tAdicione portateis utilizando a opcao de [Adicionar portatil].\n\n");
	} else {
		if (portateisDisponiveis == 0) {
		printf ("\tNao existem portateis disponiveis no sistema.\n");
		} else {
		    // procura portatil e retorna posicao do vetor de portateis
			idPortatil = lerInteiro ("\t> Introduza o ID do portatil (22XXX) : ", 22000, 22999);
			posicaoVetorPortateis = procuraPortatil (vetorPortateis, totalPortateis, idPortatil);
			if (posicaoVetorPortateis == NAO_ENCONTRADO) {
				printf ("\n\tO portatil indicado nao se encontra no sistema.\n\n");
			} else {
				if (vetorPortateis[posicaoVetorPortateis].estado == PORTATIL_REQUISITADO) {
					printf ("\n\tO portatil indicado encontra-se requisitado. Por favor efetue a devolucao primeiro!\n\n");
				} else {
					ponteiroAuxiliar = vetorAvarias;
					vetorAvarias = realloc (vetorAvarias, (*totalAvarias + 1) * sizeof (tipoAvaria));
					if (vetorAvarias == NULL) {
						printf ("\t*ERRO* Nao foi possivel alocar memoria!\n");
						vetorAvarias = ponteiroAuxiliar;
					} else {
						// introduzir avaria
						vetorAvarias[*totalAvarias].tipo = lerTipoAvaria ("\t> Introduza o tipo de avaria : \n");
						vetorAvarias[*totalAvarias].idPortatil = idPortatil;
						printf ("\t> Introduza a data de avaria : \n");
						vetorAvarias[*totalAvarias].dataAvaria = lerData();
						vetorAvarias[*totalAvarias].duracao = NAO_ENCONTRADO; // -1 significa que ainda nao entregou - ativo
						// atualiza contadores
						if (vetorAvarias[*totalAvarias].tipo == AVARIA_TEMPORARIA) {
							vetorPortateis[posicaoVetorPortateis].estado = PORTATIL_AVARIADO_TEMPORARIAMENTE;
						} else {
							vetorPortateis[posicaoVetorPortateis].estado = PORTATIL_AVARIADO_PERMANENTEMENTE;
						}
						vetorPortateis[posicaoVetorPortateis].contadorAvarias++;
						(*totalAvarias)++;

						printf ("\n\tAvaria registada com sucesso.\n\tO estado do portatil %d passou para avariado.\n\n", vetorPortateis[posicaoVetorPortateis].id);
					}
				}
			}
		}
	}
	return vetorAvarias;
}

void adicionarReparacao (tipoAvaria vetorAvarias[], int totalAvarias, tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis) {

	int idPortatil, indice;
	int posicaoVetorAvarias=NAO_ENCONTRADO, posicaoVetorPortateis=NAO_ENCONTRADO;
	int portateisComAvariaTemporaria = 0, portateisComAvariaPermanente = 0;
	int diferencaDias;

	for (indice = 0; indice < totalAvarias; indice++) {
		if (vetorAvarias[indice].tipo == AVARIA_TEMPORARIA) {
			portateisComAvariaTemporaria++;
		}
		if (vetorAvarias[indice].tipo == AVARIA_PERMANENTE) {
			portateisComAvariaPermanente++;
		}
	}
	if (portateisComAvariaTemporaria == 0 && portateisComAvariaPermanente == 0) {
		printf ("\tNao existem portateis avariados.\n\n");
	} else {
		if (portateisComAvariaTemporaria == 0  && portateisComAvariaPermanente > 0) {
			printf ("\tOs portateis encontrados nao tem reparacao!\n\n");
		} else {
			listarPortateisPorEstado ("Portateis avariados:", vetorPortateis, totalPortateis, PORTATIL_AVARIADO_TEMPORARIAMENTE);
			idPortatil = lerInteiro ("\t> Introduza o ID do portatil : ", 22000, 22999);
			posicaoVetorPortateis = procuraPortatil (vetorPortateis, totalPortateis, idPortatil);
			if (posicaoVetorPortateis == NAO_ENCONTRADO) {
				printf ("\n\tO Portatil introduzido nao existe no sistema. \n\n");
			} else {
				posicaoVetorAvarias = procurarAvaria (vetorAvarias, totalAvarias, idPortatil);
				if (posicaoVetorAvarias == NAO_ENCONTRADO) {
					printf ("\n\tNao existe avaria / reparacao para o portatil indicado\n\n");
				} else {
					printf ("\n\t--------------------------------------------------------------------------------------------\n\tResumo : ");
					mostrarAvaria (vetorAvarias[posicaoVetorAvarias]);
					printf ("\t--------------------------------------------------------------------------------------------\n");
					printf ("\n\t> Introduza a data de reparacao : \n");
					do {
						vetorAvarias[posicaoVetorAvarias].dataReparacao = lerData();
						diferencaDias = calcularNrDiasEntreDatas (vetorAvarias[posicaoVetorAvarias].dataAvaria, vetorAvarias[posicaoVetorAvarias].dataReparacao);
						if (diferencaDias < 0) {
							printf ("\n\t*ERRO* Data de reparacao anterior a data de avaria! Tente novamente.\n\n");
						}
					} while (diferencaDias < 0);
					vetorAvarias[posicaoVetorAvarias].duracao = diferencaDias;
					vetorAvarias[posicaoVetorAvarias].tipo = AVARIA_REPARADA;
					vetorPortateis[posicaoVetorPortateis].estado = PORTATIL_DISPONIVEL;
					printf ("\n\tReparacao registada com sucesso! O portatil %d voltou a estar disponivel.\n\n", vetorPortateis[posicaoVetorPortateis].id);
				}
			}
		}
	}
}

int procurarAvaria (tipoAvaria vetorAvarias[], int totalAvarias, int idPortatil) {

	int posicao = NAO_ENCONTRADO;
	int indice;

	for (indice = 0 ; indice < totalAvarias; indice++) {
		if (vetorAvarias[indice].idPortatil == idPortatil && vetorAvarias[indice].tipo == AVARIA_TEMPORARIA) {
			posicao = indice;
			indice = totalAvarias;
		}
	}
	return posicao;
}

void listarAvarias (tipoAvaria vetorAvarias[], int totalAvarias, tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis) {
	int indice;
	int posicaoVetorPortateis=NAO_ENCONTRADO;

	if (totalAvarias == 0) {
		printf ("\tNao existem avarias registadas no sistema.\n\n");
	} else {
		limparEcra();
		printf (" LISTAGEM DE AVARIAS\n");
		for (indice = 0; indice < totalAvarias; indice++) {
			posicaoVetorPortateis = procuraPortatil (vetorPortateis, totalPortateis, vetorAvarias[indice].idPortatil);
			printf ("------------------------------------------------------------------------------------------------------------\n");
			printf (" ID Portatil: %d | %s, i%d, %dGB \n", vetorPortateis[posicaoVetorPortateis].id, vetorPortateis[posicaoVetorPortateis].designacao, vetorPortateis[posicaoVetorPortateis].processador, vetorPortateis[posicaoVetorPortateis].ram);
			mostrarAvaria (vetorAvarias[indice]);
		}
		printf ("------------------------------------------------------------------------------------------------------------\n");
	}
}

void mostrarAvaria (tipoAvaria avaria) {

	if (avaria.tipo == AVARIA_PERMANENTE) {
		printf (" Avaria permanente  ");
	} else {
		printf (" Avaria temporaria  ");
	}
	printf ("| Data da avaria : %02d/%02d/%04d ", avaria.dataAvaria.dia, avaria.dataAvaria.mes, avaria.dataAvaria.ano);
	if (avaria.duracao == NAO_ENCONTRADO) {
		printf ("| Estado: Avariado \n");
	} else {
		printf ("| Estado: Reparado ");
		printf ("| Data : %02d/%02d/%04d ", avaria.dataReparacao.dia, avaria.dataReparacao.mes, avaria.dataReparacao.ano);
		printf ("| Duracao : %d dias\n", avaria.duracao);
	}
}
