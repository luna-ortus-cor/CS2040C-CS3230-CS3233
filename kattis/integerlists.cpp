#include <bits/stdc++.h>

using namespace std;

int main(){
    int tc;
    cin>>tc;
    for(int i=0;i<tc;i++){
        string s;
        cin>>s;
        int l;
        cin>>l;
        vector<int> nums;
        string temp;
        cin>>temp;
        istringstream ss(temp.substr(1,temp.length()-2));
        if(l!=0){
            string numstr;
            while(getline(ss,numstr,',')){
                nums.push_back(stoi(numstr));
            }
        }
        int rev=0;
        int start=0;
        int stop=nums.size()-1;
        bool broke=false;
        for(int j=0;j<s.length();j++){
            if(s.at(j)=='D'){
                if(stop<start){
                    broke=true;
                    break;
                }else{
                    (rev==1)?stop-=1:start+=1;
                }
            }else{
                rev = (rev==1)?0:1;
            }
        }
        if(stop<start && broke){
            cout<<"error"<<endl;
            continue;
        }else if(stop<start && !broke){
            cout<<"[]"<<endl;
            continue;
        }else if(l==0){
            cout<<"[]"<<endl;
        }else{
            cout<<"[";
            if(rev==0){
                for(int k=start;k<stop;k++){
                    cout<<nums[k]<<",";
                }
                cout<<nums[stop]<<"]"<<endl;
            }else{
                for(int k=stop;k>start;k--){
                    cout<<nums[k]<<",";
                }
                cout<<nums[start]<<"]"<<endl;
            }
        }
    }
}
