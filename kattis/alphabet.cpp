#include <bits/stdc++.h>
using namespace std;

//the idea here is the longest increasing subsequence, since we can 
//insert new characters anywhere in the string and delete redundant characters
//since the constraints are small, |s|<=50, we can use an inefficient
//O(n^2) algorithm for the LIS problem
//define the array d such that d[i] stores the longest increasing subsequence
//up to index i in the string s
//clearly then we want max d[i] for the longest increasing subsequence
//then note that for j<i, d[i]=max(1,max(d[i],d[j]+1)) if s[j]<s[i]
//(with d[i]=1) a base case since any individual character is a LIS by itself
//i.e. if s[j]<s[i] then the string ...s[j]s[i] is an increasing subsequence
//so the LIS at i is then either the max LIS at i already or the LIS at j + 1
//finally to get the number of letters needed to be added, just take 26-LIS

int main(){
    string s;
    cin>>s;
    int n=s.size();
    vector<int> d(n,1);
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            if(s[j]<s[i]){
                d[i]=max(d[i],d[j]+1);
            }
        }
    }
    int ans=d[0];
    for(int i=0;i<n;i++){
        ans=max(ans,d[i]);
    }
    cout<<26-ans<<endl;
    return 0;
}
