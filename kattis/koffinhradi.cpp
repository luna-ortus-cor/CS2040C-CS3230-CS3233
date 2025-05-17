#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//the idea is to first sort tasks by the closest deadline
//this can be done by (min) priority queue, but for efficiency
//we use a vector of pairs and sort by the deadline afterward
//then, for each task to be done, add the time taken to the current time
//push the finished task into the finished (max) priority queue
//if the current time is greater than the deadline, then look at the top
//of the priority queue, which has the finished task that has taken the longest to complete
//using caffeine drink on this task will thus afford the greatest reduction in time
//pop the old time taken, push the new time taken, and add one to the drink count
//subtract the reduction in time from the current time
//do this while the current time is greater than the deadline
//we also optimize to not push the task back into the pq if the time taken has dropped to 0
//since each push into the pq is O(log n)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n;
    cin >> n;
    vector<pair<ll, ll>> tasks(n);
    for(auto &[t,s]:tasks)cin>>t>>s;
    sort(tasks.begin(),tasks.end(),[](auto& a, auto& b) {
        return a.second<b.second;
    });
    priority_queue<ll> pq;
    ll currtime = 0, count = 0;
    for(auto &[t,s]:tasks) {
        currtime += t;
        pq.push(t);
        while(currtime>s){
            ll f=pq.top();pq.pop();
            ll newf=f/2;
            currtime-=(f-newf);
            if(newf)pq.push(newf);
            count++;
        }
    }
    cout<<count<<"\n";
    return 0;
}
