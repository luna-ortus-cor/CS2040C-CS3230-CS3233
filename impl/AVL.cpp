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
  int height;
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
  Vertex* remove(int v);
  int getTreeHeight();
  int getHeight(Vertex* v);
  int height(Vertex* v);
  int bf(Vertex* v);
  Vertex* rotateRight(Vertex* v);
  Vertex* rotateLeft(Vertex* v);
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

// O(1)
int AVL::getTreeHeight(){
  return (root==NULL)?-1:root->height;
}

// O(1)
int AVL::getHeight(Vertex* v){
  return (v==NULL)?-1:v->height;
}

// O(1)
int AVL::height(Vertex* v){
  if(v==NULL){
    return 0;
  }else{
    v->height = max(height(v->left),height(v->right))+1;
  }
  return v->height;
}

// O(1)
int AVL::bf(Vertex* v){
  return v->left->height - v->right->height;
}

// O(1)
Vertex* AVL::rotateRight(Vertex* v){
  if(v->left==NULL){
    return NULL;
  }
  Vertex* l = v->left;
  l->parent=v->parent;
  v->parent=l;
  v->left=l->right;
  if(l->right != NULL){
    l->right->parent=v;
  }
  l->right=v;
  // update heights
  v->height = max(getHeight(v->left), getHeight(v->right)) + 1;
  l->height = max(getHeight(l->left), getHeight(l->right)) + 1;
  return l;
}

// O(1)
Vertex* AVL::rotateLeft(Vertex* v){
  if(v->right==NULL){
    return NULL;
  }
  Vertex* r = v->right;
  r->parent=v->parent;
  v->parent=r;
  v->right=r->left;
  if(r->left != NULL){
    r->left->parent=v;
  }
  r->left=v;
  //update heights
  v->height = max(getHeight(v->left), getHeight(v->right)) + 1;
  r->height = max(getHeight(r->left), getHeight(r->right)) + 1;
  return r;
}

// O(h)
Vertex* AVL::insert(int v, Vertex* r=root, Vertex* p=NULL){
  if(r==NULL){
    r = new Vertex();
    r->data=v;
    r->parent=p;
    r->left=NULL;
    r->right=NULL;
    r->height=0;
  }else if(r->data>v){
    r->right=insert(v,r->right,r);
    r->right->parent=r;
  }else if(r->data<v){
    r->left=insert(v,r->left,r);
    r->left->parent=r;
  }else{
    //handle duplicate case
  }
  
  int balance = bf(r);
  if(balance==2){ //left heavy
    int balance2 = bf(r->left);
    if(balance2 >=0){
      r=rotateRight(r);
    }else{
      r->left=rotateLeft(r->left);
      r=rotateRight(r);
    }
  }else if(balance==-2){ //right heavy
    int balance2 = bf(r->right);
    if(balance2 <=0){
      r=rotateLeft(r);
    }else{
      r->right=rotateRight(r->right);
      r=rotateLeft(r);
    }
  }else{
    //do nothing
  }
  r->height=height(r);
  return r;
}

// O(h)
Vertex* AVL::remove(int v, Vertex* r){
  if(r==NULL){
    return r;
  }
  if(r->data==v){
    if(r->right==NULL&&r->left==NULL){
      delete r;
      r=NULL;
    }else if(r->left==NULL){
      Vertex* temp = r;
      r->right->parent=r->parent;
      r=r->right;
      delete temp;
    }else if(r->right==NULL){
      Vertex* temp = r;
      r->left->parent=r->parent;
      r=r->left;
      delete temp;
    }else{
      Vertex* succ = Search(Successor(v));
      r->data = succ->data;
      r->right=remove(succ->data, r->right);
      // or, replace with predecessor also works
      // Vertex* pred = Search(Predecessor(v));
      // r->data = pred->data;
      // r->left=remove(pred->data, r->left);
    }
  }else if(r->data<v){
    r->right=remove(v,r->right);
  }else if(r->data>v){
    r->left=remove(v,r->left);
  }else{
    //do nothing
  }
  // now handle changes in the bf
  if(r!=NULL){
    int balance = bf(r);
    if(balance==2){ //left heavy
      int balance2 = bf(r->left);
      if(balance2 >=0){
        r=rotateRight(r);
      }else{
        r->left=rotateLeft(r->left);
        r=rotateRight(r);
      }
    }else if(balance==-2){ //right heavy
      int balance2 = bf(r->right);
      if(balance2 <=0){
        r=rotateLeft(r);
      }else{
        r->right=rotateRight(r->right);
        r=rotateLeft(r);
      }
    }
    r->height=height(r);
  }
  return r;
}
