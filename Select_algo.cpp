#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void insertionSort(vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int partition(vector<int>& arr, int left, int right, int pivot) {
    int pivotIndex = left;
    for (int j = left; j <= right; ++j) {
        if (arr[j] == pivot) {
            pivotIndex = j;
            break;
        }
    }
    swap(arr[pivotIndex], arr[right]);

    int i = left;
    for (int j = left; j < right; ++j) {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[right]);
    return i;
}

int selectKthSmallest(vector<int>& arr, int left, int right, int k) {
    int n = right - left + 1;
    if (n <= 5) {
        insertionSort(arr, left, right);
        return arr[left + k - 1];
    }

    vector<int> medians;
    for (int i = left; i <= right; i += 5) {
        int subRight = min(i + 4, right);
        insertionSort(arr, i, subRight);
        int subLen = subRight - i + 1;
        medians.push_back(arr[i + subLen / 2]);
    }

    int medianOfMedians = selectKthSmallest(medians, 0, medians.size() - 1, (medians.size() + 1) / 2);

    int pivotIndex = partition(arr, left, right, medianOfMedians);
    int rank = pivotIndex - left + 1;

    if (k == rank) {
        return arr[pivotIndex];
    } else if (k < rank) {
        return selectKthSmallest(arr, left, pivotIndex - 1, k);
    } else {
        return selectKthSmallest(arr, pivotIndex + 1, right, k - rank);
    }
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    if (!(cin >> n) || n <= 0) {
        cout << "Invalid input! Program terminating." << endl;
        return 1;
    }

    vector<int> nums(n);
    cout << "Enter " << n << " array elements: ";
    for (int j = 0; j < n; ++j) {
        if (!(cin >> nums[j])) {
            cout << "Invalid input! Program terminating." << endl;
            return 1;
        }
    }

    int i;
    cout << "Enter i (to find the i-th minimum element, between 1 and " << n << "): ";
    if (!(cin >> i) || i < 1 || i > n) {
        cout << "Invalid input! Program terminating." << endl;
        return 1;
    }

    int result = selectKthSmallest(nums, 0, n - 1, i);
    cout << "The " << i << "th minimum element is: " << result << endl;

    return 0;
}
