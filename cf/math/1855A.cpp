#include <bits/stdc++.h>
 
using namespace std;
 
int main()
{
    int t,n,p,c;
    cin>>t;
    while(t--){
        cin>>n;
        c=0;
        for(int i=1;i<=n;i++){
            cin>>p;
            if(p==i){
                c++;
            }
        }
        cout<<c/2+(c%2?1:0)<<endl;
    }
    return 0;
}
