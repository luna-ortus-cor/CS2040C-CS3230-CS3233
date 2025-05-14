#include <bits/stdc++.h>
using namespace std;

//first note, given the line ax+by+c=0, the distance from any point x',y'
//to the line is |ax'+by'+c|/sqrt(a^2+b^2)
//given points x1,y1 and x2,y2, then for any x,y on the line we must have
//(y-y1)/(x-x1)=(y2-y1)/(x2-x1)=m i.e. same slope
//this gives us (y-y1)(x2-x1)=(y2-y1)(x-x1) -> (x2-x1)y-y1(x2-x1)=(y2-y1)x-x1(y2-y1)
//->(y2-y1)x+(x1-x2)y+x1(y1-y2)+y1(x2-x1)=0
//i.e. ax+by+c=0 -> a=y2-y1, b=x1-x2, c=...
//in this case we can simply take c=0-ax-by for any x,y on the line
//then we just have to maintain the minimum distance between any point and the line
//as well as the distance from each point to the line
//output all the cities where the distance to the line is equal to the minimum
//note that since we did not divide by sqrt(a^2+b^2) in our calculation the
//initial minimum (for the constraints x,y in [0,1000]) has a rough upper bound of
//a<=1000,b<=1000,sqrt(a^2+b^2)<=1000,actualdist<=1000sqrt(2)<2000 and so
//ax+by+c<2000*1000<2000001

vector<int> lineq(int x1, int y1, int x2, int y2){
    int a=y2-y1;
    int b=x1-x2;
    int c=0-(a*x1)-(b*y1);
    vector<int> abc={a,b,c};
    return abc;
}

int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        vector<int> abc=lineq(x1,y1,x2,y2);
        int a=abc[0];
        int b=abc[1];
        int c=abc[2];
        vector<string> names;
        vector<int> danger;
        int m;
        cin>>m;
        int most=2000001;
        for(int j=0;j<m;j++){
            string name;
            int x0,y0;
            cin>>name>>x0>>y0;
            names.push_back(name);
            most=min(most,abs((a*x0)+(b*y0)+c));
            danger.push_back(abs((a*x0)+(b*y0)+c));
        }
        for(int j=0;j<m;j++){
            if(danger[j]==most){
                cout<<names[j]<<" ";
            }
        }
        cout<<endl;
    }
  return 0;
}
