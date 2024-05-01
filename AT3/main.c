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
		Room* room = (Room*) malloc(ROOMS * sizeof(Room));

		if(room == NULL) {
			printf("Não foi possível alocar a memória. Encerrando o programa...\n");
			exit(1);
		} else {
			int qtdQuartos = 0;

			// Lendo o arquivo e salvando as informações na struct Room;
			lendoArquivo(arquivo, room, &qtdQuartos);

			// Exibindo o menu principal;
			exibirMenu(arquivo, room, &qtdQuartos);
		}

		// Liberando memória alocada;
		free(room);
	}

	// Fechando o arquivo e encerrando o programa;
	fclose(arquivo);
	printf("Programa encerrado com sucesso!\n");

	system("pause");
	return 0;
}

static void lendoArquivo(FILE* file, Room* room, int* num) {
	while(fscanf(file, "%d;%[^;\n]", &room[*num].number, room[*num].status) != EOF) {
		room[*num].guestSize = 0;

		while(fscanf(file, ";%[^;\n]\n", room[*num].guest[room[*num].guestSize].name) == 1) {
			room[*num].guestSize++;

			if(room[*num].guestSize >= 4) break;
		}

		(*num)++;
	}
}

static void salvandoArquivo(FILE* file, Room* room, int qtdQuartos) {
	file = fopen(FILE_PATH, "w");

	if(file == NULL) {
		printf("Erro ao abrir o arquivo. Encerrando o programa...\n");
		exit(1);
	} else {
		for(int i = 0; i < qtdQuartos; i++) {
			if(room[i].number != 0) {
				fprintf(file, "%d;%s", room[i].number, room[i].status);

				for(int j = 0; j < room[i].guestSize; j++) {
					fprintf(file, ";%s", room[i].guest[j].name);
				}

				fprintf(file, "\n");
			}
		}

		fclose(file);
	}
}

// Exibe informações da struct;
static void exibindoQuartos(Room* room, int num) {
	for(int i = 0; i < num; i++) {
		printf("Nº: %d\n", room[i].number);
		printf("Status: %s\n", room[i].status);
		printf("Nº de hóspedes: %d\n", room[i].guestSize);

		if(room[i].guestSize > 0) {
			printf("Hóspedes:\n");
			for(int j = 0; j < room[i].guestSize; j++) {
				printf(" - %s\n", room[i].guest[j].name);
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

static void exibirMenu(FILE* arquivo, Room* room, int* qtdQuartos) {
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
				adicionarHospede(room, *qtdQuartos);
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
				exibirQuartosDisponiveis(room, *qtdQuartos);
				system("pause");
				break;

			case 7:
				limparTela();
				salvandoArquivo(arquivo,room, *qtdQuartos);
				printf("Arquivo salvo com sucesso!\n");
				system("pause");
				break;

			default:
				break;
		}
	} while(opcao != 0);
}

static void exibirQuartosDisponiveis(Room* room, int qtdQuartos) {
	printf("Quartos disponíveis:\n");
	for(int i = 0; i < qtdQuartos; i++) {
		if(strcmp(room[i].status, "Disponivel") == 0) {
			printf("Quarto Nº: %d\n", room[i].number);
		}
	}
}

static void adicionarHospede(Room* room, int qtdQuartos) {
	// Exibindo quartos disponíveis;
	exibirQuartosDisponiveis(room, qtdQuartos);

	int numQuarto = 0;

	printf("Insira o número do quarto: ");
	while(scanf("%d", &numQuarto) != 1 || numQuarto < 1) {
		printf("Número inválido. Insira novamente: ");
		while(getchar() != '\n');
	}

	// Verificando se o quarto está disponível;
	if(strcmp(room[numQuarto].status, "Disponivel") == 0) {
		// TODO: Adicionar lógica para adicionar hóspede no quarto;
			Guest hospede;
		
		printf("Digite o nome do hospede");
		scanf("%s \n", hospede.name);
		
		room [numQuarto].guest [0] = hospede;
		room [numQuarto].guestSize ++;
	} else {
		printf("Quarto não disponível, tente novamente.");
	}
}