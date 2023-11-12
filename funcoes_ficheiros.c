#include <stdio.h>
#include <stdlib.h>

#include "funcoes_portateis.h"
#include "funcoes_ficheiros.h"

void gravarFicheiroBinario (tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis, tipoRequisicao vetorRequisicoes[], int totalRequisicoes, int nrRequisicao) {

	FILE *ficheiro;
	ficheiro = fopen ("sgp_data.dat", "wb");

	int quant, erro;

	if (ficheiro == NULL) {
		printf ("\t> Erro ao abrir o ficheiro <");
		enterParaContinuar();
	} else {
		quant = fwrite (&totalPortateis, sizeof (int), 1, ficheiro);
		if (quant != 1) {
			printf ("\t> Erro ao salvar ficheiro (%d vs %d) <", quant, 1);
		} else {
			quant = fwrite (vetorPortateis, sizeof (tipoPortatil), totalPortateis, ficheiro);
			if (quant != totalPortateis) {
				printf ("\t> Erro ao salvar ficheiro (%d vs %d) <", quant, totalPortateis);
			} else {
				quant = fwrite (&totalRequisicoes, sizeof (int), 1, ficheiro);
				if (quant != 1) {
					printf ("\t> Erro ao salvar ficheiro (%d vs %d) <", quant, totalRequisicoes);
				} else {
					quant = fwrite (&nrRequisicao, sizeof (int), 1, ficheiro);
					if (quant != 1) {
						printf ("\t> Erro ao ler ficheiro (%d vs %d) <", quant, nrRequisicao);
					} else {
						quant = fwrite (vetorRequisicoes, sizeof (tipoRequisicao), totalRequisicoes, ficheiro);
						if (quant != totalRequisicoes) {
							printf ("\t> Erro ao salvar ficheiro (%d vs %d) <", quant, totalRequisicoes);
						} else {
							limparEcra();
							printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");
							printf ("\n\n\n\n\n\n\n\n\n\n");
							printf ("                                          Dados guardados com sucesso!\n\n");
							printf ("\n\n\n\n\n\n\n\n\n\n\n");
							printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");
						}
					}
				}
			}
		}
		erro = fclose (ficheiro);
		if (erro != 0) {
			printf ("\t> Erro %d ao fechar ficheiro <\n", erro);
		}
	}
}

tipoRequisicao *lerFicheiroBinario (tipoPortatil vetorPortateis[MAX_PORTATEIS], int *totalPortateis, tipoRequisicao vetorRequisicoes[], int *totalRequisicoes, int *nrRequisicao) {

	FILE *ficheiro;
	ficheiro = fopen ("sgp_data.dat", "rb");

	int quant, erro;

	if (ficheiro == NULL) {
		printf ("\t> Erro ao abrir o ficheiro <\n\n");
		enterParaContinuar();
	} else {
		quant = fread (& (*totalPortateis), sizeof (int), 1, ficheiro);
		if (quant != 1) {
			printf ("\t> Erro ao ler ficheiro (%d vs %d) <\n", quant, 1);
		} else {
			if (*totalPortateis == 0) {
				printf ("\t> Erro ao ler ficheiro (%d vs %d) <\n", quant, 1);
			} else {
				quant = fread (vetorPortateis, sizeof (tipoPortatil), *totalPortateis, ficheiro);
				if (quant != *totalPortateis) {
					printf ("\t> Erro ao ler ficheiro (%d vs %d) <\n", quant, *totalPortateis);
					*totalPortateis = 0;
				} else {
					quant = fread (& (*totalRequisicoes), sizeof (int), 1, ficheiro);
					if (quant != 1) {
						printf ("\t> Erro ao ler ficheiro (%d vs %d) <", quant, *totalRequisicoes);
					} else {
						quant = fread (& (*nrRequisicao), sizeof (int), 1, ficheiro);
						if (quant != 1) {
							printf ("\t> Erro ao ler ficheiro (%d vs %d) <", quant, *nrRequisicao);
						} else {
							vetorRequisicoes = realloc (vetorRequisicoes, (*totalRequisicoes) * sizeof (tipoRequisicao));
							if (vetorRequisicoes == NULL) {
								*totalRequisicoes = 0;
								*nrRequisicao = 0;
							} else {
								quant = fread (vetorRequisicoes, sizeof (tipoRequisicao), *totalRequisicoes, ficheiro);
								if (quant != *totalRequisicoes) {
									printf ("\t> Erro ao ler ficheiro (%d vs %d) <", quant, *totalRequisicoes);
								}
							}
						}
					}
				}
			}
			erro = fclose (ficheiro);
			if (erro != 0) {
				printf ("\t\t\t> Erro %d ao fechar ficheiro <\n\t\t\t\n", erro);
			}
			limparEcra();
			printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");
			printf ("\n\n\n\n\n\n\n\n\n\n");
			printf ("                                           Dados carregados com sucesso!\n\n");
			printf ("\n\n\n\n\n\n\n\n\n\n\n");
			printf ("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n\n");
		}
	}
	return vetorRequisicoes;
}

