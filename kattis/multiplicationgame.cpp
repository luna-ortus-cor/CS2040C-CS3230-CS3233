#include<bits/stdc++.h>
using namespace std;
//observe, it is tie whenever there are more than 2 prime factors
//else, check exponent on prime factors,
//if exponents on prime factors differ by more than 1, tie
//else if exponents on prime factors are equal, other player wins
//else if exponents on prime factors differ by 1, same player wins
//if prime number (number of prime factor==0), person who starts first wins
//if number of prime factor=1, person who starts first wins if odd exponent, else other player
//10=2*5, exponent equal, other player wins
//20=2^2*5, exponent differ by less than 1, same player wins
//30=2*3*5, more than 2 prime factor, so tie
//40=2^3*5, exponent differ by more than 1, so tie
//check factors up to 50000, since 50000^2>2^31-1
//so at most check 50000*10000=5e8, doable in 3s
//rmb to check after iterating 50000 that N becomes 1 i.e. all prime factors found
//else there is (one) prime factor of exponent 1 >50000 and so need to account for it

int factor(int N){
    int num_p=0,a=0,b=0;
    for(int i=2;i<50000;i++){
        if(N==1)break;
        if(N%i==0)num_p++;
        if(num_p>2)return 0;
        while(N%i==0){
            if(num_p%2)a++;
            else b++;
            N/=i;
        }
    }
    //technically can return all in one line xd
    if(N!=1){num_p++;num_p%2?a=1:b=1;}
    return num_p<=2?num_p==1?a%2+(a%2?0:2):abs(a-b)>1?0:a==b?2:1:0;
}

int main(){
    int T;cin>>T;
    int N,c;string s;
    while(T--){
        cin>>N>>s;
        c=factor(N);
        if(c==1) cout<<(s=="Alice"?"Alice":"Bob")<<"\n";
        else if(c==2) cout<<(s=="Alice"?"Bob":"Alice")<<"\n";
        else cout<<"tie\n";
    }
    return 0;
}
