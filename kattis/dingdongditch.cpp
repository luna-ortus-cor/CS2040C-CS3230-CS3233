#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll get(){
    char ch;
    while(ch=getchar(),(ch<'0'||ch>'9')&&ch!='-');
    ll s=ch-'0';
    while(ch=getchar(),ch>='0'&&ch<='9')s=s*10+ch-'0';
    return s;
}

int main() {
    int N,Q,t;
    N=get();Q=get();
    ll A[N];
    for (int i = 0; i < N; ++i)
        A[i]=get();
    sort(A,A+N);partial_sum(A,A+N,A);
    for(int i = 0; i < Q; ++i){
        t=get();
        printf("%lld\n", A[~-t]);
    }
    return 0;
}
