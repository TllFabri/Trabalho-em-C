#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h>
#include <time.h>   

#define MAX_COMPONENTES 20 

typedef struct {
    char nome[30];       
    char tipo[20];       
    int prioridade;      
} Componente;

void bubbleSortNome(Componente lista[], int n, int *comparacoes);
void insertionSortTipo(Componente lista[], int n, int *comparacoes);
void selectionSortPrioridade(Componente lista[], int n, int *comparacoes);
int buscaBinariaPorNome(Componente lista[], int n, char nome[]);
void mostrarComponentes(Componente lista[], int n);
void trocar(Componente *a, Componente *b); 

bool ordenadoPorNome = false;

void trocar(Componente *a, Componente *b) {
    Componente temp = *a;
    *a = *b;
    *b = temp;
}

void mostrarComponentes(Componente lista[], int n) {
    printf("\n--- Componentes da Torre ---\n");
    printf("%-30s %-15s %-10s\n", "NOME", "TIPO", "PRIORIDADE");
    printf("------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-30s %-15s %-10d\n",
               lista[i].nome, lista[i].tipo, lista[i].prioridade);
    }
    printf("------------------------------------------------------\n");
}

void bubbleSortNome(Componente lista[], int n, int *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            (*comparacoes)++; 
            if (strcmp(lista[j].nome, lista[j + 1].nome) > 0) {
                trocar(&lista[j], &lista[j + 1]);
            }
        }
    }
}

void insertionSortTipo(Componente lista[], int n, int *comparacoes) {
    *comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = lista[i];
        int j = i - 1;
        
        while (j >= 0) {
            (*comparacoes)++; 
            if (strcmp(lista[j].tipo, chave.tipo) > 0) {
                lista[j + 1] = lista[j];
                j--;
            } else {
                break;
            }
        }
        lista[j + 1] = chave;
    }
}

void selectionSortPrioridade(Componente lista[], int n, int *comparacoes) {
    *comparacoes = 0;
    int min_idx;

    for (int i = 0; i < n - 1; i++) {
        min_idx = i;
        for (int j = i + 1; j < n; j++) {
            (*comparacoes)++; 
            if (lista[j].prioridade < lista[min_idx].prioridade) {
                min_idx = j;
            }
        }
        trocar(&lista[min_idx], &lista[i]);
    }
}

int buscaBinariaPorNome(Componente lista[], int n, char nome[]) {
    int ini = 0, fim = n - 1;

    while (ini <= fim) {
        int meio = ini + (fim - ini) / 2; 
        int cmp = strcmp(lista[meio].nome, nome);

        if (cmp == 0) {
            return meio; 
        } else if (cmp < 0) {
            ini = meio + 1; 
        } else { 
            fim = meio - 1; 
        }
    }
    return -1; 
}

int main() {
    Componente componentes[MAX_COMPONENTES];
    int contador = 0;
    int opcao;

    do {
        printf("\n===== TORRE DE RESGATE - ORGANIZADOR DE COMPONENTES =====\n");
        printf("1. Adicionar Componente\n");
        printf("2. Listar Componentes\n");
        printf("3. Ordenar Componentes (Escolha de Estratégia)\n");
        printf("4. Buscar Componente-Chave (Busca Binária)\n");
        printf("0. Sair e Montar Torre\n");
        printf("---------------\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            opcao = -1;
            continue;
        }
        getchar(); 

        switch (opcao) {
            case 1:
                if (contador < MAX_COMPONENTES) {
                    printf("Nome do Componente: ");
                    fgets(componentes[contador].nome, 30, stdin);
                    componentes[contador].nome[strcspn(componentes[contador].nome, "\n")] = 0;

                    printf("Tipo (controle, suporte, propulsão, etc.): ");
                    fgets(componentes[contador].tipo, 20, stdin);
                    componentes[contador].tipo[strcspn(componentes[contador].tipo, "\n")] = 0;

                    printf("Prioridade (1 a 10): "); 
                    if (scanf("%d", &componentes[contador].prioridade) != 1 || componentes[contador].prioridade < 1 || componentes[contador].prioridade > 10) {
                        printf("Prioridade inválida! Usando prioridade 1.\n");
                        componentes[contador].prioridade = 1;
                    }
                    getchar();

                    contador++;
                    ordenadoPorNome = false; 
                    printf("Componente adicionado!\n");
                } else {
                    printf("Limite de componentes (%d) atingido!\n", MAX_COMPONENTES);
                }
                break;

            case 2:
                mostrarComponentes(componentes, contador);
                break;

            case 3: {
                if (contador == 0) {
                    printf("Nenhum componente para ordenar.\n");
                    break;
                }
                int crit;
                printf("\n--- Escolha a Estratégia de Ordenação ---\n");
                printf("1. Ordenar por Nome (Bubble Sort)\n");
                printf("2. Ordenar por Tipo (Insertion Sort)\n");
                printf("3. Ordenar por Prioridade (Selection Sort)\n");
                printf("Escolha: ");
                scanf("%d", &crit);
                getchar();

                int comp;
                clock_t inicio, fim;
                double tempo_execucao;
                
                inicio = clock();
                
                switch (crit) {
                    case 1:
                        bubbleSortNome(componentes, contador, &comp);
                        ordenadoPorNome = true;
                        printf("Ordenado por Nome (Bubble Sort).\n");
                        break;
                    case 2:
                        insertionSortTipo(componentes, contador, &comp);
                        ordenadoPorNome = false;
                        printf("Ordenado por Tipo (Insertion Sort).\n");
                        break;
                    case 3:
                        selectionSortPrioridade(componentes, contador, &comp);
                        ordenadoPorNome = false;
                        printf("Ordenado por Prioridade (Selection Sort).\n");
                        break;
                    default:
                        printf("Opção inválida!\n");
                        break;
                }
                
                fim = clock();
                tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

                printf("-> Total de Comparacoes: %d\n", comp);
                printf("-> Tempo de Execucao: %.6f segundos\n", tempo_execucao);

                mostrarComponentes(componentes, contador);
                break;
            }

            case 4: {
                if (!ordenadoPorNome) {
                    printf("A lista precisa estar ordenada por NOME antes de buscar o componente-chave!\n");
                    printf("Use a opcao 3 e escolha 'Ordenar por Nome'.\n");
                    break;
                }
                char nomeBusca[30];
                printf("Nome do componente-chave para busca: ");
                fgets(nomeBusca, 30, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = 0;
                
                int pos = buscaBinariaPorNome(componentes, contador, nomeBusca);
                
                if (pos >= 0) {
                    printf("\n*** Componente-Chave Encontrado na Posicao %d ***\n", pos + 1);
                    printf("-> %s (%s) - Prioridade: %d\n",
                           componentes[pos].nome, componentes[pos].tipo,
                           componentes[pos].prioridade);
                } else {
                    printf("Componente-Chave nao encontrado. A montagem nao pode ser iniciada!\n");
                }
                break;
            }

            case 0:
                printf("Iniciando Montagem Final da Torre... Saindo do sistema.\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

    }while (opcao != 0);

    return EXIT_SUCCESS;
}