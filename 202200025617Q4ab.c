/*

GRUPO: 

ANDERSON TAVARES BARRETO DE ARAUJO - 202200025410
GABRYEL BARRETO ARAUJO - 202200025500
JOSE LUCAS RODRIGUES GOIS - 202200025617
PEDRO BRUNO TELES E SOUZA - 202200025724

Github: https://github.com/goislucas/prova2PAA

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int teste_do_triangulo(float pontos[3][2], float ponto[2]){
    float area_main , area1, area2, area3;
    area_main = fabs((pontos[0][0]*(pontos[1][1] - pontos[2][1]) + pontos[1][0]*(pontos[2][1] - pontos[0][1]) + pontos[2][0]*(pontos[0][1] - pontos[1][1]))/2);
    area1 = fabs((ponto[0]*(pontos[1][1] - pontos[2][1]) + pontos[1][0]*(pontos[2][1] - ponto[1]) + pontos[2][0]*(ponto[1] - pontos[1][1]))/2);
    area2 = fabs((pontos[0][0] * (ponto[1] - pontos[2][1]) + ponto[0] * (pontos[2][1] - pontos[0][1]) + pontos[2][0]*(pontos[0][1] - ponto[1]))/2);
    area3 = fabs((pontos[0][0]*(pontos[1][1] - ponto[1]) + pontos[1][0]*(ponto[1] - pontos[0][1]) + ponto[0]*(pontos[0][1] - pontos[1][1]))/2);

    if(area_main == 0){
        return 0;
    }
    if(area_main == area1 + area2 + area3){
        return 1;
    }
    else{
        return 0;
    }
}

int teste_do_triangulo_para_varios_pontos(float matriz[][2] , float pontos[3][2],int quant){

    for(int i = 0 ; i < quant ; i++){
        if(((matriz[i][0] == pontos[0][0])&&(matriz[i][1] == pontos[0][1]))||
        ((matriz[i][0] == pontos[1][0])&&(matriz[i][1] == pontos[1][1]))||
        ((matriz[i][0] == pontos[2][0])&&(matriz[i][1] == pontos[2][1]))){

            continue;

        }

        float ponto[2];
        ponto[0] = matriz[i][0];
        ponto[1] = matriz[i][1];

        if(teste_do_triangulo(pontos,ponto) == 0){
            return 0;
        }
     }
        return 1;
    }
    

int combinacoes_de_3_pontos(float matriz[][2] , int quant){
    for(int i = 0 ; i < quant - 2 ; i++){
        float vetor1[2];
        vetor1[0] = matriz[i][0];
        vetor1[1] = matriz[i][1];
        for(int j = i+1 ; j < quant - 1 ; j++){
            float vetor2[2];
            vetor2[0] = matriz[j][0];
            vetor2[1] = matriz[j][1];
            for(int k = j+1 ; k<quant ; k++){
                float vetor3[2];
                vetor3[0] = matriz[k][0];
                vetor3[1] = matriz[k][1];

                float pontos[3][2] = {{vetor1[0],vetor1[1]},{vetor2[0],vetor2[1]},{vetor3[0],vetor3[1]}};

                if(teste_do_triangulo_para_varios_pontos(matriz,pontos,quant) == 1){
                    printf("Para os pontos {(%.1f,%.1f),(%.1f,%.1f),(%.1f,%.1f)} eh possivel formar um triangulo que contenha todos os outros pontos!",vetor1[0],vetor1[1],vetor2[0],vetor2[1],vetor3[0],vetor3[1]);
                    return 1;
                }
            }
        }
    }
    printf("Nao existem pontos que possam formar um triangulo que contenha todos os outros pontos!");
    return 0;
}



void main(){
    int quant1 = 4;
    int quant2 = 6;
    
    float pontos_atendem[6][2] = {{1,1},{3,1},{2,3},{2,2}};
    
    float pontos_nao_atendem[6][2] = {{2, 3}, {20, 21}, {16, 5},{30, 32}, {25, 27}, {22, 25}};
    
    printf("Teste com pontos que atendem a condicao:\n");
    combinacoes_de_3_pontos(pontos_atendem, quant1);

    printf("\n\nTeste com pontos que nao atendem a condicao:\n");
    combinacoes_de_3_pontos(pontos_nao_atendem, quant2);

}

//Letra B) Complexidade = O(n^4)