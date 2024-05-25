#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
//observe that 1 is always valid, so min num item is 1
//then now for any 2 item in subset to sum to <= X clearly
//max and 2nd max ele in subset must sum to <= X
//so sort array of prices, iterate through
//stop when curr ele + next ele > X, output ans

int main(){
    ll n,x,p;cin>>n>>x;
    vector<ll> ps;
    while(cin>>p)ps.push_back(p);
    sort(ps.begin(),ps.end());
    vector<ll>::iterator it=ps.begin();
    ll temp,ans=1;
    while(it+1<ps.end()){
        temp=*it+*(it+1);it++;
        if(temp>x)break;
        else ans++;
    }
    cout<<ans<<endl;
    return 0;
}
