#include <bits/stdc++.h>

using namespace std;

# we first store number of pages in each chapter, as well as their pre-requisite (parent)
# we also store which chapters are cumulative chapters by noting which chapters are not pre-requisites for another chapter
# then, for each cumulative chapter, we calculate the total number of pages
# finally, for every pair of cumulative chapters, we find the number of pages by considering where the parents of the 2 chapters intersect, as any chapters
# that are parents for both cumulative chapters will be double counted
# then we just take the minimum over the nested for loop

int main(){
    int n,m;
    cin>>n>>m;
    vector<int> pages(n+1);
    int temp;
    for(int i=1;i<n+1;i++){
        cin>>temp;
        pages[i]=temp;
    }
    vector<int> parent(n+1,0);
    vector<unordered_map<int,int>> parents(n+1);
    vector<int> cumulative(n+1,0);
    vector<int> cc(n+1,1);
    cc[0]=0;
    int a,b;
    for(int i=0;i<m;i++){
        cin>>a>>b;
        parent[b]=a;
        cc[a]=0;
    }
    vector<int> finalcc;
    for(int i=1;i<cc.size();i++){
        if(cc[i]==1){
            finalcc.push_back(i);
        }
    }
    for(int i:finalcc){
        int s = 0;
        unordered_map<int,int> tempmap;
        int curr = i;
        while(curr!=0){
            s+=pages[curr];
            tempmap.emplace(make_pair(curr,1));
            curr = parent[curr];
        }
        tempmap.emplace(make_pair(0,0));
        cumulative[i]=s;
        parents[i] = tempmap;
    }
    int ans = 1000000;
    for(int i = 0;i<finalcc.size();i++){
        int p = cumulative[finalcc[i]];
        for(int j = i+1;j<finalcc.size();j++){
            int curr = finalcc[j];
            int temp = 0;
            while(parents[finalcc[i]].find(curr)==parents[finalcc[i]].end()){
                temp+=pages[curr];
                curr = parent[curr];
            }
            ans=min(ans,p+temp);
        }
    }
    cout<<ans<<endl;
    return 0;
}
