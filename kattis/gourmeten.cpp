#include<bits/stdc++.h>
using namespace std;int N,M,a[1000],t[30];
int g(int m){if(m<0)return 0;if(m==0)return 1;if(a[m]!=-1)return a[m];int s=0;for(int i=0;i<N;i++)s+=g(m-t[i]);a[m]=s;return s;}
int main(){cin>>M>>N;copy_n(istream_iterator<int>(cin),N,t);for(int i=0;i<=M;i++)a[i]=-1;cout<<g(M);}
