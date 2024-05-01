#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "guest.h"

int main(void) {
	configEnviroment();

	FILE* file = fopen(FILE_PATH, "r");

	if(file == NULL) {
		printf("Não foi possível abrir o arquivo. Encerrando o programa...\n");
		exit(1);
	} else {
		Room* room = (Room*) malloc(ROOMS * sizeof(Room));

		if(room == NULL) {
			printf("Não foi possível alocar a memória. Encerrando o programa...\n");
			exit(1);
		} else {
			int num = 0;
			// Lendo o arquivo e salvando as informações na struct Room;
			readFile(file, room, &num);

			// TODO: criar um menu interativo;

			// Exibindo os dados da struct;
			showRooms(room, num);
		}

		// Liberando memória alocada;
		free(room);
	}

	// Fechando o arquivo e encerrando o programa;
	fclose(file);
	printf("Programa encerrado com sucesso!\n");

	system("pause");
	return 0;
}

static void readFile(FILE* file, Room* room, int* num) {
	while(fscanf(file, "%d;%[^;\n]", &room[*num].number, room[*num].status) != EOF) {
		room[*num].guestSize = 0;

		while(fscanf(file, ";%[^;\n]\n", room[*num].guest[room[*num].guestSize].name) == 1) {
			room[*num].guestSize++;

			if(room[*num].guestSize >= 4) break;
		}

		(*num)++;
	}
}

static void saveFile(FILE* file, Room* room) {
	file = fopen(FILE_PATH, "w");

	if(file == NULL) {
		printf("Erro ao abrir o arquivo. Encerrando o programa...\n");
		exit(1);
	} else {
		// TODO: criar lógica para salvar as modificações da struct Room no arquivo;
	}
}

// Exibe informações da struct;
static void showRooms(Room* room, int num) {
	for (int i = 0; i < num; i++) {
		printf("Nº: %d\n", room[i].number);
		printf("Status: %s\n", room[i].status);
		printf("Nº de hóspedes: %d\n", room[i].guestSize);

		if (room[i].guestSize > 0) {
			printf("Hóspedes:\n");
			for (int j = 0; j < room[i].guestSize; j++) {
				printf(" - %s\n", room[i].guest[j].name);
			}
		}

		printf("\n====================\n\n");
	}
}

static void clearScreen() {
	#ifdef _WIN32
	system("cls");
	#elif __linux__
	system("clear");
	#endif
}

static void configEnviroment() {
	setlocale(LC_ALL, "Portuguese");
	system("color 0A");
	system("title Gerenciamento de Hotel");
}

void menu(int x) {

	do {
		printf("1. Inserir hóspedes em um quarto vazio\n2. Listar hóspedes por ordem alfabética\n3. Buscar hóspede\n");
		printf("4. Editar hóspede\n5. Liberar um quarto\n6. Mostrar os números dos quartos vazios\n7. Salvar lista de hóspedes com respectivos quartos em arquivo.\n");
		printf("Pressione 0 para sair do programa\n");
		printf("Digite o numero da opcao desejada :");
		scanf("%d", &x);
		switch (x)
		{
		case 1:
			printf("xxx\n");
			// funcionalidade aqui;
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
			printf("xxx\n");
			// funcionalidade aqui;
			break;

		case 7:
			printf("xxx\n");
			// funcionalidade aqui;
			break;

		default:
			printf("Opção inválida!\n");
			break;

		}
	} while (x != 0);

}