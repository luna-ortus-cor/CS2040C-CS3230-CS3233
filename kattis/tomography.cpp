#include <bits/stdc++.h>
using namespace std;

//realise that permutation of row and column sums
//does not change correctness of output/existence of soln
//then can see greedy property, for every row sum
//take 1 from the largest column sums possible
//remember to sort after each iteration
//also see Gale-Ryser theorem

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int m,n;
    cin>>m>>n;
    vector<int> ms(m),ns(n);
    int msum=0,nsum=0;
    for(int i=0;i<m;i++){cin>>ms[i];msum+=ms[i];}
    for(int i=0;i<n;i++){cin>>ns[i];nsum+=ns[i];}
    if(msum!=nsum){cout<<"No";return 0;}
    sort(ms.begin(),ms.end(),greater<int>());
    sort(ns.begin(),ns.end(),greater<int>());
    for(int i=0;i<m;i++){
        sort(ns.begin(),ns.end(),greater<int>());
        for(int j=0;j<ms[i];j++){
            if(ns[j]<1){cout<<"No";return 0;} 
            ns[j]--;
        }
    }
    cout<<"Yes";
    return 0;
}
