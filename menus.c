#include <stdio.h>

#include "menus.h"
#include "funcoes_auxiliares.h"
#include "funcoes_estatisticas.h"
#include "funcoes_portateis.h"

int lerOpcaoMenu (int minimo, int maximo) {
	int opcao, controlo;

	do {

		printf ("                                                                                   Introduza a opcao -> ");
		controlo = scanf ("%d", &opcao);
		limpaBufferStdin();

		if (controlo == 0 || (opcao < minimo || opcao > maximo)) {
			printf ("\n\tOpcao invalida. Por favor, introduza uma das opcoes disponiveis no menu.\n\n");
		}
	} while (controlo == 0 || (opcao < minimo || opcao > maximo));

	return opcao;
}

int menuPrincipal (int totalPortateis, int portateisDisponiveis, int totalRequisicoes, int requisicoesAtivas) {

	int opcao;

	limparEcra();
	printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n");
	printf ("|                                       SOFTWARE DE GESTAO DE PORTATEIS                                    |\n");
	printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n");
	printf ("Portateis existentes :  %2d                                                        Portateis disponiveis:  %2d\n", totalPortateis, portateisDisponiveis);
	printf ("Requisicoes efetuadas:  %2d                                                        Requisicoes ativas   :  %2d\n", totalRequisicoes, requisicoesAtivas);
	printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");

	printf ("\t\t\t\t\t[1] Adicionar | Editar portatil\n\n");
	printf ("\t\t\t\t\t[2] Consultar\n\n");
	printf ("\t\t\t\t\t[3] Requisicoes | Devolucoes\n\n");
	printf ("\t\t\t\t\t[4] Avarias | Reparacoes\n\n");
	printf ("\t\t\t\t\t[5] Estatisticas\n\n");
	printf ("\t\t\t\t\t[6] Informacoes\n\n");
	printf ("\t\t\t\t\t[7] Carregar dados\n\n");
	printf ("\t\t\t\t\t[8] Guardar dados\n\n");
	printf ("\t\t\t\t\t[0] Sair\n\n");
	printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");
	opcao = lerOpcaoMenu (0, 8);
	printf ("\n");
	return opcao;
}

// ADICIONAR / EDITAR PORTATIL
int menuPortatil (void) {

	int opcao;

	limparEcra();
	printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");
	printf ("\n\n\n\n\n\n\n\n\n");
	printf ("\t\t\t\t\t[1] Adicionar portatil\n\n");
	printf ("\t\t\t\t\t[2] Editar localizacao de portatil\n\n");
	printf ("\t\t\t\t\t[0] Voltar\n\n");
	printf ("\n\n\n\n\n\n\n\n");
	printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");
	opcao = lerOpcaoMenu (0, 2);
	printf ("\n");

	return opcao;
}

// CONSULTAR
int menuConsultar (int totalPortateis) {

	int opcao = 0;

	if (totalPortateis == 0) {
		printf ("\tO menu CONSULTAR encontra-se desativado porque nao existem portateis no sistema.\n");
		printf ("\tAdicione portateis utilizando a opcao de [Adicionar portatil].\n\n");
		enterParaContinuar();
	} else {
		limparEcra();
		printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");
		printf ("\n\n\n\n\n\n\n\n");
		printf ("\t\t\t\t\t[1] Consultar portateis\n\n");
		printf ("\t\t\t\t\t[2] Consultar requisicoes\n\n");
		printf ("\t\t\t\t\t[3] Consultar avarias\n\n");
		printf ("\t\t\t\t\t[0] Voltar\n\n");
		printf ("\n\n\n\n\n\n\n");
		printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");
		opcao = lerOpcaoMenu (0, 3);
		printf ("\n");
	}

	return opcao;
}

int submenuConsultarPortatil (void) {

	int opcao;

	limparEcra();
	printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n");
	printf ("\n\n\n\n\n\n\n\n\n");
	printf ("\t\t\t\t\t[1] Visao geral\n\n");
	printf ("\t\t\t\t\t[2] Pesquisar por portatil\n\n");
	printf ("\t\t\t\t\t[0] Voltar\n\n");
	printf ("\n\n\n\n\n\n\n\n\n");
	printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");
	opcao = lerOpcaoMenu (0, 2);
	printf ("\n");

	return opcao;
}

int submenuConsultarRequisicao (void) {

	int opcao;

	limparEcra();
	printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n");
	printf ("\n\n\n\n\n\n\n\n\n");
	printf ("\t\t\t\t\t[1] Visao geral\n\n");
	printf ("\t\t\t\t\t[2] Pesquisar por requisicao\n\n");
	printf ("\t\t\t\t\t[0] Voltar\n\n");
	printf ("\n\n\n\n\n\n\n\n\n");
	printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");
	opcao = lerOpcaoMenu (0, 2);
	printf ("\n");

	return opcao;
}

