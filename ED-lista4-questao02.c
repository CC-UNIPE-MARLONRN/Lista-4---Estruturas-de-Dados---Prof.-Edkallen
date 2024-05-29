/*
** Função : Criar um programa para Implementar uma pilha de números reais.
** Autor: Marlon Rufino do nascimento 2º período turma A 2024.1
** Data: 24/05/2024  
** Observações: Estou utilizando a função 'setlocale' da biblioteca 'locale.h' para a representação de acentuação padrão da lingua portuguesa, tais como ´, ^, `, ª ...  
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MAX 100 // Máximo de elementos da pilha

typedef struct pilha Pilha;

struct pilha {
    int topo; // elemento topo da pilha: array[tamanho do array - 1]
    float array[MAX]; // array do tipo real
};

Pilha *criarPilha(void) {
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));
    if (p == NULL) {
        printf("Memória insuficiente!\n");
        exit(1);
    }
    p->topo = 0;
    return p;
}

void push(Pilha *p, float valor) {
    // Se a pilha estiver cheia ele exibe a mensagem e não adiciona
    if (p->topo == MAX) {
        printf("\nPilha lotada!\n");
        return;
    }
    // insere o elemento na próxima posição do topo
    p->array[p->topo] = valor;
    p->topo++;
}

int verifica_pilha_vazia(Pilha *p) {
    return (p->topo == 0);
}

float pop(Pilha *p) {
    if (verifica_pilha_vazia(p)) {
        printf("\nPilha vazia!\n");
        return -1;
    }
    p->topo--;
    return p->array[p->topo]; // captura o elemento do topo
}

void exibir_pilha(Pilha *p) {
    if (verifica_pilha_vazia(p)) {
        printf("\nA pilha está vazia.\n");
        return;
    }
    printf("\nPilha (do topo para a base):\n");
    for (int i = p->topo - 1; i >= 0; i--) {
        printf("%.2f\n", p->array[i]);
    }
}

//Função Main
int main() {
    setlocale(LC_ALL, "portuguese");

    Pilha *pilha = criarPilha();
    int opcao;
    float valor;

    do {
        printf("\n======Menu:======\n");
        printf("1. Inserir (push)\n");
        printf("2. Retirar (pop)\n");
        printf("3. Exibir pilha\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite um valor para inserir: ");
                scanf("%f", &valor);
                push(pilha, valor);
                exibir_pilha(pilha);
                break;
            case 2:
                valor = pop(pilha);
                if (valor != -1) {
                    printf("\nValor retirado: %.2f\n", valor);
                }
                exibir_pilha(pilha);
                break;
            case 3:
                exibir_pilha(pilha);
                break;
            case 4:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                break;
        }
    } while (opcao != 4);

    free(pilha);
    return 0;
}
