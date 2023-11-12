#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "funcoes_auxiliares.h"
#include "funcoes_requisicoes.h"
#include "funcoes_portateis.h"
#include "funcoes_ficheiros.h"
#include "constantes.h"

int updateRequisicoesAtivas (tipoRequisicao vetorRequisicoes[], int totalRequisicoes) {

	int indice, requisicoesAtivas = 0;

	for (indice = 0; indice < totalRequisicoes; indice++) {
		if (vetorRequisicoes[indice].estadoRequisicao == REQUISICAO_ATIVA) {
			requisicoesAtivas++;
		}
	}
	return requisicoesAtivas;
}

int procurarRequisicao (tipoRequisicao vetorRequisicoes[], int totalRequisicoes) {

	int indice, comparacao, idlenght;
	int posicaoVetor = NAO_ENCONTRADO; // devolve -1 se nao encontrar
	char idRequisicao [MAX_STRING];

	lerString ("\t> Introduza o ID da requisicao : ", idRequisicao, MAX_STRING);
	idlenght = strlen (idRequisicao);
	for (indice = 0; indice < idlenght; indice++) {
		idRequisicao[indice] = toupper (idRequisicao[indice]);
	}
	for (indice = 0; indice < totalRequisicoes; indice++) {
		comparacao = strcmp (vetorRequisicoes[indice].id, idRequisicao);
		if (comparacao == 0) {
			posicaoVetor = indice;
			indice = totalRequisicoes;
		}
	}
	return posicaoVetor;
}

tipoRequisicao lerDadosRequisicao (tipoPortatil portatil, int nrRequisicao) {

	tipoRequisicao dadosRequisicao;
	int diasDataRequisicao, diasDataAquisicao;

	sprintf (dadosRequisicao.id, "REQ%03d", nrRequisicao + 1);
	dadosRequisicao.idPortatil = portatil.id;

	lerString ("\t> Nome utente : ", dadosRequisicao.nomeUtente, MAX_STRING);
	printf ("\t> Tipo utente : \n");
	dadosRequisicao.tipoUtente = lerTipoUtente();
	do {
		printf ("\t> Data de requisicao\n");
		dadosRequisicao.dataRequisicao = lerData();
		diasDataRequisicao = calcularNrDeDiasDesdeAnoRef (dadosRequisicao.dataRequisicao);
		diasDataAquisicao = calcularNrDeDiasDesdeAnoRef (portatil.dataAquisicao);
		if (diasDataRequisicao<diasDataAquisicao) {
			printf ("\n\t*ERRO*\n\tData de requisicao do portatil nao pode ser anterior a data de aquisicao do portatil (%02d/%02d/%4d)\n\n",portatil.dataAquisicao.dia,portatil.dataAquisicao.mes,portatil.dataAquisicao.ano);
		}
	} while (diasDataRequisicao<diasDataAquisicao);
	printf ("\t> Prazo requisicao [Max %d dias] : ",MAX_DIAS_REQUISICAO);
	dadosRequisicao.prazoRequisicao = lerInteiro ("", 1, MAX_DIAS_REQUISICAO);
	dadosRequisicao.dataDevolucao = calcularDataAposXDias (dadosRequisicao.dataRequisicao, dadosRequisicao.prazoRequisicao);
	dadosRequisicao.estadoRequisicao = REQUISICAO_ATIVA;
	return dadosRequisicao;
}

int lerTipoUtente (void) {

	int opcao;

	printf ("\t\t[1] Estudante\n");
	printf ("\t\t[2] Docente\n");
	printf ("\t\t[3] Tecnico administrativo\n");
	opcao = lerInteiro ("\t\t\tIntroduza a opcao -> ", 1, 3);
	return opcao;
}

