#include <bits/stdc++.h>

using namespace std;

int valid(vector<int> p1, vector<int> p2){
    bool ended=false;
    int score = p1[0]+p2[0];
    if(p1[0]>11||p2[0]>11||(p1[0]==11&&p2[0]==11)){
        return 0+1;
    }else if((p1[0]==11||p2[0]==11) && !ended){
        ended=true;
        if(score%4==1||score%4==2){
            swap(p1[0],p2[0]);
        }
    }else{
        if(score%4==1||score%4==2){
            swap(p1[0],p2[0]);
        }
    }
    
    for(int i=1;i<p1.size();i++){
        score = p1[i]+p2[i];
        if(p1[i]>11||p2[i]>11||(p1[i]==11&&p2[i]==11)){
            return i+1;
        }else if((p1[i]==11||p2[i]==11) && !ended){
            ended=true;
            if(score%4==1||score%4==2){
                swap(p1[i],p2[i]);
            }
            if(p1[i]<p1[i-1]||p2[i]<p2[i-1]){
                return i+1;
            }
        }else if((p1[i]==11||p2[i]==11) && ended){
            if(score%4==1||score%4==2){
                swap(p1[i],p2[i]);
            }
            if(p1[i]!=p1[i-1]||p2[i]!=p2[i-1]){
                return i+1;
            }
        }else{
            if(score%4==1||score%4==2){
                swap(p1[i],p2[i]);
            }
            if(p1[i]<p1[i-1]||p2[i]<p2[i-1]){
                return i+1;
            }
        }
    }
    return p1.size()+1;
}

int main(){
    int n;
    cin>>n;
    vector<int> p1,p2;
    for(int i=0;i<n;i++){
        int a,b;
        char c;
        scanf("%2d",&a);
        scanf("%*c",&c);
        scanf("%2d",&b);
        p1.push_back(a);
        p2.push_back(b);
    }
    int v = valid(p1,p2);
    if(v==n+1){
        cout<<"ok"<<endl;
    }else{
        cout<<"error"<<" "<<v<<endl;
    }
    return 0; 
}


//this valid is incorrect, based on assumption that there can be scores "in between" change of serves
//i.e. 1-0 and 0-1 are both valid to represent A scoring, when in fact only 0-1 is valid if A scores 
int valid2(vector<int> p1, vector<int> p2, int idx, int total, bool inverted){
    if(idx==p1.size()){
        return idx+1;
    }else if((p1[idx]==11&&p2[idx]>0)||(p1[idx]>0&&p2[idx]==11)){
        return idx+1;
    }else if((p1[idx]+p2[idx])%2==1 && p1[idx]+p2[idx]==total && inverted){
        swap(p1[idx],p2[idx]);
        if(p1[idx]>=p1[idx-1] && p2[idx] >= p2[idx-1]){
            return valid2(p1,p2,idx+1,p1[idx]+p2[idx],inverted);
        } else {
            return idx+1;
        }
    }else if((p1[idx]+p2[idx])%2==1 && p1[idx]+p2[idx]==total && !inverted){
        if(p1[idx]>=p1[idx-1] && p2[idx] >= p2[idx-1]){
            return valid2(p1,p2,idx+1,p1[idx]+p2[idx],inverted);
        } else {
            return idx+1;
        }
    }else if((p1[idx]+p2[idx])%2==1 && p1[idx]+p2[idx]!=total){
        int a=-1,b=-1;
        if(p1[idx]>=p1[idx-1]&&p2[idx]>=p2[idx-1]){
            a=valid2(p1,p2,idx+1,p1[idx]+p2[idx],false);
        }
        swap(p1[idx],p2[idx]);
        if(p1[idx]>=p1[idx-1]&&p2[idx]>=p2[idx-1]){
            b=valid2(p1,p2,idx+1,p1[idx]+p2[idx],true);
        }
        if(a!=-1||b!=-1){
            return max(a,b);
        }else{
            return idx+1;
        }
    }else{
        if(p1[idx]>=p1[idx-1]&&p2[idx]>=p2[idx-1]){
            return valid2(p1,p2,idx+1,p1[idx]+p2[idx],false);
        }else{
            return idx+1;
        }
    }
}
