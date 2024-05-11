#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <malloc.h>

#include "../include/types.h"
#include "../include/functions.h"

// Le o arquivo e salva as informações na struct Quarto;
void lerArquivo(FILE* arquivo, Quarto* quarto, int* qtdQuartos) {
	while(fscanf(arquivo, "%d;%[^;\n];", &quarto[*qtdQuartos].num, quarto[*qtdQuartos].status) != EOF) {
		quarto[*qtdQuartos].qtdHospede = 0;

		while(fscanf(arquivo, "%[^;\n];", quarto[*qtdQuartos].hospede[quarto[*qtdQuartos].qtdHospede].nome) == 1) {
			quarto[*qtdQuartos].qtdHospede++;

			if(quarto[*qtdQuartos].qtdHospede >= (QTD_MAX_HOSPEDE / QTD_MAX_QUARTOS)) break;
		}

		(*qtdQuartos)++;
	}
}

// Pega as informações da struct Quarto e salva no arquivo;
void salvarArquivo(FILE* arquivo, Quarto* quarto, int qtdQuartos) {
	arquivo = fopen(CAMINHO_ARQUIVO, "w");

	if(arquivo == NULL) {
		printf("Erro ao abrir o arquivo. Encerrando o programa...\n");
		exit(1);
	} else {
		for(int i = 0; i < qtdQuartos; i++) {
			if(quarto[i].num != 0) {
				fprintf(arquivo, "%d;%s", quarto[i].num, quarto[i].status);

				for(int j = 0; j < quarto[i].qtdHospede; j++) {
					fprintf(arquivo, ";%s", quarto[i].hospede[j].nome);
				}

				fprintf(arquivo, "\n");
			}
		}

		fclose(arquivo);

		printf("Arquivo salvo com sucesso!\n");
	}
}

void adicionarHospede(Quarto* quarto, int qtdQuartos) {
   // Exibindo quartos disponsaveis;
	exibirQuartosDisponiveis(quarto, qtdQuartos);

	int numQuarto = 0;

	printf("Insira o numero do quarto: ");
	while(scanf("%d", &numQuarto) != 1 || numQuarto < 1 || numQuarto > QTD_MAX_QUARTOS) {
		printf("Numero invalido. Insira um numero valido: ");
		while(getchar() != '\n');
	}

	// Verificando se o quarto esta disponivel;
	if(strcmp(quarto[numQuarto - 1].status, "Disponivel") == 0) {
		Hospede* hospede = (Hospede*) malloc(sizeof(Hospede));

		if(hospede == NULL) {
			printf("Erro ao alocar memoria. Encerrando o programa...");
			exit(1);
		} else {
			printf("Digite o nome do hospede: ");
			while(scanf(" %[^\n]", hospede->nome) != 1) {
				printf("Erro ao ler o nome do hospede, tente novamente: ");
				while(getchar() != '\n');
			};

			// Adicionando hospede ao quarto e incrementando a quantidade total de hospedes do quarto;
			quarto[numQuarto - 1].hospede[quarto[numQuarto - 1].qtdHospede] = *hospede;
			quarto[numQuarto - 1].qtdHospede++;

			// Alterando o status do quarto para ocupado;
			if(quarto[numQuarto - 1].qtdHospede == (QTD_MAX_HOSPEDE / QTD_MAX_QUARTOS)) strcpy(quarto[numQuarto - 1].status, "Ocupado");
		}

		// Liberando a memoria do hospede;
		free(hospede);
	} else {
		printf("Quarto nao disponivel, tente novamente.\n");
	}
}

void trocarValores(Hospede* a, Hospede* b) {
	Hospede temp = *a;
	*a = *b;
	*b = temp;
}

int particionarVetor(Hospede* hospede, int left, int right) {
	Hospede pivot = hospede[right];
	int i = left - 1;

	for(int j = left; j < right; j++) {
		Hospede* A = &hospede[j];
		Hospede* B = &pivot;

		if(strcmp(A->nome, B->nome) <= 0) {
			i++;
			trocarValores(&hospede[i], &hospede[j]);
		}
	}

	trocarValores(&hospede[i + 1], &hospede[right]);
	return i + 1;
}

void quickSort(Hospede* hospede, int left, int right) {
	if(left < right) {
		int p = particionarVetor(hospede, left, right);

		quickSort(hospede, left, p - 1);
		quickSort(hospede, p + 1, right);
	}
}

// Aloca todos os hospedes em uma struct Hospede;
Hospede* guardarHospedes(Quarto* quarto, int qtdQuartos, int* qtdTotalHospedes) {
	Hospede* hospede = (Hospede*) malloc(QTD_MAX_HOSPEDE * sizeof(Hospede));

	if(hospede == NULL) {
		printf("Erro ao alocar memoria. Encerrando o programa...\n");
		exit(1);
	} else {
		for(int i = 0; i < qtdQuartos; i++) {
			for(int j = 0; j < quarto[i].qtdHospede; j++) {
				hospede[*qtdTotalHospedes] = quarto[i].hospede[j];

				(*qtdTotalHospedes)++;
			}
		}
	}

	return hospede;
}

