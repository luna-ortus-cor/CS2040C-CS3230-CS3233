#include<bits/stdc++.h>
using namespace std;
//base 8 is 2^3
//base 16 is 2^4
//so every 4 digits in base 8 is 1,8,64,512
//every 3 digits in base 16 is 1,16,256
//these can represent equivalent, similar to
//bin to hex is 4 bin->1 hex cos bin is 1,2,4,8, hex is 1
//so just handle parsing, pad to multiple of 4 length
//convert each group of 4 to hex
//pad to length 3 and concatenate
//handle side cases of input=0

string oct2hex(string o){
    unordered_map<int,string> um({{10,"A"},
        {11,"B"},{12,"C"},{13,"D"},{14,"E"},{15,"F"}
    });
    int dec=(o[0]-'0')*512+(o[1]-'0')*64+(o[2]-'0')*8+(o[3]-'0');
    string hex="";
    while(dec){
        int temp=dec%16;
        if(temp<10)hex=to_string(temp)+hex;
        else hex=um[temp]+hex;
        dec/=16;
    }
    if(hex.size()==1)hex="00"+hex;
    else if(hex.size()==2)hex="0"+hex;
    else if(hex.size()==0)hex="000";
    return hex;
}

int main(){
    string in;cin>>in;
    if(in=="0"){cout<<0<<"\n";return 0;}
    int s=in.size();
    for(int i=0;i<4-(s%4);i++){
        in="0"+in;
    }
    string ans="";
    for(int i=0;i<in.size()/4;i++){
        ans+=oct2hex(in.substr(4*i,4));
        //cout<<ans<<endl;
    }
    while(ans[0]=='0'){ans=ans.substr(1,-1);}
    cout<<ans<<"\n";
    return 0;
}
