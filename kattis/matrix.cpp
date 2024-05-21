#include <bits/stdc++.h>
using namespace std;
//just use inv of 2x2 matrix (a b;c d)
//M-1=1/det * (d -b;-c a)
//det=ad-bc

int main(){
    int a,b,c,d,i=1,det;string s;
    while(cin>>a>>b>>c>>d){
        cout<<"Case "<<i<<":\n";
        det=a*d-b*c;
        cout<<d/det<<" "<<-b/det<<"\n";
        cout<<-c/det<<" "<<a/det<<"\n";
        getline(cin,s);getline(cin,s);
        i++;
    }
}
