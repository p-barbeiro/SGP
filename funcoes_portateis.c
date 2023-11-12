#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes_portateis.h"
#include "funcoes_requisicoes.h"
#include "funcoes_auxiliares.h"

void adicionarPortatil (tipoPortatil vetorPortateis[MAX_PORTATEIS], int *totalPortateis) {

	char opcaoRepetirAdicionarPortatil;
	int posicaoVetor;

	if (*totalPortateis < MAX_PORTATEIS) {

		limparEcra();

		printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n");
		printf ("                                          Adicionar novo portatil                                         \n");
		printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");

		do {
			do {
				vetorPortateis[*totalPortateis].id = lerInteiro ("\t> ID Portatil (22XXX) : ", 22000, 22999);
				posicaoVetor = procuraPortatil (vetorPortateis, *totalPortateis, vetorPortateis[*totalPortateis].id);

				if (posicaoVetor != NAO_ENCONTRADO) {
					printf ("\n\t\tO Portatil introduzido ja existe no sistema. Tente novamente.\n\n");
				}
			} while (posicaoVetor != NAO_ENCONTRADO);

			lerString ("\t> Designacao : ", vetorPortateis[*totalPortateis].designacao, MAX_STRING);
			vetorPortateis[*totalPortateis].processador = lerProcessador();
			vetorPortateis[*totalPortateis].ram = lerInteiro ("\t> Memoria RAM : ", MIN_RAM, MAX_RAM);
			vetorPortateis[*totalPortateis].estado = PORTATIL_DISPONIVEL; // A primeira vez que se adiciona o portatil, ele fica automaticamente disponivel.
			printf ("\t> Data de aquisicao : \n");
			vetorPortateis[*totalPortateis].dataAquisicao = lerData();
			lerLocalizacao ("\t> Localizacao :\n", vetorPortateis[*totalPortateis].localizacao);
			vetorPortateis[*totalPortateis].valor = lerFloat ("\t> Valor do Portatil : ", 0, 9999.99);
			printf ("\nmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");

			(*totalPortateis)++;

			printf ("\tPortatil adicionado com sucesso !\n\n");

			if (*totalPortateis < MAX_PORTATEIS) {
				opcaoRepetirAdicionarPortatil = repetirAdicionarPortatil();
			} else {
				printf ("\t* AVISO *\n\tAtingiu o limite de portateis que podem ser adicionados!\n\n");
				enterParaContinuar();
			}

		} while (opcaoRepetirAdicionarPortatil == 'S' && *totalPortateis < MAX_PORTATEIS);
	} else {
		printf ("\tAtingiu o limite de portateis que podem ser adicionados ao sistema!\n\n");
		enterParaContinuar();
	}
}

char repetirAdicionarPortatil (void) {

	char opcaoRepetirAdicionarPortatil;

	printf ("\tDeseja adicionar mais um portatil ?\n\t[S]im / [N]ao  :  ");
	do {
		opcaoRepetirAdicionarPortatil = lerCaracter();
		switch (opcaoRepetirAdicionarPortatil) {
		case 'S':
			printf ("\nmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");
			break;

		case 'N':
			break;

		default:
			printf ("\n\tOpcao invalida. Tente novamente.\n\t[S]im para adicionar novo portatil\n\t[N]ao para voltar ao menu principal ->");
		}
	} while (opcaoRepetirAdicionarPortatil != 'S' && opcaoRepetirAdicionarPortatil != 'N');

	return opcaoRepetirAdicionarPortatil;
}

int lerProcessador (void) {

	int processador;

	printf ("\t> Processador (i3, i5, i7) : i");
	do {
		processador = lerInteiroPositivo();
		if (processador != PROCESSADOR_I3 && processador != PROCESSADOR_I5 && processador != PROCESSADOR_I7) {
			printf ("\n\tProcessador invalido!\n\tIntroduza um dos processadores indicados (i[3], i[5], i[7]) : i");
		}
	} while (processador != PROCESSADOR_I3 && processador != PROCESSADOR_I5 && processador != PROCESSADOR_I7);

	return processador;
}

