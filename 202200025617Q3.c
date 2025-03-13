/*

GRUPO: 

ANDERSON TAVARES BARRETO DE ARAUJO - 202200025410
GABRYEL BARRETO ARAUJO - 202200025500
JOSE LUCAS RODRIGUES GOIS - 202200025617
PEDRO BRUNO TELES E SOUZA - 202200025724

Github: https://github.com/goislucas/prova2PAA

*/

/*

3. Considere que temos uma lista de valores reais x1, …, xN. O valor x (não 
necessariamente pertencente à lista) que minimiza a soma de |x - xi| para i de 1 
a N é a mediana dos xi (no caso de N par, a mediana é a média dos valores 
centrais). 

Considere agora que temos uma lista de pontos no plano cartesiano p1=(x1, y1), 
…, pN=(xN, yN). Queremos achar um ponto p=(x, y) (não necessariamente da 
lista) que minimiza a soma da distância Manhattan entre cada pi e p. Essa 
distância é dada por d(p, pi) = |x - xi| + |y - yi|. 

a) Crie uma função pol(P) que retorna o ponto p que resolve o problema do 
segundo parágrafo, onde P = [p1, p2, … , pN]. 

    float* pol(float** P, int N);

b) Qual a complexidade de tempo da sua solução? 

    O método de ordenação Quick Sort (qsort) irá definir o O(n²) para o 
    pior caso, pois a cópia das coordenadas possui O(n) e o cálculo 
    da mediana possui tempo constante.
    
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Distância entre dois pontos.
float d(float* p, float* pi) { 
    return (fabs(p[0] - pi[0]) + fabs(p[1] - pi[1])); 
}

// Função de comparação para o qsort.
int comparaPontos(const void* a, const void* b) {
    if ((*(const float*)a - *(const float*)b) < 0 )
        return -1;
    else if ((*(const float*)a - *(const float*)b) > 0 )
        return 1;
    return 0;
}

// Função para cálculo da mediana em uma lista de números.
float mediana(float* numeros, int N) {
    qsort(numeros, N, sizeof(float), comparaPontos);
    if (N % 2 == 0)
        return (numeros[(N / 2) - 1] + numeros[N / 2]) / 2;
    else
        return numeros[(int)(N / 2)];
}

// Função que retorna o ponto mais próximo de todos os pontos em uma lista de pontos dada.
float* pol(float** P, int N) {
    float* ponto = (float*)malloc(2 * sizeof(float));
    float pontosX[N], pontosY[N];
    
    for (int i = 0; i < N; i++) {
        pontosX[i] = P[i][0];
        pontosY[i] = P[i][1];
    }
    
    ponto[0] = mediana(pontosX, N);
    ponto[1] = mediana(pontosY, N);
    
    return ponto;
}

int main() {
    float** P;
    int opcao, N;
    
    printf("Deseja inserir as coordenadas manualmente(1) ou testar com as que defini(2)? Escolha 1 ou 2.\n");
    scanf("%d", &opcao);

    if (opcao == 1) {
        printf("\nQuantos pontos deseja? ");
        scanf("%d", &N);
        
        P = (float**)malloc(N * sizeof(float*));
        
        for (int i = 0; i < N; i++) {
            P[i] = (float*)malloc(2 * sizeof(float));
            printf("\nInsira a coordenada x%d: ", i);
            scanf("%f", &P[i][0]);
            printf("Insira a coordenada y%d: ", i);
            scanf("%f", &P[i][1]);
        }

    } else if (opcao == 2) {
        float PTemp[][2] = {{1,2}, {10,4}, {21,3}, {7,5}};
        N = sizeof(PTemp) / sizeof(PTemp[0]);

        P = (float**)malloc(N * sizeof(float*));
        for (int i = 0; i < N; i++) {
            P[i] = (float*)malloc(2 * sizeof(float));
            P[i][0] = PTemp[i][0];
            P[i][1] = PTemp[i][1];
        }
    } else {
        printf("Opcao invalida!\n");
        return 1;
    }
    
<<<<<<< HEAD
=======
    printf("\nPONTOS\n");
    for (int i = 0; i < N; i++) {
        printf("(%.2f, %.2f)", P[i][0], P[i][1]);
        if (i + 1 < N) {
            printf(", ");
        }
    }
    printf("\n");

>>>>>>> 6e7298d (Commit Final)
    float* ponto = pol(P, N);
    
    printf("\nPONTO MEDIANO\n(%.2f, %.2f)\n", ponto[0], ponto[1]);
    
    float distanciaTotal = 0;
    for (int i = 0; i < N; i++) {
        distanciaTotal = distanciaTotal + d(ponto, P[i]);
    }
    printf("\nDISTANCIA TOTAL\n%.2f\n", distanciaTotal);
    
    for (int i = 0; i < N; i++) {
        free (P[i]);
    }
    
    free (P);
    free (ponto);
    
    return 0;
}