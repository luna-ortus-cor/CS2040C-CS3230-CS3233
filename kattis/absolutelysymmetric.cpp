#include<bits/stdc++.h>
using namespace std;
//let an absoutely symmetric element be such that |A(i,j)|=|A(j,i)|
//clearly every diagonal element is absolutely symmetric
//if A(i,j)==A(j,i) or A(i,j)==-A(j,i) likewise absolutely symmetric
//if none of the above are true, then check if the difference between A(i,j) and A(j,i) is even
//any odd difference can never be expressed as a sum of absolutely symmetric elements
//since any absolutely symmetric element has either 0 or even diff (e-(-e)=2e)
//if even diff then we can have c=(a+b)/2, d=a-c, e=b-c as absolutely symmetric elements (and c is int)
//since d=-e (d=a-c=a-(a+b)/2=a/2-b/2=-(b/2-a/2)=-(b-(a+b)/2)=-(b-c)=-e)
//so if there is an odd difference then cannot be decomposed, so print -1
//then notice we only need a max of 2 such decomposition matrices since A(i1,j1) does not affect
//absolutely symmetricness of A(i2,j2) (assuming not same/diagonal/symmetric elements)
//so use one matrix B to store all already symmetric elements + center element of even diff
//and one matric C to store the diff between element and center element for even diff

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;

vll solve(const ll a,const ll b){return {(a-b)/2,a-(a-b)/2,-((a-b)/2),a-(a-b)/2};}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll n,a,b;
    cin>>n;
    ll ans=1;
    vvll A(n,vector<ll>(n,0)),ans1(n,vector<ll>(n,0)),ans2(n,vector<ll>(n,0));
    for(ll i=0;i<n;i++){
        for(ll j=0;j<n;j++){
            cin>>A[i][j];
        }
    }
    for(ll i=0;i<n;i++){
        for(ll j=i;j<n;j++){
            a=A[i][j];
            b=A[j][i];
            if(abs(a)==abs(b)){
                ans1[i][j]=a;
                ans1[j][i]=b;
            }else if((a-b)%2==0){
                vll c=solve(a,b);
                ans1[i][j]=c[0];
                ans2[i][j]=c[1];
                ans1[j][i]=c[2];
                ans2[j][i]=c[3];
                ans=2;
            }else{
                cout<<-1;
                return 0;
            }
        }
    }
    cout<<ans<<"\n";
    for(ll i=0;i<n;i++){
        for(ll j=0;j<n;j++){
            cout<<ans1[i][j]<<" ";
        }
        cout<<"\n";
    }
    if(ans==2){
        for(ll i=0;i<n;i++){
            for(ll j=0;j<n;j++){
                cout<<ans2[i][j]<<" ";
            }
            cout<<"\n";
        }
    }
    return 0;
}
