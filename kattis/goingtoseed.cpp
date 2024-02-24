#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll solve(ll n,ll N,ll start,ll end){
    ll l1,r1,l2,r2,w1,w2;
    start=max(start,n);
    end=min(end,N-1);
    if(end-start==3){
        cout<<"Q "<<start+1<<" "<<start+2<<" "<<start+2<<" "<<start+3<<endl;
        cout.flush();
        cin>>w1>>w2;
        if(w1&&w2){
            return start+2;
        }else if(w1){
            return start+1;
        }else if(w2){
            return start+3;
        }else{
            return start+4;
        }
    }
    if(end-start==2){
        cout<<"Q "<<start+1<<" "<<start+2<<" "<<start+2<<" "<<start+3<<endl;
        cout.flush();
        cin>>w1>>w2;
        if(w1&&w2){
            return start+2;
        }else if(w1){
            return start+1;
        }else{
            return start+3;
        }
    }
    if(end-start==1){
        cout<<"Q "<<start+1<<" "<<start+1<<" "<<end+1<<" "<<end+1<<endl;
        cout.flush();
        cin>>w1>>w2;
        if(w1){
            return start+1;
        }else{
            return start+2;
        }
    }
    if(end-start==0){
        return start+1;
    }
    
    l1=max(start,n);
    l2=min(start+((end-start)/4),N-1);
    r1=min(start+(2*(end-start-1)/4),N-1); //dunno why it works
    r2=min(start+(3*(end-start)/4),N-1);
    cout<<"Q "<<l1+1<<" "<<r1+1<<" "<<l2+1<<" "<<r2+1<<endl;
    cout.flush();
    cin>>w1>>w2;
    if(w1&&w2){
        return solve(n,N,l2-1,r1+1);
    }else if(w1){
        return solve(n,N,l1-1,l2);
    }else if(w2){
        return solve(n,N,r1,r2+1);
    }else{
        return solve(n,N,r2,end+1);
    }
}

int main(){
    ll N;
    cin>>N;
    ll n = 0;
    ll ans = solve(n,N,0,N-1);
    cout<<"A "<<ans<<endl;
    cout.flush();
    return 0;
}
