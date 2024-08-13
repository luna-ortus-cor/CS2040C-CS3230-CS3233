#include<bits/stdc++.h>
using namespace std;

int main(){
    //2 unordered map, one for str to int and one for int to str
    //then is just direct simulation while handling the unknown cases
    //use 1 mil as not possible value due to constraints on inputs
    string instr;
    unordered_map<string,int> str2int;
    unordered_map<int,string> int2str;
    while(cin>>instr){
        if(instr=="def"){
            string word; int num;
            cin>>word>>num;
            if(str2int.find(word)!=str2int.end()){
                int prevnum=str2int[word];
                str2int[word]=num;
                int2str.erase(prevnum);
                int2str.emplace(num,word);
            }else{
                str2int.emplace(word,num);
                int2str.emplace(num,word);
            }
        }else if(instr=="calc"){
            string var=""; string op="";
            string conc = "";
            int ans = 0;
            string out = "";
            cin>>var;
            out+=var;
            if(str2int.find(var)==str2int.end()){
                ans=1000000; //not possible value
            }else{
                ans=str2int[var];
            }
            while(1){
                cin>>op;
                if(op=="="){
                    out+=" = ";
                    break;
                }
                cin>>var;
                if(op=="+"){
                    out+=" + ";
                    if(str2int.find(var)==str2int.end()){
                        ans=1000000; //not possible value
                    }else{
                        if(ans!=1000000)ans+=str2int[var];
                    }
                }else{
                    out+=" - ";
                    if(str2int.find(var)==str2int.end()){
                        ans=1000000; //not possible value
                    }else{
                        if(ans!=1000000)ans-=str2int[var];
                    }
                }
                out+=var;
            }
            if(ans==1000000)out+="unknown";
            else{
                if(int2str.find(ans)==int2str.end())out+="unknown";
                else out+=int2str[ans];
            }
            cout<<out<<"\n";
        }else{
            str2int.clear();
            int2str.clear();
        }
    }
return 0;
}
