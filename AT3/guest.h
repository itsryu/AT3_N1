#pragma once

#include "stdio.h"

#define FILE_PATH "guests.csv"
#define LENGTH 100
#define ROOMS 50

typedef struct {
	char nome[LENGTH];
} Hospede;

typedef struct {
	int num;
	char status[11];
	Hospede hospede[4];
	int qtdHospede;
} Quarto;

static void configurandoAmbiente();
static void limparTela();
static void lendoArquivo(FILE* arquivo, Quarto* quarto, int* qtdQuartos);
static void salvandoArquivo(FILE* arquivo, Quarto* quarto, int qtdQuartos);
static void exibirQuartosDisponiveis(Quarto* quarto, int qtdQuartos);
static void exibindoQuartos(Quarto* room, int num);
static void exibirMenu(FILE* arquivo, Quarto* quarto, int* qtdQuartos);
static void adicionarHospede(Quarto* quarto, int qtdDeQuartos);