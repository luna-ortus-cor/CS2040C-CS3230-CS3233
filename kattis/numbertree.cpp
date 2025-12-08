#include <bits/stdc++.h>
using namespace std;

//instead of directly calculating the node value
//instead calculate how much we have to subtract from 2^h to get the node value
//then this gives a min heap with 1, 2, 3,... etc from top to bottom, left to right
//then we can easily determine this value, starting from the root 1
//L will *2, R will *2+1, do this for every char in the sequence
//finally subtract this value from 2^h
//which can be done easily using the bit operations and also due to the constraints (will fit in int)

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int h;
    cin>>h;
    int a=1;
    string s;
    cin>>s;
    for(auto c:s){
        a*=2;
        if(c=='L')a+=0;
        else a+=1;
    }
    cout<<(1<<(h+1))-a;
    return 0;
}
