#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include "guest.h"

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
		exit(1);
	} else {
		Quarto* quarto = (Quarto*) malloc(QTD_MAX_QUARTOS * sizeof(Quarto));

		if(quarto == NULL) {
			printf("Não foi possível alocar a memória. Encerrando o programa...\n");
			exit(1);
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

	system("pause");
	return 0;
}

static void lerArquivo(FILE* arquivo, Quarto* quarto, int* qtdQuartos) {
	while(fscanf(arquivo, "%d;%[^;\n];", &quarto[*qtdQuartos].num, quarto[*qtdQuartos].status) != EOF) {
		quarto[*qtdQuartos].qtdHospede = 0;

		while(fscanf(arquivo, "%[^;\n];", quarto[*qtdQuartos].hospede[quarto[*qtdQuartos].qtdHospede].nome) == 1) {
			quarto[*qtdQuartos].qtdHospede++;

			if(quarto[*qtdQuartos].qtdHospede >= (QTD_MAX_HOSPEDE / QTD_MAX_QUARTOS)) break;
		}

		(*qtdQuartos)++;
	}
}

static void salvarArquivo(FILE* arquivo, Quarto* quarto, int qtdQuartos) {
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

static void exibirMenu(FILE* arquivo, Quarto* quarto, int* qtdQuartos) {
	int opcao = 0;

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
			{
				limparTela();
				adicionarHospede(quarto, *qtdQuartos);

				system("pause");
				break;
			}
			case 2:
			{
				limparTela();
				int qtdTotalHospedes = 0;
				Hospede* hospede = guardarHospedes(quarto, *qtdQuartos, &qtdTotalHospedes);
	
				quickSort(hospede, 0, qtdTotalHospedes - 1);
				listarHospedes(hospede, qtdTotalHospedes);

				system("pause");
				break;
			}
			case 3:
			{
				limparTela();
    			buscarHospedePorNome(quarto, *qtdQuartos);
				system("pause");
				break;
			}
			case 4:
			{
				printf("xxx\n");
				// funcionalidade aqui;
				system("pause");
				break;
			}
			case 5:
			{
				printf("xxx\n");
				// funcionalidade aqui;
				system("pause");
				break;
			}
			case 6:
			{
				limparTela();
				exibirQuartosDisponiveis(quarto, *qtdQuartos);

				system("pause");
				break;
			}
			case 7:
				limparTela();
				salvarArquivo(arquivo, quarto, *qtdQuartos);
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
			printf(" %d |", quarto[i].num);
		}
	}
	printf("\n\n");
}

static void adicionarHospede(Quarto* quarto, int qtdQuartos) {
	// Exibindo quartos disponíveis;
	exibirQuartosDisponiveis(quarto, qtdQuartos);

	int numQuarto = 0;

	printf("Insira o número do quarto: ");
	while(scanf("%d", &numQuarto) != 1 || numQuarto < 1 || numQuarto > QTD_MAX_QUARTOS) {
		printf("Número inválido. Insira novamente: ");
		while(getchar() != '\n');
	}

	// Verificando se o quarto está disponível;
	if(strcmp(quarto[numQuarto - 1].status, "Disponivel") == 0) {
		Hospede* hospede = (Hospede*) malloc(sizeof(Hospede));

		if(hospede == NULL) {
			printf("Erro ao alocar memória. Encerrando o programa...");
			exit(1);
		} else {
			printf("Digite o nome do hospede: ");
			while(scanf(" %[^\n]", hospede->nome) != 1) {
				printf("Erro ao ler o nome do hóspede, tente novamente: ");
				while(getchar() != '\n');
			};

			// Adicionando hóspede ao quarto e incrementando a quantidade total de hóspedes do quarto;
			quarto[numQuarto - 1].hospede[quarto[numQuarto - 1].qtdHospede] = *hospede;
			quarto[numQuarto - 1].qtdHospede++;

			// Alterando o status do quarto para ocupado;
			if(quarto[numQuarto - 1].qtdHospede == (QTD_MAX_HOSPEDE / QTD_MAX_QUARTOS)) strcpy(quarto[numQuarto - 1].status, "Ocupado");
		}

		// Liberando a memória do hospede;
		free(hospede);
	} else {
		printf("Quarto não disponível, tente novamente.\n");
	}
}

static void trocarValores(Hospede* a, Hospede* b) {
	Hospede temp = *a;
	*a = *b;
	*b = temp;
}

static int particionarVetor(Hospede* hospede, int left, int right) {
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

static void quickSort(Hospede* hospede, int left, int right) {
	if(left < right) {
		int p = particionarVetor(hospede, left, right);

		quickSort(hospede, left, p - 1);
		quickSort(hospede, p + 1, right);
	}
}

static Hospede* guardarHospedes(Quarto* quarto, int qtdQuartos, int* qtdTotalHospedes) {
	Hospede* hospede = (Hospede*) malloc(QTD_MAX_HOSPEDE * sizeof(Hospede));

	if(hospede == NULL) {
		printf("Erro ao alocar a memória. Encerrando o programa...\n");
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

static void listarHospedes(Hospede* hospede, int qtdHospedes) {
	printf("Hóspedes em ordem alfabética:\n\n");
	for(int i = 0; i < qtdHospedes; i++) {
		printf("- %s\n", hospede[i].nome);
	}
}

//--------------------------------------- FUNÇÕES PARA FINS DE DESENVOLVIMENTO ---------------------------------------//

// Alocar quartos no arquivo (Aloca todos os quartos como disponível e deleta os hóspedes);
static void alocarQuartos(FILE* arquivo) {
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

// Exibe informações da struct Quarto;
static void exibirQuartos(Quarto* quarto, int qtdQuartos) {
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

//-------------------------------------------------------------------------------------------------------------------//

static void limparTela() {
	#ifdef _WIN32
	system("cls");
	#elif __linux__
	system("clear");
	#endif
}

static void configurarAmbiente() {
	setlocale(LC_ALL, "Portuguese");
	system("color 0A");
	system("title Gerenciamento de Hotel");
}


// Adicionando funcao 3; buscando hospede

static void buscarHospedePorNome(Quarto* quarto, int qtdQuartos) {
    char nome[MAX];
    int encontrado = 0;

    printf("Digite o nome do hospede a ser buscado: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < qtdQuartos; i++) {
        for (int j = 0; j < quarto[i].qtdHospede; j++) {
            if (strcmp(quarto[i].hospede[j].nome, nome) == 0) {
                printf("Hospede encontrado:\n");
                printf("Quarto: %d\n", quarto[i].num);
                printf("Nome: %s\n", quarto[i].hospede[j].nome);
                encontrado = 1;
                break;
            }
        }
        if (encontrado) break;
    }

    if (!encontrado) {
        printf("Hospede nao encontrado.\n");
    }
}
