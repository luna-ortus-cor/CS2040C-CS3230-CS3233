#include <bits/stdc++.h>
using namespace std;

struct Interval{
    double left,right;
    bool operator<(const Interval& other)const{return left<other.left;}
};

void solve(){
    int n;
    double l,w;
    while(cin>>n>>l>>w){
        vector<Interval> intervals;
        double half_w=w/2.0;
        for(int i=0;i<n;i++){
            double x,r;
            cin>>x>>r;
            if(r>half_w){
                double dx=sqrt(r*r-half_w*half_w);
                intervals.push_back({x-dx,x+dx});
            }
        }
        sort(intervals.begin(),intervals.end());
        int ans=0,i=0;
        double covered=0;
        bool possible=true;
        while(covered<l){
            double reached=-1.0;
            bool found=false;
            while(i<intervals.size()&&intervals[i].left<=covered){
                if(intervals[i].right>reached){
                    reached=intervals[i].right;
                    found=true;
                }
                i++;
            }
            if(!found||reached<=covered){
                possible=false;
                break;
            }
            covered=reached;
            ans++;
        }
        if(possible)cout<<ans<<"\n";
        else cout<<"-1\n";
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}
