#include <bits/stdc++.h>

using namespace std;

int main() {
    int K;
    cin >> K;
    int f1 = 1;
    int f2 = 0;
    int temp = 0;
    for(int i = 1; i < K; i++){
        temp = f1;
        f1 += f2;
        f2 = temp;
    }
    cout << f2 << " " << f1;
    return 0;
}