tipoRequisicao* adicionarRequisicao (tipoRequisicao vetorRequisicoes[], int *totalRequisicoes, tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis, int *nrRequisicao) {

	tipoRequisicao dadosRequisicao;
	tipoRequisicao *ponteiroAuxiliar;
	int portatilID, posicaoVetor=NAO_ENCONTRADO;
	int portateisDisponiveis = 0;

    portateisDisponiveis = updatePortateisDisponiveis (vetorPortateis, totalPortateis);

	if (portateisDisponiveis != 0) {
		listarPortateisPorEstado ("Portateis disponiveis:", vetorPortateis, totalPortateis, PORTATIL_DISPONIVEL);
		portatilID = lerInteiro ("\t> Introduza o ID do portatil a requisitar : ", 22000, 22999);
		posicaoVetor = procuraPortatil (vetorPortateis, totalPortateis, portatilID);
		if (posicaoVetor == NAO_ENCONTRADO) {
			printf ("\n\tO Portatil indicado nao se encontra no sistema.\n");
		} else {
			if (vetorPortateis[posicaoVetor].estado == PORTATIL_REQUISITADO) {
				printf ("\n\tO Portatil indicado ja se encontra reservado.\n");
			} else {
				if (vetorPortateis[posicaoVetor].estado == PORTATIL_AVARIADO_TEMPORARIAMENTE) {
					printf ("\n\tO Portatil encontra-se avariado e nao pode ser reservado.\n");
				} else {
					ponteiroAuxiliar = vetorRequisicoes;
					vetorRequisicoes = realloc (vetorRequisicoes, (*totalRequisicoes + 1) * sizeof (tipoRequisicao));
					if (vetorRequisicoes == NULL) {
						printf ("\t*ERRO* Nao foi possivel alocar memoria!\n");
						vetorRequisicoes = ponteiroAuxiliar;
					} else {
						dadosRequisicao = lerDadosRequisicao (vetorPortateis[posicaoVetor], *nrRequisicao);
						logRequisicao (dadosRequisicao, vetorPortateis[posicaoVetor]); // regista requisicao no ficheiro log
						vetorRequisicoes[*totalRequisicoes] = dadosRequisicao;
						(*totalRequisicoes)++;
						(*nrRequisicao)++;
						vetorPortateis[posicaoVetor].estado = PORTATIL_REQUISITADO;
						vetorPortateis[posicaoVetor].contadorRequisicoes++;
						mostrarResumoRequisicao (dadosRequisicao);
					}
				}
			}
		}
	} else {
		printf ("\tNao existem portateis disponiveis !\n\n");
	}
	return vetorRequisicoes;
}

void prolongarRequisicao (tipoRequisicao vetorRequisicoes[], int totalRequisicoes, tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis) {

	int posicaoVetorRequisicoes=NAO_ENCONTRADO, posicaoVetorPortateis=NAO_ENCONTRADO, diasAcrescentar;
	int requisicoesAtivas=0;

    requisicoesAtivas = updateRequisicoesAtivas (vetorRequisicoes, totalRequisicoes);

	if (requisicoesAtivas == 0) {
		printf ("\tNao existem requisicoes ativas de momento.\n");
		printf ("\tAdicione requisicoes utilizando a opcao de [Adicionar requisicao].\n\n");
	} else {
		// listar requisicoes ativas
		listarRequisicoesAtivas (vetorRequisicoes, totalRequisicoes);
		// procurar requisicao
		posicaoVetorRequisicoes = procurarRequisicao (vetorRequisicoes, totalRequisicoes);
		if (posicaoVetorRequisicoes == NAO_ENCONTRADO) {
			printf ("\n\tA requisicao indicada nao se encontra no sistema.\n");
		} else {
			if (vetorRequisicoes[posicaoVetorRequisicoes].estadoRequisicao == REQUISICAO_CONCLUIDA) {
				printf ("\n\tA requisicao indicada ja se encontra CONCLUIDA.\n");
			} else {
				posicaoVetorPortateis = procuraPortatil (vetorPortateis, totalPortateis, vetorRequisicoes[posicaoVetorRequisicoes].idPortatil);
				mostrarResumoRequisicao (vetorRequisicoes[posicaoVetorRequisicoes]);
				printf ("\t> Prolongar prazo devolucao [Max. %d dias] : ",MAX_DIAS_PROLONGAR);
				diasAcrescentar = lerInteiro ("", 1, MAX_DIAS_PROLONGAR);
				vetorRequisicoes[posicaoVetorRequisicoes].prazoRequisicao += diasAcrescentar;
				vetorRequisicoes[posicaoVetorRequisicoes].dataDevolucao = calcularDataAposXDias (vetorRequisicoes[posicaoVetorRequisicoes].dataRequisicao, vetorRequisicoes[posicaoVetorRequisicoes].prazoRequisicao);
				printf ("\n\tRequisicao prolongada com sucesso.\n\tPrazo de requisicao alargado para %d dias, data de devolucao (estimada) : %02d/%02d/%4d\n\n", vetorRequisicoes[posicaoVetorRequisicoes].prazoRequisicao, vetorRequisicoes[posicaoVetorRequisicoes].dataDevolucao.dia, vetorRequisicoes[posicaoVetorRequisicoes].dataDevolucao.mes, vetorRequisicoes[posicaoVetorRequisicoes].dataDevolucao.ano);
				logProlongarRequisicao (vetorRequisicoes[posicaoVetorRequisicoes], vetorPortateis[posicaoVetorPortateis], diasAcrescentar); /* Regista ficheiro log */
			}
		}
	}
}

