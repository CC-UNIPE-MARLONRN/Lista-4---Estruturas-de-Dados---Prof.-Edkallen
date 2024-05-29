/*
** Função: Definir uma estrutura chamada perfil_saude que receba os dados de um paciente e determine um diagnóstico e os utilize em um vetor;
** Autor: Marlon Rufino do Nascimento, 2º período, turma A, 2024.1
** Data: 25/05/2024  
** Observações: Estou utilizando a função 'setlocale' da biblioteca 'locale.h' para a representação de acentuação padrão da língua portuguesa, tais como ´, ^, `, ª ...  
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

// Estrutura do tipo data para armazenar o valor da data
typedef struct {
    char dia[2]; // Para permitir o 0 antes do número do dia
    char mes[2]; // Para permitir o 0 antes do número do mês
    int ano;
} Data;

// Estrutura Perfil_saude
typedef struct {
    char Nome_completo[80];
    char sexo[1]; // Apenas um caractere para o sexo
    Data data_nascimento;
    float altura;
    float peso;
} Perfil_saude;

// Função para criar um novo paciente
Perfil_saude Criar_paciente(char *nome, char sexo, char *dia, char *mes, int ano, float altura, float peso) {
    Perfil_saude novoPaciente;

    // Copia o nome completo do paciente
    strncpy(novoPaciente.Nome_completo, nome, 79);
    novoPaciente.Nome_completo[79] = '\0';
    
    // Define o sexo do paciente
    novoPaciente.sexo[0] = sexo;
    
    // Copia a data de nascimento
    strncpy(novoPaciente.data_nascimento.dia, dia, 2);
    strncpy(novoPaciente.data_nascimento.mes, mes, 2);
    novoPaciente.data_nascimento.ano = ano;
    
    // Define altura e peso do paciente
    novoPaciente.altura = altura;
    novoPaciente.peso = peso;

    return novoPaciente;
}

// Função que calcula a idade de acordo com a data de nascimento
int calcularIdade(Perfil_saude *p) {
    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);

    int ano_atual = local_time->tm_year + 1900;
    int mes_atual = local_time->tm_mon + 1;
    int dia_atual = local_time->tm_mday;

    int idade = ano_atual - p->data_nascimento.ano;

    if (mes_atual < atoi(p->data_nascimento.mes) || 
       (mes_atual == atoi(p->data_nascimento.mes) && dia_atual < atoi(p->data_nascimento.dia))) {
        idade--;
    }
    return idade;
}

// Função que calcula o IMC (Índice de Massa Corporal)
float calcularIMC(Perfil_saude *p) {
    return p->peso / (p->altura * p->altura);
}

// Função que exibe o estado do IMC
void estadoIMC(Perfil_saude *p) {
    float imc = calcularIMC(p);

    printf("IMC: %.2f - ", imc);
    if (imc < 18.5) {
        printf("Abaixo do peso\n");
    } else if (imc >= 18.5 && imc < 24.9) {
        printf("Peso normal\n");
    } else if (imc >= 25 && imc < 29.9) {
        printf("Sobrepeso\n");
    } else {
        printf("Obesidade\n");
    }
}

// Função que calcula a frequência cardíaca máxima
int calcularFrequenciaCardiacaMaxima(Perfil_saude *p) {
    return 220 - calcularIdade(p);
}

// Função que calcula a frequência cardíaca ideal mínima
int calcularFrequenciaCardiacaIdealMin(Perfil_saude *p) {
    return calcularFrequenciaCardiacaMaxima(p) * 0.5;
}

// Função que calcula a frequência cardíaca ideal máxima
int calcularFrequenciaCardiacaIdealMax(Perfil_saude *p) {
    return calcularFrequenciaCardiacaMaxima(p) * 0.85;
}

// Função que calcula a expectativa de vida baseada no sexo do paciente
int calcularExpectativaDeAnos(Perfil_saude *p) {
    if (p->sexo[0] == 'M' || p->sexo[0] == 'm') {
        return 72; // Expectativa aproximada de vida para homens, segundo o censo de 2022 do IBGE
    } else {
        return 79; // Expectativa aproximada de vida para mulheres, segundo o censo de 2022 do IBGE
    }
}

// Função que exibe o perfil do paciente
void exibir_perfil(Perfil_saude *pacientes, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n=== Perfil do Paciente %d ===\n", i + 1);
        printf("Nome completo: %s\n", pacientes[i].Nome_completo);
        printf("Sexo: %c\n", pacientes[i].sexo[0]);
        printf("Data de Nascimento: %.2s/%.2s/%d (%d anos)\n", pacientes[i].data_nascimento.dia, pacientes[i].data_nascimento.mes, pacientes[i].data_nascimento.ano, calcularIdade(&pacientes[i]));
        printf("Altura: %.2f m\n", pacientes[i].altura);
        printf("Peso: %.2f kg\n", pacientes[i].peso);
        estadoIMC(&pacientes[i]);
        printf("Frequência Cardíaca Máxima: %d bpm\n", calcularFrequenciaCardiacaMaxima(&pacientes[i]));
        printf("Frequência Cardíaca Ideal: %d - %d bpm\n", calcularFrequenciaCardiacaIdealMin(&pacientes[i]), calcularFrequenciaCardiacaIdealMax(&pacientes[i]));
        printf("Expectativa de Vida: %d anos\n", calcularExpectativaDeAnos(&pacientes[i]));
    }
}

// Função que captura os dados do paciente
void capturar_dados(Perfil_saude *pacientes, int n) {
    char nome[80];
    char sexo;
    char dia[3];
    char mes[3];
    int ano;
    float altura;
    float peso;

    for (int i = 0; i < n; i++) {
        printf("\nDigite os dados do paciente %d:\n", i + 1);

        // Captura o nome completo do paciente
        printf("Digite o nome completo: ");
        fgets(nome, 80, stdin);
        nome[strcspn(nome, "\n")] = '\0'; 

        // Captura o sexo do paciente
        printf("Digite o sexo (M/F): ");
        scanf(" %c", &sexo);
        getchar(); 

        // Captura o dia de nascimento do paciente
        printf("Digite o dia de nascimento (DD): ");
        fgets(dia, 3, stdin);
        dia[strcspn(dia, "\n")] = '\0'; 
        getchar(); 

        // Captura o mês de nascimento do paciente
        printf("Digite o mês de nascimento (MM): ");
        fgets(mes, 3, stdin);
        mes[strcspn(mes, "\n")] = '\0'; 

        // Captura o ano de nascimento do paciente
        printf("Digite o ano de nascimento (AAAA): ");
        scanf("%d", &ano);

        // Captura a altura do paciente
        printf("Digite a altura (em metros): ");
        scanf("%f", &altura);

        // Captura o peso do paciente
        printf("Digite o peso (em kg): ");
        scanf("%f", &peso);
        getchar(); 

        // Cria o perfil do paciente com os dados capturados
        pacientes[i] = Criar_paciente(nome, sexo, dia, mes, ano, altura, peso);
    }
}

int main() {
    setlocale(LC_ALL, "portuguese");

    int n;

    // Captura o número de pacientes
    printf("Digite o número de pacientes: ");
    scanf("%d", &n);
    getchar(); 

    // Aloca memória para armazenar os perfis dos pacientes
    Perfil_saude *pacientes = (Perfil_saude*)malloc(n * sizeof(Perfil_saude));
    if (pacientes == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Captura os dados dos pacientes
    capturar_dados(pacientes, n);

    // Exibe os perfis dos pacientes
    exibir_perfil(pacientes, n);

    // Libera a memória alocada
    free(pacientes);

    return 0;
}
