#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Function to remove leading zeros from a number string
string removeLeadingZeros(string s) {
    int start = 0;
    while (start < (int)s.length() - 1 && s[start] == '0') {
        start++;
    }
    return s.substr(start);
}

// Function to add two large number strings
string addStrings(string num1, string num2) {
    string result = "";
    int i = num1.length() - 1;
    int j = num2.length() - 1;
    int carry = 0;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += num1[i--] - '0';
        if (j >= 0) sum += num2[j--] - '0';
        carry = sum / 10;
        result += to_string(sum % 10);
    }
    reverse(result.begin(), result.end());
    return result;
}

// Function to subtract two large number strings (assumes num1 >= num2)
string subtractStrings(string num1, string num2) {
    string result = "";
    int i = num1.length() - 1;
    int j = num2.length() - 1;
    int borrow = 0;

    while (i >= 0) {
        int sub = (num1[i--] - '0') - borrow;
        if (j >= 0) sub -= (num2[j--] - '0');

        if (sub < 0) {
            sub += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result += to_string(sub);
    }
    reverse(result.begin(), result.end());
    return removeLeadingZeros(result);
}

// Function to append zeros (equivalent to multiplying by 10^zeros)
string shiftLeft(string num, int zeros) {
    if (num == "0" || zeros <= 0) return num;
    return num + string(zeros, '0');
}

// 1) Traditional Divide and Conquer Multiplication (4 Recursive Calls)
// Time Complexity: O(n^2)
string traditionalDivideAndConquer(string X, string Y) {
    X = removeLeadingZeros(X);
    Y = removeLeadingZeros(Y);

    if (X == "0" || Y == "0") return "0";

    int n1 = X.length();
    int n2 = Y.length();

    // Base case: small numbers (<= 2 digits) can be directly multiplied
    if (n1 <= 2 && n2 <= 2) {
        long long val = stoll(X) * stoll(Y);
        return to_string(val);
    }

    int N = max(n1, n2);
    if (N % 2 != 0) N++; // Make N even for equal partitioning

    // Pad with leading zeros to make both strings length N
    while ((int)X.length() < N) X = "0" + X;
    while ((int)Y.length() < N) Y = "0" + Y;

    int m = N / 2;

    // Splitting numbers into high and low halves
    string a = X.substr(0, N - m);
    string b = X.substr(N - m);
    string c = Y.substr(0, N - m);
    string d = Y.substr(N - m);

    // 4 recursive multiplications: ac, ad, bc, bd
    string ac = traditionalDivideAndConquer(a, c);
    string ad = traditionalDivideAndConquer(a, d);
    string bc = traditionalDivideAndConquer(b, c);
    string bd = traditionalDivideAndConquer(b, d);

    // Formula: ac * 10^(2m) + (ad + bc) * 10^m + bd
    string term1 = shiftLeft(ac, 2 * m);
    string term2 = shiftLeft(addStrings(ad, bc), m);
    string term3 = bd;

    string result = addStrings(addStrings(term1, term2), term3);
    return removeLeadingZeros(result);
}

// 2) Karatsuba Algorithm (3 Recursive Calls)
// Time Complexity: O(n^1.585)
string karatsuba(string X, string Y) {
    X = removeLeadingZeros(X);
    Y = removeLeadingZeros(Y);

    if (X == "0" || Y == "0") return "0";

    int n1 = X.length();
    int n2 = Y.length();

    // Base case: small numbers (<= 2 digits) can be directly multiplied
    if (n1 <= 2 && n2 <= 2) {
        long long val = stoll(X) * stoll(Y);
        return to_string(val);
    }

    int N = max(n1, n2);
    if (N % 2 != 0) N++; // Make N even for equal partitioning

    // Pad with leading zeros to make both strings length N
    while ((int)X.length() < N) X = "0" + X;
    while ((int)Y.length() < N) Y = "0" + Y;

    int m = N / 2;

    // Splitting numbers into high and low halves
    string a = X.substr(0, N - m);
    string b = X.substr(N - m);
    string c = Y.substr(0, N - m);
    string d = Y.substr(N - m);

    // 3 recursive multiplications: ac, bd, (a+b)*(c+d)
    string ac = karatsuba(a, c);
    string bd = karatsuba(b, d);

    string a_plus_b = addStrings(a, b);
    string c_plus_d = addStrings(c, d);
    string p3 = karatsuba(a_plus_b, c_plus_d);

    // (ad + bc) = (a+b)(c+d) - ac - bd
    string ad_plus_bc = subtractStrings(subtractStrings(p3, ac), bd);

    // Formula: ac * 10^(2m) + (ad + bc) * 10^m + bd
    string term1 = shiftLeft(ac, 2 * m);
    string term2 = shiftLeft(ad_plus_bc, m);
    string term3 = bd;

    string result = addStrings(addStrings(term1, term2), term3);
    return removeLeadingZeros(result);
}

int main() {
    cout << "==========================================================" << endl;
    cout << "      LARGE INTEGER MULTIPLICATION DEMONSTRATION          " << endl;
    cout << "==========================================================" << endl;

    string num1, num2;
    cout << "\nEnter first large integer: ";
    if (!(cin >> num1)) {
        num1 = "12345678901234567890";
        num2 = "98765432109876543210";
        cout << num1 << endl;
        cout << "Enter second large integer: " << num2 << endl;
    } else {
        cout << "Enter second large integer: ";
        cin >> num2;
    }

    cout << "\n----------------------------------------------------------" << endl;
    cout << "Number 1: " << num1 << " (" << num1.length() << " digits)" << endl;
    cout << "Number 2: " << num2 << " (" << num2.length() << " digits)" << endl;
    cout << "----------------------------------------------------------" << endl;

    // 1) Traditional Divide and Conquer
    string resultDNC = traditionalDivideAndConquer(num1, num2);
    cout << "\n1) Traditional Divide & Conquer Result:\n" << resultDNC << endl;

    // 2) Karatsuba Algorithm
    string resultKaratsuba = karatsuba(num1, num2);
    cout << "\n2) Karatsuba Algorithm Result:\n" << resultKaratsuba << endl;

    // Verification
    if (resultDNC == resultKaratsuba) {
        cout << "\nSUCCESS: Both algorithms produced identical results!" << endl;
    } else {
        cout << "\nERROR: Results do not match!" << endl;
    }

    return 0;
}
