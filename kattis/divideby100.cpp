#include <bits/stdc++.h>
using namespace std;

//handle each case carefully
//when N/M<1 and when this has trailing zero
//when N/M is integer (and remove trailing zero)
//when N/M is not integer (and remove trailing zero)

int main(){
    string N,M;
    cin>>N>>M;
    int m=M.size()-1;
    int n=N.size();
    if(n<=m){
        string result="0."+string(m-n,'0')+N;
        int lastNonZero=result.length()-1;
        while(lastNonZero>=0 && result[lastNonZero]=='0'){
            lastNonZero--;
        }
        result=result.substr(0,lastNonZero+1);
        cout<<result;
    }else{
        string integerPart = N.substr(0, n-m);
        string fractionalPart = N.substr(n-m);
        if(fractionalPart.empty()){
            cout<<integerPart;
        }else{
            int lastNonZero=fractionalPart.length()-1;
            while(lastNonZero>=0 && fractionalPart[lastNonZero]=='0'){
                lastNonZero--;
            }
            fractionalPart=fractionalPart.substr(0,lastNonZero+1);
            if(fractionalPart.empty()){
                cout<<integerPart;
            }else{
                cout<<integerPart<<"."<<fractionalPart;
            }
        }
    }    
    return 0;
}
