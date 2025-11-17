#include <iostream>
#include <vector>
using namespace std;

// =============================
// Max Pairwise Product 
// =============================

long long maxPairwiseProductSimple(vector<int>& v) {
    long long maxProduct = 0;
    for (int i = 0;i < v.size();i++) {
        for (int j = i + 1;j < v.size();j++) {
            long long prod = (long long)v[i] * v[j];
            if (prod > maxProduct) maxProduct = prod;
        }
    }
    return maxProduct;
}

long long maxPairwiseProductFast(vector<int>& v) {
    int max1 = 0, max2 = 0;
    for (int i = 0;i < v.size();i++) {
        if (v[i] > max1) {
            max2 = max1;
            max1 = v[i];
        }
        else if (v[i] > max2) {
            max2 = v[i];
        }
    }
    return (long long)max1 * max2;
}

void stressTestMaxProduct() {
    int t; cout << "\nHow many test cases? "; cin >> t;
    while (t--) {
        int n; cout << "Enter number of elements: "; cin >> n;
        vector<int> v(n);
        cout << "Enter elements: "; for (int i = 0;i < n;i++) cin >> v[i];
        long long resSimple = maxPairwiseProductSimple(v);
        long long resFast = maxPairwiseProductFast(v);
        cout << "Naive: " << resSimple << "  Fast: " << resFast << endl;
        if (resSimple == resFast) cout << " Results match!\n";
        else cout << " Results differ!\n";
    }
}

// =============================
// Recursive GCD 
// =============================

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

void recursionExample() {
    int a, b;
    cout << "\nEnter two numbers to find GCD: ";
    cin >> a >> b;
    cout << "GCD is: " << gcd(a, b) << endl;
}

// =============================
// Main function
// =============================

int main() {
    cout << "=============================\n";
    cout << "Name: Maham Fatima\n";
    cout << "Class: BSAI-III-A\n";
    cout << "Roll No: 241408\n";
    cout << "=============================\n";

    // =============================
    // Max Pairwise Product Example
    // =============================
    vector<int> v = { 1, 10, 2, 6, 5 };
    cout << "\nVector elements: "; for (int x : v) cout << x << " "; cout << endl;
    cout << "Naive solution: " << maxPairwiseProductSimple(v) << endl;
    cout << "Fast solution: " << maxPairwiseProductFast(v) << endl;

    // =============================
    // Recursive GCD Example
    // =============================
    recursionExample();

    // =============================
    // Stress Test Max Pairwise Product
    // =============================
    stressTestMaxProduct();

    return 0;
}
