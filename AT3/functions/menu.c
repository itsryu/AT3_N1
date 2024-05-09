#include <stdio.h>

#include "../include/types.h"
#include "../include/functions.h"

// Menu principal do programa;
void exibirMenu(FILE* arquivo, Quarto* quarto, int* qtdQuartos) {
	int opcao = 0;

	do {
		limparTela();
		printf("---------- Gerenciador de H�spede ----------\n\n");
		printf("1. Inserir h�spedes em um quarto vazio\n2. Listar h�spedes por ordem alfab�tica\n3. Buscar h�spede\n");
		printf("4. Editar h�spede\n5. Liberar um quarto\n6. Mostrar os n�meros dos quartos vazios\n7. Salvar lista de h�spedes com respectivos quartos em arquivo.\n\n");
		printf("Pressione 0 para sair do programa\n");
		printf("Digite o n�mero da op��o desejada: ");

		while(scanf("%d", &opcao) != 1) {
			printf("Op��o inv�lida. Digite novamente: ");
			while(getchar() != '\n');
		}

		switch(opcao) {
			case 1:
			{
				limparTela();
				adicionarHospede(quarto, *qtdQuartos);
				pausarTela();
				break;
			}
			case 2:
			{
				limparTela();
				int qtdTotalHospedes = 0;
				Hospede* hospede = guardarHospedes(quarto, *qtdQuartos, &qtdTotalHospedes);

				quickSort(hospede, 0, qtdTotalHospedes - 1);
				listarHospedes(hospede, qtdTotalHospedes);

				pausarTela();
				break;
			}
			case 3:
			{
				limparTela();
				char nome[MAX_CHAR];

				printf("Digite o nome do hospede a ser buscado: ");
				while(scanf(" %[^\n]", nome) != 1) {
					printf("Nome inválido. Digite novamente: ");
				}

				Hospede* hospede = buscarHospede(quarto, *qtdQuartos, nome);

				if(hospede != NULL) {
					printf("Hóspede encontrado: %s\n", hospede->nome);
				} else {
					printf("Hóspede não encontrado\n");
				}

				pausarTela();
				break;
			}
			case 4:
			{
				limparTela();
				char nome[MAX_CHAR];

				printf("Digite o nome do hospede a ser editado: ");
				while(scanf(" %[^\n]", nome) != 1) {
					printf("Nome inválido. Digite novamente: ");
				}

				Hospede* hospede = buscarHospede(quarto, *qtdQuartos, nome);

				if(hospede != NULL) {
					editarHospede(hospede);
				} else {
					printf("Hóspede não encontrado\n");
				}

				pausarTela();
				break;
			}
			case 5:
			{
				int numQuarto = 0;
				exibirQuartosOcupados(quarto, *qtdQuartos);

				printf("Digite o número do quarto a ser liberado: ");
				while(scanf("%d", &numQuarto) != 1 || numQuarto < 1 || numQuarto > QTD_MAX_QUARTOS) {
					printf("Número de quarto inválido, tente novamente: ");
				}

				liberarQuarto(quarto, numQuarto);
				pausarTela();
				break;
			}
			case 6:
			{
				limparTela();
				quartoVazio(quarto);
				pausarTela();
				break;
			}
			case 7:
				limparTela();
				salvarArquivo(arquivo, quarto, *qtdQuartos);
				pausarTela();
				break;

			default:
				break;
		}
	} while(opcao != 0);
}