Hospede* buscarHospede(Quarto* quarto, int qtdQuartos, char* nome) {
	for(int i = 0; i < qtdQuartos; i++) {
		for(int j = 0; j < quarto[i].qtdHospede; j++) {
			if(strcmp(quarto[i].hospede[j].nome, nome) == 0) {
				return &quarto[i].hospede[j];
			}
		}
	}

	return NULL;
}

void editarHospede(Hospede* hospede) {
	char novoNome[MAX_CHAR] = { "" };
	printf("Digite o novo nome para o hóspede: ");
	while(scanf(" %[^\n]", novoNome) != 1) {
		printf("Nome inválido. Digite novamente: ");
	}

	strcpy(hospede->nome, novoNome);

	printf("Hospede atualizado com sucesso!\n");
}

void liberarQuarto(Quarto* quarto, int numQuarto) {
	if(strcmp(quarto[numQuarto - 1].status, "Disponivel") == 0) {
		printf("Quarto já está disponível.\n");
	} else {
		Hospede** hospede = &quarto[numQuarto - 1].hospede;

		for(int i = 0; i < quarto[numQuarto - 1].qtdHospede; i++) {
			hospede[i] = NULL;
		}

		quarto[numQuarto - 1].qtdHospede = 0;
		strcpy(quarto[numQuarto - 1].status, "Disponivel");

		printf("Quarto liberado com sucesso!\n");
	}
}


void exibirHospedes(Hospede* hospede, int qtdHospedes) {
	printf("Hospedes:\n\n");

	for(int i = 0; i < qtdHospedes; i++) {
		printf("%dº - %s\n", i + 1, hospede[i].nome);
	}

	printf("\n");
}

void exibirQuartosDisponiveis(Quarto* quarto, int qtdQuartos) {
	printf("Quartos disponiveis:\n");
	for(int i = 0; i < qtdQuartos; i++) {
		if(strcmp(quarto[i].status, "Disponivel") == 0) {
			printf("%d", quarto[i].num);
			if(i < qtdQuartos - 1) printf(" - ");
		}
	}
	printf("\n\n");
}

void exibirQuartosVazios(Quarto* quarto) {
	printf("Quartos vazios:\n");
	for(int i = 0; i < QTD_MAX_QUARTOS; i++) {
		if(quarto[i].qtdHospede == 0) {
			printf("%d", quarto[i].num);
			if(i < QTD_MAX_QUARTOS - 1) printf(" - ");
		}
	}
	printf("\n\n");
}

void exibirQuartosOcupados(Quarto* quarto, int qtdQuartos, int* qtdQuartosOcupados) {
	int aux = 1;

	printf("Quartos ocupados:\n");
	for(int i = 0; i < qtdQuartos; i++) {
		if(strcmp(quarto[i].status, "Ocupado") == 0) {
			if(!aux) printf(" - ");

			printf("%d", quarto[i].num);
			aux = 0, (*qtdQuartosOcupados)++;
		}
	}

	printf("\n");
}
//--------------------------------------- FUNÇÕES PARA FINS DE DESENVOLVIMENTO ---------------------------------------//

// Exibe informações da struct Quarto;
void exibirQuartos(Quarto* quarto, int qtdQuartos) {
	for(int i = 0; i < qtdQuartos; i++) {
		printf("Nº do quarto: %d\n", quarto[i].num);
		printf("Status: %s\n", quarto[i].status);
		printf("Nº de hospedes: %d\n", quarto[i].qtdHospede);

		if(quarto[i].qtdHospede > 0) {
			printf("Hospedes:\n");
			for(int j = 0; j < quarto[i].qtdHospede; j++) {
				printf(" - %s\n", quarto[i].hospede[j].nome);
			}
		}

		printf("\n====================\n\n");
	}
}

// Alocar quartos no arquivo (Aloca todos os quartos como disponivel e deleta os hospedes);
void alocarQuartos(FILE* arquivo) {
	arquivo = fopen(CAMINHO_ARQUIVO, "w");

	if(arquivo == NULL) {
		printf("Erro ao abrir o arquivo. Encerrando o programa...\n");
		exit(1);
	} else {
		for(int i = 0; i < QTD_MAX_QUARTOS; i++) {
			fprintf(arquivo, "%d;Disponivel\n", i + 1);
		}
	}

	fclose(arquivo);
}

//-------------------------------------------------------------------------------------------------------------------//

// Limpa a tela do console;
void limparTela() {
	#ifdef _WIN32
	system("cls");
	#elif __linux__
	system("clear");
	#endif
}

// Pausa a tela do console;
void pausarTela() {
	printf("Pressione ENTER para continuar...\n");
	while(getchar() != '\n');
	getchar();
}

// Configura o ambiente de execução;
void configurarAmbiente() {
	#ifdef _WIN32
	system("color 0A");
	system("title Gerenciamento de Hotel");
	#endif

	char* local = setlocale(LC_ALL, "");

	if(local == NULL || strcmp(local, "Portuguese_Brazil.1252") != 0) {
		#ifdef _WIN32
		setlocale(LC_ALL, "Portuguese");
		#elif __linux__
		setlocale(LC_ALL, "pt_BR.UTF-8");
		#endif
	}
}

//-------------------------------------------------------------------------------------------------------------------//

