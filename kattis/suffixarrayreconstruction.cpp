#include <bits/stdc++.h>
using namespace std;

void solve(){
    int l,s;
    cin>>l>>s;
    vector<char> v(l,'-');
    bool possible=true;
    for(int i=0;i<s;i++){
        int p;
        string str;
        cin>>p>>str;
        if(!possible)continue;
        int star_pos=-1;
        for(int j=0;j<str.size();j++)if(str[j]=='*')star_pos=j;
        if(star_pos==-1){
            for(int j=0;j<str.size();j++){
                char c=str[j];
                int idx=j+p-1;
                if(v[idx]=='-')v[idx]=c;
                else if(v[idx]!=c)possible=false;
            }
        }else{
            for(int j=0;j<star_pos;j++){
                char c=str[j];
                int idx=j+p-1;
                if(v[idx]=='-')v[idx]=c;
                else if(v[idx]!=c)possible=false;
            }
            int str_idx=str.size()-1,v_idx=l-1;
            while(str_idx>star_pos){
                char c=str[str_idx];
                if(v[v_idx]=='-')v[v_idx]=c;
                else if(v[v_idx]!=c)possible=false;
                str_idx--;
                v_idx--;
            }
        }
    }
    string ans;
    for(auto c:v){
        if(c=='-'){
            possible=false;
            break;
        }
        ans+=c;
    }
    if(possible)cout<<ans<<"\n";
    else cout<<"IMPOSSIBLE\n";
    return;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--)solve();
    return 0;
}
