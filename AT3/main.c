#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include "guest.h"

// Função principal;
int main(void) {
	// Configurando o ambiente de execução;
	configurandoAmbiente();

	FILE* arquivo = fopen(FILE_PATH, "r");

	if(arquivo == NULL) {
		printf("Não foi possível abrir o arquivo. Encerrando o programa...\n");
		exit(1);
	} else {
		Quarto* quarto = (Quarto*) malloc(ROOMS * sizeof(Quarto));

		if(quarto == NULL) {
			printf("Não foi possível alocar a memória. Encerrando o programa...\n");
			exit(1);
		} else {
			int qtdQuartos = 0;

			// Lendo o arquivo e salvando as informações na struct Room;
			lendoArquivo(arquivo, quarto, &qtdQuartos);

			// Exibindo o menu principal;
			exibirMenu(arquivo, quarto, &qtdQuartos);
		}

		// Liberando memória alocada;
		free(quarto);
	}

	// Fechando o arquivo e encerrando o programa;
	fclose(arquivo);
	printf("Programa encerrado com sucesso!\n");

	system("pause");
	return 0;
}

static void lendoArquivo(FILE* arquivo, Quarto* quarto, int* num) {
	while(fscanf(arquivo, "%d;%[^;\n]", &quarto[*num].num, quarto[*num].status) != EOF) {
		quarto[*num].qtdHospede = 0;

		while(fscanf(arquivo, ";%[^;\n]\n", quarto[*num].hospede[quarto[*num].qtdHospede].nome) == 1) {
			quarto[*num].qtdHospede++;

			if(quarto[*num].qtdHospede >= 4) break;
		}

		(*num)++;
	}
}

static void salvandoArquivo(FILE* arquivo, Quarto* quarto, int qtdQuartos) {
	arquivo = fopen(FILE_PATH, "w");

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
	}
}

// Exibe informações da struct;
static void exibindoQuartos(Quarto* quarto, int qtdQuartos) {
	for(int i = 0; i < qtdQuartos; i++) {
		printf("Nº: %d\n", quarto[i].num);
		printf("Status: %s\n", quarto[i].status);
		printf("Nº de hóspedes: %d\n", quarto[i].qtdHospede);

		if(quarto[i].qtdHospede > 0) {
			printf("Hóspedes:\n");
			for(int j = 0; j < quarto[i].qtdHospede; j++) {
				printf(" - %s\n", quarto[i].hospede[j].nome);
			}
		}

		printf("\n====================\n\n");
	}
}

static void limparTela() {
	#ifdef _WIN32
	system("cls");
	#elif __linux__
	system("clear");
	#endif
}

static void configurandoAmbiente() {
	setlocale(LC_ALL, "Portuguese");
	system("color 0A");
	system("title Gerenciamento de Hotel");
}

static void exibirMenu(FILE* arquivo, Quarto* quarto, int* qtdQuartos) {
	int opcao;

	do {
		limparTela();
		printf("---------- Gerenciador de Hóspede ----------\n\n");
		printf("1. Inserir hóspedes em um quarto vazio\n2. Listar hóspedes por ordem alfabética\n3. Buscar hóspede\n");
		printf("4. Editar hóspede\n5. Liberar um quarto\n6. Mostrar os números dos quartos vazios\n7. Salvar lista de hóspedes com respectivos quartos em arquivo.\n\n");
		printf("Pressione 0 para sair do programa\n");
		printf("Digite o numero da opcao desejada: ");

		while(scanf("%d", &opcao) != 1) {
			printf("Opção inválida. Digite novamente: ");
			while(getchar() != '\n');
		}

		switch(opcao) {
			case 1:
				limparTela();
				adicionarHospede(quarto, *qtdQuartos);
				system("pause");
				break;
			case 2:
				printf("xxx\n");
				// funcionalidade aqui;
				break;

			case 3:
				printf("xxx\n");
				// funcionalidade aqui;
				break;

			case 4:
				printf("xxx\n");
				// funcionalidade aqui;
				break;

			case 5:
				printf("xxx\n");
				// funcionalidade aqui;
				break;

			case 6:
				limparTela();
				exibirQuartosDisponiveis(quarto, *qtdQuartos);
				system("pause");
				break;

			case 7:
				limparTela();
				salvandoArquivo(arquivo, quarto, *qtdQuartos);
				printf("Arquivo salvo com sucesso!\n");
				system("pause");
				break;

			default:
				break;
		}
	} while(opcao != 0);
}

static void exibirQuartosDisponiveis(Quarto* quarto, int qtdQuartos) {
	printf("Quartos disponíveis:\n");
	for(int i = 0; i < qtdQuartos; i++) {
		if(strcmp(quarto[i].status, "Disponivel") == 0) {
			printf("Quarto Nº: %d\n", quarto[i].num);
		}
	}
}

static void adicionarHospede(Quarto* quarto, int qtdQuartos) {
	// Exibindo quartos disponíveis;
	exibirQuartosDisponiveis(quarto, qtdQuartos);

	int numQuarto = 0;

	printf("Insira o número do quarto: ");
	while(scanf("%d", &numQuarto) != 1 || numQuarto < 1) {
		printf("Número inválido. Insira novamente: ");
		while(getchar() != '\n');
	}

	// Verificando se o quarto está disponível;
	if(strcmp(quarto[numQuarto - 1].status, "Disponivel") == 0) {
		// TODO: Adicionar verificação se quarto chegou ao máximo de hóspedes e pensar na lógica do fato de um quarto possuir mais de um hóspede e quando ele ficará ocupado;
		Hospede hospede = { "" };

		printf("Digite o nome do hospede: ");
		while(scanf(" %[^\n]", hospede.nome) != 1) {
			printf("Erro ao ler o nome do hóspede, tente novamente: ");
			while(getchar() != '\n');
		};

		quarto[numQuarto - 1].hospede[quarto[numQuarto - 1].qtdHospede] = hospede;
		quarto[numQuarto - 1].qtdHospede++;
	} else {
		printf("Quarto não disponível, tente novamente.\n");
	}
}