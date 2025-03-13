<<<<<<< HEAD
/*

GRUPO: 

ANDERSON TAVARES BARRETO DE ARAUJO - 202200025410
GABRYEL BARRETO ARAUJO - 202200025500
JOSE LUCAS RODRIGUES GOIS - 202200025617
PEDRO BRUNO TELES E SOUZA - 202200025724

Github: https://github.com/goislucas/prova2PAA

*/

=======
>>>>>>> 6e7298d (Commit Final)
#include <stdio.h>
#include <math.h>

float ponto_medio[2] = {0,0};
float distancia;

void distancia_entre_dois_pontos(float ponto1[] , float ponto2[]){
    distancia = sqrt(pow((ponto1[0] - ponto2[0]),2) + pow((ponto1[1] - ponto2[1]),2));
}

<<<<<<< HEAD
=======
void media_dos_pontos(float pontos[][2] , int quant){

    ponto_medio[0] = 0;
    ponto_medio[1] = 0;

    for(int i = 0 ; i < quant ; i++){
        ponto_medio[0] = ponto_medio[0] + pontos[i][0];
        ponto_medio[1] = ponto_medio[1] + pontos[i][1];
    }

    ponto_medio[0] = ponto_medio[0]/quant;
    ponto_medio[1] = ponto_medio[1]/quant;

}

>>>>>>> 6e7298d (Commit Final)
int inCirc(float pontos[][2] , float raio , int quant){
    media_dos_pontos(pontos,quant);

    for(int i = 0 ; i < quant ; i++){
        float ponto[2];
        ponto[0] = pontos[i][0];
        ponto[1] = pontos[i][1];
        
        distancia_entre_dois_pontos(ponto_medio,ponto);

        if(distancia == 0){
            continue;
        }
        if(distancia > raio){
            printf("O conjunto de pontos dado nao esta contido no circulo de raio %.2f",raio);
            return 0;
        }
    }
    printf("O conjunto de pontos dado esta contido no circulo de raio %.2f",raio);
    return 1;
}

<<<<<<< HEAD

void media_dos_pontos(float pontos[][2] , int quant){

    ponto_medio[0] = 0;
    ponto_medio[1] = 0;

    for(int i = 0 ; i < quant ; i++){
        ponto_medio[0] = ponto_medio[0] + pontos[i][0];
        ponto_medio[1] = ponto_medio[1] + pontos[i][1];
    }

    ponto_medio[0] = ponto_medio[0]/quant;
    ponto_medio[1] = ponto_medio[1]/quant;

}

=======
>>>>>>> 6e7298d (Commit Final)
void main(){
    int quant = 4;
    float raio = 150;
        
    float pontos[4][2] = {{1,1},{3,1},{2,3},{100,100}}; 
    
    inCirc(pontos , raio , quant);

}
//Letra D) Complexidade = O(n)