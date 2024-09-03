#include<bits/stdc++.h>
using namespace std;
const int INF=1e9;

//construct an array d such that
//d[i] is the length of the LIS that ends in the element at index i
//if d[i]=1, then the LIS is just the element v[i]
//else the LIS ends at some v[i] and before it is some v[j] with j<i and v[j]<v[i]
//so iterate over all j<i with v[j]<v[i], and take LIS formed by appending v[i]
//to the LIS ending in v[j] with length d[j] i.e. d[i]=d[j]+1
//this is n^2
//to restore subsequence generate auxilliary array p such that
//p[i] is the index j of the 2nd last element in the LIS
//ending in i i.e. the index j at which highest value of d[i] obtained
//this points to ancestors in the LIS
//then start at index i with maximal d[i], 
//follow ancestors to deduce LIS elements until reach element with d[i]=1 (ancestors=-1)
//to ensure lexicographically earliest requirement
//i.e. a1,a2,...,am < b1,b2,...,bm if exists ai<bi for some i and 
//aj=bj for all j<i
//update p[i]=j only when 
//a. no ancestors i.e. p[i]=-1 or
//b. another LIS of same length exists, but this current v[j] is smaller than v[p[i]] or
//c. the LIS is longer than previous LIS i.e. d[j]>d[p[i]]

int main(){
    int n,a;
    while(cin>>n){
        if(n==0)break;
        vector<int> v;
        vector<int> d(n,1);
        vector<int> p(n,-1);
        for(int j=0;j<n;j++){
            cin>>a;
            v.push_back(a);
        }
        int ans=1,pos=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<i;j++){
                if(v[j]<v[i]){ //d[i]=max(d[i],d[j]+1)
                //cout<<d[j]<<" "<<d[p[i]]<<endl;
                    //p[i]=j;
                    
                    if(p[i]==-1||(d[j]==d[p[i]]&&v[j]<v[p[i]])||d[j]>d[p[i]]){
                        p[i]=j;
                    }
                    
                    d[i]=max(d[i],d[j]+1);
                }
                /*
                if (v[j]<v[i] && ((d[i]==d[j]&&p[i]!=-1&&v[j]<v[p[i]])||(d[i]<=d[j]))) {
                    d[i]=d[j]+1;
                    p[i]=j;
                }
                */
            }
            if(d[i]>ans){
                ans=d[i];
                pos=i;
            }else if(d[i]==ans && v[i]<v[pos]){ //ensure lexicographically earliest
                ans=d[i];
                pos=i;
            }
        }
        /*
        int ans=d[0],pos=0;
        for(int i=1;i<n;i++){
            if(d[i]>ans){
                ans=d[i];
                pos=i;
            }
        }
        */
        cout<<ans<<" ";
        vector<int> s(ans);
        for(int i=ans-1;i>=0;i--){
            s[i]=v[pos];
            pos=p[pos];
        }
        //we can also do this with 
        /*
        vector<int> s;
        while(pos!=-1){
            s.push_back(v[pos]);
            pos=p[pos];
        }
        reverse(s.begin(),s.end());
        */
        for(auto i:s){
            cout<<i<<" ";
        }
        cout<<"\n";
        /*
        for(auto i:v){
            cout<<i<<" ";
        }
        cout<<"\n";
        for(auto i:d){
            cout<<i<<" ";
        }
        cout<<"\n";
        for(auto i:p){
            cout<<i<<" ";
        }
        cout<<"\n";
        */
    }
}



//construct an array d such that
//d[l] holds the smallest element that an
//increasing subseq of length l ends in
//we can update the value of d[l] for every a[i]
//by checking if d[l-1]<a[i] and a[i]<d[l]
//this is n^2
//note that d is a sorted array 
//since we can remove the last number from 
//an increasing subseq of length l, d[l]
//and get another increasing subseq of length 
//l-1 with smaller last number d[l-1]
//and there is only one location for such an update
//since there is only one location where d[l-1]<a[i]<d[l]
//therefore we can use binary search to find this location
//this makes it nlogn
//but i think this cant work if need to return the lexicographically earliest LIS
/*
int main(){
    int n,a;
    while(cin>>n){
        if(n==0)break;
        vector<int> v;
        vector<int> d(n+1,INF);d[0]=-INF;
        vector<int> p(n,-1);
        for(int j=0;j<n;j++){
            cin>>a;
            v.push_back(a);
        }
        for(int i=0;i<n;i++){
            int l=upper_bound(d.begin(),d.end(),v[i])-d.begin();
            if(d[l-1]<v[i]&&v[i]<d[l]){
                d[l]=v[i];
            }
        }
        int ans=0;
            for (int l = 0; l <= n; l++) {
                if (d[l] < INF)
                    ans = l;
        }
        cout<<ans<<" ";
        for(auto c:d){
            if(c!=-INF&&c!=INF)
                cout<<c<<" ";
        }
        cout<<"\n";
    }
    return 0;
}
*/