int adicionarDevolucao (tipoRequisicao vetorRequisicoes[], int *totalRequisicoes, tipoPortatil vetorPortatil[MAX_PORTATEIS], int totalPortateis) {

	int posicaoVetorRequisicoes = NAO_ENCONTRADO, posicaoVetorPortateis = NAO_ENCONTRADO;
	int totalDiasRequisicao = 0;
    int requisicoesAtivas=0;

    requisicoesAtivas = updateRequisicoesAtivas (vetorRequisicoes, *totalRequisicoes);

	if (requisicoesAtivas == 0) {
		printf ("\tNao existem requisicoes ativas de momento.\n");
		printf ("\tAdicione requisicoes utilizando a opcao de [Adicionar requisicao].\n\n");
	} else {
		// listar requisicoes ativas
		listarRequisicoesAtivas (vetorRequisicoes, *totalRequisicoes);
		// procurar requisicao
		posicaoVetorRequisicoes = procurarRequisicao (vetorRequisicoes, *totalRequisicoes);
		if (posicaoVetorRequisicoes == NAO_ENCONTRADO) {
			printf ("\n\tA requisicao indicada nao se encontra no sistema.\n");
		} else {
			if (vetorRequisicoes[posicaoVetorRequisicoes].estadoRequisicao == REQUISICAO_CONCLUIDA) {
				printf ("\n\tA requisicao indicada ja se encontra concluida.\n");
			} else {
				posicaoVetorPortateis = procuraPortatil (vetorPortatil, totalPortateis, vetorRequisicoes[posicaoVetorRequisicoes].idPortatil);
				printf ("\t> Introduza a data de devolucao : \n");
				do {
					vetorRequisicoes[posicaoVetorRequisicoes].dataDevolucao = lerData();
					totalDiasRequisicao = calcularNrDiasEntreDatas (vetorRequisicoes[posicaoVetorRequisicoes].dataRequisicao, vetorRequisicoes[posicaoVetorRequisicoes].dataDevolucao);
					if (totalDiasRequisicao < 0) {
						printf ("\n\t*ERRO* Data de devolucao anterior a data de requisicao! Tente novamente.\n\n");
					}
				} while (totalDiasRequisicao < 0);
				lerLocalizacao ("\t> Introduza o local de devolucao : \n", vetorRequisicoes[posicaoVetorRequisicoes].localizacao);
				//Verificar se existe multa
				if (totalDiasRequisicao > vetorRequisicoes[posicaoVetorRequisicoes].prazoRequisicao) {
					vetorRequisicoes[posicaoVetorRequisicoes].multa = (totalDiasRequisicao - vetorRequisicoes[posicaoVetorRequisicoes].prazoRequisicao) * MULTA;
				} else {
					vetorRequisicoes[posicaoVetorRequisicoes].multa = 0;
				}
				// atualizar contadores + atualizar localizacao do pc
				vetorPortatil[posicaoVetorPortateis].estado = PORTATIL_DISPONIVEL;
				vetorPortatil[posicaoVetorPortateis].contadorDias+= totalDiasRequisicao;
				strcpy (vetorPortatil[posicaoVetorPortateis].localizacao, vetorRequisicoes[posicaoVetorRequisicoes].localizacao);
				vetorRequisicoes[posicaoVetorRequisicoes].estadoRequisicao = REQUISICAO_CONCLUIDA;
				mostrarResumoRequisicao (vetorRequisicoes[posicaoVetorRequisicoes]);
				// escreve no log
				logDevolucao (vetorRequisicoes[posicaoVetorRequisicoes], vetorPortatil[posicaoVetorPortateis], totalDiasRequisicao);
			}
		}
	}
	return posicaoVetorRequisicoes;
}