// REQUISITAR / DEVOLVER
int menuRequisicaoDevolucao (int totalPortateis) {

	int opcao = 0;

	if (totalPortateis == 0) {
		printf ("\tO menu REQUISICAO / DEVOLUCAO encontra-se desativado porque nao existem portateis no sistema.\n");
		printf ("\tAdicione portateis utilizando a opcao de [Adicionar portatil].\n\n");
		enterParaContinuar();
	} else {
		limparEcra();
		printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");
		printf ("\n\n\n\n\n\n\n\n");
		printf ("\t\t\t\t\t[1] Nova requisicao\n\n");
		printf ("\t\t\t\t\t[2] Prolongar requisicao\n\n");
		printf ("\t\t\t\t\t[3] Devolucoes\n\n");
		printf ("\t\t\t\t\t[0] Voltar\n\n");
		printf ("\n\n\n\n\n\n\n");
		printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");
		opcao = lerOpcaoMenu (0, 3);
		printf ("\n");
	}
	return opcao;
}

// AVARIAS / REPARACOES
int menuAvarias (int totalPortateis) {

	int opcao = 0;

	if (totalPortateis == 0) {
		printf ("\tO menu AVARIAS / REPARACOES encontra-se desativado porque nao existem portateis no sistema.\n");
		printf ("\tAdicione portateis utilizando a opcao de [Adicionar portatil].\n\n");
        enterParaContinuar();
	} else {
		limparEcra();
		printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n");
		printf ("\n\n\n\n\n\n\n\n\n");
		printf ("\t\t\t\t\t[1] Registar avaria\n\n");
		printf ("\t\t\t\t\t[2] Registar reparacao\n\n");
		printf ("\t\t\t\t\t[0] Voltar\n\n");
		printf ("\n\n\n\n\n\n\n\n\n");
		printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");
		opcao = lerOpcaoMenu (0, 2);
		printf ("\n");
	}
	return opcao;
}

// ESTATISTICAS
void menuEstatisticas (tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis, tipoRequisicao vetorRequisicoes[], int totalRequisicoes) {

	float mediaMultas = 0.00;
	float percetagemI3 = 0.00, percetagemI5 = 0.00, percetagemI7 = 0.00;

	int portateisDisponiveis;
	int requisicoesAtivas;

// CALCULOS
    portateisDisponiveis = updatePortateisDisponiveis(vetorPortateis,totalPortateis);
    requisicoesAtivas = updateRequisicoesAtivas (vetorRequisicoes,totalRequisicoes);
	percentagemProcessadores (vetorPortateis, totalPortateis, &percetagemI3, &percetagemI5, &percetagemI7);
	custoMedioMultas (vetorRequisicoes, totalRequisicoes, &mediaMultas);

// PERCENTAGENS

	if (totalPortateis == 0) {
		printf ("\tO menu ESTATISTICAS encontra-se desativado porque nao existem portateis no sistema.\n");
		printf ("\tAdicione portateis utilizando a opcao de [Adicionar portatil].\n\n");
	} else {
		limparEcra();
		printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n");
		printf ("|                                                 ESTATISTICAS                                             |\n");
		printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n\n");
		printf ("    Portateis existentes  : %-2d                                           Processadores com i3 :   %6.2f %%   \n\n", totalPortateis, percetagemI3);
		printf ("    Portateis disponiveis : %-2d                                           Processadores com i5 :   %6.2f %%   \n\n", portateisDisponiveis, percetagemI5);
		printf ("    Requisicoes Efetuadas : %-2d                                           Processadores com i7 :   %6.2f %%   \n\n", totalRequisicoes, percetagemI7);
		printf ("    Requisicoes Ativas    : %-2d                                          Custo medio de multas : %6.2f EUR    \n\n", requisicoesAtivas, mediaMultas);
		printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");
		tipoUtenteMenorRequisicao (vetorRequisicoes, totalRequisicoes);
		printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");
		printf ("    Devolucao(oes) mais recente(s) : \n\n");
		ultimasDevolucoes(vetorRequisicoes,totalRequisicoes);
		printf ("\nmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");
	}
}

// INFORMACOES
void menuInformacoes (void) {

	limparEcra();
	printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n");
	printf ("|                                       SOFTWARE DE GESTAO DE PORTATEIS                                    |\n");
	printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n\n\n");
	printf ("                                      Engenharia Informatica 2022 / 2023\n\n");
	printf ("                                           Programacao I - Projeto\n\n\n\n\n");
	printf ("                                               Desenvolvido por:\n\n\n\n\n\n");
	printf ("                                           David Ferreira - 2221859\n\n");
	printf ("                                           Pedro Barbeiro - 2221986\n\n\n\n");
	printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");
}

// SAIR
char menuSair (void) {

	char opcaoMenuSair;

	limparEcra();
	printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");
	printf ("\n\n\n\n\n\n\n\n\n\n\n");
	printf ("                             Tem a certeza que pretende sair ?  [S]im ou [N]ao\n");
	printf ("\n\n\n\n\n\n\n\n\n\n\n");
	printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");
	printf ("                                                                                   Introduza a opcao -> ");

	do {
		opcaoMenuSair = lerCaracter();

		switch (opcaoMenuSair) {
		case 'S':
			break;

		case 'N':
			break;

		default:
			printf ("\n\tOpcao invalida.\n\tIntroduza [S]im para sair ou [N]ao para voltar ao menu principal -> ");
			break;
		}
	} while (opcaoMenuSair != 'S' && opcaoMenuSair != 'N');

	return opcaoMenuSair;
}
