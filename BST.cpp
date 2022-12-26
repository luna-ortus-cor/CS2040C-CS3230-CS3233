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
  Vertex* Search(Vertex* r, int v);
  int findMin(vertex* r);
  int findMax(Vertex* r);
}

// O(h)
Vertex* BST::Search(Vertex* r, int v){
  if(r==NULL){
    return NULL;
  }else if(v<r->data){
    return Search(r->left,v);
  }else if(v>r->data){
    return Search(r->right,v);
  }else{
    return r;
  }
}

// O(h)
int BST::findMin(Vertex* r){
  while(r!=NULL){
    if(r->left==NULL){
      return r->data;
    }else{
      return findMin(r->left);
    }
  }
  return NULL;
}

// O(h)
int BST::findMax(Vertex* r){
  while(r!=NULL){
    if(r->right==NULL){
      return r->data;
    }else{
      return findMax(r->right);
    }
  }
  return NULL;
}

  
