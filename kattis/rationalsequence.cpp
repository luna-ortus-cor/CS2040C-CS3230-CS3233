#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//consider starting from node F(1)=1/1
//then the left child is F(2)=1/2=F(10) in binary
//then the right child is F(3)=2/1=F(11) in binary
//similarly for the rest of the tree
//i.e. we can construct p/q from n by knowing the binary representation of n
//from the MSB, a 0 is taking the left child, and a 1 is taking the right child
//i.e. if 0, p/q will move to p/(p+q), if 1, p/q will move to (p+q)/q
//we can reverse this to construct n from p/q starting from the LSB
//given p/q, if p<q, then it is left child of parent p/(q-p)
//given p/q, if p>q, then it is right child of parent (p-q)/q
//this sequence of left and right children constructs n in binary from the LSB
//so given p/q, we construct n, then move to n+1, and reconstruct new p/q
//we will force use of long long to avoid potential overflow
//note: the above solution does not work due to requiring construction of n
//since p,q are in range 2^31, then n has value up to 2^(2^32) which overflows
//we also cannot use the string representation of n in binary, since
//2^(2^32) has 1+(2^32)(log10(2))=1.3e9 digits
//with P<=1e3, this will require iterating through ~1e12 digits which is not feasible
//thus we must make use of a graph traversal algorithm
//first note the special case of n/1; the next in sequence is 1/n+1
//otherwise, note that given p/q, we can determine if it is the left or right child
//and also determine the parent; denote the left child by 0 and the right child by 1
//then consider going from a left child to the right child
//this involves moving up to the parent then down to the other child
//then for a right child, we move up to the parent, then move up to the parent's parent
//and the move down twice to the child
//i.e. every move up to parent necessitates a move down to child
//also notice the flip of the bits i.e. a left child -> parent (0) corresponds to a
//parent -> right child (1) and similarly right child -> parent (1) corresponds to a
//parent -> left child (0) (although with different parent now)
//this invariant is true also for the parent itself (e.g. if parent -> parent parent)
//then the only possible sequences are 0->1, 10->01, 110->100, 1...10->10...0
//we also run into MLE when using recursion, so have to use iterative

/*
tuple<ll,ll> generate(ll p,ll q){
    if(q==1){
        return{q,p+1};
    }else if(p<q){
        q-=p; //0
        p+=q; //1
        return {p,q};
    }else{
        p-=q; //1
        auto[np,nq]=generate(p,q);
        nq+=np; //0
        return {np,nq};
    }
}
*/

tuple<ll,ll> generate(ll p,ll q){
    if(q==1)return{q,p+1};
    ll count=0;
    while(p>q){
        p-=q;
        count++;
    }
    q-=p;
    p+=q;
    while(count--){
        q+=p;
    }
    return{p,q};
}

int main(){
    int P,K;
    ll p,q,newp,newq;
    string s;
    cin>>P;
    while(P--){
        cin>>K;
        cin>>s;
        p=stoll(s.substr(0,s.find("/"))),q=stoll(s.substr(s.find("/")+1));
        auto [newp,newq]=generate(p,q);
        cout<<K<<" "<<newp<<"/"<<newq<<"\n";
    }
    return 0;
}

/*
ll pqton(ll p, ll q){
    ll res=0;
    ll idx=1;
    while(p){
        if(p<q){ //left child
            q-=p;
        }else if(p>q){ //right child
            p-=q;
            res+=idx;
        }else{
            p=q=0;
            res+=idx;
        }
        idx*=2;
    }
    cout<<res<<endl;
    return res;
}

tuple<ll,ll> ntopq(ll n){
    bool started=false; //handle leading zero
    ll p=0, q=0;
    for (int i = 63; i >= 0; i--) {
        if(!(started|((n>>i)&1)))continue;
        started=true;
        if(!p){
            p=q=1;
            continue;
        }
        if((n>>i)&1)p+=q; //right child
        else q+=p; //left child
    }
    return {p,q};
}

int main(){
    int P,K;
    ll p,q,newp,newq;
    string s;
    cin>>P;
    while(P--){
        cin>>K;
        cin>>s;
        p=stoll(s.substr(0,s.find("/"))),q=stoll(s.substr(s.find("/")+1));
        auto [newp,newq]=ntopq(pqton(p,q)+1);
        cout<<K<<" "<<newp<<"/"<<newq<<"\n";
    }
    return 0;
}
*/
