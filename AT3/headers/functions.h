#pragma once

#include "stdio.h"

#include "../headers/types.h"

void limparTela();
void pausarTela();
void configurarAmbiente();
void alocarQuartos(FILE* arquivo);
void lerArquivo(FILE* arquivo, Quarto* quarto, int* qtdQuartos);
void salvarArquivo(FILE* arquivo, Quarto* quarto, int qtdQuartos);
void exibirQuartosDisponiveis(Quarto* quarto, int qtdQuartos);
void exibirQuartos(Quarto* quarto, int qtdQuartos);
void exibirMenu(FILE* arquivo, Quarto* quarto, int* qtdQuartos);
void adicionarHospede(Quarto* quarto, int qtdQuartos);
Hospede* guardarHospedes(Quarto* quarto, int qtdQuartos, int* qtdHospedes);
void listarHospedes(Hospede* hospede, int qtdHospedes);
void quickSort(Hospede* hospede, int left, int right);
int particionarVetor(Hospede* hospede, int left, int right);
void trocarValores(Hospede* a, Hospede* b);