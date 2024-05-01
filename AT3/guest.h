#pragma once

#include "stdio.h"

#define FILE_PATH "guests.csv"
#define LENGTH 100
#define ROOMS 50

typedef struct {
	char name[LENGTH];
} Guest;

typedef struct {
	int number;
	char status[11];
	Guest guest[4];
	int guestSize;
} Room;

static void configurandoAmbiente();
static void limparTela();
static void lendoArquivo(FILE* file, Room* room, int* num);
static void salvandoArquivo(FILE* file, Room* room, int qtdQuartos);
static void exibindoQuartos(Room* room, int num);
static void exibirMenu(Room* room, int* qtdDeQuartos);
static void adicionarHospede(Room* room, int qtdDeQuartos);