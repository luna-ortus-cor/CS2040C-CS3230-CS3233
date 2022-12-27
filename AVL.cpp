// BST supports most operations in O(h)~O(N) time
// Need to create balanced BST such that h~logN, i.e. O(h)~O(logN)
// define height(v) for each vertex v, defined as:
// The number of edges on the path from vertex v down to its deepest leaf. 
// This attribute is saved in each vertex so we can access a vertex's height in O(1) without having to recompute it every time.
// i.e.
// v.height = -1 (if v is an empty tree)
// v.height = max(v.left.height, v.right.height) + 1 (otherwise)
// height of BST is then root.height
// if N elements, then lower bound is h>log2(N), upper bound is h<N
// for AVL tree, h<2*log2(N)
// at every insert/remove operation, we only change height of vertices located along insertion/removal path
// i.e. x.height = max(x.left.height, x.right.height) + 1
// Define AVL Tree Invariant i.e. property that will never change
// Vertex v is said to be height-balanced iff |v.left.height - v.right.height| <= 1
// Define balance factor bf(v)=v.left.height-v.right.height
// Then if bf(v) != 1 || bf(v) != -1 || bf(v) != 0: need to rotate in order to preserve both BST and AVL invariant

struct Vertex { 
  int data; 
  Vertex* parent;
  Vertex* left;
  Vertex* right;
};

class AVL:public Vertex{
private:
  Vertex *root;
public:
  AVL(){
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
  void remove(int v);
}

// O(h)~O(N)
Vertex* AVL::Search(int v, Vertex* r=root){
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
int AVL::findMin(Vertex* r=root){
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
int AVL::findMax(Vertex* r=root){
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
int AVL::Successor(int v){
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
int AVL::Predecessor(int v){
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
void AVL::inOrder(Vertex* r=root){
  if(r==NULL){
    return;
  }
  inOrder(r->left);
  cout<<r->data<<endl;
  inOrder(r->right);
}

// O(N)
void AVL::preOrder(Vertex* r=root){
  if(r==NULL){
    return;
  }
  cout<<r->data<<endl;
  preOrder(r->left);
  preOrder(r->right);
}

// O(N)
void AVL::postOrder(Vertex* r=root){
  if(r==NULL){
    return;
  }
  postOrder(r->left);
  postOrder(r->right);
  cout<<r->data<<endl;
}
