#include <bits/stdc++.h>

using namespace std;

int main(){ //A is 1, B is 2, C is 4
    queue<int> q0,q1,q2,q3,q4,q5,q6;
    int numq=0;
    string s;
    cin>>s;
    for(char c:s){
        if(c=='A'){
            if(q6.empty()){
                if(!q4.empty()){
                    int q=q4.front();
                    q4.pop();
                    q5.push(q);
                }else if(!q2.empty()){
                    int q=q2.front();
                    q2.pop();
                    q3.push(q);
                }else if(!q0.empty()){
                    int q=q0.front();
                    q0.pop();
                    q1.push(q);
                }else{
                    numq++;
                    q1.push(numq);
                }
            }else{
                int q=q6.front();
                q6.pop();
                q0.push(q);
            }
        }else if(c=='B'){
            if(q5.empty()){
                if(!q4.empty()){
                    int q=q4.front();
                    q4.pop();
                    q6.push(q);
                }else if(!q1.empty()){
                    int q=q1.front();
                    q1.pop();
                    q3.push(q);
                }else if(!q0.empty()){
                    int q=q0.front();
                    q0.pop();
                    q2.push(q);
                }else{
                    numq++;
                    q2.push(numq);
                }
            }else{
                int q=q5.front();
                q5.pop();
                q0.push(q);
            }
        }else{
            if(q3.empty()){
                if(!q2.empty()){
                    int q=q2.front();
                    q2.pop();
                    q6.push(q);
                }else if(!q1.empty()){
                    int q=q1.front();
                    q1.pop();
                    q5.push(q);
                }else if(!q0.empty()){
                    int q=q0.front();
                    q0.pop();
                    q4.push(q);
                }else{
                    numq++;
                    q4.push(numq);
                }
            }else{
                int q=q3.front();
                q3.pop();
                q0.push(q);
            }
        }
    }
    cout<<numq<<endl;
    return 0;
}
