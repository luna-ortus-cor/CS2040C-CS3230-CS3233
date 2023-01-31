#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// clearly when there are at least 2 zeros, we can assign one zero to each plot of land
// when there are no zeros, if the number of twos is even, we can assign equal number of two to each plot of land
// if number of twos is odd, then the difference will be pow(2,n2/2)
// when there is only 1 zero, if there are only ones and no twos, then the answer is 1
// if there are only twos and no ones, then the answer is 2
// if there are both ones and twos, then we must see if we are able to assign the one to a plot of land and everything else to the other, for answer of 1
// this is only possible if r,c>2, else consider: 0 1 2, where we are not able to assign 1 to a plot of land without splitting the other plot
// the exception is if 1 is at the edge, i.e. 1 0 2, 0 2 1, etc.
// else, answer is 2

int main(){
    int r,c;
    cin>>r>>c;
    int n0=0,n1=0,n2=0,temp;
    bool edge=false;
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            cin>>temp;
            if(temp==0){
                n0++;
            }else if(temp==2){
                n2++;
            }else{
                n1++;
                if((i==0 || i==r-1) && (j==0 || j==c-1)){
                    edge=true;
                }            
            }
        }
    }
    if(n0>=2){
        cout<<0<<endl;
    }else if(n0==1){
        if(n1>=1 && n2==0){
            cout<<1<<endl;
        }else if(n2>=1 && n1==0){
            cout<<2<<endl;
        }else{
            if(r>1 && c>1){
                cout<<1<<endl;
            }else{
                if(edge){
                    cout<<1<<endl;
                }else{
                    cout<<2<<endl;
                }
            }
        }
    }else{
        if(n2%2==1){
            cout<<(ll)pow(2,n2/2)<<endl;
        }else{
            cout<<0<<endl;
        }
    }
}
