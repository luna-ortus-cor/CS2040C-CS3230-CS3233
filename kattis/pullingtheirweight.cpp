#include <bits/stdc++.h>

using namespace std;

// double pointers

int main(){
    int m;
    cin>>m;
    vector<int> weights;
    for(int i=0;i<m;i++){
        int w;
        cin>>w;
        weights.push_back(w);
    }
    sort(weights.begin(),weights.end());
    int a=0;
    int b=weights.size()-1;
    int lsum=weights[a],rsum=weights[b];
    while(a<=b){
        if(a==b){
            break;
        }
        if(lsum<=rsum){
            a++;
            lsum+=weights[a];
        }else{
            b--;
            rsum+=weights[b];
        }
    }
    if(lsum==rsum){
        cout<<weights[a]<<endl;
    }else{
        if(weights[a-1]==weights[b]){
            cout<<weights[a-1]<<endl;
        }else{
            cout<<weights[a-1]+1<<endl;
        }
    }
    return 0;
}
