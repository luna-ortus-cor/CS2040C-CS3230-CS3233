#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main(){
    int n,q;
    cin >> n >> q;
    vector<bool> primes(n+1, true);
    primes[0] = false;
    primes[1] = false;
    int m = sqrt(n);
    int count = 0;
    
    for(int i=2;i<m+1;i++){
        if(primes[i]){
            for(int j=i*i;j<n+1;j+=i){
                primes[j]=false;
            }
        }
    }
    
    for(int k=0;k<n+1;k++){
        if(primes[k]){
            count++;
        }
    }
    cout<<count<<endl;
    for(int i=0;i<q;i++){
        int x;
        cin >> x;
        cout<<primes[x]<<endl;
    }
    
}
