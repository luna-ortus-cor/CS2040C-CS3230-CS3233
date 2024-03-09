#include <iostream>
#include <vector>
#include <cctype>
 
using namespace std;
 
int main()
{
    int t;
    cin>>t;
    for(int i=0;i<t;i++){
        vector<char> v;
        for(int j=0;j<8;j++){
            for(int k=0;k<8;k++){
                char c;
                cin>>c;
                if(isalpha(c)){
                    v.push_back(c);
                }
            }
        }
        string s(v.begin(),v.end());
        cout<<s<<endl;
    }
    return 0;
}
