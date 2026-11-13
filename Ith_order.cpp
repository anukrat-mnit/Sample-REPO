#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int partition(vector<int>& nums, int st, int ed) {
        int piv = nums[ed];
        int bef = st - 1;

        for (int i = st; i < ed; i++) {
            if (nums[i] < piv) {
                swap(nums[++bef], nums[i]);
            }
        }

        swap(nums[++bef], nums[ed]);
        return bef;
    }

    int random_select(vector<int>& nums, int st, int ed, int k) {
        if (st == ed) return nums[st];

        int q = partition(nums, st, ed);

        if (q == k)
            return nums[q];
        else if (q > k)
            return random_select(nums, st, q - 1, k);
        else
            return random_select(nums, q + 1, ed, k);
    }

    int findKthLargest(vector<int>& nums, int K) {
        int k = nums.size() - K;
        return random_select(nums, 0, nums.size() - 1, k);
    }
};

int main() {
    vector<int> nums = {12, 3, 5, 7, 4, 19, 26, 8};

    int i = 3;

    Solution obj;

    cout << "Array: ";
    for (int value : nums) {
        cout << value << " ";
    }

    cout << "\n" << i << "rd largest element is: "
         << obj.findKthLargest(nums, i) << '\n';

    return 0;
}