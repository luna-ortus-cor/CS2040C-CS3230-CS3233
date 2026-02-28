//+-*AB+CDE -> AB*CD+-E+
//-*AB++CDE -> AB*CD+E+-

using namespace std;

int precedence(char c){
  if(c=='^'){
    return 3;
  }else if(c=='/'||c=='*'){
    return 2;
  }else if(c=='+'||c=='-'){
    return 1;
  }else if(c=='('||c==')'){
    return 0;
  }else{
    return -1;
  }
}

int main(){
  string expr = "";
  stack<string> s;
  string out = "";
  
  reverse(expr.begin(),expr.end());
  for(int i=0;i<expr.length();i++){
    if(precedence(expr.at(i))>0){
      string a,b,temp;
      a=s.top();
      s.pop();
      b=s.top();
      s.pop();
      temp = a+b+expr.at(i);
      s.push(temp);
    }else{
      s.push(string(1,expr.at(i)));
    }
  }
  out = s.top();
  cout<<out<<endl;
  return 0;
}
