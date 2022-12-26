//binary search tree is where every node to the left is smaller than parent, and every node to the right is larger than parent
//for equal values, need to tweak
//implements Table or Map Abstract Data Type (ADT)
//needs to support following 3 operations as efficiently as possible
//exists(v),insert(v),remove(v)
//if use unsorted array/vector, O(N), O(1), O(N) time complexity respectively
//if use sorted array/vector, O(logN), O(N), O(N) time complexity respectively
//other operations possible: min ele, max ele, next larger ele, previous smaller ele, list ele in sorted
//consists of root vertex, internal vertices, and leaf vertex (vertices)
//each vertex at least 4 attributes: parent (can be null), left, right, key/value/data
//all vertices on left subtree strictly smaller than parent, and all vertices on right subtree strictly greater than parent
//to handle duplicate, can include additional data to store frequency/occurence of value
//static data structure: only efficient if no (or rare) inserts/deletes/updates
//dynamic data structure: efficient even if many inserts/deletes/updates

struct Vertex { 
  int data; 
  Vertex* parent;
  Vertex* left;
  Vertex* right;
};

class BST:public Vertex{
private:
  Vertex *root;
public:
  BST(){
    root=NULL;
  }
  Vertex* Search(int v, Vertex* r);
  int findMin(Vertex* r);
  int findMax(Vertex* r);
  int Successor(int v);
  int Predecessor(int v);
  void inOrder(Vertex* r);
  void preOrder(Vertex* r);
  void postOrder(Vertex* r);
  Vertex* insert(int v, Vertex* r, Vertex* p);
}

// O(h)~O(N)
Vertex* BST::Search(int v, Vertex* r=root){
  if(r==NULL){
    return NULL;
  }else if(v<r->data){
    return Search(v,r->left);
  }else if(v>r->data){
    return Search(v,r->right);
  }else{
    return r;
  }
}

// O(h)~O(N)
int BST::findMin(Vertex* r=root){
  while(r!=NULL){
    if(r->left==NULL){
      return r->data;
    }else{
      return findMin(r->left);
    }
  }
  return NULL;
}

// O(h)~O(N)
int BST::findMax(Vertex* r=root){
  while(r!=NULL){
    if(r->right==NULL){
      return r->data;
    }else{
      return findMax(r->right);
    }
  }
  return NULL;
}

// O(h)~O(N)
int BST::Successor(int v){
  Vertex* ptr = Search(root,v);
  if(ptr==NULL){
    return NULL;
  }
  if(v==findMax()){
    return NULL;
  }
  if(ptr->right!=NULL){
    return findMin(ptr->right);
  }else{
    Vertex* p = ptr->parent;
    while(p!=NULL && ptr==p->right){
      ptr = p;
      p = ptr->parent;
    }
    if(p==NULL){
      return NULL;
    }else{
      return p->data;
    }
  }
}

// O(h)~O(N)
int BST::Predecessor(int v){
  Vertex* ptr = Search(root,v);
  if(ptr==NULL){
    return NULL;
  }
  if(v==findMin()){
    return NULL;
  }
  if(ptr->left!=NULL){
    return findMax(ptr->left);
  }else{
    Vertex* p = ptr->parent;
    while(p!=NULL && ptr==p->left){
      ptr = p;
      p = ptr->parent;
    }
    if(p==NULL){
      return NULL;
    }else{
      return p->data;
    }
  }
}

// O(N)
void BST::inOrder(Vertex* r=root){
  if(r==NULL){
    return;
  }
  inOrder(r->left);
  cout<<r->data<<endl;
  inOrder(r->right);
}

// O(N)
void BST::preOrder(Vertex* r=root){
  if(r==NULL){
    return;
  }
  cout<<r->data<<endl;
  preOrder(r->left);
  preOrder(r->right);
}

// O(N)
void BST::postOrder(Vertex* r=root){
  if(r==NULL){
    return;
  }
  postOrder(r->left);
  postOrder(r->right);
  cout<<r->data<<endl;
}

// O(h)~O(N)
Vertex* BST::insert(int v,Vertex* r=root,Vertex* p=NULL){
  if(r==NULL){
    Vertex* vtx = new Vertex();
    vtx->data=v;
    vtx->right=NULL;
    vtx->left=NULL;
    vtx->parent=p;
    r=vtx;
  }else{
    if(v<r->data){
      r->left=insert(v,r->left,r);
    }else if(v>r->data){
      r->right=insert(v,r->right,r);
    }else{
      // if duplicate, need to handle separately
    }
  }
  return r;
}
    
