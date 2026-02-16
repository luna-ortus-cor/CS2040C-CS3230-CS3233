#include<bits/stdc++.h>
using namespace std;

struct Point{int x,y;};

double dist(Point a,Point b){
    int dx=a.x-b.x;
    int dy=a.y-b.y;
    return sqrt(dx*dx+dy*dy);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,m,p;
    cin>>n>>m>>p;
    vector<Point> judges(n),tars(m),feathers(p);
    for(int i=0;i<n;i++)cin>>judges[i].x>>judges[i].y;
    for(int i=0;i<m;i++)cin>>tars[i].x>>tars[i].y;
    for(int i=0;i<p;i++)cin>>feathers[i].x>>feathers[i].y;
    vector<tuple<double,int,int>> tar2judge;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            tar2judge.push_back({dist(judges[i],tars[j]),i,j});
        }
    }
    vector<tuple<double,int,int>> feather2judge;
    for(int i=0;i<n;i++){
        for(int j=0;j<p;j++){
            feather2judge.push_back({dist(judges[i],feathers[j]),i,j});
        }
    }
    sort(tar2judge.begin(),tar2judge.end());
    sort(feather2judge.begin(),feather2judge.end());
    vector<int> judgetar(n,0);
    vector<int> judgefeather(n,0);
    vector<int> tarused(m,0);
    vector<int> featherused(p,0);
    int judgetarcount=n,judgefeathercount=n;
    double ans=0.0;
    for(auto [d,j,t]:tar2judge){
        if(!judgetar[j]&&!tarused[t]){
            judgetar[j]--;
            tarused[t]--;
            judgetarcount--;
            ans+=d;
        }
        if(!judgetarcount)break;
    }
    for(auto [d,j,f]:feather2judge){
        if(!judgefeather[j]&&!featherused[f]){
            judgefeather[j]--;
            featherused[f]--;
            judgefeathercount--;
            ans+=d;
        }
        if(!judgefeathercount)break;
    }
    cout<<fixed<<setprecision(10)<<ans<<"\n";
    return 0;
}
