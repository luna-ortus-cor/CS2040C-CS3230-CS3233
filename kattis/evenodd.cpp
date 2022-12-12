#include <bits/stdc++.h>

using namespace std;

#define mod 1000000007
typedef long long ll;

//We define F(x)=f(1)+f(2)+...+f(x)
//observe that f(2X)=f(X)+1
//then for even numbers
//f(2)+f(4)+...+f(2X)=\sum_{i=1}^X f(2i)=\sum_{i=1}^X f(i)+1=F(X)+X
//observe that f(2X-1)=f(2X)+1, except for f(1)=0, instead of 2
//then for odd numbers
//f(1)+f(3)+...+f(2X-1)=-2+\sum_{i=1}^X f(2i-1)=-2+\sum_{i=1}^X f(2i)+1
//=-2+X+\sum_{i=1}^X f(2i)=-2+X+F(X)+X
//So, F(2X)=2F(X)+3X-2, and F(2X+1)=F(2X)+f(2X+1)

ll f(ll x){
    ll i = 0;
    while(x!=1){
        if(x%2==0){
            x/=2;
        }else{
            x+=1;
        }
        i=(i+1)%mod;
    }
    return i;
}

ll F(ll x){
    if(x==1||x==0){
        return 0;
    }else{
        if(x%2==0){
            ll temp = 3*x/2 %mod;
            if(temp<2){
                temp+=mod;
                temp-=2;
            }else{
                temp-=2;
            }
            return ((2*F(x/2)%mod)+temp)%mod;
        }else{
            return F(x-1)%mod+f(x)%mod;
        }
    }
}

int main(){
    ll L,R;
    cin>>L>>R;
    if(L==R){
        cout<<f(L)<<endl;
    }else{
        ll r = F(R);
        ll l = F(L-1);
        ll ans = r-l;
        if(ans<0){
            ans+=mod;
        }
        cout<<ans<<endl;
    }
}
