//A*B-(C+D)+E -> AB*CD+-E+

using namespace std;

int precedence(char c){
  if(c=='^'){
    return 3;
  }else if(c=='/'||c=='*'){
    return 2;
  }else if(c=='+'||c=='-'){
    return 1;
  }else{
    return 0;
  }
}

int main(){
  string expr = "";
  stack<char> s;
  string out = "";
  
  for(int i=0;i<expr.length();i++){
    if(precedence(expr.at(i)==0)){
      out+=expr.at(i);
    }else if(expr.at(i)=='('){
      s.push(expr.at(i));
    }else if(expr.at(i)==')'){
      while(s.top()!='('){
        out+=s.top();
        s.pop();
      }
      s.pop();
    }else{
      while(!s.empty() && precedence(expr.at(i))<=precedence(s.top())){
        out+=s.top();
        s.pop();
      }
      s.push(expr.at(i));
    }
  }
  while(!s.empty()){
    out+=s.top();
    s.pop();
  }
  cout<<out<<endl;
  return 0;
}
