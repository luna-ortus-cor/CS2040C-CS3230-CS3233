#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//this problem is easily solved by dfs, with some memoization
//consider dfs at any node, the number of ways to reach that node
//is given by the sum of the number of ways to reach each of its parents
//i.e. if 1->2 3 4 and 5->2 4 6 and 7->2 8 9 then number of ways to reach
//2 is 3 (from parents 1, 5, 7)
//that is, we invert the structure, instead of storing 1->2 3 4 we store
//2->1 3->1 4->1 instead in the adjacency list
//then notice that once a node has been fully explored by dfs, it is guaranteed
//that the value of that node i.e. number of ways to reach it, will not change
//so we can store that value in the vector sections (memoize), this occurs
//just before the dfs call returns
//the base case is when we reach any node with a pre-stored value, initially
//this is only the node 1 (with value 1), which we set at the start
//then we just have to dfs on each of the ending "favourably" nodes
//a stack is not needed, i just used it since i was originally doing dfs iteratively
//and not by recursion but the recursive version is easier to implement

ll dfs(int section, vector<vector<int>> &adj, vector<ll> &sections){
    if(sections[section]) return sections[section];
    ll count=0;
    for(int parent:adj[section]){
        count+=dfs(parent,adj,sections);
    }
    sections[section]=count;
    return count;
}

int main(){
    int T,S,F;
    ll a,b,c,d;
    string line,s;
    cin>>T;
    while(T--){
        cin>>S;
        F=0;
        stack<int> stak;
        vector<ll> sections(401,0);
        sections[1]=1;
        vector<vector<int>> adj(401,vector<int>());
        cin.ignore();
        while(S--){
            getline(cin,line);
            istringstream ss(line);
            if(ss>>a>>b>>c>>d){
                adj[b].push_back(a);
                adj[c].push_back(a);
                adj[d].push_back(a);
            }else{
                ss.clear();
                ss.str(line);
                ss>>a>>s;
                if(s=="favourably"){
                    stak.push(a);
                }
            }
        }
        ll count=0;
        while(!stak.empty()){
            a=stak.top();stak.pop();
            count+=dfs(a,adj,sections);
        }
        cout<<count<<"\n";
    }
    return 0;
}
