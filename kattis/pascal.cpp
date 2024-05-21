#include <bits/stdc++.h>
using namespace std;
//idea is given N, counter counts the result of
//N/p*(p-1), p smallest prime factor of N
//so iterate from 2 to sqrt(N) to check 
//for such p, then calc N/p*(p-1)
//decide to use 1e5 instead since N bounded by 1e9
//note if N is 1 then ans is 0
//if N is prime then ans is N-1, nonprime N must have divisor in <1e5

int main(){
    int N;cin>>N;
    if(N==1){cout<<0;return 0;}
    else{for(int i=2;i<100001;i++){if(N%i==0){cout<<N/i*(i-1);return 0;}}}
    cout<<N-1;
    return 0;
}