void listarRequisicoes (tipoRequisicao vetorRequisicoes[], int totalRequisicoes) {

	int indiceRequisicoes;

	if (totalRequisicoes == 0) {
		printf ("\tNao existem requisicoes ativas de momento.\n");
		printf ("\tAdicione requisicoes utilizando a opcao de [Adicionar requisicao].\n\n");
	} else {
		limparEcra();
		printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n");
		printf (" ID REQ. | Portatil | Nome                           | Tipo Utente | Data Req.  | Prazo Req. | Estado  \n");
		for (indiceRequisicoes = 0; indiceRequisicoes < totalRequisicoes; indiceRequisicoes++) {
			mostrarRequisicao (vetorRequisicoes[indiceRequisicoes]);
		}
		printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n");
	}
}

void listarRequisicoesDetalhe (tipoRequisicao vetorRequisicoes[], int totalRequisicoes, tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis) {

	int posicaoVetorRequisicoes=NAO_ENCONTRADO, posicaoVetorPortateis=NAO_ENCONTRADO;
	int totalDiasRequisicao;

	if (totalRequisicoes == 0) {
		printf ("\tNao existem requisicoes ativas de momento.\n");
		printf ("\tAdicione requisicoes utilizando a opcao de [Adicionar requisicao].\n\n");
	} else {
		// procurar requisicao
		posicaoVetorRequisicoes = procurarRequisicao (vetorRequisicoes, totalRequisicoes);
		if (posicaoVetorRequisicoes == NAO_ENCONTRADO) {
			printf ("\n\tA requisicao indicada nao se encontra no sistema.\n");
		} else {
			posicaoVetorPortateis = procuraPortatil (vetorPortateis, totalPortateis, vetorRequisicoes[posicaoVetorRequisicoes].idPortatil);
			limparEcra();
			printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n");
			printf ("\n    ID Requisicao : %-30s                                   Estado : ", vetorRequisicoes[posicaoVetorRequisicoes].id);
			if (vetorRequisicoes[posicaoVetorRequisicoes].estadoRequisicao == REQUISICAO_CONCLUIDA) {
				printf (" CONCLUIDA   ");
			} else {
				printf (" ATIVA       ");
			}
			printf ("\n\n    ----------------------------------------------------------------------------------------------------\n\n");
			printf ("    Dados da reserva\n\n");
			printf ("\tNome de utente               : %s\n", vetorRequisicoes[posicaoVetorRequisicoes].nomeUtente);
			printf ("\tTipo de utente               : ");
			if (vetorRequisicoes[posicaoVetorRequisicoes].tipoUtente == TIPO_ESTUDANTE) {
				printf ("Estudante");
			} else {
				if (vetorRequisicoes[posicaoVetorRequisicoes].tipoUtente == TIPO_DOCENTE) {
					printf ("Docente");
				} else {
					printf ("Tecnico Administrativo");
				}
			}
			printf ("\n\tData de requisicao           : %02d/%02d/%4d", vetorRequisicoes[posicaoVetorRequisicoes].dataRequisicao.dia, vetorRequisicoes[posicaoVetorRequisicoes].dataRequisicao.mes, vetorRequisicoes[posicaoVetorRequisicoes].dataRequisicao.ano);
			if (vetorRequisicoes[posicaoVetorRequisicoes].estadoRequisicao == REQUISICAO_CONCLUIDA) {
				totalDiasRequisicao = calcularNrDiasEntreDatas (vetorRequisicoes[posicaoVetorRequisicoes].dataRequisicao, vetorRequisicoes[posicaoVetorRequisicoes].dataDevolucao);
				if (totalDiasRequisicao > vetorRequisicoes[posicaoVetorRequisicoes].prazoRequisicao) {
					printf ("\n\tTotal de dias da requisicao  : %d dias [%d dias (requisitados) + %d dias (atraso)]", totalDiasRequisicao, vetorRequisicoes[posicaoVetorRequisicoes].prazoRequisicao, totalDiasRequisicao - vetorRequisicoes[posicaoVetorRequisicoes].prazoRequisicao);
				} else {
					printf ("\n\tTotal de dias da requisicao  : %d dias", totalDiasRequisicao);
				}
				printf ("\n\tData de devolucao            : %02d/%02d/%4d", vetorRequisicoes[posicaoVetorRequisicoes].dataDevolucao.dia, vetorRequisicoes[posicaoVetorRequisicoes].dataDevolucao.mes, vetorRequisicoes[posicaoVetorRequisicoes].dataDevolucao.ano);
				printf ("\n\tLocal de devolucao           : %s", vetorRequisicoes[posicaoVetorRequisicoes].localizacao);
				if (totalDiasRequisicao > vetorRequisicoes[posicaoVetorRequisicoes].prazoRequisicao) {
					printf ("\n\tMulta                        : %.2f EUR\n", vetorRequisicoes[posicaoVetorRequisicoes].multa);
				} else {
					printf ("\n\tMulta                        : Sem multa\n");
				}
			} else {
				printf ("\n\tPrazo de requisicao          : %2d dias", vetorRequisicoes[posicaoVetorRequisicoes].prazoRequisicao);
				printf ("\n\tData de devolucao (Estimada) : %02d/%02d/%4d\n\n", vetorRequisicoes[posicaoVetorRequisicoes].dataDevolucao.dia, vetorRequisicoes[posicaoVetorRequisicoes].dataDevolucao.mes, vetorRequisicoes[posicaoVetorRequisicoes].dataDevolucao.ano);
			}
			printf ("\n\n    ----------------------------------------------------------------------------------------------------\n\n");
			printf ("    Dados do portatil requisitado\n\n");
			printf ("\tID                             : %5d\n", vetorPortateis[posicaoVetorPortateis].id);
			printf ("\tDesignacao                     : %s\n", vetorPortateis[posicaoVetorPortateis].designacao);
			printf ("\tCPU / RAM                      : i%d / %dGB\n", vetorPortateis[posicaoVetorPortateis].processador, vetorPortateis[posicaoVetorPortateis].ram);
			printf ("\tQuantidade de dias requisitado : %d\n", vetorPortateis[posicaoVetorPortateis].contadorDias);
			printf ("\tEstado do portatil             : ");
			if (vetorPortateis[posicaoVetorPortateis].estado == PORTATIL_DISPONIVEL) {
				printf ("Disponivel");
			} else {
				if (vetorPortateis[posicaoVetorPortateis].estado == PORTATIL_REQUISITADO) {
					printf ("Requisitado");
				} else {
					printf ("Avariado");
				}
			}

			printf ("\n\nmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");
		}
	}
}

