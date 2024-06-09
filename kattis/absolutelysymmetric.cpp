#include<bits/stdc++.h>
using namespace std;
//let an absoutely symmetric element be such that |A(i,j)|=|A(j,i)|
//clearly every diagonal element is absolutely symmetric
//if A(i,j)==A(j,i) or A(i,j)==-A(j,i) likewise absolutely symmetric
//if none of the above are true, then check if the difference between A(i,j) and A(j,i) is even
//any odd difference can never be expressed as a sum of absolutely symmetric elements
//since any absolutely symmetric element has either 0 or even diff (e-(-e)=2e)
//if even diff then we can have c=(a+b)/2, d=a-c, e=b-c as absolutely symmetric elements (and c is int)
//since d=-e (d=a-c=a-(a+b)/2=a/2-b/2=-(b/2-a/2)=-(b-(a+b)/2)=-(b-c)=-e)
//so if there is an odd difference then cannot be decomposed, so print -1
//then notice we only need a max of 2 such decomposition matrices since A(i1,j1) does not affect
//absolutely symmetricness of A(i2,j2) (assuming not same/diagonal/symmetric elements)
//so use one matrix B to store all already symmetric elements + center element of even diff
//and one matric C to store the diff between element and center element for even diff

int main(){
    int n,e;cin>>n;
    vector<vector<int>> A(n,vector<int>(n,0));
    vector<vector<int>> B(n,vector<int>(n,0));
    vector<vector<int>> C(n,vector<int>(n,0));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>e;A[i][j]=e;
        }
    }
    int exists=1,num=1;
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            if(i==j)B[i][j]=A[i][j];
            else if(A[i][j]==A[j][i]||A[i][j]==-A[j][i]){
                B[i][j]=A[i][j];B[j][i]=A[j][i];
            }else if((A[i][j]-A[j][i])%2==0){
                int c = (A[i][j]+A[j][i])/2;
                B[i][j]=B[j][i]=c;
                C[i][j]=A[i][j]-c;C[j][i]=A[j][i]-c;
                num=2;
            }else{
                exists=0;break;
            }
        }
        if(!exists)break;
    }
    if(!exists)cout<<-1<<"\n";
    else{
        cout<<num<<"\n";
        for(auto v:B){
            for(auto e:v){
                cout<<e<<" ";
            }
            cout<<"\n";
        }
        if(num-1){
            for(auto v:C){
                for(auto e:v){
                    cout<<e<<" ";
                }
                cout<<"\n";
            }
        }
    }
    return 0;
}
