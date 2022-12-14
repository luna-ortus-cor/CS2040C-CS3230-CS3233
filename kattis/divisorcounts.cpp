#include <bits/stdc++.h>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin>>N;
    vector<int> factors(N+1,1);
    for(int i=2;i<=N;i++){
        factors[i]++;
        for(int j=i+i;j<N+1;j+=i){
            factors[j]++;
        }
    }
    for(int i=1;i<=N;i++){
        cout<<factors[i]<<"\n";
    }
    return 0;
}
