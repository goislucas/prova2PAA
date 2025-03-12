/*

GRUPO: 

ANDERSON TAVARES BARRETO DE ARAUJO - 202200025410
GABRYEL BARRETO ARAUJO - 202200025500
JOSE LUCAS RODRIGUES GOIS - 202200025617
PEDRO BRUNO TELES E SOUZA - 202200025724

Github: https://github.com/goislucas/prova2PAA

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <chrono> // Para medir tempo de execução
#include <tuple>
#include <iomanip>
#include <string>

const int K = 1; // Alterar valor do k

using namespace std;
using namespace chrono; // Para medir tempo

// LETRA A
void readPointsFromFile(const string &filename, vector<double> &X, vector<double> &Y) {
    
    ifstream file(filename);
    if (!file) {
        cerr << "Erro ao abrir o arquivo." << endl;
        perror("Motivo");  // Exibe a descrição do erro
        return;
    }
    
    int N;
    file >> N; // Lendo o número de pontos
    
    double x, y;
    char comma;
    for (int i = 0; i < N; ++i) {
        file >> x >> comma >> y; // Lendo os valores separados por vírgula
        if (comma != ',') {
            cerr << "Erro no formato do arquivo." << endl;
            return;
        }
        X.push_back(x);
        Y.push_back(y);
    }
}

// LETRA B
vector<vector<double>> poly(vector<double> &X, int k){

    vector<vector<double>> M(X.size(), vector<double>(k + 1));

    for(int i = 0; i < (int) X.size(); i++){
        for(int j = 0; j < k + 1; j++){
            M[i][j] = pow(X[i], k - j);
        }
    }

    return M;

}

// LETRA C - Função para inverter uma matriz quadrada usando o método de Gauss-Jordan
vector<vector<double>> inv(vector<vector<double>> M) {
    int n = M.size();
    vector<vector<double>> I(n, vector<double>(n, 0)); // Matriz identidade

    // Criar a matriz identidade
    for (int i = 0; i < n; i++)
        I[i][i] = 1;

    // Aplicando o método de Gauss-Jordan
    for (int i = 0; i < n; i++) {
        // Verifica se o pivô é zero e troca linhas, se necessário
        if (fabs(M[i][i]) < 1e-9) {
            bool swapped = false;
            for (int j = i + 1; j < n; j++) {
                if (fabs(M[j][i]) > 1e-9) {
                    swap(M[i], M[j]);
                    swap(I[i], I[j]);
                    swapped = true;
                    break;
                }
            }
            if (!swapped) {
                cerr << "Erro: Matriz singular, não pode ser invertida!" << endl;
                return {};
            }
        }

        // Normaliza a linha atual (tornando o pivô 1)
        double pivot = M[i][i];
        for (int j = 0; j < n; j++) {
            M[i][j] /= pivot;
            I[i][j] /= pivot;
        }

        // Zera os elementos abaixo e acima do pivô
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = M[k][i];
                for (int j = 0; j < n; j++) {
                    M[k][j] -= factor * M[i][j];
                    I[k][j] -= factor * I[i][j];
                }
            }
        }
    }
    return I;
}

// LETRA D

// Função para transpor uma matriz
vector<vector<double>> transposta(const vector<vector<double>> &M) {

    int rows = M.size();
    int cols = M[0].size();
    vector<vector<double>> T(cols, vector<double>(rows));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            T[j][i] = M[i][j];
        }
    }
    return T;
}

// Função para multiplicar duas matrizes
vector<vector<double>> multiplica(const vector<vector<double>> &A, const vector<vector<double>> &B) {

    int rowsA = A.size(), colsA = A[0].size();
    int colsB = B[0].size();
    vector<vector<double>> C(rowsA, vector<double>(colsB, 0));

    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            for (int k = 0; k < colsA; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// Função para calcular P = inv(A^T * A) * (A^T * Y)
tuple<vector<vector<double>>, double, double> ajusta(vector<double> &X, vector<double> &Y, int k) {

    auto start = steady_clock::now(); // Início do tempo

    vector<vector<double>> A = poly(X, k);       // Construir matriz A
    vector<vector<double>> At = transposta(A);    // Calcular A^T
    vector<vector<double>> AtA = multiplica(At, A); // Calcular A^T * A
    vector<vector<double>> AtA_inv = inv(AtA);   // Inverter (A^T * A)

    if (AtA_inv.empty()) {
        cerr << "Erro: Matriz (A^T * A) não invertível." << endl;
        return {{}, -1, -1};
    }

    vector<vector<double>> AtY(Y.size(), vector<double>(1));
    for (size_t i = 0; i < Y.size(); i++)
        AtY[i][0] = Y[i];

    vector<vector<double>> P = multiplica(AtA_inv, multiplica(At, AtY)); // P = inv(AtA) * (At * Y)
    auto stop = steady_clock::now();

    // Calcular erro SSE = || A * P - Y ||²
    vector<vector<double>> AP = multiplica(A, P);
    long double SSE = 0.0;
    for (size_t i = 0; i < Y.size(); i++) {
        double erro = AP[i][0] - Y[i];
        SSE += erro * erro;
    }

    long double duration = duration_cast<nanoseconds>(stop - start).count() / 1e9; 

    return make_tuple(P, duration, SSE);
}

// LETRA E

 // - Para o arquivo a1.txt, tem-se:
 // k = 1 --> Tempo de execução(cálculo de P) = 0.001010; SSE = 562627.134500
 // k = 2 --> Tempo de execução(cálculo de P) = 0.001009; SSE = 277824.003057
 // k = 10 --> Tempo de execução(cálculo de P) = 0.003009; SSE = 24109.383454

 // - Para o arquivo a2.txt, tem-se:
 // k = 1 --> Tempo de execução(cálculo de P) = 0.004017; SSE = 1648787.351667
 // k = 2 --> Tempo de execução(cálculo de P) = 0.006095; SSE = 244506.810764
 // k = 10 --> Tempo de execução(cálculo de P) = 0.028285; SSE = 244367.432403

 // - Para o arquivo a3.txt, tem-se:
 // k = 1 --> Tempo de execução(cálculo de P) = 0.054295; SSE = 9590.351581
 // k = 2 --> Tempo de execução(cálculo de P) = 0.056885; SSE = 9144.300210
 // k = 10 --> Tempo de execução(cálculo de P) = 0.265469; SSE = 408.293337

// LETRA F

 // Construção da matriz através de poly(X, k) --> Cria a matriz A de tamanho N×(K+1)
 // Complexidade: O(NK)

 // Transposição da matriz através de transposta(A) --> Cria a matriz A^T de tamanho Nx(K+1)
 // Complexidade: O(NK)

 // Multiplicação de matrizes --> multiplica A^T * A, ou seja matriz de tamanho Nx(K+1)xN*Nx(K+1) = (K+1)^2
 // Complexidade: O(NK^2), pois cada elemento dessa matriz é calculado como produto escalar de 2 linhas e colunas, o que exige O(N) operações

 //Inversao da matriz
 // Complexidade: O(K^3), utilizando o método de gauss-jordan, sua complexidade é O(M^3), e como M = K + 1

 // Complexidade para achar P
 // O(K^2)

 // Complexidade total: O(NK^2 + K^3)

 //Sim, os tempos seguem a expectativa:

 //Quando K dobra, o tempo aproximadamente quadruplica. Quando N aumenta, o tempo cresce linearmente.
 // Para K=10, os tempos são significativamente maiores, mostrando o impacto do termo O(K^3). Isso confirma que a complexidade 
 
int main() {

    vector<double> X, Y;
    readPointsFromFile("a1.txt", X, Y); // Alterar o arquivo lido

    // Teste para saber se está lendo os pontos no arquivo
    //for (size_t i = 0; i < X.size(); i++) {
    //    cout << "(" << X[i] << ", " << Y[i] << ")" << endl;
    //}

    vector<vector<double>> Ak = poly(X, K);

    /* Printa a matriz
    for(int i = 0; i < (int) X.size(); i++){
        for(int j = 0; j < (int) Ak[0].size(); j++){
            cout << Ak[i][j] << " ";
        }
        cout << endl;
    }*/

    vector<vector<double>> P;
    long double duration, SSE;

    tie(P, duration, SSE) = ajusta(X, Y, K);

    cout << fixed << setprecision(6); // Garante 3 casas decimais SEM notação científica
    cout << "Tempo de calculo de P: " << duration << " segundos" << endl;
    cout << "Erro SSE: " << SSE << endl;

    return 0;
}
