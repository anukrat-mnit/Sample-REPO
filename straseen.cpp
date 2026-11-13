#include <iostream>
#include <vector>

using namespace std;

using Matrix = vector<vector<int>>;

Matrix add(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<int>(n));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    return C;
}

Matrix subtract(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<int>(n));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }

    return C;
}

Matrix strassen(const Matrix& A, const Matrix& B) {
    int n = A.size();

    if(n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    int k = n / 2;

    Matrix A11(k, vector<int>(k));
    Matrix A12(k, vector<int>(k));
    Matrix A21(k, vector<int>(k));
    Matrix A22(k, vector<int>(k));

    Matrix B11(k, vector<int>(k));
    Matrix B12(k, vector<int>(k));
    Matrix B21(k, vector<int>(k));
    Matrix B22(k, vector<int>(k));

    for(int i = 0; i < k; i++) {
        for(int j = 0; j < k; j++) {

            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    Matrix P1 = strassen(add(A11, A22), add(B11, B22));
    Matrix P2 = strassen(add(A21, A22), B11);
    Matrix P3 = strassen(A11, subtract(B12, B22));
    Matrix P4 = strassen(A22, subtract(B21, B11));
    Matrix P5 = strassen(add(A11, A12), B22);
    Matrix P6 = strassen(subtract(A21, A11), add(B11, B12));
    Matrix P7 = strassen(subtract(A12, A22), add(B21, B22));

    Matrix C11 = add(subtract(add(P1, P4), P5), P7);
    Matrix C12 = add(P3, P5);
    Matrix C21 = add(P2, P4);
    Matrix C22 = add(subtract(add(P1, P3), P2), P6);

    Matrix C(n, vector<int>(n));

    for(int i = 0; i < k; i++) {
        for(int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    return C;
}

void printMatrix(const Matrix& M) {
    for(const auto& row : M) {
        for(int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {

    Matrix A = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 5, 11, 3},
        {10, 14, 0, 6}
    };

    Matrix B = {
        {8, 5, 14, 0},
        {12, 1, 2, 9},
        {8, 7, 6, 5},
        {4, 3, 2, 1}
    };

    Matrix C = strassen(A, B);

    cout << "Matrix A:\n";
    printMatrix(A);

    cout << "\nMatrix B:\n";
    printMatrix(B);

    cout << "\nResultant Matrix C:\n";
    printMatrix(C);

    return 0;
}