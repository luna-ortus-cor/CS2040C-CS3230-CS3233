#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//suppose player 1 is winning for n=a
//clearly player 1 will win for n=b, 9a<b<=18a
//otherwise player 2 will win
//we can apply induction to show that
//Stan is winning on (1,9], Ollie is winning on (0,1]
//for n<=9 implies Stan is winning on (18x+1,18x+9]
//Ollie is winning on (18x,18x+1]
//thus while n>9 we continually divide by 18
//until n is in (0,9] 
//e.g. 362/18 = 9 > Stan win
//e.g. 17/18 < 1 > Ollie win

int main(){
    ll n;
    while(cin>>n){
        double nn = (double) n;
        while(nn>9.0){
            nn/=18.0;
        }
        if(nn<=1){
            cout<<"Ollie wins."<<endl;
        }else{
            cout<<"Stan wins."<<endl;
        }
    }
    return 0;
}
