//*AB-+CD+E -> AB*CD+-E+

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
    
  }
}
