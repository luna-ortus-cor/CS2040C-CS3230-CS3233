#include <bits/stdc++.h>

using namespace std;

int main(){
    int N,M;
    cin>>N>>M;
    vector<int> heights;
    int temp;
    for(int i=0;i<N;i++){
        cin>>temp;
        heights.push_back(temp);
    }
    sort(heights.begin(),heights.end(),greater<int>());
    int h=heights[0];
    int curr=0;
    int diff=0;
    int k=-1;
    for(int i=1;i<N;i++){
        diff=heights[i-1]-heights[i];
        if(curr+diff*i<M){
            h=heights[i];
            curr+=diff*i;
        }else{
            k=i;
            break;
        }
        if(i==N-1){
            diff=heights[0];
            k=N;
        }
    }
    for(int j=0;j<diff;j++){
        curr+=k;
        h-=1;
        if(curr>=M){
            cout<<h<<endl;
            break;
        }
    }
    return 0;
}
