#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//observe that since the order of L and R operations is invariant
//we can simply proceed with taking all R operations first then all L operations
//for a series of R operations, note that the answer follows the triangle numbers
//specifically, for r R operations, we go from 1 to (r+1)(r+2)/2
//(r terms beginning from 1 -> r+1 th triangle number)
//then now notice that from any number, a series of L operations then follows a
//"shifted" triangle number sequence i.e. beginning from the nth row, a series of l L
//operations will add n, then add n+1, then add n+2, ..., then add n+l+1 (for l terms)
//This is equivalent to taking the triangle number sequence 0, 1, 3, 6, 10, ... then adding the
//offset of l*r (since we begin from the rth row), thus this adds l(l+1)/2 + lr
//(l terms beginning from 0 -> lth triangle number) + offset
//so the answer is simply (r+1)(r+2)/2 + l(l+1)/2 + lr

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin>>T;
    ll L,R,ans;
    while(T--){
        cin>>L>>R;
        ans=(R+1)*(R+2)/2 + L*(L+1)/2 + L*R;
        cout<<ans<<"\n";
    }
}
