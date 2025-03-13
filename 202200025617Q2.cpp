/*

GRUPO: 

ANDERSON TAVARES BARRETO DE ARAUJO - 202200025410
GABRYEL BARRETO ARAUJO - 202200025500
JOSE LUCAS RODRIGUES GOIS - 202200025617
PEDRO BRUNO TELES E SOUZA - 202200025724

Github: https://github.com/goislucas/prova2PAA

*/

#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const string arquivo = "a1.txt"; // Nome do arquivo exemplo de entrada

// Funções da questão 1
using namespace std;
using namespace chrono; // Para medir tempo

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

vector<vector<double>> poly(vector<double> &X, int k){

    vector<vector<double>> M(X.size(), vector<double>(k + 1));

    for(int i = 0; i < (int) X.size(); i++){
        for(int j = 0; j < k + 1; j++){
            M[i][j] = pow(X[i], k - j);
        }
    }

    return M;

}

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

// LETRA A
// Função para calcular mínimos quadrados para regressão linear Y' = b0 + b1 * X
tuple<double, double> regressaoLinear(const vector<double> &X, const vector<double> &Y) {
    int N = X.size();
    if (N == 0) return {0, 0};

    double somaX = 0, somaY = 0, somaXY = 0, somaX2 = 0;

    for (int i = 0; i < N; i++) {
        somaX += X[i];
        somaY += Y[i];
        somaXY += X[i] * Y[i];
        somaX2 += X[i] * X[i];
    }

    double mediaX = somaX / N;
    double mediaY = somaY / N;

    double b1 = (somaXY - N * mediaX * mediaY) / (somaX2 - N * mediaX * mediaX);
    double b0 = mediaY - b1 * mediaX;

    return {b0, b1};
}

// LETRA B
tuple<double, double> ajustaExp(vector<double> &X, vector<double> &Y) {
    vector<double> Y_ln; // Vetor para armazenar ln(Y)

    // Transformando Y -> ln(Y)
    for (double y : Y) {
        if (y <= 0) {
            cerr << "Erro: Não é possível calcular ln(y) para y <= 0." << endl;
            return {-1, -1};
        }
        Y_ln.push_back(log(y));
    }

    // Ajustando uma regressão linear no modelo Y' = b0 + b1 * X
    vector<vector<double>> P;
    tie(P, ignore, ignore) = ajusta(X, Y_ln, 1); // k=1 pois é um modelo linear

    // Verificando se a regressão foi bem-sucedida
    if (P.empty()) {
        cerr << "Erro ao ajustar modelo exponencial." << endl;
        return {-1, -1};
    }

    // Recuperando os coeficientes p1 e p2
    double b0 = P[0][0]; // b0 = ln(p1)
    double b1 = P[1][0]; // b1 = p2

    double p1 = exp(b0); // p1 = e^b0
    double p2 = b1;      // p2 = b1

    return {p1, p2};
}

int main() {
    vector<double> X, Y;
    readPointsFromFile(arquivo, X, Y);

    if (X.empty() || Y.empty()) {
        cerr << "Erro: Nenhum dado carregado." << endl;
        return 1;
    }

    // Regressão linear sobre os valores transformados
    double b0, b1;
    tie(b0, b1) = regressaoLinear(X, Y);

    // Recuperando os valores reais de p1 e p2
    double p1 = exp(b0); // p1 = exp(b0)
    double p2 = b1;      // p2 = b1

    cout << fixed << setprecision(6);
    cout << "Coeficientes ajustados:" << endl;
    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;

    return 0;
}