void listarRequisicoesAtivas (tipoRequisicao vetorRequisicoes[], int totalRequisicoes) {

	int indiceRequisicao;

	printf ("\n\tRequisicoes ativas : ");
	printf ("\n\t--------------------------------------------------------------------------------------------\n");
	for (indiceRequisicao = 0; indiceRequisicao < totalRequisicoes; indiceRequisicao++) {
		if (vetorRequisicoes[indiceRequisicao].estadoRequisicao == REQUISICAO_ATIVA) {
			printf ("\tID: %s | Portatil ID: %d | %s, data req. %02d/%02d/%4d, prazo %d dias \n", vetorRequisicoes[indiceRequisicao].id, vetorRequisicoes[indiceRequisicao].idPortatil, vetorRequisicoes[indiceRequisicao].nomeUtente
			        , vetorRequisicoes[indiceRequisicao].dataRequisicao.dia, vetorRequisicoes[indiceRequisicao].dataRequisicao.mes, vetorRequisicoes[indiceRequisicao].dataRequisicao.ano
			        , vetorRequisicoes[indiceRequisicao].prazoRequisicao);
		}
	}
	printf ("\t--------------------------------------------------------------------------------------------\n\n");
}

void mostrarResumoRequisicao (tipoRequisicao requisicao) {

	int totalDiasRequisicao;

	printf ("\n\tResumo da requisicao :");
	printf ("\n\t--------------------------------------------------------------------------------------------");
	printf ("\n\tID Requisicao                : %s", requisicao.id);
	printf ("\n\tID Portatil                  : %5d", requisicao.idPortatil);
	printf ("\n\tNome / Tipo Utente           : %s, ", requisicao.nomeUtente);
	if (requisicao.tipoUtente == TIPO_ESTUDANTE) {
		printf ("Estudante");
	} else {
		if (requisicao.tipoUtente == TIPO_DOCENTE) {
			printf ("Docente");
		} else {
			printf ("Tecnico Administrativo");
		}
	}
	printf ("\n\tData de requisicao           : %02d/%02d/%4d", requisicao.dataRequisicao.dia, requisicao.dataRequisicao.mes, requisicao.dataRequisicao.ano);
	if (requisicao.estadoRequisicao == REQUISICAO_CONCLUIDA) {
		totalDiasRequisicao = calcularNrDiasEntreDatas (requisicao.dataRequisicao, requisicao.dataDevolucao);
		if (totalDiasRequisicao > requisicao.prazoRequisicao) {
			printf ("\n\tTotal de dias da requisicao  : %d dias [%d dias (requisitados) + %d dias (atraso)]", totalDiasRequisicao, requisicao.prazoRequisicao, totalDiasRequisicao - requisicao.prazoRequisicao);
		} else {
			printf ("\n\tTotal de dias da requisicao  : %d dias", totalDiasRequisicao);
		}
		printf ("\n\tData de devolucao            : %02d/%02d/%4d", requisicao.dataDevolucao.dia, requisicao.dataDevolucao.mes, requisicao.dataDevolucao.ano);
		printf ("\n\tLocal de devolucao           : %s", requisicao.localizacao);
		if (totalDiasRequisicao > requisicao.prazoRequisicao) {
			printf ("\n\tMulta                        : %.2f EUR\n", requisicao.multa);
		} else {
			printf ("\n\tMulta                        : Sem multa\n");
		}
	} else {
		printf ("\n\tPrazo de requisicao          : %d dias", requisicao.prazoRequisicao);
		printf ("\n\tData de devolucao (Estimada) : %02d/%02d/%4d\n", requisicao.dataDevolucao.dia, requisicao.dataDevolucao.mes, requisicao.dataDevolucao.ano);
	}
	printf ("\t--------------------------------------------------------------------------------------------\n\n");
}

