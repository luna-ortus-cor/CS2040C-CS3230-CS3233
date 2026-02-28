using namespace std;

int main(){
  string expr = "";
  
  stack<char> s;
  for(int i=0;i<expr.length();i++){
    if(s.empty()){
      s.push(expr.at(i));
    }else if((s.top()=='('&&expr.at(i)==')')||(s.top()=='['&&expr.at(i)==']')||(s.top()=='{'&&expr.at(i)=='}')){
      s.pop();
    }else{
      s.push(expr.at(i));
    }
  }
  if(s.empty()){
    cout<<"balanced"<<endl;
  }else{
    cout<<"not balanced"<<endl;
  }
  return 0;
}
