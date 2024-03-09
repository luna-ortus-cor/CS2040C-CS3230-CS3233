#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
//any range of numbers with start and end
//divisible by 9 has sum 0 mod 9
//so just consider numbers outside 
//the largest such range
int main(){
    ll L,R;
    cin>>L>>R;
    ll ans=0;
    for(ll i=0;i<9-(L%9);i++){
        ans=(ans+L+i)%9;
    }
    for(ll i=0;i<R%9;i++){
        ans=(ans+R-i)%9;
    }
    cout<<ans%9<<endl;
    return 0;
}
