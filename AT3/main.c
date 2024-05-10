#include <stdio.h>
#include <malloc.h>

#include "./include/types.h"
#include "./include/functions.h"

// Fun��o principal;
int main(void) {
	// Configurando o ambiente de execu��o;
	configurarAmbiente();

	FILE* arquivo = fopen(CAMINHO_ARQUIVO, "r");

	if(arquivo == NULL) {
		printf("Não foi possivel abrir o arquivo. Encerrando o programa...\n");
		return 1;
	} else {
		Quarto* quarto = (Quarto*) malloc(QTD_MAX_QUARTOS * sizeof(Quarto));

		if(quarto == NULL) {
			printf("Não foi possivel alocar a memoria. Encerrando o programa...\n");
			return 1;
		} else {
			int qtdQuartos = 0;

			// Lendo o arquivo e salvando as informa��es na struct Quarto;
			lerArquivo(arquivo, quarto, &qtdQuartos);

			// Exibindo o menu principal;
			exibirMenu(arquivo, quarto, &qtdQuartos);
		}

		// Liberando mem�ria alocada;
		free(quarto);
	}

	// Fechando o arquivo e encerrando o programa;
	fclose(arquivo);
	printf("Programa encerrado com sucesso!\n");
	return 0;
}
