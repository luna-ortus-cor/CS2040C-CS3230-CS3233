#include<bits/stdc++.h>

using namespace std;

int main(){
    int N,T;
    cin>>N>>T;
    int temp;
    vector<int> duration;
    for(int i=0;i<N;i++){
        cin>>temp;
        if(temp<T){
            cout<<"NO"<<endl;
            return 0;
        }
        duration.push_back(temp);
    }
    sort(duration.begin(),duration.end());
    for(int i=duration.size()-1;i>=0;i--){
        if(i*T>=duration[i]){
            cout<<"NO"<<endl;
            return 0;
        }
    }
    cout<<"YES"<<endl;
    return 0;
}
