/*

GRUPO: 

ANDERSON TAVARES BARRETO DE ARAUJO - 202200025410
GABRYEL BARRETO ARAUJO - 202200025500
JOSE LUCAS RODRIGUES GOIS - 202200025617
PEDRO BRUNO TELES E SOUZA - 202200025724

Github: https://github.com/goislucas/prova2PAA

*/

/*

6. Considere que A é um array contendo N strings de comprimentos variados,
formadas exclusivamente por letras minúsculas e sem acentos.

a) Qual método de ordenação você utilizaria para ordenar A eficientemente? Qual
a complexidade temporal do método escolhido para este problema?

    O método utilizado é o Quick Sort baseado na comparação de strings. A complexidade de qsort é O(n²), 
    sendo o pior caso quando a palavra pivô for sempre a última ou a primeira do array de palavras.

b) Duas (ou mais) strings são anagramas se uma é uma permutação dos
símbolos da(s) outra(s). Crie uma função anagroup(A) que retorna os
anagramas contidos em A agrupados.

    char*** anagroup(char *palavras[], int N, int *grupos, int *tamanhoGrupo). A função definida neste
    arquivo é baseada na comparação de frequências de letras em cada palavra e gera um "hash" para as 
    frequências agrupadas.
    
c) Qual a complexidade de anagroup(A)?

    O(n²). Ao assumir o pior caso, onde não existem anagramas, a função anagroup irá percorrer N grupos 
    ao dercorrer da inserção de N palavras. Além disso, essa complexidade poderia ser diferente se o tamanho 
    das palavras não fosse constante, conforme o nosso ambiente, onde MAX_TAM_PALAVRA. 

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAM_PALAVRA 46 // A maior palavra do alfabeto português é pneumoultramicroscopicossilicovulcanoconiótico, com 46 letras.
#define TAM_ALFABETO 26 // Tamanho do alfabeto português.

// Função de comparação para o qsort.
int compararPalavras(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

// Função de comparação para encontrar anagramas baseado na frequência de cada letra do alfabeto.
int compararFrequencias(int a[], int b[]) {
    for (int i = 0; i < TAM_ALFABETO; i++) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}

// Função para encontrar anagramas e listá-los.
char*** anagroup(char *palavras[], int N, int *grupos, int *tamanhoGrupo) {
    char ***arrayAnagramas = malloc(N * sizeof(char **));
    int frequenciaPalavra[N][TAM_ALFABETO];
    int frequenciasGrupos[N][TAM_ALFABETO];

    for (int i = 0; i < N; i++) {
        arrayAnagramas[i] = malloc(N * sizeof(char *));
        tamanhoGrupo[i] = 0;
    }

    // Inicializa as frequências das palavras.
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < TAM_ALFABETO; j++) {
            frequenciaPalavra[i][j] = 0;
        }
    }
    
    // Calculando as frequências de cada letra nas palavras.
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < strlen(palavras[i]); j++) {
            int index = palavras[i][j] - 'a';
            if (index >= 0 && index < TAM_ALFABETO) {
                frequenciaPalavra[i][index]++;
            }
        }
    }
    
    // Agrupando as palavras com base nas frequências.
    for (int i = 0; i < N; i++) {
        int encontrado = 0;
        for (int j = 0; j < *grupos; j++) {
            if (compararFrequencias(frequenciaPalavra[i], frequenciasGrupos[j])) {
                arrayAnagramas[j][tamanhoGrupo[j]] = palavras[i];
                tamanhoGrupo[j]++;
                encontrado = 1;
                break;
            }
        }
        
        // Se não encontrou grupo com frequência igual, cria um novo.
        if (!encontrado) {
            arrayAnagramas[*grupos][0] = palavras[i];
            tamanhoGrupo[*grupos]++;
            for (int k = 0; k < TAM_ALFABETO; k++) {
                frequenciasGrupos[*grupos][k] = frequenciaPalavra[i][k];
            }

            (*grupos)++;
        }
    }

    return arrayAnagramas;
}

int main() {
    int opcao, N;
    char **palavras = NULL;
    printf("Deseja inserir as palavras manualmente(1) ou testar com um array que defini(2)? Escolha 1 ou 2.\n");
    scanf("%d", &opcao);
    getchar();

    if (opcao == 1) {
        // INSERÇÃO MANUAL.
        printf("Digite o numero de palavras: ");
        scanf("%d", &N);
        getchar();

        palavras = malloc(N * sizeof(char *));
        for (int i = 0; i < N; i++) {
            printf("Palavra %d: ", i+1);
            palavras[i] = malloc((MAX_TAM_PALAVRA + 1) * sizeof(char)); // Considerando o ENTER com o +1.
            scanf("%s", palavras[i]);
        }
    } else if (opcao == 2) {
        // INSERÇÃO ARRAY ESTÁTICO PARA TESTES.
        char *palavrasTemp[] = {"amor", "roma", "gato", "toga", "pato", "taco", "flor", "carta", "tacra", "bola", "pino", "casa", "saca", "arpa", "para", "rato", "ator", "cao", "jaca", "oca", "cora", "arar", "ora", "rara", "caja", "aco", "aro"};
        N = sizeof(palavrasTemp) / sizeof(palavrasTemp[0]);

        palavras = malloc(N * sizeof(char *));
        for (int i = 0; i < N; i++) {
            palavras[i] = malloc((strlen(palavrasTemp[i]) + 1) * sizeof(char));
            strcpy(palavras[i], palavrasTemp[i]);
        }
    } else {
        printf("Opção invalida!\n");
        return 1;
    }

    printf("\nPALAVRAS INSERIDAS\n[");
    for (int i = 0; i < N; i++) {
        printf("%s", palavras[i]);
        if (i + 1 < N) {
            printf(", ");
        }
    }
    printf("]\n");

    qsort(palavras, N, sizeof(char *), compararPalavras);

    printf("\nPALAVRAS ORDENADAS\n[");
    for (int i = 0; i < N; i++) {
        printf("%s", palavras[i]);
        if (i + 1 < N) {
            printf(", ");
        }
    }
    printf("]\n");

    int grupos = 0;
    int tamanhoGrupo[N];
    char ***anagramas = anagroup(palavras, N, &grupos, tamanhoGrupo);

    printf("\nANAGRAMAS\n[");
    for (int i = 0; i < grupos; i++) {
        printf("[");
        for (int j = 0; j < tamanhoGrupo[i]; j++) {
            printf("%s", anagramas[i][j]);
            if (j + 1 < tamanhoGrupo[i]) {
                printf(", ");
            }
        }
        printf("]");
        if (i + 1 < grupos) {
            printf(", ");
        }
    }
    printf("]\n");

    for (int i = 0; i < grupos; i++) {
        free(anagramas[i]);
    }
    free(anagramas);

    for (int i = 0; i < N; i++) {
        free(palavras[i]);
    }
    free(palavras);

    return 0;
}
