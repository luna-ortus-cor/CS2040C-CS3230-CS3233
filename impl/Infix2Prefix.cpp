//A*B-(C+D)+E -> -*AB++CDE

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
  stack<char> s;
  string out = "";
  
  reverse(expr.begin(),expr.end());
  for(int i=0;i<expr.length();i++){
    if(precedence(expr.at(i))==-1){
      out+=expr.at(i);
    }else if(expr.at(i)=='('){
      while(s.top()!=')'){
        out+=s.top();
        s.pop();
      }
      s.pop();
    }else if(expr.at(i)==')'){
      s.push(expr.at(i));
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
  reverse(out.begin(),out.end());
  cout<<out<<endl;
  return 0;
}
