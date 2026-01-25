#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int U,d,x;
    char c;
    cin>>d>>U;
    priority_queue<int,vector<int>,greater<int>> minheap;
    int curr=1;
    queue<pair<int,int>> q;
    for(int j=1;j<=U;j++){
        cin>>c;
        if(!q.empty()){
            if(q.front().second==j){
                minheap.push(q.front().first);
                q.pop();
            }
        }
        if(c=='a'){
            if(minheap.empty()){
                cout<<curr<<"\n";
                curr++;
            }else{
                auto i=minheap.top();
                minheap.pop();
                cout<<i<<"\n";
            }
        }else{
            cin>>x;
            q.push(make_pair(x,j+d));
        }
    }
    return 0;
}
