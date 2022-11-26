#include <bits/stdc++.h>

using namespace std;

int perfect(long n,int f){
    int m=0;
    while(abs(n)%f==0){
        m+=1;
        n/=f;
        if(n==1){
            return m;
        }
        if(n==-1 || f==-1){
            break;
        }
    }
    return 0;
}

int power(long n){
    int m=1;
    if(n>0){
        for(int f=2;f<(int) sqrt(n)+1;f++){
            m=max(m,perfect(n,f));
            if(m>1){
                return m;
            }
        }
    }else{
        for(int f=-2;f>-((int) sqrt(-n))-1;f--){
            m=max(m,perfect(n,f));
            if(m>1){
                return m;
            }
        }
    }
    return m;
}

int main(){
    long n=-1;
    while(true){
        cin>>n;
        if(n!=0){
            cout<<power(n)<<endl;
            continue;
        }
        break;
    }
}
