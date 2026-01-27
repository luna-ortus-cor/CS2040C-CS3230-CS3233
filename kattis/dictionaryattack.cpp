#include<bits/stdc++.h>
using namespace std;
//the idea is meet in the middle

bool match(const string& pwd, const string& dwd){
    if(pwd.length()!=dwd.length())return false;
    for(int i=0;i<pwd.length();i++)if(isalpha(pwd[i])&&pwd[i]!=dwd[i])return false;
    return true;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin>>N;
    string pwd;
    vector<string> dict(N);
    for(int i=0;i<N;i++){
        cin>>dict[i];
    }
    vector<unordered_set<string>> change(4);
    for(const string& word:dict){
        vector<unordered_set<string>> vus(4);
        vus[0].insert(word);
        for(int i=1;i<=3;i++){
            for(const string& prev:vus[i-1]){
                string curr=prev;
                for(int j=0;j<curr.length()-1;j++){
                    swap(curr[j],curr[j+1]);
                    vus[i].insert(curr);
                    swap(curr[j],curr[j+1]);
                }
            }
        }
        for(int i=0;i<=3;i++){
            for(const string& s:vus[i])change[i].insert(s);
        }
    }
    while(cin>>pwd){
        int digits=0;
        for(char c:pwd)if(isdigit(c))digits++;
        if(digits>3){
            cout<<pwd<<"\n";
            continue;
        }
        bool bad=false;
        int swaps_rem=3-digits;
        for(int i=0;i<=swaps_rem;i++){
            for(const string& dwd:change[i]){
                if(match(pwd,dwd)){
                    bad=true;
                    break;
                }
            }
            if(bad)break;
        }
        if(!bad)cout<<pwd<<"\n";
    }
    return 0;
}
