#include <bits/stdc++.h>
using namespace std;

//just simple simulation, handle the various input formats correctly
//parse to get the numbers, and use mod 10 to extract the digits
//increment count of each digit in v, and finally sum at the end

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    string s;
    int num;
    cin.ignore();
    while(n--){
        getline(cin,s);
        cout<<s<<"\n";
        cin>>num;
        cin>>s;
        cout<<num<<" "<<s<<"\n";
        vector<int> v(10,0);
        cin.ignore();
        while(num){
            getline(cin,s);
            if(s.size()>5){
                int start,end,diff;
                char c;
                stringstream ss(s);
                ss>>c;
                ss>>start;
                ss>>end;
                ss>>diff;
                for(int i=start;i<=end;i+=diff){
                    int x=i;
                    while(x){
                        v[x%10]++;
                        x/=10;
                    }
                    num--;
                }
            }else{
                stringstream ss(s);
                int x;
                ss>>x;
                while(x){
                    v[x%10]++;
                    x/=10;
                }
                num--;
            }
        }
        for(int i=0;i<10;i++){
            cout<<"Make "<<v[i]<<" digit "<<i<<"\n";
        }
        int sum=accumulate(v.begin(),v.end(),0);
        cout<<"In total "<<sum<<" digit"<<(sum==1?"\n":"s\n");
    }
    return 0;
}
