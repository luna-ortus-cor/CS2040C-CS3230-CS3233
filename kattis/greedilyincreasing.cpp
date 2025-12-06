#include <bits/stdc++.h>
using namespace std;

//starting from first element (prev), add prev to v
//iterate through integers and pick the first element (curr) larger than prev
//add curr to v, set prev to curr
//output v as specified

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    int prev,curr;
    vector<int> v;
    cin>>prev;
    v.push_back(prev);
    while(cin>>curr){
        if(curr>prev){
            v.push_back(curr);
            prev=curr;
        }
    }
    cout<<v.size()<<endl;
    for(int i:v){
        cout<<i<<" ";
    }
    cout<<endl;
    return 0;
}
