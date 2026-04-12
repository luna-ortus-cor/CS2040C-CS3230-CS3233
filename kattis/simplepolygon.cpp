#include <bits/stdc++.h>
using namespace std;

struct Point{
    int x,y,id;
};

int cp(Point a,Point b,Point c){
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}

int dist(Point a,Point b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

void solve(){
    int n;
    cin>>n;
    vector<Point> p(n);
    int pivotidx=0;
    for(int i=0;i<n;i++){
        cin>>p[i].x>>p[i].y;
        p[i].id=i;
        if(p[i].y<p[pivotidx].y||(p[i].y==p[pivotidx].y&&p[i].x<p[pivotidx].x)){
            pivotidx=i;
        }
    }
    swap(p[0],p[pivotidx]);
    sort(p.begin()+1,p.end(),[&](Point a,Point b){
        int c=cp(p[0],a,b);
        if(c==0)return dist(p[0],a)<dist(p[0],b);
        return c>0;
    });
    int last=n-1;
    while(last>1&&cp(p[0],p[last],p[n-1])==0)last--;
    reverse(p.begin()+last+1,p.end());
    for(int i=0;i<n;i++)cout<<p[i].id<<" ";
    cout<<"\n";
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
