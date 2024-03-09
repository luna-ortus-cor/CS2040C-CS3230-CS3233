#include <iostream>
using namespace std;
 
int main(){
    int t;
    cin>>t;
    for(int i=0;i<t;i++){
        int n;
        cin>>n;
        int ans = -1;
        int m = 0;
        for(int j = 0;j<n;j++){
            int a,b;
            cin>>a>>b;
            if(a<=10 && b>m){
                m=b;
                ans=j;
            }
        }
        cout<<ans+1<<endl;
    }
    return 0;
}
