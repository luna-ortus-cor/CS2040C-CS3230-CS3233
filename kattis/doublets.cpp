#include <bits/stdc++.h>
using namespace std;

bool doublet(const string& a,const string& b){
    if(a.length()!=b.length())return false;
    int diff=0;
    for(int i=0;i<a.length();i++){
        if(a[i]!=b[i])diff++;
        if(diff>1)return false;
    }
    return diff==1;
}

void solve(){
    vector<string> dict;
    unordered_map<string,int> word2id;
    string line;
    while(getline(cin,line)&&!line.empty()){
        word2id[line]=dict.size();
        dict.push_back(line);
    }
    int n=dict.size();
    vector<vector<int>> adj(n);
    unordered_map<string,vector<int>> patterns;
    for(int i=0;i<n;i++){
        string s=dict[i];
        for(int j=0;j<s.length();j++){
            char original=s[j];
            s[j]='*';
            patterns[s].push_back(i);
            s[j]=original;
        }
    }
    for(auto e:patterns){
        vector<int> ids=e.second;
        for(int i=0;i<ids.size();i++){
            for(int j=i+1;j<ids.size();j++){
                adj[ids[i]].push_back(ids[j]);
                adj[ids[j]].push_back(ids[i]);
            }
        }
    }
    string start,end;
    while(cin>>start>>end){
        if(start==end)cout<<start<<"\n\n";
        else if(start.length()!=end.length())cout<<"No solution.\n\n";
        else{
            int sID=word2id[start];
            int eID=word2id[end];
            queue<int> q;
            vector<int> parent(n,-1);
            vector<int> visited(n,0);
            q.push(sID);
            visited[sID]=1;
            bool found=false;
            while(!q.empty()){
                int curr=q.front();
                q.pop();
                if(curr==eID){
                    found=true;
                    break;
                }
                for(int nID:adj[curr]){
                    if(!visited[nID]){
                        visited[nID]=1;
                        parent[nID]=curr;
                        q.push(nID);
                    }
                }
            }
            if(found){
                vector<string> path;
                for(int i=eID;i!=-1;i=parent[i])path.push_back(dict[i]);
                reverse(path.begin(),path.end());
                for(string s:path)cout<<s<<"\n";
            }else cout<<"No solution.\n";
            cout<<"\n";
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}
