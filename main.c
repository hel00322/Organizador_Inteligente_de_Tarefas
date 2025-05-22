#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//definindo o numero maximo de tarefas
#define MAX_TAREFAS 50

//estrutura da uma tarefa
typedef struct {
    char titulo[100];
    int dias_prazo;
    int importancia;// niveis de importancia 1=baixa, 2=media, 3=alta
    int prioridade;
} Tarefa;

//funcao que calcula a prioridade da tarefa
int calcularPrioridade(int dias, int importancia) {
    return (importancia * 50) + (100 - dias);
}
//explicando a formula:
//(importancia * 50) = da um peso a importancia (ex: importancia 3 = peso 150 (3*50))
//(100 - dias) = quanto menos dias para o prazo final mais peso tem a tarefa (ex: prazo 3 dias = peso 97 (100-3))
//somando esses dois requisitos temos o valor da prioridade (150 + 97) 297
//resumindo, quanto MAIOR a importancia e MENOR o prazo MAIOR a prioridade

//funcao para add nova tarefa
void adicionarTarefa(Tarefa tarefas[], int *quantidade) {
    if (*quantidade >= MAX_TAREFAS) {
        printf("Voce atingiu o limite de tarefas\n");
        return;
    }

    Tarefa nova;//cria uma variavel para armazenar os dados da tarefa

    printf("\nDigite o titulo da tarefa: ");
    getchar(); // Limpa o enter do teclado (nao sei pq mas estava pulando a parte do titulo ai useu isso para limpar a memoria do teclado e ele entender que nao estava entrando uma variavel vazia " ")
    fgets(nova.titulo, 50, stdin); //usando o fgets pois ele le espacos, nova.titulo eh a variavel, 50 o tamanho e stdin eha origem (teclado)

    printf("Quantos dias faltam para o prazo? ");
    scanf("%d", &nova.dias_prazo);

    printf("Qual a importancia? (1=baixa, 2=media, 3=alta): ");
    scanf("%d", &nova.importancia);

    //calculando a prioridade da tarefa
    nova.prioridade = calcularPrioridade(nova.dias_prazo, nova.importancia);

    //add a tarefa na lista
    tarefas[*quantidade] = nova;
    (*quantidade)++;

    printf("\nTarefa adicionada com sucesso!\n");
}

//funcao para ordenar as tarefas pela prioridade
void ordenarTarefas(Tarefa tarefas[], int quantidade) {
    Tarefa temp; //variavel temporaria ok
    for (int i = 0; i < quantidade - 1; i++) {
        for (int j = i + 1; j < quantidade; j++) {
            if (tarefas[j].prioridade > tarefas[i].prioridade) {
                // Troca as tarefas de lugar
                temp = tarefas[i];
                tarefas[i] = tarefas[j];
                tarefas[j] = temp;
            }
        }
    }
}

// listar todas as tarefas
void listarTarefas(Tarefa tarefas[], int quantidade) {
    if (quantidade == 0) {
        printf("\nNenhuma tarefa cadastrada.\n");
        return;
    }

    ordenarTarefas(tarefas, quantidade);

    printf("\n==== Lista de Tarefas ====\n");
    for (int i = 0; i < quantidade; i++) {
        printf("\n%d. %s", i + 1, tarefas[i].titulo);
        printf("   Prazo: %d dias\n", tarefas[i].dias_prazo);
        printf("   Importancia: nivel %d\n", tarefas[i].importancia);
    }
}

int main() {
    Tarefa tarefas[MAX_TAREFAS];//vetor que guarda as tarefas
    int quantidade = 0;
    int opcao;

    do {
        //menu
        printf("\n===== ORGANIZADOR INTELIGENTE DE TAREFAS =====\n\n");
        printf("1 - Adicionar Tarefa\n");
        printf("2 - Listar Tarefas\n");
        printf("3 - Sair\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarTarefa(tarefas, &quantidade);
                break;
            case 2:
                listarTarefas(tarefas, quantidade);
                break;
            case 3:
                printf("\nEncerrando o programa.\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }

    } while (opcao != 3); //repete ate escolher a op sair

    return 0;
}
