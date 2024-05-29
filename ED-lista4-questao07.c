/*
** Função : Implementar uma estrtura que simule uma fila de uma clinica medica.
** Autor: Marlon Rufino do nascimento 2º período turma A 2024.1
** Data: 27/05/2024  
** Observações: Estou utilizando a função 'setlocale' da biblioteca 'locale.h' para a representação de acentuação padrão da lingua portuguesa, tais como ´, ^, `, ª ...  
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h> 
#include <string.h>

// Definição da estrutura para representar um paciente
typedef struct paciente {
    char nome_paciente[60]; //capitura o nome do paciente
} Pacientes;

// Definição da estrutura para representar uma posição na fila
typedef struct Posicao {
    Pacientes paciente; // cria uma variavel de referencia para a estrutura paciente para capiturar as informações
    struct Posicao *proximo; // Próxima posição na fila
} Posicao;

// Definição da estrutura para representar a fila de atendimento
typedef struct atendimento{
    Posicao *primeiro; // Primeiro paciente da fila
    int qtd_pacientes; // Quantidade de pacientes na fila
    Posicao *ultimo; // Último paciente da fila
} Atendimento;

// Função para criar uma nova fila de atendimento
Atendimento *CriaFila() {
    Atendimento *fila = (Atendimento *)malloc(sizeof(Atendimento));

    if (fila == NULL) {
        printf("Memória insuficiente!\n");
        exit(1);
    }

    fila->primeiro = fila->ultimo = NULL;
    fila->qtd_pacientes = 0;

    return fila;
}

// Função para adicionar uma nova posição na fila
Posicao *AdicionaPosicao() {
    Posicao *posicao = (Posicao *)malloc(sizeof(Posicao));

    if (posicao == NULL) {
        printf("Memória insuficiente!\n");
        exit(1);
    }

    posicao->proximo = NULL;

    return posicao;
}

// Função para verificar se a fila está vazia
int verifica_fila_vazia(Atendimento *fila) {
    return fila->qtd_pacientes == 0;
}

// Função para adicionar um novo paciente à fila
void adicionar_paciente(Atendimento *fila, char *nome_paciente) {
    Pacientes *novo_paciente = (Pacientes *)malloc(sizeof(Pacientes));
    
    if (novo_paciente == NULL) {
        printf("Memória Insuficiente\n");
        exit(1);
    }

    strcpy(novo_paciente->nome_paciente, nome_paciente);
    
    Posicao *nova_posicao = AdicionaPosicao();
    
    if (nova_posicao == NULL) {
        printf("Memória Insuficiente\n");
        exit(1);
    }

    nova_posicao->paciente = *novo_paciente;
    
    if (verifica_fila_vazia(fila)) {
        fila->primeiro = nova_posicao;
    } else {
        fila->ultimo->proximo = nova_posicao;
    }
    
    fila->ultimo = nova_posicao;
    fila->qtd_pacientes++;

    printf("\nPaciente adicionado com sucesso!\n");
}

// Função para chamar o próximo paciente da fila
Atendimento *proximo_paciente(Atendimento *fila) {
    if (verifica_fila_vazia(fila)) {
        printf("\nNão há pacientes na fila\n");
        return NULL;
    }

    Posicao *temp = fila->primeiro;
    char *nome_paciente = temp->paciente.nome_paciente;

    fila->primeiro = fila->primeiro->proximo;
    if (fila->primeiro == NULL) {
        fila->ultimo = NULL;
    }
    
    printf("\nPróximo Paciente: %s\n", nome_paciente);
    free(temp);
    fila->qtd_pacientes--;

    return nome_paciente;
}

// Função para obter a quantidade de pacientes na fila
int quantidade_pacientes(Atendimento *fila) {
    return fila->qtd_pacientes;
}

// Função para exibir a fila de pacientes
void exibir_fila(Atendimento *fila) {
    Posicao *temp = fila->primeiro;
    
    if(verifica_fila_vazia(fila)){
        printf("\nNão há pacientes na fila!\n");
        return 1;
    }
    
    printf("Fila de Atendimento:\n");
    printf("{ ");
    while (temp != NULL) {
        printf("%s, ", temp->paciente.nome_paciente);
        temp = temp->proximo;
    }
    printf("\b\b }\n");
}

// Função principal
int main() {
    setlocale(LC_ALL, "portuguese"); 

    Atendimento *fila = CriaFila();
    int opcao;
    char nome_paciente[60];

    do {
        printf("\n======= MENU =======\n");
        printf("1. Adicionar Paciente\n");
        printf("2. Próximo Paciente\n");
        printf("3. Quantidade de Pacientes\n");
        printf("4. Exibir Fila\n");
        printf("5. Sair\n");
        printf("====================\n");

        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer de entrada

        switch (opcao) {
            case 1:
                printf("Digite o nome do paciente: ");
                fgets(nome_paciente, sizeof(nome_paciente), stdin);
                nome_paciente[strcspn(nome_paciente, "\n")] = '\0';
                adicionar_paciente(fila, nome_paciente);
                break;
            case 2:
                proximo_paciente(fila);
                break;
            case 3:
                printf("\nQuantidade de Pacientes na Fila: %d\n", quantidade_pacientes(fila));
                break;
            case 4:
                exibir_fila(fila);
                break;
            case 5:
                printf("\nSaindo do programa...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                break;
        }
    } while (opcao != 5);

    free(fila); // Libera a memória alocada para a fila
    return 0;
}
