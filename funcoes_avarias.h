#ifndef FUNCOES_AVARIAS_H_INCLUDED
#define FUNCOES_AVARIAS_H_INCLUDED

#include "estruturas.h"

tipoAvaria* adicionarAvaria (tipoAvaria vetorAvarias[], int *totalAvarias, tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis);
int lerTipoAvaria (char mensagem [MAX_STRING]);
int procurarAvaria (tipoAvaria vetorAvarias[], int totalAvarias, int idPortatil);
void adicionarReparacao (tipoAvaria vetorAvarias[], int totalAvarias, tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis);
void listarAvarias (tipoAvaria vetorAvarias[], int totalAvarias, tipoPortatil vetorPortateis[MAX_PORTATEIS], int totalPortateis);
void mostrarAvaria (tipoAvaria avaria);

#endif // FUNCOES_AVARIAS_H_INCLUDED
