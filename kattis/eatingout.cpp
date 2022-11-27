#include <bits/stdc++.h>

using namespace std;

int main(){
    int m,a,b,c;
    cin>>m>>a>>b>>c;
    if(a+b+c>=2*m+1){
        cout<<"impossible"<<endl;
    }else{
        cout<<"possible"<<endl;
    }
    return 0;
}
