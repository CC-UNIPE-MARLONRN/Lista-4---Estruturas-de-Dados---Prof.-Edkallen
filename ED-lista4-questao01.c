/*
** Função : Criar uma base de dados usando a técnica de lista encadeada para gerir os livros de uma biblioteca.
** Autor: Marlon Rufino do nascimento 2º período turma A 2024.1
** Data: 24/05/2024  
** Observações: Estou utilizando a função 'setlocale' da biblioteca 'locale.h' para a representação de acentuação padrão da lingua portuguesa, tais como ´, ^, `, ª ...  
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX 100 //Defina o MAX de livros da biblioteca

//Criação de um dado Livros referenciando a estrutura livros
typedef struct livros Livros;

//Estrutura livros
struct livros {
    char autor[60];
    char titulo[50];
    char editora[50];
    int ano_de_edicao;
    struct Livro *prox_livro;
};

//Função que cria uma nova estrutura e capitura como parametro os dados e insere na estrutura de livros 
Livros* criarLivro(char *autor, char *titulo, char *editora, int ano) {
    Livros* novoLivro = (Livros*)malloc(sizeof(Livros));
    strcpy(novoLivro->autor, autor);
    strcpy(novoLivro->titulo, titulo);
    strcpy(novoLivro->editora, editora);
    novoLivro->ano_de_edicao = ano;
    novoLivro->prox_livro = NULL;
    return novoLivro;
}

//Realiza uma inserção ordenada dos livros de maneira que um livro é inserido em seguida do outro
Livros *insere_ordenado(Livros *l, Livros *novoLivro) {
    Livros *anterior = NULL;
    Livros *atual = l;

    // Encontra a posição correta na lista
    while (atual != NULL && strcmp(atual->titulo, novoLivro->titulo) < 0) {
        anterior = atual;
        atual = atual->prox_livro;
    }

    // Insere o novo livro na posição
    if (anterior == NULL) {
        novoLivro->prox_livro = l;
        return novoLivro;
    } else {
        anterior->prox_livro = novoLivro;
        novoLivro->prox_livro = atual;
        return l;
    }
}


//Remove os livros de acordo com a posicao na lista
Livros *remover_livro(Livros *l, char *titulo) {
  Livros *li_ant = NULL;
  Livros *li_atual = l;
  while (li_atual != NULL && strcmp(li_atual->titulo, titulo) != 0) {
    li_ant = li_atual;
    li_atual = li_atual->prox_livro;
  }
  if (li_atual == NULL) {
    return l;
    printf("\nLivro não encontrado!");
  }
  if (li_ant == NULL) {
    l = li_atual->prox_livro;
  } else {
    li_ant->prox_livro = li_atual->prox_livro;
  }
  free(li_atual);
  printf("\nLivro removido com sucesso!\n");
  return l;
}

//Imprime os livros
void exibe_livros(Livros*l) {
  Livros *p;
  printf("\nBiblioteca: [ ");
  for (p = l; p != NULL; p = p->prox_livro) {
    printf("%s: (%s), ", p->titulo, p->autor);
  }
  printf("\b\b ]\n");
}

void buscaLivroPorTitulo(Livros *l, char *titulo) {
    Livros *p;
    int encontrado = 0;
    for (p = l; p != NULL; p = p->prox_livro) {
        if (strcmp(p->titulo, titulo) == 0) {
            encontrado = 1;
            printf("\nLivro encontrado:\n");
            printf("Autor: %s\n", p->autor);
            printf("Título: %s\n", p->titulo);
            printf("Editora: %s\n", p->editora);
            printf("Ano de Edição: %d\n", p->ano_de_edicao);
            break;
        }
       }
       if(!encontrado){
           printf("\nLivro não encontrado.\n");
       }
    }

void buscaLivrosPorAutor(Livros *l, char *autor) {
    Livros *p;
    int encontrou = 0;
    printf("\nAutor: %s\n", autor);
    printf("\nLivros do autor %s:\n", autor);
    for (p = l; p != NULL; p = p->prox_livro) {
        if (strcmp(p->autor, autor) == 0) {
            printf("- %s (%d);\n", p->titulo, p->ano_de_edicao); 
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf("\nNenhum livro encontrado com esse autor.\n");
    }
}

void alteracaoLivro(Livros *l, char *titulo, int tipo_de_alteracao, char *novo_valor) {
    Livros *p;
    for (p = l; p != NULL; p = p->prox_livro) {
        if (strcmp(p->titulo, titulo) == 0) {
            break;
        }
    }

    if (p == NULL) {
        printf("Livro não encontrado.\n");
         return;
    }

    switch (tipo_de_alteracao) {
        case 1:
            strcpy(p->autor, novo_valor);
            printf("Autor alterado com sucesso!\n");
            break;
        case 2:
            strcpy(p->titulo, novo_valor);
            printf("Título alterado com sucesso!\n");
            break;
        case 3:
            strcpy(p->editora, novo_valor);
            printf("Editora alterada com sucesso!\n");
            break;
        case 4: {
            int novo_ano = atoi(novo_valor);
            p->ano_de_edicao = novo_ano;
            printf("Ano de edição alterado com sucesso!\n");
            break;
        }
        default:
            printf("Opção de alteração inválida!\n");
            break;
    }
}

//Função main
int main() {
    setlocale(LC_ALL, "portuguese");

    Livros *biblioteca = NULL;
    int opcao = 0;
    char autor[60];
    char titulo[50];
    char editora[50];
    int ano;

    do {
        printf("\n======= MENU =======\n");
        printf("1. Inserir livro\n");
        printf("2. Remover livro\n");
        printf("3. Exibir biblioteca\n");
        printf("4. Buscar livro por título\n");
        printf("5. Buscar livros por autor\n");
        printf("6. Alterar livro\n");
        printf("7. Sair\n");
        printf("====================\n");

        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer de entrada

        switch (opcao) {
            case 1:
                printf("Digite o autor: ");
                fgets(autor, sizeof(autor), stdin);
                autor[strcspn(autor, "\n")] = '\0';
                printf("Digite o título: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0'; 
                printf("Digite a editora: ");
                fgets(editora, sizeof(editora), stdin);
                editora[strcspn(editora, "\n")] = '\0';
                printf("Digite o ano de edição: ");
                scanf("%d", &ano);
                getchar(); // Limpar o buffer de entrada
                biblioteca = insere_ordenado(biblioteca, criarLivro(autor, titulo, editora, ano));
                break;
            case 2:
                if (biblioteca == NULL)
                    printf("\nBiblioteca vazia!\n");
                else {
                    printf("Digite o título do livro a ser removido: ");
                    fgets(titulo, sizeof(titulo), stdin);
                    titulo[strcspn(titulo, "\n")] = '\0'; 
                    biblioteca = remover_livro(biblioteca, titulo);
                }
                break;
            case 3: 
                if (biblioteca == NULL)
                    printf("\nBiblioteca vazia!\n");
                else
                    exibe_livros(biblioteca);
                break;
            case 4:
                if (biblioteca == NULL)
                    printf("\nBiblioteca vazia!\n");
                else {
                    printf("Digite o título do livro a ser buscado: ");
                    fgets(titulo, sizeof(titulo), stdin);
                    titulo[strcspn(titulo, "\n")] = '\0'; 
                    buscaLivroPorTitulo(biblioteca, titulo);
                }
                break;
            case 5:
                if (biblioteca == NULL)
                    printf("\nBiblioteca vazia!\n");
                else {
                    printf("Digite o nome do autor para buscar livros: ");
                    fgets(autor, sizeof(autor), stdin);
                    autor[strcspn(autor, "\n")] = '\0'; 
                    buscaLivrosPorAutor(biblioteca, autor);
                }
                break;
            case 6:
                if (biblioteca == NULL)
                    printf("\nBiblioteca vazia!\n");
                else {
                    char livro_alterar[50];

                    printf("\nDigite o título do livro que deseja alterar: ");
                    fgets(livro_alterar, sizeof(livro_alterar), stdin);
                    livro_alterar[strcspn(livro_alterar, "\n")] = '\0'; 
                    
                     Livros* livro = NULL;
                     //fazer uma verificação se existe aquele livro antes de executar as opções
                        for (livro = biblioteca; livro != NULL; livro = livro->prox_livro) {
                            if (strcmp(livro->titulo, livro_alterar) == 0) {
                                break;
                            }
                        }

                        if (livro == NULL) {
                            printf("\nLivro não encontrado!");
                            break;
                        }
                        
                    int selecao = 0;
                    char novo_valor[100];
                    do{
                        printf("\n ======= Alteração de Livro: =======\n");
                        printf("1. Alterar autor\n");
                        printf("2. Alterar título\n");
                        printf("3. Alterar editora\n");
                        printf("4. Alterar ano de publicação\n");
                        printf("5. Sair\n");
                        printf("Escolha uma opção: ");
                        scanf("%d", &selecao);
                        getchar(); // Limpa o buffer de entrada

                        switch (selecao) {
                            case 1: 
                                printf("\nDigite o novo nome do autor: ");
                                fgets(novo_valor, sizeof(novo_valor), stdin);
                                novo_valor[strcspn(novo_valor, "\n")] = '\0'; 

                                alteracaoLivro(biblioteca, livro_alterar, 1, novo_valor);
                                break;
                            case 2: 
                                printf("\nDigite o novo título: ");
                                fgets(novo_valor, sizeof(novo_valor), stdin);
                                novo_valor[strcspn(novo_valor, "\n")] = '\0'; 

                                alteracaoLivro(biblioteca, livro_alterar, 2, novo_valor);
                                strcpy(livro_alterar, novo_valor);
                                break;
                            case 3: 
                                printf("\nDigite a nova editora: ");
                                fgets(novo_valor, sizeof(novo_valor), stdin);
                                novo_valor[strcspn(novo_valor, "\n")] = '\0'; 

                                alteracaoLivro(biblioteca, livro_alterar, 3, novo_valor);
                                break;
                            case 4: 
                                printf("\nDigite o novo ano: ");
                                fgets(novo_valor, sizeof(novo_valor), stdin);
                                novo_valor[strcspn(novo_valor, "\n")] = '\0'; 

                                alteracaoLivro(biblioteca, livro_alterar, 4, novo_valor);
                                break;
                            case 5: 
                                printf("\nSaindo...\n");
                                
                            default:
                                printf("Escolha indisponível!\n");
                        }
                    }while(selecao != 5);
                }
                break;
            case 7:
                printf("\nSaindo do programa...\n");
                // Liberar memória alocada para os livros antes de sair
                while (biblioteca != NULL) {
                    Livros *temp = biblioteca;
                    biblioteca = biblioteca->prox_livro;
                    free(temp);
                }
                return 0;
            default:
                printf("\nOpção inválida. Por favor, escolha uma opção válida.\n");
                break;
        }
    } while (opcao != 7);

    return 0;
}
