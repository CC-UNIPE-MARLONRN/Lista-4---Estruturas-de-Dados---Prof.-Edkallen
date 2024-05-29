/*
** Função : Implemenar uma função que classifica os elementos de um vetor em ordem crescente usando "classificação por seleção".
** Autor: Marlon Rufino do nascimento 2º período turma A 2024.1
** Data: 25/05/2024  
** Observações: Estou utilizando a função 'setlocale' da biblioteca 'locale.h' para a representação de acentuação padrão da lingua portuguesa, tais como ´, ^, `, ª ...  
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//Prototipo da Função
void ClassificaVetorPorSelecao(int *, int);

//Função main
int main(){
    setlocale(LC_ALL, "portuguese");

    int tamanho_vetor = 10; // tamanho do vetor

    int vetor[tamanho_vetor];

    printf("Vetor original: ");
    printf("{");
        for (int i = 0; i < tamanho_vetor; i++) {
        vetor[i] = rand() % 100; // Gera números aleatórios entre 0 e 99
        printf("%d", vetor[i]);
        if(i != tamanho_vetor - 1) 
            printf(", ");
        else
            printf("}");
    }

    // Chamando a função ClassificaVetorPorSelecao para ordenar o vetor
    ClassificaVetorPorSelecao(vetor, tamanho_vetor);

    printf("\nVetor Ordenado por seleção: \n");
    printf("Vetor {");
    for (int v = 0; v < tamanho_vetor - 1; v++){
        printf("%d, ", vetor[v]);       
    }
        printf("%d}", vetor[tamanho_vetor - 1]);

    return 0;

}

// Função que classifica os valores por meio da seleção
void ClassificaVetorPorSelecao(int *vetor, int tamanho){
    int menor_elemento, indice_menor;

    // Captura os elementos do vetor para serem comparados
    for (int i = 0; i < tamanho - 1; i++){
        menor_elemento = vetor[i];
        indice_menor = i;

        // Compara os elementos do vetor para saber o menor
        for(int j = i + 1; j < tamanho; j++){
            if(vetor[j] < menor_elemento){
                menor_elemento = vetor[j];
                indice_menor = j;
            }
        }
        // Se o índice menor for diferente de i, captura o elemento do vetor e substitui pelo menor elemento na posição
        if(indice_menor != i){
            int aux = vetor[i];
            vetor[i] = vetor[indice_menor];
            vetor[indice_menor] = aux;
        }
    }
}