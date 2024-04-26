#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "guest.h"

int main() {
	configEnviroment();

	FILE* file = fopen(FILE_PATH, "r");

	if(file == NULL) {
		printf("Não foi possível criar o arquivo. Encerrando o programa...\n");
		exit(1);
	} else {
		Room* guest = (Room*) malloc(ROOMS * sizeof(Room));

		if(guest == NULL) {
			printf("Não foi possível alocar a memória. Encerrando o programa...\n");
			exit(1);
		} else {
			// to do: ler o arquivo e criar um menu;
		}

		// Liberando memória alocada;
		free(guest);
	}

	// Fechando o arquivo e encerrando o programa;
	fclose(file);
	printf("Programa encerrado com sucesso!\n");

	return 0;
}

static void readFile(FILE* file) {
	// to do: implementar a leitura do arquivo (analisar a melhor forma de fazer isso);
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