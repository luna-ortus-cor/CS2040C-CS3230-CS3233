#include<bits/stdc++.h>
using namespace std;
//input size is small enough to just
//simulate prime reduction process entirely

pair<int,int> reduce(int x,int times){
    int y=x;int temp=0;
    for(int i=2;i<=ceil(pow(x,0.5));i++){
        while(x%i==0){
            x/=i;
            temp+=i;
        }
    }
    if(x==y)return make_pair(x,times+1); //prime number larger than sqrt
    else if(x!=1)return reduce(temp+x,times+1); //composite number, has prime factor larger than sqrt
    else if(temp==y)return make_pair(temp,times+1); //very small prime number
    else return reduce(temp,times+1); //composite number, fully factored
}

int main(){
    int n;
    while(cin>>n){
        if(n!=4){
            pair<int,int>p=reduce(n,0);
            cout<<p.first<<" "<<p.second<<"\n";
        }
    }
}
