#include <bits/stdc++.h>
using namespace std;
#include <bits/extc++.h> 
using namespace __gnu_pbds;

struct Team {
    int id;
    int solved;
    int penalty;
    bool operator<(const Team& other) const {
        if(solved!=other.solved)
            return solved>other.solved;
        if(penalty!=other.penalty)
            return penalty<other.penalty;
        return id<other.id;
    }
};

typedef tree<Team, null_type, less<Team>, rb_tree_tag, tree_order_statistics_node_update> ost;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,m,t,p;
    cin>>n>>m;
    vector<Team> teams(n+1);
    for(int i=1;i<=n;i++){
        teams[i]={i,0,0};
    }
    ost rank;
    for(int i=1;i<=n;i++){
        rank.insert(teams[i]);
    }
    for(int i=0;i<m;i++){
        cin>>t>>p;
        //alternatively can use reference to each team to avoid erase insert?
        //ans:no, if no erase-insert tree will not rebalance (since ost is a bbst (red-black))
        rank.erase(teams[t]);
        teams[t].solved++;
        teams[t].penalty+=p;
        rank.insert(teams[t]);
        cout<<rank.order_of_key(teams[1])+1<<"\n";
    }
    return 0;
}
