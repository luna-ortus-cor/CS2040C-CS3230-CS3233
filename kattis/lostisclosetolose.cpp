#include <bits/stdc++.h>
using namespace std;

bool isClose(const string& a, const string& b){
    int n=a.size(),m=b.size();
    if(abs(n-m)>1)return false;
    if(n==m){
        int diffs=0;
        vector<int> p;
        for(int i=0;i<n;i++){
            if(a[i]!=b[i]){
                diffs++;
                p.push_back(i);
            }
        }
        if(diffs==1)return true;
        if(diffs==2&&p[1]==p[0]+1&&a[p[0]]==b[p[1]]&&a[p[1]]==b[p[0]])return true;
        return false;
    }
    const string& s1=(n>m)?a:b;
    const string& s2=(n>m)?b:a;
    int i=0,j=0,diff=0;
    while(i<s1.size()&&j<s2.size()){
        if(s1[i]==s2[j]){
            i++;
            j++;
        }else{
            i++;
            diff++;
            if(diff>1)return false;
        }
    }
    return true;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    set<string> dictSet;
    string current="";
    char c;
    while(cin.get(c)){
        if(isalpha(c)){
            current+=tolower(c);
        }else if(c==' '||c=='\n'||c=='\r'){
            if(!current.empty())dictSet.insert(current);
            current="";
        }
    }
    if(!current.empty())dictSet.insert(current);
    vector<string> dict(dictSet.begin(),dictSet.end());
    sort(dict.begin(),dict.end());
    bool printAny=false;
    for(int i=0;i<dict.size();i++){
        vector<string> matches;
        for(int j=0;j<dict.size();j++){
            if(i==j)continue;
            if(isClose(dict[i],dict[j])){
                matches.push_back(dict[j]);
            }
        }
        sort(matches.begin(),matches.end());
        if(!matches.empty()){
            printAny=true;
            cout<<dict[i]<<":";
            for(auto m:matches)cout<<" "<<m;
            cout<<"\n";
        }
    }
    if(!printAny)cout<<"***\n";
    return 0;
}
