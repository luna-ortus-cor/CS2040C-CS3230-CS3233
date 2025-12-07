#include <bits/stdc++.h>
using namespace std;

//simulate the text editor using a deque and a char buffer (vector)
//for movement of cursor to home/end, add the text in the buffer to deque
//at appropriate place i.e. where cursor was prior to moving
//for deletion, delete from buffer unless buffer is empty
//then check if cursor at end, if so need to delete from end of deque
//also check for case where multiple cursor movement may add empty strings to deque
//and affect deletion from deque in the abovementioned case

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin>>t;
    string s;
    cin.ignore();    
    while(t--){
        int pos=1;
        deque<string> dq;
        vector<char> buffer;
        getline(cin,s);
        for(auto c:s){
            if(c=='<'){
                if(!buffer.empty())buffer.pop_back();
                else if(!dq.empty()){
                    if(!dq.empty() && pos){
                        string temp=dq.back();
                        dq.pop_back();
                        if(!temp.empty())temp.pop_back();
                        if(!temp.empty())dq.push_back(temp);
                    }
                }
            }else if(c=='['){
                if(!buffer.empty()){
                    string temp(buffer.begin(),buffer.end());
                    buffer.clear();
                    if(pos)dq.push_back(temp);
                    else dq.push_front(temp);
                }
                pos=0;
            }else if(c==']'){
                if(!buffer.empty()){
                    string temp(buffer.begin(),buffer.end());
                    buffer.clear();
                    if(!pos)dq.push_front(temp);
                    else dq.push_back(temp);
                }
                pos=1;
            }else{
                buffer.push_back(c);
            }
        }
        string temp(buffer.begin(),buffer.end());
        if(pos)dq.push_back(temp);
        else dq.push_front(temp);
        for(auto a:dq){
            cout<<a;
        }
        cout<<"\n";
    }
    return 0;
}