void lerLocalizacao (char mensagem [MAX_STRING], char vetorCaracteres[MAX_STRING]) {
	int opcao;

	printf ("%s", mensagem);
	printf ("\t\t[1] Residencias\n");
	printf ("\t\t[2] Campus1\n");
	printf ("\t\t[3] Campus2\n");
	printf ("\t\t[4] Campus5\n");
	opcao = lerInteiro ("\t\t\tIntroduza a opcao -> ", 1, 4);

	switch (opcao) {
	case 1:
		strcpy (vetorCaracteres, "Residencias");
		break;

	case 2:
		strcpy (vetorCaracteres, "Campus1");
		break;

	case 3:
		strcpy (vetorCaracteres, "Campus2");
		break;

	case 4:
		strcpy (vetorCaracteres, "Campus5");
		break;

	default:
		printf ("\n\tOpcao invalida. Tente novamente.\n");
		break;
	}

}

void mostrarPortatil (tipoPortatil portatil) {

	printf (" %-6d|", portatil.id);
	printf (" %-30s |", portatil.designacao);
	printf (" i%1d  |", portatil.processador);
	printf (" %-3dGB |", portatil.ram);
	if (portatil.estado == PORTATIL_DISPONIVEL) {
		printf (" Disponivel  ");
	} else {
		if (portatil.estado == PORTATIL_REQUISITADO) {
			printf (" Requisitado ");
		} else {
			if (portatil.estado == PORTATIL_AVARIADO_TEMPORARIAMENTE) {
				printf (" Avariado(T) ");
			} else {
				printf (" Avariado(P) ");
			}
		}
	}
	printf ("| %04d/%02d/%02d |", portatil.dataAquisicao.ano, portatil.dataAquisicao.mes, portatil.dataAquisicao.dia);
	printf (" %-11s |", portatil.localizacao);
	printf (" %-7.2f EUR \n", portatil.valor);
}

void listarPortateis (tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis) {

	int indicePortatil;

	if (totalPortateis == 0) {
		printf ("\tNao existem portateis no sistema.\n");
		printf ("\tAdicione portateis utilizando a opcao de [Adicionar portatil].\n\n");
	} else {
		limparEcra();
		printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n");
		printf (" ID    | Designacao                     | CPU | RAM   | Estado      | Aquisicao  | Localizacao | Valor      \n");
		printf ("------------------------------------------------------------------------------------------------------------\n");
		for (indicePortatil = 0; indicePortatil < totalPortateis; indicePortatil++) {
			mostrarPortatil (vetorPortateis[indicePortatil]);
		}
	}
	printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");
}

void listarPortateisPorEstado (char mensagem[MAX_STRING], tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis, int estado) {

	int indicePortatil;

	printf ("\n\t%s", mensagem);
	printf ("\n\t--------------------------------------------------------------------------------------------\n");

	for (indicePortatil = 0; indicePortatil < totalPortateis; indicePortatil++) {
		if (vetorPortateis[indicePortatil].estado == estado) {
			printf ("\tID: %d | %s, i%d, %dGB, localizacao : %s \n", vetorPortateis[indicePortatil].id, vetorPortateis[indicePortatil].designacao, vetorPortateis[indicePortatil].processador, vetorPortateis[indicePortatil].ram, vetorPortateis[indicePortatil].localizacao);
		}
	}

	printf ("\t--------------------------------------------------------------------------------------------\n\n");
}

int procuraPortatil (tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis, int idPortatil) {

	int indicePortatil;
	int posicaoVetor = NAO_ENCONTRADO; // devolve -1 se nao encontrar

	for (indicePortatil = 0; indicePortatil < totalPortateis; indicePortatil++) {
		if (vetorPortateis[indicePortatil].id == idPortatil) {
			posicaoVetor = indicePortatil;
			indicePortatil = totalPortateis;
		}
	}

	return posicaoVetor;
}

