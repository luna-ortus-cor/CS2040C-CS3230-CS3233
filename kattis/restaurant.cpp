#include <bits/stdc++.h>
using namespace std;

//simulate a queue with 2 stacks
//drop all plates in stack 2
//when taking, take from stack 1
//if no plates to take from stack 1, flip stack 2 to stack 1

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    while(n){
        string s;
        int d;
        int s1=0,s2=0;
        while(n--){
            cin>>s>>d;
            if(s=="DROP"){
                cout<<"DROP 2 "<<d<<"\n";
                s2+=d;
            }else{
                if(s1>=d){
                    cout<<"TAKE 1 "<<d<<"\n";
                    s1-=d;
                }else{
                    int rem=d-s1;
                    if(s1!=0){
                        cout<<"TAKE 1 "<<s1<<"\n";
                        s1-=s1;
                    }
                    cout<<"MOVE 2->1 "<<s2<<"\n";
                    s1+=s2;
                    s2-=s2;
                    cout<<"TAKE 1 "<<rem<<"\n";
                    s1-=rem;
                }
            }
        }
        cout<<"\n";
        cin>>n;
    }
    return 0;
}
