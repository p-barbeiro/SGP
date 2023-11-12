#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "funcoes_auxiliares.h"

char lerCaracter (void) {
	char caracter;
	int controlo;

	do {
		controlo = scanf ("%c", &caracter);
		caracter = toupper (caracter);
		if (caracter != '\n') {
			limpaBufferStdin();
		}
		if (controlo == 0) {
			printf ("\tCaracter invalido. Tente novamente.");
		}
	} while (controlo == 0 || caracter == '\n');

	return caracter;
}

int lerInteiro (char mensagem[MAX_STRING], int minimo, int maximo) {
	int numero, controlo;

	do {
		printf ("%s", mensagem);
		controlo = scanf ("%d", &numero);  // scanf devolve quantidade de valores vàlidos obtidos
		limpaBufferStdin();     //limpa todos os caracteres do buffer stdin (nomeadamente o \n)

		if (controlo == 0) {
			printf ("\n\tValor invalido. Introduza um numero inteiro\n\n");
		} else {

			if (numero < minimo || numero > maximo) {
				printf ("\n\tO valor introduzido tem de estar no intervalo [%d - %d].\n\tPor favor, tente novamente.\n\n", minimo, maximo);
			}

		}
	} while (numero < minimo || numero > maximo || controlo == 0);

	return numero;
}

float lerFloat (char mensagem[MAX_STRING], float minimo, float maximo) {
	float numero;
	int controlo;
	do {
		printf ("%s", mensagem);
		controlo = scanf ("%f", &numero);  // scanf devolve quantidade de valores vàlidos obtidos
		limpaBufferStdin();

		if (controlo == 0) {
			printf ("\tValor invalido. Introduza um numero decimal (float)\n");
		} else {
			if (numero < minimo || numero > maximo) {
				printf ("\tValor invalido. Tente novamente.\n\n");
			}
		}
	} while (numero < minimo || numero > maximo || controlo == 0);
	return numero;
}

void lerString (char mensagem[MAX_STRING], char vetorCaracteres[MAX_STRING], int maximoCaracteres) {
	int tamanhoString;
	do {		// Repete leitura caso sejam obtidas strings vazias
		printf ("%s", mensagem);
		fgets (vetorCaracteres, maximoCaracteres, stdin);
		tamanhoString = strlen (vetorCaracteres);
		if (tamanhoString == 1) {
			printf ("\n\tNao foi introduzido nenhum caracter. Apenas carregou no ENTER.\n\n"); // apenas faz sentido limpar buffer se a ficarem caracteres
		}
	} while (tamanhoString == 1);
	if (vetorCaracteres[tamanhoString - 1] != '\n') { // ficaram caracteres no buffer....
		limpaBufferStdin();  // apenas faz sentido limpar buffer se a ficarem caracteres
	} else {
		vetorCaracteres[tamanhoString - 1] = '\0'; 	//Elimina o \n da string armazenada em vetor
	}
}

void limpaBufferStdin (void) {
	char chr;
	do {
		chr = getchar();
	} while (chr != '\n' && chr != EOF);
}

int lerInteiroPositivo (void) {
	int numero, controlo;
	do {
		controlo = scanf ("%d", &numero);  // scanf devolve quantidade de valores validos obtidos
		limpaBufferStdin();     //limpa todos os caracteres do buffer stdin (nomeadamente o \n)

		if (controlo == 0) {
			printf ("\tApenas sao aceites numeros inteiros. Tente novamente : ");
		} else {
			if (numero < 0) {
				printf ("\tNumero invalido. Tente novamente : ");
			}
		}
	} while (numero < 0 || controlo == 0);

	return numero;
}

tipoData lerData (void) {

	tipoData data;

	int maxDiaMes;
	data.ano = lerInteiro ("\t\tAno : ", MIN_ANO, MAX_ANO);
	data.mes = lerInteiro ("\t\tMes : ", 1, 12);
	maxDiaMes = calcularMaximoDiasPorMes (data.mes, data.ano);
	data.dia = lerInteiro ("\t\tDia : ", 1, maxDiaMes);
	return data;
}