void mostrarRequisicao (tipoRequisicao requisicao) {

	int totalDias = 0;

	printf ("------------------------------------------------------------------------------------------------------------\n");
	printf (" %-7s |", requisicao.id);
	printf (" ID:%-5d |", requisicao.idPortatil);
	printf (" %-30s |", requisicao.nomeUtente);
	if (requisicao.tipoUtente == TIPO_ESTUDANTE) {
		printf (" Estudante   ");
	} else {
		if (requisicao.tipoUtente == TIPO_DOCENTE) {
			printf (" Docente     ");
		} else {
			printf (" Tec. Admin. ");
		}
	}
	printf ("| %02d/%02d/%4d |", requisicao.dataRequisicao.dia, requisicao.dataRequisicao.mes, requisicao.dataRequisicao.ano);
	printf (" %d dias    |", requisicao.prazoRequisicao);
	if (requisicao.estadoRequisicao == REQUISICAO_CONCLUIDA) {
		printf (" CONCLUIDA   \n");
	} else {
		printf (" ATIVA       \n");
	}
	if (requisicao.estadoRequisicao == REQUISICAO_CONCLUIDA) {
		totalDias = calcularNrDiasEntreDatas (requisicao.dataRequisicao, requisicao.dataDevolucao);
		printf ("                                                     | Devolucao   : %02d/%02d/%4d | Total      : %d dias\n", requisicao.dataDevolucao.dia,
		        requisicao.dataDevolucao.mes,
		        requisicao.dataDevolucao.ano,
		        totalDias);
		printf ("                                                     | Localizacao : %-11s| Multa      : %.2f EUR\n", requisicao.localizacao, requisicao.multa);
	}
}
