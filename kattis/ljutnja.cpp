#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

//likely reason why commented out methods did not work 
//was due to use of pow() 
//in this method we observe that for ascending sorted v,
//we try to remove (s-M) candies, so that we do not exceed M candies
//so, at every child, we attempt to remove (s-M)/(N-i) candies
//i.e. excess candy divide by number of remaining children
//if the child has insufficient candy, we just take all
//update value of S

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    ll M,N;
    cin>>M>>N;
    vector<ll> v;
    ll temp;
    ll s=-M;
    for(ll i=0;i<N;i++){
        cin>>temp;
        v.push_back(temp);
        s+=temp;
    }
    sort(v.begin(),v.end());
    ll ans=0;
    for(ll i=0;i<N;i++){
        ll m = min(v[i],s/(N-i));
        ans+=m*m;
        s-=m;
    }
    cout<<ans;
    return 0;
}

//this also doesnt work, not sure why
//we attempt similar idea as the bottom soln
//where we sort the vector in descending order
//iterating through, we need to hit M candies, so we
//decrease number of candies wanted by each children to the
//next smallest number, until no further increase in M is possible
//we then handle the intermediate case
/**
int main(){
    ll M,N;
    cin>>M>>N;
    unordered_map<ll,ll> a;
    vector<ll> v;
    ll temp;
    for(ll i=0;i<N;i++){
        cin>>temp;
        if(a.find(temp)==a.end()){
            a[temp]=1;
            v.push_back(temp);
        }else{
            a[temp]++;
        }
    }
    
    sort(v.begin(),v.end(),greater<ll>());
    
    ll idx=0;
    while(M>0 && idx<v.size()-1){
        ll m = a[v[idx]];
        if(M-(m*(v[idx]-v[idx+1]))>0){
            M-=(m*(v[idx]-v[idx+1]));
            a[v[idx+1]]+=a[v[idx]];
            a[v[idx]]=0;
            idx++;
        }else{
            break;
        }
    }
    //cout<<M<<endl;
    ll ans=0;
    if(M>0){
        ll val1 = M/a[v[idx]];
        ll val2 = val1+1;
        ll rem2 = M-(val1*a[v[idx]]);
        ll rem1 = a[v[idx]]-rem2;
        //cout<<rem1<<" "<<val1<<" "<<rem2<<" "<<val2<<" "<<v[idx]<<endl;
        ans += rem1*pow(v[idx]-val1,2);
        ans += rem2*pow(v[idx]-val2,2);
        for(ll i=idx+1;i<v.size();i++){
            ans+=a[v[i]]*pow(v[i],2);
        }
    }
    cout<<ans<<endl;
    return 0;
}**/

// no clue why below doesnt work on kattis but works locally
// idea is to sort vector of children desired number
// while sum of wishes is greater than M
// iterate through vector, add square of wishes * number of children with those wishes
// subtract wishes * number of children from s
// handle any remaining s
/**
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    ll M,N;
    cin>>M>>N;
    unordered_map<ll,ll> a;
    vector<ll> v;
    ll temp;
    ll s;
    for(ll i=0;i<N;i++){
        cin>>temp;
        s+=temp;
        if(a.find(temp)==a.end()){
            a[temp]=1;
            v.push_back(temp);
        }else{
            a[temp]++;
        }
    }
    sort(v.begin(),v.end());
    ll valid_child=N;
    ll num_deduct=0;
    ll ans=0;
    ll idx=0;

    while(s>=M && idx<v.size()){
        if(s-valid_child*v[idx]>=M){
            s-=valid_child*v[idx];
            num_deduct=v[idx];
            ans+=pow(v[idx],2)*a[v[idx]];
            valid_child-=a[v[idx]];
            a[v[idx]]=0;
            idx++;
        }else{
            break;
        }
    }

    if(s>M && valid_child>0){
        ll d = (s-M)/valid_child;
        ans+=valid_child*pow(num_deduct+d,2);
        s-=valid_child*d;
        num_deduct+=d;
        if(s>M){
            ans+=(valid_child-(s-M))*pow(num_deduct,2);
            ans+=(s-M)*pow(num_deduct+1,2);
        }
    }
    cout<<ans<<endl;
    return 0;
}**/
