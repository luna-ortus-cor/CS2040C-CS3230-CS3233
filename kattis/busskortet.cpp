#include <bits/stdc++.h>

using namespace std;

int main(){
    int total;
    cin>>total;
    int denom [] = {100,200,500};
    int M [10001];
    for(int i=0;i<10001;i++){
        M[i]=10001;
    }
    M[0]=0;
    for(int d:denom){
        for(int v=0;v<=10001-d-1;v++){
            M[v+d]=min(M[v+d],M[v]+1);
        }
    }
    for(int i=total;i<10001;i++){
        if(M[i]!=10001){
            cout<<M[i]<<endl;
            break;
        }
    }
}
