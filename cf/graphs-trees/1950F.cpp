#include<bits/stdc++.h>
using namespace std;
//technically should also go under greedy 
//idea is just to greedy all the 2-nodes, then 1-nodes, then 0-nodes, to minimize height
//use queue to store nodes that require child nodes (i.e. 0-nodes should never be in queue)
//queue also stores height of node, keep track of max height whenever adding new node
//root the tree first then start filling in child nodes until no more nodes but queue not empty (incomplete tree)
//or queue empty (tree finished) but have leftover nodes (cannot fit)
//consider case by case for each popped node from queue (do not pop if unable to fill in all child nodes)
int height(int a, int b, int c){
    queue<pair<int,int>> q;
    int maxh=0;
    bool rooted=false;
    while(a){
        if(q.empty()&&!rooted){
            q.emplace(2,0);
            a--;
            rooted=true;
        }else if(q.empty()){
            break;
        }
        pair<int,int> p = q.front();
        maxh=max(maxh,p.second+1);
        if(a>=2){
            a-=2;
            q.emplace(2,p.second+1);
            q.emplace(2,p.second+1);
            q.pop();
        }else if(a==1){
            q.emplace(2,p.second+1);
            a=0;
            if(b>=1){
                q.emplace(1,p.second+1);
                b--;
                q.pop();
            }else if(c>=1){
                c--;
                q.pop();
            }else{
                return -1;
            }
        }
    }
    //cout<<"a ok ";
    while(b){
        if(q.empty()&&!rooted){
            q.emplace(1,0);
            b--;
            rooted=true;
        }else if(q.empty()){
            break;
        }
        pair<int,int> p = q.front();
        maxh=max(maxh,p.second+1);
        if(p.first==2){
            if(b>=2){
                b-=2;
                q.emplace(1,p.second+1);
                q.emplace(1,p.second+1);
                q.pop();
            }else if(b==1){
                b--;
                q.emplace(1,p.second+1);
                if(c>=1){
                    c--;
                    q.pop();
                }else{
                    return -1;
                }
            }else{
                return -1;
            }
        }else{
            if(b>=1){
                b--;
                q.emplace(1,p.second+1);
                q.pop();
            }else if(c>=1){
                c--;
                q.pop();
            }else{
                return -1;
            }
        }
    }
    //cout<<"b ok ";
    while(c){
        if(q.empty()&&!rooted){
            c--;
            rooted=true;
            break;
        }else if(q.empty()){
            break;
        }
        pair<int,int> p = q.front();
        maxh=max(maxh,p.second+1);
        if(p.first==2){
            if(c>=2){
                c-=2;
                q.pop();
            }else{
                return -1;
            }
        }else{
            if(c>=1){
                c-=1;
                q.pop();
            }else{
                return -1;
            }
        }
    }
    //cout<<"c ok ";
    if(a || b || c || !q.empty()){
        return -1;
    }else{
        return maxh;
    }
}

int main(){
    int t;cin>>t;
    int a,b,c;
    while(cin>>a>>b>>c){
        cout<<height(a,b,c)<<'\n';
    }
}
