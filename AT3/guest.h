#pragma once

#include "stdio.h"

#define CAMINHO_ARQUIVO "./guests.csv"
#define MAX 100
#define QTD_MAX_QUARTOS 50
#define QTD_MAX_HOSPEDE 200

typedef struct {
	char nome[MAX];
} Hospede;

typedef struct {
	int num;
	char status[11];
	Hospede hospede[4];
	int qtdHospede;
} Quarto;

static void configurarAmbiente();
static void limparTela();
static void alocarQuartos(FILE* arquivo);
static void lerArquivo(FILE* arquivo, Quarto* quarto, int* qtdQuartos);
static void salvarArquivo(FILE* arquivo, Quarto* quarto, int qtdQuartos);
static void exibirQuartosDisponiveis(Quarto* quarto, int qtdQuartos);
static void exibirQuartos(Quarto* quarto, int qtdQuartos);
static void exibirMenu(FILE* arquivo, Quarto* quarto, int* qtdQuartoss);
static void adicionarHospede(Quarto* quarto, int qtdDeQuartos);
static Hospede* guardarHospedes(Quarto* quarto, int qtdQuartos, int* qtdHospedes);
static void listarHospedes(Hospede* hospede, int qtdHospedes);
static void quickSort(Hospede* hospede, int left, int right);
static int particionarVetor(Hospede* hospede, int left, int right);
static void trocarValores(Hospede* a, Hospede* b);