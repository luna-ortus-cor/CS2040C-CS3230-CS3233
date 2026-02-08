#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<vector<ll>> mul(const vector<vector<ll>>& A, const vector<vector<ll>>& B, ll mod){
    int n=A.size();
    vector<vector<ll>> C(n,vector<ll>(n));
    for(int i=0;i<n;i++)
        for(int k=0;k<n;k++)
            if (A[i][k])
                for(int j=0;j<n;j++)
                    C[i][j]=(C[i][j]+A[i][k]*B[k][j])%mod;
    return C;
}

vector<vector<ll>> mpow(vector<vector<ll>> A, ll e, ll mod){
    int n=A.size();
    vector<vector<ll>> R(n,vector<ll>(n));
    for(int i=0;i<n;i++)R[i][i]=1;
    while(e){
        if (e&1)R=mul(R,A,mod);
        A=mul(A,A,mod);
        e>>=1;
    }
    return R;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin>>N;
    vector<ll> a(N+1);
    for(int i=0;i<=N;i++)cin>>a[i];
    vector<ll> x(N);
    for(int i=0;i<N;i++)cin>>x[i];
    int Q;
    cin>>Q;
    int S=N+1;
    vector<vector<ll>> T(S,vector<ll>(S));
    for(int i=0;i<N;i++)T[0][i]=a[i+1];
    T[0][N]=a[0];
    for(int i=1;i<N;i++)T[i][i-1]=1;
    T[N][N]=1;

    while(Q--){
        ll Tq,M;
        cin>>Tq>>M;
        if(Tq<N){
            ll v=x[Tq]%M;
            if(v<0)v+=M;
            cout<<v<<"\n";
            continue;
        }
        vector<vector<ll>> TM=T;
        for(int i=0;i<S;i++)
            for(int j=0;j<S;j++)
                TM[i][j]=((TM[i][j]%M)+M)%M;

        auto P=mpow(TM,Tq-(N-1),M);

        vector<ll> init(S);
        for (int i=0;i<N;i++) {
            ll v=x[N-1-i]%M;
            if(v<0)v+=M;
            init[i]=v;
        }
        init[N]=1%M;

        ll ans=0;
        for (int i=0;i<S;i++)
            ans=(ans+P[0][i]*init[i])%M;
        cout<<ans<<"\n";
    }
    return 0;
}
