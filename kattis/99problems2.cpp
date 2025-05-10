#include <bits/stdc++.h>
using namespace std;

//the idea is for each Q, do binary search on the list of problem difficulties
//then handle cases based on T and if problem can be deleted
//so this is O(n log n)
//use multiset to make erasing elements easier
//refer to comments in code for more detail

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N,Q,T,D;
    cin>>N>>Q;
    
    vector<int> problems(N);
    for(int i=0;i<N;i++){
        cin>>problems[i];
    }
    
    sort(problems.begin(),problems.end()); //sort problems first for binary search
    multiset<int> problemSet(problems.begin(),problems.end()); //push into multiset
    
    for(int i=0;i<Q;i++){
        cin>>T>>D;
        auto it=problemSet.begin(); //random init of auto iterator
        if(T==2){ //discard problem not harder than D
            it=problemSet.upper_bound(D); //will either return first problem > D or point to end
            if(it!=problemSet.begin()){ //ensure pointer not at first element, if at first element, no problem can be deleted since all problems > D
                it--; //get last problem <= D
                if(it!=problemSet.end() && *it<=D){ //check problem is not end (is valid) and is <= D
                    cout<<*it<<"\n";
                    problemSet.erase(it); //remove problem
                    continue;
                }
            }
            cout<<-1<<"\n";
        }else{ //discard problem strcitly harder than D
            it=problemSet.upper_bound(D); //will either return first problem > D or point to end
            if(it!=problemSet.end() && *it>D){ //check problem is not end (is valid) and is > D
                cout<<*it<<"\n";
                problemSet.erase(it); //remove problem
                continue;
            }
            cout<<-1<<"\n";
        }
    }
}
