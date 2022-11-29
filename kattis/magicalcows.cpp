#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
    int C,N,M;
    cin>>C>>N>>M;
    int doubled=0;
    int notdoubled=0;
    unordered_map<int,int> add;
    for(int i=0;i<N;i++){
        int temp;
        cin>>temp;
        if(temp<=C/2){
            notdoubled++;
            int days=0;
            while(temp<=C/2){
                days++;
                temp*=2;
            }
            if(add.find(days)!=add.end()){
                add[days]++;
            }else{
                add.emplace(make_pair(days,1));
            }
        }else{
            doubled++;
        }
    }
    vector<ll> doubletdy(51);
    vector<ll> total(51);
    doubletdy[0]=doubled;
    total[0]=notdoubled+doubletdy[0];
    for(int i=1;i<51;i++){
        if(add.find(i)!=add.end()){
            doubletdy[i]=2*doubletdy[i-1]+add[i];
            notdoubled-=add[i];
        }else{
            doubletdy[i]=2*doubletdy[i-1];
        }
        total[i]=doubletdy[i]+notdoubled;
    }
    for(int i=0;i<M;i++){
        int m;
        cin>>m;
        cout<<total[m]<<endl;
    }
    return 0;
}
