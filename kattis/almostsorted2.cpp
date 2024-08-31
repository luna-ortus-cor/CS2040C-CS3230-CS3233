#include<bits/stdc++.h>
using namespace std;

//just need to compare sorted w non sorted array
//look at first point of difference between the 2 arrays
//if those elements can be reversed to form the sorted array
//then output yes, else no
//soln is nlogn

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,e;cin>>n;
    vector<int> v1,v2;
    while(cin>>e){v1.push_back(e);v2.push_back(e);}
    sort(v2.begin(),v2.end());
    vector<int>::iterator a=v1.begin();
    vector<int>::iterator b=v1.end()-1;
    vector<int>::iterator c=v2.begin();
    vector<int>::iterator d=v2.end()-1;
    while(a!=v1.end()&&*a==*c){a++;c++;}
    while(b>=v1.begin()&&*b==*d){b--;d--;}
    reverse(a,b+1);
    if(v1==v2)cout<<"Yes";
    else cout<<"No";
    return 0;
}
