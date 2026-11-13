#include <iostream>
#include <vector>
#include <string>
using namespace std;

int peakIndexInMountainArray(vector<int>& arr) {
        int high, low, mid;
        high = arr.size()-1;
        low = 0;
        while(high>=low){
            mid = (high-low)/2 + low;
            if(arr[mid]>arr[mid-1] && arr[mid]>arr[mid+1]) return arr[mid];
            else if(arr[mid]>arr[mid-1] && arr[mid]<arr[mid+1]){
                low = mid+1;
            }
            else if(arr[mid]>arr[mid+1] && arr[mid]<arr[mid-1]){
                high = mid;
            }
        }
        return 0;
    }

int main(){
    vector <int> nums = {1,4,6,7,10,9,3,1};
    cout << "The peak of given array is: " << peakIndexInMountainArray(nums) << endl;
    return 0;
}