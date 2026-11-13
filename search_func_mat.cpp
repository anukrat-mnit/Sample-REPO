#include <iostream>
#include <vector>
using namespace std;

bool searchMatrix(const vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) {
        return false;
    }

    int rows = matrix.size();
    int cols = matrix[0].size();

    // Start from the top-right corner
    int row = 0;
    int col = cols - 1;

    while (row < rows && col >= 0) {
        if (matrix[row][col] == target) {
            return true;
        }
        else if (matrix[row][col] > target) {
            // Current value is too large, move left
            col--;
        }
        else {
            // Current value is too small, move down
            row++;
        }
    }

    return false;
}

void printMatrix(const vector<vector<int>>& matrix) {
    for (const vector<int>& row : matrix) {
        for (int value : row) {
            cout << value << "\t";
        }
        cout << '\n';
    }
}

int main() {
    // Each row and column is sorted in ascending order
    vector<vector<int>> matrix = {
        {1,  4,  7, 11, 15},
        {2,  5,  8, 12, 19},
        {3,  6,  9, 16, 22},
        {10, 13, 14, 17, 24}
    };

    int target = 16;

    cout << "Matrix:\n";
    printMatrix(matrix);

    cout << "\nTarget: " << target << '\n';

    if (searchMatrix(matrix, target)) {
        cout << "Target found in the matrix.\n";
    }
    else {
        cout << "Target not found in the matrix.\n";
    }

    return 0;
}