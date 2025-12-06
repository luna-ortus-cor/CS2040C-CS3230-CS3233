#include <bits/stdc++.h>
using namespace std;

//convert string to array of 0,1
//check n%2==a[i]^b[i] i.e. parity of n matches a^b
//difficult to use bitset since leading zeroes and also too large (up to 2^1000)
//i.e. converting to int and xor will lose the leading zeroes, although in python 2^1000<1e308

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    string line;
    cin>>line;
    vector<int> a(line.size());
    transform(line.begin(),line.end(),a.begin(),[](char c){return c-'0';});
    cin>>line;
    vector<int> b(line.size());
    transform(line.begin(),line.end(),b.begin(),[](char c){return c-'0';});
    bool deleted=true;
    for(int i=0;i<line.size();i++){
        if((n%2)!=(a[i]^b[i]))deleted=false;
    }
    if(deleted){
        cout<<"Deletion succeeded\n";
    }else{
        cout<<"Deletion failed\n";
    }
}
