#pragma once

#define CAMINHO_ARQUIVO "./guests.csv"
#define QTD_MAX_QUARTOS 50
#define QTD_MAX_HOSPEDE 200
#define MAX_CHAR 100

typedef struct {
	char nome[MAX_CHAR];
} Hospede;

typedef struct {
	int num;
	char status[11];
	Hospede hospede[QTD_MAX_HOSPEDE / QTD_MAX_QUARTOS];
	int qtdHospede;
} Quarto;