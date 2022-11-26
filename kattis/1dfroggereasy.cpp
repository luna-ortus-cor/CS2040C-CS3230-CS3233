#include <bits/stdc++.h>

using namespace std;

int main(){
    int n,s,m;
    cin>>n>>s>>m;
    int square [n];
    int visited [n];
    int temp;
    for(int i =0;i<n;i++){
        cin>>temp;
        square[i]=temp;
        visited[i]=0;
    }
    int pos=square[s-1];
    int counter=0;
    while(true){
        //cout<<pos<<endl;
        if(pos==m){
            cout<<"magic\n"<<counter<<endl;
            break;
        }
        if(visited[s-1]==1){
            cout<<"cycle\n"<<counter<<endl;
            break;
        }else{
            visited[s-1]=1;
        }
        if(pos>0 && s+pos<=n){
            s+=pos;
            pos=square[s-1];
            counter++;
            continue;
        }else if (pos>0 && s+pos>n){
            cout<<"right\n"<<counter+1<<endl;
            break;
        }
        if(pos<0 && s+pos>0){
            s+=pos;
            pos=square[s-1];
            counter++;
            continue;
        }else{
            cout<<"left\n"<<counter+1<<endl;
            break;
        }
    }
    return 0;
}
