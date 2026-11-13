#include <iostream>
#include <vector>
using namespace std;

using Matrix = vector<vector<int>>;

// Add two matrices
Matrix add(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    return C;
}

// Recursive divide-and-conquer matrix multiplication
Matrix multiply(const Matrix& A, const Matrix& B) {
    int n = A.size();

    // Base case
    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    int half = n / 2;

    Matrix A11(half, vector<int>(half));
    Matrix A12(half, vector<int>(half));
    Matrix A21(half, vector<int>(half));
    Matrix A22(half, vector<int>(half));

    Matrix B11(half, vector<int>(half));
    Matrix B12(half, vector<int>(half));
    Matrix B21(half, vector<int>(half));
    Matrix B22(half, vector<int>(half));

    // Split A and B into four submatrices
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half];
            A21[i][j] = A[i + half][j];
            A22[i][j] = A[i + half][j + half];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half];
            B21[i][j] = B[i + half][j];
            B22[i][j] = B[i + half][j + half];
        }
    }

    Matrix C11 = add(
        multiply(A11, B11),
        multiply(A12, B21)
    );

    Matrix C12 = add(
        multiply(A11, B12),
        multiply(A12, B22)
    );

    Matrix C21 = add(
        multiply(A21, B11),
        multiply(A22, B21)
    );

    Matrix C22 = add(
        multiply(A21, B12),
        multiply(A22, B22)
    );

    // Combine four result matrices
    Matrix C(n, vector<int>(n, 0));

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j] = C11[i][j];
            C[i][j + half] = C12[i][j];
            C[i + half][j] = C21[i][j];
            C[i + half][j + half] = C22[i][j];
        }
    }

    return C;
}

void printMatrix(const Matrix& matrix) {
    for (const vector<int>& row : matrix) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << '\n';
    }
}

int main() {
    Matrix A = {
        {1, -2, 3, 4},
        {5, 6, 7, 8},
        {9, 5, -1, 3},
        {0, 2, 0, 6}
    };

    Matrix B = {
        {8, 5, 1, 0},
        {-2, 1, 2, 9},
        {8, 7, 6, -5},
        {4, 3, 2, 1}
    };

    Matrix C = multiply(A, B);

    cout << "Matrix A:\n";
    printMatrix(A);

    cout << "\nMatrix B:\n";
    printMatrix(B);

    cout << "\nResultant Matrix C:\n";
    printMatrix(C);

    return 0;
}