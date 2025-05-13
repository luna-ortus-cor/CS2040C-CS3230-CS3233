#include <bits/stdc++.h>
using namespace std;

//first create an unordered map mapping first letters to a vector of words
//that start with that first letter
//then look at the last letter (last) of the previous word (prev)
//if no words starting with that letter exist, output "?"
//else store the first word that begins with that letter (first)
//then for each word beginning with that letter (s)
//check if this words's last letter (e) has any words beginning with it
//if no, output the word (s) with "!"
//if yes, check if the number of words is 1 and if the word's first letter (e)
//is the same as the other word's first letter (s) (since we would have used up s already)
//if yes, output the word (s) with "!"
//else in all other cases output just the first word (first)

int main(){
    string prev,next;
    int n;
    cin>>prev;
    cin>>n;
    unordered_map<char,vector<string>> startwith;
    while(n--){
        cin>>next;
        startwith[next[0]].push_back(next);
    }
    char last=*(prev.end()-1);
    if(!startwith.contains(last)){
        cout<<"?"<<endl;
    }else{
        string first=startwith[last][0];
        for(string s:startwith[last]){
            char e=*(s.end()-1);
            if(!startwith.contains(e)){
                cout<<s<<"!"<<endl;
                return 0;
            }else{
                if(startwith[e].size()==1 && e==s[0]){
                   cout<<s<<"!"<<endl;
                   return 0;
                }
            }
        }
        cout<<first<<endl;
    }
    return 0;
}