void gravarFicheiroAvariasBinario (tipoAvaria vetorAvarias[], int totalAvarias) {
	FILE *ficheiro;
	int quant, erro;
	ficheiro = fopen ("sgp_data_avarias.dat", "wb");

	if (ficheiro == NULL) {
		printf ("\t> Erro ao abrir o ficheiro <");
		enterParaContinuar();
	} else {
		quant = fwrite (&totalAvarias, sizeof (int), 1, ficheiro);

		if (quant != 1) {
			printf ("\t> Erro ao salvar ficheiro (%d vs %d) <", quant, totalAvarias);
		} else {
			quant = fwrite (vetorAvarias, sizeof (tipoAvaria), totalAvarias, ficheiro);

			if (quant != totalAvarias) {
				printf ("\t> Erro ao salvar ficheiro (%d vs %d) <", quant, totalAvarias);
			}
		}
	}

	erro = fclose (ficheiro);

	if (erro != 0) {
		printf ("\t> Erro %d ao fechar ficheiro <\n", erro);
	}
}

tipoAvaria *lerFicheiroAvariasBinario (tipoAvaria vetorAvarias[], int *totalAvarias) {

	FILE *ficheiro;
	ficheiro = fopen ("sgp_data_avarias.dat", "rb");

	int quant, erro;

	if (ficheiro == NULL) {
		printf ("\t> Erro ao abrir o ficheiro <\n\n");
		enterParaContinuar();
	} else {
		quant = fread (& (*totalAvarias), sizeof (int), 1, ficheiro);
		if (quant != 1) {
			printf ("\t> Erro ao carregar ficheiro (%d vs %d) Total <", quant, *totalAvarias);
		} else {
			vetorAvarias = realloc (vetorAvarias, (*totalAvarias) * sizeof (tipoAvaria));
			if (vetorAvarias == NULL) {
				vetorAvarias = 0;
				*totalAvarias = 0;
			} else {
				quant = fread (vetorAvarias, sizeof (tipoAvaria), *totalAvarias, ficheiro);
				if (quant != *totalAvarias) {
					printf ("\t> Erro ao carregar ficheiro (%d vs %d) <", quant, *totalAvarias);
				}
			}
		}
		erro = fclose (ficheiro);
		if (erro != 0) {
			printf ("\t\t\t> Erro %d ao fechar ficheiro < \n\t\t\t\n", erro);
		}
	}
	return vetorAvarias;
}

