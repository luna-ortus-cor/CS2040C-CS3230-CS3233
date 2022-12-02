#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int reverse(ll num){
    string s = to_string(num);
    string new_s = "";
    for(int i=s.length()-1;i>=0;i--){
        if(s.at(i)!='3'&&s.at(i)!='4'&&s.at(i)!='7'){
            if(s.at(i)=='6'){
                new_s+='9';
            }else if(s.at(i)=='9'){
                new_s+='6';
            }else{
                new_s+=s.at(i);
            }
        }else{
            return num;
        }
    }
    return stoll(new_s);
}

int main(){
    ll n,s,temp;
    cin>>n>>s;
    vector<ll> nums,revnums;
    unordered_multimap<ll,int> all;
    for(int i=0;i<n;i++){
        cin>>temp;
        nums.push_back(temp);
        all.emplace(make_pair(temp,i));
        ll rev = reverse(temp);
        if(rev!=temp){
            revnums.push_back(rev);
            all.emplace(make_pair(rev,i));
        }else{
            revnums.push_back(temp);
        }
    }
    vector<ll> complement(nums.size());
    vector<ll> revcomplement(revnums.size());
    for(int i=0;i<complement.size();i++){
        complement[i]=s-nums[i];
        revcomplement[i]=s-revnums[i];
    }
    for(int i=0;i<complement.size();i++){
        if(all.find(complement[i])!=all.end() && all.find(complement[i])->second!=i){
            cout<<"YES"<<endl;
            return 0;
        }
        if(all.find(revcomplement[i])!=all.end() && all.find(revcomplement[i])->second!=i){
            cout<<"YES"<<endl;
            return 0;
        }
    }
    cout<<"NO"<<endl;
    return 0;
}
