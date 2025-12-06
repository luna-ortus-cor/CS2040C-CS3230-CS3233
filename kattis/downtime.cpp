#include <bits/stdc++.h>
using namespace std;

//first note the constant proc time of each event (1000)
//thus an event that is received earlier (and the input is in chronological order)
//will "end" earlier than another event received later
//so initialize capacity of all servers = numserver*k (initially k)
//then process each event, for each event time
//if there are completed processes prior to that time
//add back to capacity of servers (and remove from queue)
//if capacity of servers is 0 then add new server (add k to capacity)
//subtract 1 from capacity for current event then add completion time to queue
//finally total servers needed is (free capacity + occupied capacity)//k

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,k;
    cin>>n>>k;
    int cap=k;
    queue<int> done;
    int time;
    while(n--){
        cin>>time;
        while(!done.empty() && done.front()<=time){
            done.pop();
            cap++;
        }
        if(!cap)cap+=k;
        cap--;
        done.push(time+1000);
    }
    cout<<(cap+done.size())/k<<endl;
    return 0;
}
