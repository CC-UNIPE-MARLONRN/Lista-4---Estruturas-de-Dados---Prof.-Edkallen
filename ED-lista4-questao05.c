/*
** Função : Criar um programa para gerenciar uma pilha de processos em C, onde cada processo possui identificador(número) e uma descrição(string). 
** Autor: Marlon Rufino do nascimento 2º período turma A 2024.1
** Data: 26/05/2024  
** Observações: Estou utilizando a função 'setlocale' da biblioteca 'locale.h' para a representação de acentuação padrão da lingua portuguesa, tais como ´, ^, `, ª ...  
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define MAX 100 // Máximo de elementos da pilha
#define DESCRICAO_MAX 256 // Tamanho máximo da descrição

typedef struct {
    int id; // Identificador do processo
    char descricao[DESCRICAO_MAX]; // Descrição do processo
} Processo;

typedef struct {
    int topo; // Elemento topo da pilha: array[tamanho do array - 1]
    Processo array[MAX]; // Array de processos
} Pilha;

Pilha *criarPilha(void) {
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));
    if (p == NULL) {
        printf("Memória insuficiente!\n");
        exit(1);
    }
    p->topo = 0;
    return p;
}

void push(Pilha *p, Processo proc) {
    if (p->topo == MAX) {
        printf("\nPilha lotada!\n");
        return;
    }
    p->array[p->topo] = proc;
    p->topo++;
}

int verifica_pilha_vazia(Pilha *p) {
    return (p->topo == 0);
}

Processo pop(Pilha *p) {
    Processo processo;
    if (verifica_pilha_vazia(p)) {
        printf("\nPilha vazia!\n");
        processo.id = -1;
        strcpy(processo.descricao, "");
        return processo;
    }
    p->topo--;
    return p->array[p->topo];
}

void exibir_pilha(Pilha *p) {
    if (verifica_pilha_vazia(p)) {
        printf("\nA pilha está vazia.\n");
        return;
    }
    printf("\nPilha de processos (do topo para a base):\n");
    for (int i = p->topo - 1; i >= 0; i--) {
        printf("ID: %d - Descrição: %s\n", p->array[i].id, p->array[i].descricao);
    }
}

void esvaziar_pilha(Pilha *p) {
    while (!verifica_pilha_vazia(p)) {
        Processo processo = pop(p);
        printf("Encerrardo o processo #%d – %s\n", processo.id, processo.descricao);
    }
}

int main() {
    setLocale(LC_ALL,"portuguese");

    Pilha *pilha = criarPilha();
    int opcao;
    Processo processo;

    do {
        printf("\n====== Menu: ======\n");
        printf("1. Inserir processo\n");
        printf("2. Retirar processo\n");
        printf("3. Exibir Processos\n");
        printf("4. Encerrar processos\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
            case 1:
                printf("Digite o identificador do processo: ");
                scanf("%d", &processo.id);
                getchar(); // Limpa o buffer do teclado
                printf("Digite a descrição do processo: ");
                fgets(processo.descricao, DESCRICAO_MAX, stdin);
                processo.descricao[strcspn(processo.descricao, "\n")] = '\0'; 
                push(pilha, processo);
                exibir_pilha(pilha);
                break;
            case 2:
                processo = pop(pilha);
                if (processo.id != -1) {
                    printf("\nRemovido o processo #%d – %s\n", processo.id, processo.descricao);
                }
                exibir_pilha(pilha);
                break;
            case 3:
                exibir_pilha(pilha);
                break;
            case 4:
                printf("\nSaindo...\n");
                esvaziar_pilha(pilha);
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                break;
        }
    } while (opcao != 4);

    free(pilha);
    return 0;
}
