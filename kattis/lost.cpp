#include <bits/stdc++.h>

using namespace std;

#define inf 9223372036854775807
typedef long long ll;

int main(){
    int n,m;
    cin>>n>>m;
    if(m<n){
        cout<<"Impossible"<<endl;
        return 0;
    }
    vector<string> langs;
    langs.push_back("English");
    unordered_map<string,ll> mapping;
    mapping.emplace(make_pair("English",0));
    for(int i=0;i<n;i++){
        string s;
        cin>>s;
        langs.push_back(s);
        mapping.emplace(make_pair(s,i+1));
    }
    vector<vector<ll>> dists(n+1,vector<ll>(n+1));
    for(int i=0;i<m;i++){
        string s1,s2;
        ll d;
        cin>>s1>>s2>>d;
        dists[mapping[s1]][mapping[s2]]=d;
        dists[mapping[s2]][mapping[s1]]=d;
    }
    vector<vector<ll>> tr(101);
    vector<int> visited(n+1);
    vector<int> parent(n+1);
    ll mincost= 0;
    tr[0].push_back(0);
    visited[0]=1;
    int counter = 1;
    for(int i=1;i<n+1;i++){
        vector<ll> prev = tr[i-1];
        if(prev.size()==0){
            break;
        }
        while(true){
            ll curr = inf;
            int idx = -1;
            int par = -1;
            for(ll p:prev){
                for(int j=0;j<n+1;j++){
                    if(dists[p][j]!=0&&visited[j]!=1&&dists[p][j]<curr){
                        curr=dists[p][j];
                        idx=j;
                        par=p;
                    }
                }
            }
            if(idx==-1){
                break;
            }else{
                counter++;
                visited[idx]=1;
                tr[i].push_back(idx);
                parent[idx]=par;
                mincost+=curr;
            }
        }
        if(counter==n+1){
            break;
        }
    }
    if(counter==n+1){
        cout<<mincost<<endl;
    }else{
        cout<<"Impossible"<<endl;
    }
    return 0;
}

//below solution wrong, this problem is not an MST, is a BFS

// minimum spanning tree

pair<ll,ll> minele(vector<ll> keys,vector<ll> visited){
    ll curr=inf;
    ll minidx=-1;
    for(int i=0;i<keys.size();i++){
        if(visited[i]==0 && keys[i]<curr){
            curr=keys[i];
            minidx=i;
        }
    }
    return make_pair(minidx,curr);
}

int main2(){
    int n,m;
    cin>>n>>m;
    if(m<n){
        cout<<"Impossible"<<endl;
        return 0;
    }
    vector<string> langs;
    langs.push_back("English");
    unordered_map<string,ll> mapping;
    mapping.emplace(make_pair("English",0));
    for(int i=0;i<n;i++){
        string s;
        cin>>s;
        langs.push_back(s);
        mapping.emplace(make_pair(s,i+1));
    }
    vector<vector<ll>> dists(n+1,vector<ll>(n+1));
    for(int i=0;i<m;i++){
        string s1,s2;
        ll d;
        cin>>s1>>s2>>d;
        dists[mapping[s1]][mapping[s2]]=d;
        dists[mapping[s2]][mapping[s1]]=d;
    }
    
    ll mincost=0;
    vector<ll> keys(n+1); //minimum dist for each node from current tree
    vector<ll> visited(n+1);
    vector<ll> parent(n+1); //for debugging, to keep track of which node was added wrt to parent
    for(int i=0;i<n+1;i++){
        keys[i]=inf;
    }
    keys[0]=0;
    parent[0]=-1;
    for(int i=0;i<n+1;i++){ //need to visit n+1 nodes
        pair<ll,ll> ele=minele(keys,visited);
        if(ele.first==-1){
            cout<<"Impossible"<<endl;
            return 0;
        }
        visited[ele.first]=1;
        mincost+=ele.second;
        for(int j=0;j<n+1;j++){
            //this focuses on minimizing cost and not distances
            //if(dists[ele.first][j]!=0 && visited[j]!=1 && dists[ele.first][j]<keys[j]){ //dists here is actually costs
            if(dists[ele.first][j]!=0 && visited[j]!=1){
                parent[j]=ele.first;
                keys[j]=dists[ele.first][j];
            }
        }
    }
    cout<<mincost<<endl;
    for(ll i:parent){cout<<i<<" ";}
    cout<<endl;
    return 0;
}
