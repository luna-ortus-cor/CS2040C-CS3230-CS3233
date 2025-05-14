#include <bits/stdc++.h>
using namespace std;

//first note the property (invariant) of any pivot, for any array a
//partitioned by a pivot p such that a=[a_i...p...a_j] we must have a_i<p<a_j
//since it is given all elements are unique
//so we iterate through all elements, at each index keeping track of the max
//in [0...a_i] and the min in [a_j...n-1]
//then for any index k where the max and min coincide, the element at k is a pivot
//since v[k] is a max in v[0...k] and a min in v[k...n-1] i.e. v[0...k-1]<v[k]<v[k+1...n-1]
//all that remains is to print according to the context of the problem

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    vector<int> v(n);
    for(int i=0;i<n;i++){
        cin>>v[i];
    }
    vector<int> maxs(n);
    vector<int> mins(n);
    int currmax=0;
    int currmin=1000001;
    for(int i=0;i<n;i++){
        currmax=maxs[i]=max(currmax,v[i]);
        currmin=mins[n-1-i]=min(currmin,v[n-1-i]);
    }
    vector<int> ans;
    ans.push_back(0);
    for(int i=0;i<n;i++){
        if(maxs[i]==mins[i]){
            if(++ans[0]<=100)ans.push_back(v[i]);
        }
    }
    for(auto a:ans)cout<<a<<" ";
    return 0;
}