void logRequisicao (tipoRequisicao requisicao, tipoPortatil portatil) {

	FILE *ficheiroLog;
	ficheiroLog = fopen ("sgp_log_requisicoes.txt", "a");

	if (ficheiroLog == NULL) {
		printf ("\t> Erro ao abrir ficheiro <");
	} else {
		fprintf (ficheiroLog, "# %s # ", requisicao.id);
		fprintf (ficheiroLog, "[REQ. ATIVA] # ");
		fprintf (ficheiroLog, "Data requisicao : %02d/%02d/%04d # ", requisicao.dataRequisicao.dia, requisicao.dataRequisicao.mes, requisicao.dataRequisicao.ano);
		fprintf (ficheiroLog, "Portatil %d,i%d,%dGB # ", requisicao.idPortatil, portatil.processador, portatil.ram);
		fprintf (ficheiroLog, "%s,", requisicao.nomeUtente);
		if (requisicao.tipoUtente == TIPO_ESTUDANTE) {
			fprintf (ficheiroLog, "Estudante");
		} else {
			if (requisicao.tipoUtente == TIPO_DOCENTE) {
				fprintf (ficheiroLog, "Docente");
			} else {
				fprintf (ficheiroLog, "Tecnico administrativo");
			}
		}
		fprintf (ficheiroLog, ",Prazo requisicao:%d dias", requisicao.prazoRequisicao);
		fprintf (ficheiroLog, "\n");
		fclose (ficheiroLog);
	}
}

void logProlongarRequisicao (tipoRequisicao requisicao, tipoPortatil portatil, int diasAcrescentar) {
	FILE *ficheiroLog;
	ficheiroLog = fopen ("sgp_log_requisicoes.txt", "a");

	if (ficheiroLog == NULL) {
		printf ("\t> Erro ao abrir ficheiro <");
	} else {
		fprintf (ficheiroLog, "# %s # ", requisicao.id);
		fprintf (ficheiroLog, "[REQ. PROLONGADA] # ");
		fprintf (ficheiroLog, "Data requisicao : %02d/%02d/%04d # ", requisicao.dataRequisicao.dia, requisicao.dataRequisicao.mes, requisicao.dataRequisicao.ano);
		fprintf (ficheiroLog, "Portatil %d,i%d,%dGB # ", requisicao.idPortatil, portatil.processador, portatil.ram);
		fprintf (ficheiroLog, "%s,", requisicao.nomeUtente);
		if (requisicao.tipoUtente == TIPO_ESTUDANTE) {
			fprintf (ficheiroLog, "Estudante");
		} else {
			if (requisicao.tipoUtente == TIPO_DOCENTE) {
				fprintf (ficheiroLog, "Docente");
			} else {
				fprintf (ficheiroLog, "Tecnico administrativo");
			}
		}
		fprintf (ficheiroLog, ",+%d dia(s)", diasAcrescentar);
		fprintf (ficheiroLog, ",Novo prazo requisicao:%d dias", requisicao.prazoRequisicao);
		fprintf (ficheiroLog, "\n");
		fclose (ficheiroLog);
	}
}

void logDevolucao (tipoRequisicao requisicao, tipoPortatil portatil, int totalDias) {
	FILE *ficheiroLog;
	ficheiroLog = fopen ("sgp_log_requisicoes.txt", "a");

	if (ficheiroLog == NULL) {
		printf ("\t> Erro ao abrir ficheiro <");
	} else {
		fprintf (ficheiroLog, "# %s # ", requisicao.id);
		fprintf (ficheiroLog, "[REQ. CONCLUIDA] # ");
		fprintf (ficheiroLog, "Data devolucao : %02d/%02d/%04d # ", requisicao.dataDevolucao.dia, requisicao.dataDevolucao.mes, requisicao.dataDevolucao.ano);
		fprintf (ficheiroLog, "Portatil %d,i%d,%dGB # ", requisicao.idPortatil, portatil.processador, portatil.ram);
		fprintf (ficheiroLog, "%s,", requisicao.nomeUtente);
		if (requisicao.tipoUtente == TIPO_ESTUDANTE) {
			fprintf (ficheiroLog, "Estudante");
		} else {
			if (requisicao.tipoUtente == TIPO_DOCENTE) {
				fprintf (ficheiroLog, "Docente");
			} else {
				fprintf (ficheiroLog, "Tecnico administrativo");
			}
		}
		fprintf (ficheiroLog, ",Duracao total %d dias,", totalDias);
		fprintf (ficheiroLog, "Multa %.2f EUR", requisicao.multa);
		fprintf (ficheiroLog, "\n");
		fclose (ficheiroLog);
	}

}
