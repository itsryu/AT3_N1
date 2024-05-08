#include <stdio.h>
#include <malloc.h>

#include "./include/types.h"
#include "./include/functions.h"

// TODO: Criar função para buscar hóspede pelo nome (possuir retorno pois será utilizado na função para editar um hóspede);
// TODO: Criar um README.md com as instruções de como compilar e executar o programa;
// TODO: Criar uma função para editar determinado hóspede;
// TODO: Criar função para exibir os quartos vazios;

// Função principal;
int main(void) {
	// Configurando o ambiente de execução;
	configurarAmbiente();

	FILE* arquivo = fopen(CAMINHO_ARQUIVO, "r");

	if(arquivo == NULL) {
		printf("Não foi possível abrir o arquivo. Encerrando o programa...\n");
		return 1;
	} else {
		Quarto* quarto = (Quarto*) malloc(QTD_MAX_QUARTOS * sizeof(Quarto));

		if(quarto == NULL) {
			printf("Não foi possível alocar a memória. Encerrando o programa...\n");
			return 1;
		} else {
			int qtdQuartos = 0;

			// Lendo o arquivo e salvando as informações na struct Quarto;
			lerArquivo(arquivo, quarto, &qtdQuartos);

			// Exibindo o menu principal;
			exibirMenu(arquivo, quarto, &qtdQuartos);
		}

		// Liberando memória alocada;
		free(quarto);
	}

	// Fechando o arquivo e encerrando o programa;
	fclose(arquivo);
	printf("Programa encerrado com sucesso!\n");
	return 0;
}