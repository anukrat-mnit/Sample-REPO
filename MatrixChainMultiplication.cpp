#include <iostream>
#include <vector>
using namespace std;

void printOptimalParenthesis(int i, int j, const vector<vector<int>>& s) {
    if (i == j) {
        cout << "A" << i;
        return;
    }
    cout << "(";
    printOptimalParenthesis(i, s[i][j], s);
    printOptimalParenthesis(s[i][j] + 1, j, s);
    cout << ")";
}

void matrixChainOrder(const vector<int>& p) {
    int n = p.size() - 1;
    vector<vector<int>> m(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> s(n + 1, vector<int>(n + 1, 0));

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            m[i][j] = 1e9;

            for (int k = i; k < j; k++) {
                int cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }

    cout << "Optimal Parenthesization: ";
    printOptimalParenthesis(1, n, s);
    cout << endl;
    cout << "Minimum number of scalar multiplications: " << m[1][n] << endl;
}

int main() {
    vector<int> p = {10, 20, 30, 40, 30};

    cout << "Matrix Dimensions: ";
    for (int i = 0; i < p.size() - 1; i++) {
        cout << "A" << i + 1 << " (" << p[i] << "x" << p[i + 1] << ") ";
    }
    cout << "\n\n";

    matrixChainOrder(p);

    return 0;
}
