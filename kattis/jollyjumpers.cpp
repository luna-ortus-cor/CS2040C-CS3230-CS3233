#include <bits/stdc++.h>
using namespace std;

//simply loop through all lines
//for each line check first digit n, initialize vector of size n-1 to 0
//for each of remaining n integers check difference between consecutive integers
//this can be done while reading the integers
//by using prev, curr and setting prev to curr after every integer read
//if 1<=abs(diff)<=n-1 then set particular index in vector to 1
//finally check if sum of vector is equal to n-1
//if yes, jolly, else not jolly

int main(){
    string line;
    int n,prev,curr;
    while(getline(cin,line)){
        istringstream iss(line);
        iss>>n;
        vector<int> diff(n-1,0);
        iss>>prev;
        while(iss>>curr){
            int idx=abs(curr-prev);
            if(1<=idx && idx<=n-1){
                diff[idx-1]=1;
            }
            prev=curr;
        }
        if(accumulate(diff.begin(),diff.end(),0)==n-1){
            cout<<"Jolly\n";
        }else{
            cout<<"Not jolly\n";
        }
    }
    return 0;
}