int calcularNrDiasEntreDatas (tipoData dataInicial, tipoData dataFinal) {

	int dias, diasData1, diasData2;

	diasData1 = calcularNrDeDiasDesdeAnoRef (dataInicial);
	diasData2 = calcularNrDeDiasDesdeAnoRef (dataFinal);

	dias = diasData2 - diasData1;

	return dias;
}

int calcularNrDeDiasDesdeAnoRef (tipoData data) {

	int indiceAno, indiceMes;
	int quantidadeDeDiasNoAno, quantidadeDeDiasNoMes, contadorDeDias = 0;

	/* calcula o nr de dias que passaram desde MIN_ANO-01-01 ate á data introduzida */

	for (indiceAno = MIN_ANO; indiceAno < data.ano; indiceAno++) {
		quantidadeDeDiasNoAno = calcularMaximoDiasPorAno (indiceAno);
		contadorDeDias += quantidadeDeDiasNoAno;
		/* Soma todos os dias que passaram desde o ano MIN_ANO até ao ultimo dia do ano antes ao introduzido XXXX/12/31 */
	}
	for (indiceMes = 1; indiceMes < data.mes; indiceMes++) {
		quantidadeDeDiasNoMes = calcularMaximoDiasPorMes (indiceMes, data.ano);
		contadorDeDias += quantidadeDeDiasNoMes;
		/* Soma todos os dias que passaram desde o mes 01 até ao ultimo dia antes do mes introduzido	*/
	}

	contadorDeDias += data.dia;

	return contadorDeDias;
}

int calcularMaximoDiasPorAno (int ano) {
	int dias;

	if ( (ano % 400 == 0) || (ano % 4 == 0 && ano % 100 != 0)) {
		/*Se ano for bisexto*/
		dias = 366;
	} else {
		/*Se ano nao for bisexto*/
		dias = 365;
	}

	return dias;
}

int calcularMaximoDiasPorMes (int mes, int ano) {

	int dias;

	switch (mes) {
	case 2:
		if ( (ano % 400 == 0) || (ano % 4 == 0 && ano % 100 != 0)) {
			dias = 29;
		} else {
			dias = 28;
		}
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		dias = 30;
		break;
	default:
		dias = 31;

	}
	return dias;
}

tipoData calcularDataAposXDias (tipoData data, int dia) {

	tipoData datafinal;
	int quantidadeDeDias;

	quantidadeDeDias = calcularNrDeDiasDesdeAnoRef (data);
	quantidadeDeDias += dia;
	datafinal = calcularDataAtravesDosDias (quantidadeDeDias);

	return datafinal;
}

tipoData calcularDataAtravesDosDias (int totalDeDias) {

	tipoData data;

	data.ano = MIN_ANO;
	data.mes = 1;
	data.dia = 1;

	int diasAno = 0, indiceAno, diasMes = 0, indiceMes;

	for (indiceAno = MIN_ANO; diasAno < totalDeDias; indiceAno++) {
		diasAno += calcularMaximoDiasPorAno (indiceAno);
		data.ano = indiceAno;
	}
	diasAno -= calcularMaximoDiasPorAno (data.ano);
	totalDeDias -= diasAno;

	for (indiceMes = 1; diasMes < totalDeDias; indiceMes++) {
		diasMes += calcularMaximoDiasPorMes (indiceMes, data.ano);
		data.mes = indiceMes;
	}
	diasMes -= calcularMaximoDiasPorMes (data.mes, data.ano);

	totalDeDias -= diasMes;

	data.dia = totalDeDias;

	return data;

}

void limparEcra (void) {
	int indice;
	for (indice = 0; indice < 25; indice++) {
		printf ("\n");
	}
}

void enterParaContinuar (void) {

	printf ("                                                                               Prima ENTER para continuar...");
	while (getchar() != '\n');
	printf ("\n\n");
}
