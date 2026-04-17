#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    vector<int> xs,ys;
    ld sumx=0,sumy=0;
    for(int i=0;i<n;i++){
        int x,y;
        cin>>x>>y;
        xs.push_back(x);
        ys.push_back(y);
        sumx+=x;
        sumy+=y;
    }
    ld cx=sumx/n,cy=sumy/n;
    for(int i=0;i<10000;i++){
        ld numx=0,numy=0,d=0;
        bool coincide=false;
        for(int j=0;j<n;j++){
            ld dx=cx-xs[j];
            ld dy=cy-ys[j];
            ld dist=hypot(dx,dy);
            if(dist<1e-12){
                cx=xs[j];
                cy=ys[j];
                coincide=true;
                break;
            }
            numx+=xs[j]/dist;
            numy+=ys[j]/dist;
            d+=1.0/dist;
        }
        if(coincide)break;
        ld nx=numx/d;
        ld ny=numy/d;
        if(hypot(nx-cx,ny-cy)<1e-12)break;
        cx=nx;
        cy=ny;
    }
    ld ans=0.0;
    for(int i=0;i<n;i++){
        ans+=hypot(xs[i]-cx,ys[i]-cy);
    }
    cout<<fixed<<setprecision(10)<<ans;
    return 0;
}