void alterarLocalizacaoPortatil (tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis) {

	int posicaoVetor = NAO_ENCONTRADO;
	int idPortatil;
	char novaLocalizacao[MAX_STRING];
	int comparacao;
	int portateisDisponiveis = 0;

	portateisDisponiveis = updatePortateisDisponiveis (vetorPortateis, totalPortateis);

	if (totalPortateis == 0) {
		printf ("\tNao existem portateis no sistema.\n");
		printf ("\tAdicione portateis utilizando a opcao de [Adicionar portatil].\n\n");
	} else {
		if (portateisDisponiveis==0) {
            printf ("\tNao existem portateis disponiveis.\n");
		} else {
			listarPortateisPorEstado ("\n\tPortateis disponiveis : ", vetorPortateis, totalPortateis, PORTATIL_DISPONIVEL);
			idPortatil = lerInteiro ("\t> Introduza o ID do portatil para o qual deseja alterar a localizacao : ", 22000, 22999);
			posicaoVetor = procuraPortatil (vetorPortateis, totalPortateis, idPortatil);

			if (posicaoVetor == NAO_ENCONTRADO) {
				printf ("\n\tO portatil indicado nao se encontra no sistema.\n\n");
			} else {
				if (vetorPortateis[posicaoVetor].estado == PORTATIL_REQUISITADO) {
					printf ("\n\tO portatil indicado encontra-se requisitado. Impossivel alterar localizacao!\n\n");
				} else {
					lerLocalizacao ("\t> Nova localizacao :\n", novaLocalizacao);
					comparacao = strcmp (vetorPortateis[posicaoVetor].localizacao, novaLocalizacao);

					if (comparacao == 0) {
						printf ("\n\tNao foram efetuadas alteracoes.\n\n");
						printf ("\n\tNova localizacao igual a localizacao atual.");
					} else {
						strcpy (vetorPortateis[posicaoVetor].localizacao, novaLocalizacao);
						printf ("\n\tAlteracao efetuada com sucesso!\n\n");
					}
				}
			}
		}
	}
}

int updatePortateisDisponiveis (tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis) {

	int indice, portateisDisponiveis = 0;

	for (indice = 0; indice < totalPortateis ; indice++) {
		if (vetorPortateis[indice].estado == PORTATIL_DISPONIVEL) {
			portateisDisponiveis++;
		}
	}

	return portateisDisponiveis;
}

void listarPortatilDetalhe (tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis, tipoRequisicao vetorRequisicoes[], int totalRequisicoes) {

	int indice = 0,
        posicaoVetor = NAO_ENCONTRADO,
        portatilID = 0;

	portatilID = lerInteiro ("\t> Introduza o ID do portatil a procurar (22XXX) : ", 22000, 22999);
	posicaoVetor = procuraPortatil (vetorPortateis, totalPortateis, portatilID);

	if (posicaoVetor == -1) {
		printf ("\n\tO portatil indicado nao se encontra no sistema.\n\n");
	} else {
		limparEcra();
		printf ("\nmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n");
		printf (" ID    | Designacao                     | CPU | RAM   | Estado      | Aquisicao  | Localizacao | Valor      \n");
		printf ("------------------------------------------------------------------------------------------------------------\n");
		mostrarPortatil (vetorPortateis[posicaoVetor]);

		printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");
		printf (" Quantidade de requisicoes : %d", vetorPortateis[posicaoVetor].contadorRequisicoes);
		printf ("                                                   Quantidade de avarias : %3d\n\n", vetorPortateis[posicaoVetor].contadorAvarias);
		if (totalRequisicoes > 0) {
//			printf (" Requisicoes:\n\n");
			for (indice = 0; indice < totalRequisicoes; indice ++) {
				if (vetorRequisicoes[indice].idPortatil == portatilID) {
					mostrarRequisicao (vetorRequisicoes[indice]);
				}
			}
			printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");
		} else {
			printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");
		}
	}
}
