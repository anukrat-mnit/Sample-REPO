#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
long long M = 1000000007;
long long exponent(long long num, long long power){
    if(power == 0) return 1;
    num = num % M;
    long long ans=1;
    if(0==power%2){
        long long half = exponent(num, power/2);
        ans = (half*half)%M;
    }
    else {
    ans = (num * exponent(num, power - 1))%M;
    }
    return ans;
}
int main(){
    int num1, pow;
    cout << "Enter your number: ";
    cin >> num1;

    cout << "Enter your power: ";
    cin >> pow;

    cout << exponent(num1, pow) << endl;
    return 0;
}