#include <stdio.h>
#include <stdlib.h>

#include "constantes.h"
#include "estruturas.h"
#include "funcoes_auxiliares.h"
#include "funcoes_estatisticas.h"
#include "funcoes_ficheiros.h"
#include "funcoes_portateis.h"
#include "funcoes_requisicoes.h"
#include "funcoes_avarias.h"

#include "menus.h"

int main (void) {

	tipoPortatil vetorPortateis[MAX_PORTATEIS] = {0};
	int totalPortateis = 0, portateisDisponiveis = 0;

	tipoRequisicao *vetorRequisicoes = NULL;
	int totalRequisicoes = 0, requisicoesAtivas = 0, nrRequisicao = 0;

	tipoAvaria *vetorAvarias = NULL;
	int totalAvarias = 0;

	// opcoes menu
	int opcaoMenuPrincipal = 0;
	int opcaoMenuPortatil = 0;
	int opcaoMenuConsultar = 0, opcaoSubmenuConsultarPortatil = 0, opcaoSubmenuConsultarRequisicao = 0;
	int opcaoMenuRequisicao = 0;
	int opcaoMenuAvarias = 0;
	char opcaoMenuSair = '\0';

	do {
		// atualizacao de contadores principais
		requisicoesAtivas = updateRequisicoesAtivas (vetorRequisicoes, totalRequisicoes);
		portateisDisponiveis = updatePortateisDisponiveis (vetorPortateis, totalPortateis);

		opcaoMenuPrincipal = menuPrincipal (totalPortateis, portateisDisponiveis, totalRequisicoes, requisicoesAtivas);
		switch (opcaoMenuPrincipal) {
		case 1: // menu adicionar / editar vetorPortateis
			do {
				opcaoMenuPortatil = menuPortatil();
				switch (opcaoMenuPortatil) {
				case 1: // adicionar vetorPortateis
					adicionarPortatil (vetorPortateis, &totalPortateis);
					break;

				case 2: // editar vetorPortateis
					alterarLocalizacaoPortatil (vetorPortateis, totalPortateis);
					enterParaContinuar();
					break;

				case 0: // voltar
					break;
				}
			} while (opcaoMenuPortatil != 0);
			break;

		case 2: // menu consultar
			do {
				opcaoMenuConsultar = menuConsultar (totalPortateis);
				switch (opcaoMenuConsultar) {
				case 1: // consultar portateis
					do {
						opcaoSubmenuConsultarPortatil = submenuConsultarPortatil();
						switch (opcaoSubmenuConsultarPortatil) {
						case 1: // listar portateis
							listarPortateis (vetorPortateis, totalPortateis);
							enterParaContinuar();
							break;

						case 2: // listar vetorPortateis em detalhe
							listarPortatilDetalhe (vetorPortateis, totalPortateis, vetorRequisicoes, totalRequisicoes);
							enterParaContinuar();
							break;

						case 0: // voltar
							break;
						}
					} while (opcaoSubmenuConsultarPortatil != 0);
					break;

				case 2: // consultar vetorRequisicoes
					if (totalRequisicoes == 0) {
						printf ("\tNao existem requisicoes no sistema.\n");
						printf ("\tAdicione requisicoes utilizando a opcao de [Adicionar requisicao].\n\n");
						enterParaContinuar();
					} else {
						do {
							opcaoSubmenuConsultarRequisicao = submenuConsultarRequisicao();
							switch (opcaoSubmenuConsultarRequisicao) {
							case 1: // listar vetorRequisicoes
								listarRequisicoes (vetorRequisicoes, totalRequisicoes);
								enterParaContinuar();
								break;

							case 2: // listar vetorRequisicoes em detalhe
								listarRequisicoesDetalhe (vetorRequisicoes, totalRequisicoes, vetorPortateis, totalPortateis);
								enterParaContinuar();
								break;

							case 0: // voltar
								break;
							}
						} while (opcaoSubmenuConsultarRequisicao != 0);
						break;

					case 3:  // consultar vetorAvarias
						listarAvarias (vetorAvarias, totalAvarias, vetorPortateis, totalPortateis);
						enterParaContinuar();
						break;

					case 0: // voltar
						break;
					}
				}
			} while (opcaoMenuConsultar != 0);
			break;

		case 3: // menu requisicao / devolucao
			do {
				opcaoMenuRequisicao = menuRequisicaoDevolucao (totalPortateis);
				switch (opcaoMenuRequisicao) {
				case 1: // adicionar requisicao
					vetorRequisicoes = adicionarRequisicao (vetorRequisicoes, &totalRequisicoes, vetorPortateis, totalPortateis, &nrRequisicao);
					enterParaContinuar();
					break;

				case 2: // prolongar requisicao
					prolongarRequisicao (vetorRequisicoes, totalRequisicoes, vetorPortateis, totalPortateis);
					enterParaContinuar();
					break;

				case 3: // adicionar devolucao
					adicionarDevolucao (vetorRequisicoes, &totalRequisicoes, vetorPortateis, totalPortateis);
					enterParaContinuar();
					break;

				case 0: // voltar
					break;
				}
			} while (opcaoMenuRequisicao != 0);
			break;

		case 4: // menu avarias / reparacoes
			do {
				opcaoMenuAvarias = menuAvarias (totalPortateis);
				switch (opcaoMenuAvarias) {
				case 1: // adicionar avaria
					vetorAvarias = adicionarAvaria (vetorAvarias, &totalAvarias, vetorPortateis, totalPortateis);
					enterParaContinuar();
					break;

				case 2: // adicionar reparacao
					adicionarReparacao (vetorAvarias, totalAvarias, vetorPortateis, totalPortateis);
					enterParaContinuar();
					break;

				case 0: // voltar
					break;
				}
			} while (opcaoMenuAvarias != 0);
			break;

		case 5: // menu estatisticas
			menuEstatisticas (vetorPortateis, totalPortateis, vetorRequisicoes, totalRequisicoes);
			enterParaContinuar();
			break;

		case 6:// menu  informacoes
			menuInformacoes();
			enterParaContinuar();
			break;

		case 7: // menu carregar dados
			vetorAvarias = lerFicheiroAvariasBinario (vetorAvarias, &totalAvarias);
			vetorRequisicoes = lerFicheiroBinario (vetorPortateis, &totalPortateis, vetorRequisicoes, &totalRequisicoes, &nrRequisicao);
			enterParaContinuar();
			break;

		case 8: // menu guardar dados
			gravarFicheiroAvariasBinario (vetorAvarias, totalAvarias);
			gravarFicheiroBinario (vetorPortateis, totalPortateis, vetorRequisicoes, totalRequisicoes, nrRequisicao);
			enterParaContinuar();
			break;

		case 0: // menu sair
			opcaoMenuSair = menuSair ();
			break;
		}
	} while (opcaoMenuPrincipal != 0 || opcaoMenuSair != 'S');

	free (vetorAvarias);
	free (vetorRequisicoes);

	return 0;
}
