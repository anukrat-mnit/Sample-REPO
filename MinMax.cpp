#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef struct MinMax{
    int max;    
    int min;
}MinMax;
    
MinMax finding_MinMax(const vector<int> &arr, int st, int ed){
    if(st==ed){
        MinMax ans;
        ans.max = arr[st];
        ans.min = arr[st];
        return ans;
    }

    if(st+1 == ed){
        MinMax ans;
        ans.max = max(arr[st], arr[ed]);
        ans.min = min(arr[st], arr[ed]);
        return ans;
    }
    
    MinMax result, Lresult, Rresult;
    int mid = (ed-st)/2 + st;
    Lresult = finding_MinMax(arr, st, mid);
    Rresult = finding_MinMax(arr, mid+1, ed);

    result.max = max(Lresult.max, Rresult.max);
    result.min = min(Lresult.min , Rresult.min);
    return result;

}
void verify(vector<int> arr){
sort(arr.begin(), arr.end());
for(int num:arr){
    cout << num << "  ";
}
cout << endl;
return;
}

int main(){
vector<int> arr {2,5,78,32,69,78,512,747,952,-69,-45,23,-7894,0,25};
int ed = arr.size()-1;
MinMax ans = finding_MinMax(arr, 0,ed);
cout << "The minimum of arr is: " << ans.min << endl;
cout << "The maximum of arr is: " << ans.max << endl; 
cout << "for verification: ";
verify(arr);
return 0;
}