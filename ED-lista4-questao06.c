/*
** Função : Fazer um programa, em C, que simule uma lista de compras com lista encadeada;
** Autor: Marlon Rufino do nascimento 2º período turma A 2024.1
** Data: 26/05/2024  
** Observações: Estou utilizando a função 'setlocale' da biblioteca 'locale.h' para a representação de acentuação padrão da lingua portuguesa, tais como ´, ^, `, ª ...  
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define MAX_NOME 100

// Definição da estrutura para representar um item da lista de compras
typedef struct item {
    char nome[MAX_NOME]; // Nome do item
    int quantidade; // Quantidade do item
    struct item *prox_item; // Ponteiro para o próximo item na lista
} Item;

// Função para criar um novo item
Item* criarItem(char *nome, int quantidade) {
    Item *novoItem = (Item *)malloc(sizeof(Item));
    if (novoItem == NULL) {
        printf("Memória insuficiente!\n");
        exit(1);
    }
    strcpy(novoItem->nome, nome);
    novoItem->quantidade = quantidade;
    novoItem->prox_item = NULL;
    return novoItem;
}

// Função para inserir um novo item na lista
Item* insere_item(Item *lista, Item *novoItem) {
    novoItem->prox_item = lista;
    return novoItem;
}

// Função para remover um item da lista
Item* remover_item(Item *lista, char *nome) {
    Item *anterior = NULL;
    Item *atual = lista;

    // Procurar o item na lista
    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        anterior = atual;
        atual = atual->prox_item;
    }

    // Se o item não foi encontrado
    if (atual == NULL) {
        printf("\nItem não encontrado!\n");
        return lista;
    }

    // Remover o item da lista
    if (anterior == NULL) {
        lista = atual->prox_item;
    } else {
        anterior->prox_item = atual->prox_item;
    }

    free(atual); // Liberar a memória do item removido
    printf("\nItem removido com sucesso!\n");
    return lista;
}

// Função para exibir todos os itens da lista
void exibir_itens(Item *lista) {
    if (lista == NULL) {
        printf("\nLista de compras vazia!\n");
        return;
    }

    printf("\nLista de compras:\n");
    for (Item *p = lista; p != NULL; p = p->prox_item) {
        printf("- %s, Quantidade: %d\n", p->nome, p->quantidade);
    }
}

// Função para consultar um item na lista
void consultar_item(Item *lista, char *nome) {
    for (Item *p = lista; p != NULL; p = p->prox_item) {
        if (strcmp(p->nome, nome) == 0) {
            printf("\nItem encontrado:\n");
            printf("Nome: %s, Quantidade: %d\n", p->nome, p->quantidade);
            return;
        }
    }
    printf("\nItem não encontrado.\n");
}

// Função principal
int main() {
    setlocale(LC_ALL, "portuguese"); 

    Item *lista = NULL; // Inicializar a lista de compras como vazia
    int opcao;
    char nome[MAX_NOME];
    int quantidade;

    do {
        printf("\n======= MENU =======\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Consultar item\n");
        printf("4. Exibir lista de compras\n");
        printf("5. Sair\n");
        printf("====================\n");

        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer de entrada

        switch (opcao) {
            case 1:
                printf("Digite o nome do item: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                printf("Digite a quantidade: ");
                scanf("%d", &quantidade);
                getchar(); // Limpar o buffer de entrada
                lista = insere_item(lista, criarItem(nome, quantidade));
                break;
            case 2:
                if (lista == NULL)
                    printf("\nLista de compras vazia!\n");
                else {
                    printf("Digite o nome do item a ser removido: ");
                    fgets(nome, sizeof(nome), stdin);
                    nome[strcspn(nome, "\n")] = '\0';
                    lista = remover_item(lista, nome);
                }
                break;
            case 3:
                if (lista == NULL)
                    printf("\nLista de compras vazia!\n");
                else {
                    printf("Digite o nome do item a ser consultado: ");
                    fgets(nome, sizeof(nome), stdin);
                    nome[strcspn(nome, "\n")] = '\0';
                    consultar_item(lista, nome);
                }
                break;
            case 4:
                exibir_itens(lista);
                break;
            case 5:
                printf("\nSaindo do programa...\n");
                // Liberar a memória alocada para os itens da lista
                while (lista != NULL) {
                    Item *temp = lista;
                    lista = lista->prox_item;
                    free(temp);
                }
                return 0;
            default:
                printf("\nOpção inválida. Por favor, escolha uma opção válida.\n");
                break;
        }
    } while (opcao != 5);

    return 0;
}
