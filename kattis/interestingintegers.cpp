#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define inf 1000000000

//same as below except we realise a,b are relatively small (<1E6)
//and so brute force on b is possible

void find(ll n, vector<ll> &fib){
    for(ll b = 1;b<=n;b++){
        for(ll i = 1;i<fib.size();i++){
            if(n<=b*fib[i]){
                break;
            }
            ll a = (n-(b*fib[i]))/fib[i-1];
            if(0<a&&a<=b&&a*fib[i-1]+b*fib[i]==n){
                cout<<a<<' '<<b<<endl;
                return;
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    vector<ll> fib={1,1};
    ll f = 0;
    while(f<=inf){
        vector<ll>::iterator it = fib.end();
        f = *(it-1) + *(it-2);
        fib.push_back(f);
    }
    ll tc,n;
    cin>>tc;
    while(tc--){
        cin>>n;
        find(n,fib);
    }
    return 0;
}

//does not work for some small n
/**
//we begin with some observations about Gn
//namely, that Gn = F(n-2)G1 + F(n-1)G2
//due to the constraints of the problem n<=10E9
//we only need to precompute first 50 fibonacci numbers Fn
//we loop starting from the largest fibonacci numbers so that 
//minimum G1,G2 can be attained
//we further note that Fn,F(n-1) are coprime, that is
//Gn = F(n-2)G1 + F(n-1)G2 will always have integer solutions G1,G2
//as gcd(F(n),F(n-1))=1|Gn
//we further realise something interesting about Fn
//F(n)F(n-3)-F(n-1)F(n-2) = \pm 1
//it suffices to check and change sign if -1, then
//N [ F(n)F(n-3) - F(n-1)F(n-2) ] = N
//we then just need to check if N*F(n-3)/F(n-1) > N*F(n-2)/F(n)
//if yes, then solution exists which is given by
//G1 = N*F(n-3) - N*F(n-3)/F(n-1)*F(n-1)
//G2 = -N*F(n-2)/F(n) + N*F(n-3)/F(n-1)*F(n)

int main(){
    vector<ll> fib={1,1};
    ll f = 0;
    while(f<=inf){
        vector<ll>::iterator it = fib.end();
        f = *(it-1) + *(it-2);
        fib.push_back(f);
    }
    ll tc;
    cin>>tc;
    for(ll i = 0;i<tc;i++){
        ll n;
        cin>>n;
        ll final1=inf,final2=inf;
        vector<ll>::iterator it = fib.end()-1;
        bool found = false;
        while(it>=fib.begin()+3){
            if(*it == n){
                final1=1;
                final2=1;
                found=true;
                break;
            }
            if((*it)+(*(it-1))>n){
                it--;
                continue;
            }
            /**
            //ll x0 = (*it) * (*(it-3)) > (*(it-2)) * (*(it-1)) ? n*(*(it-3)):n*(*(it-2));
            //ll y0 = (*it) * (*(it-3)) > (*(it-2)) * (*(it-1)) ? n*(*(it-2)):n*(*(it-3));
            //ll g1 = (*it) * (*(it-3)) > (*(it-2)) * (*(it-1)) ? (*it):(*(it-1));
            //ll g2 = (*it) * (*(it-3)) > (*(it-2)) * (*(it-1)) ? (*(it-1)):(*it);
            //ll x1 = (*it) * (*(it-3)) > (*(it-2)) * (*(it-1)) ? y0/g1:x0/g2;
            //ll y1 = (*it) * (*(it-3)) > (*(it-2)) * (*(it-1)) ? x0/g2:y0/g1;
            //cout<<g1<<'*'<<x0<<'-'<<g2<<'*'<<y0<<endl;
            //cout<<x1<<' '<<y1<<endl;
            //if( (*it) * (*(it-3)) > (*(it-2)) * (*(it-1)) ? y1>x1 : x1>y1){
                ll temp1 = x0-x1*g2;
                ll temp2 = x1*g1-y0;
                if((*(it-1))*temp1 + (*(it))*temp2 == n && temp1<=temp2){
                    while(temp1+(*(it))<=temp2-(*(it-1))){ //minimize b
                        temp1+=(*(it));
                        temp2-=(*(it-1));
                    }
                    cout<<temp1<<' '<<temp2<<endl;
                    if(temp2<ans2){
                        ans1=temp1;
                        ans2=temp2;
                    }
                    //break;
                }
            }
            
            ll f1 = *(it-1);
            ll f2 = *it;
            ll g1 = n*(*(it-2));
            ll g2 = n*(*(it-3));
            if(g1==0 || g2==0){
                it--;
                continue;
            }
            bool reverse = false;
            if(f1*g1-f2*g2==-n){
                reverse=true;
            }
            //cout<<f1<<'*'<<g1<<'-'<<f2<<'*'<<g2<<endl;
            //cout<<g1/f2<<' '<<g2/f1<<' '<<reverse<<endl;
            if( reverse ? g1/f2<=g2/f1 : g2/f1<=g1/f2 ){
                ll ans1 = reverse ? (g2/f1*f2) - g1 : g1 - (g1/f2*f2);
                ll ans2 = reverse ? g2 - (g2/f1*f1) : (g1/f2*f1) - g2;
                //cout<<ans1<<' '<<ans2<<endl;
                if(f1*ans1+f2*ans2==n && ans1<=ans2){
                    while(ans1+f2<=ans2-f1){
                        ans1+=f2;
                        ans2-=f1;
                    }
                    if(0<ans1 && 0<ans2 && ans1<=ans2){
                        //cout<<ans1<<' '<<ans2<<endl;
                        if(ans2<final2){
                            final1=ans1;
                            final2=ans2;
                        }
                        found=true;
                        break;
                    }
                }else if(f1*ans1+f2*ans2==n && ans1>=ans2){
                    while(ans1>=ans2){
                        ans1-=f2;
                        ans2+=f1;
                    }
                    if(0<ans1 && 0<ans2 && ans1<=ans2){
                        //cout<<ans1<<' '<<ans2<<endl;
                        if(ans2<final2){
                            final1=ans1;
                            final2=ans2;
                        }
                        found=true;
                        break;
                    }
                }
            }
            it--;
        }
        if(found){
            cout<<final1<<' '<<final2<<endl;
            continue;
        }
        for(ll b = 1;b<=n;b++){
            cout<<b<<endl;
            for(int i = 1;i<fib.size();i++){
                if(n<=b*fib[i]){
                    break;
                }
                if( (n-b*fib[i])%fib[i-1]==0 ){
                    ll a = (n-b*fib[i])/fib[i-1];
                    if(0<a&&a<=b&&a*fib[i-1]+b*fib[i]==n){
                        //found=true;
                        if(b<final2){
                            final1=a;
                            final2=b;
                        }
                        //cout<<a<<' '<<b<<endl;
                    }
                }
            }
            /**
            if(found){
                cout<<final1<<' '<<final2<<endl;
                break;
            }
            
        }
        cout<<final1<<' '<<final2<<endl;
    }
    return 0;
}**/
