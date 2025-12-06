#include <bits/stdc++.h>
using namespace std;

//first initialize vector of size n to 0
//then set count the number of arrows to 0
//iterate through the n integers
//if the parent balloon number is 0, then need to fire arrow
//increment count, increment curent balloon number
//if parent balloon number is 1, then that arrow will hit current balloon
//decrement parent balloon number, increment current balloon number
//this is to ensure each parent balloon arrow will only hit 1 child balloon
//if more than 1 possible child balloon exists

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    vector<int> v(n,0);
    int num;
    int count=0;
    while(cin>>num){
        if(v[num]){
            v[num-1]++;
            v[num]--;
        }else{
            count++;
            v[num-1]++;
        }
    }
    cout<<count<<endl;
    return 0;
}
