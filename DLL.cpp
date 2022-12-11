// Doubly Linked List
struct Vertex { // we can use either C struct or C++/Python/Java class
  int item; // the data is stored here, an integer in this example
  Vertex* next; // this pointer tells us where is the next vertex
  Vertex* prev; // this pointer tells us where is the previous vertex
};

// consider immplementation where keep track of N, number of items in LL
class LL:public Vertex{
private:
  Vertex *head,*tail;
public:
  LL(){
    head=NULL;
    tail=NULL;
  }
  Vertex* Get(int i);
  int Find(int v);
  void insertHead(int v);
  void insert(int i, int v);
  void insertBack(int v);
  void removeHead();
  void remove(int i);
  void removeBack();
}

// O(N)
Vertex* LL::Get(int i) { // returns the vertex
  Vertex* ptr = head; // we have to start from head
  for (int k = 0; k < i; ++k) // advance forward i time(s)
    ptr = ptr->next; // the pointers are pointing to the higher index
  return ptr;
}

// O(N)
int LL::Find(int v){
  Vertex* ptr = head;
  if(ptr==NULL){ //empty LL
    return -1;
  }
  bool found = false;
  int counter = 0;
  while(ptr->item!=v){
    counter++;
    ptr = ptr->next;
    if(ptr==NULL){
      return -1;
    }
  }
  return counter;
}

// O(1)
void LL::insertHead(int v){
  Vertex* vtx = new Vertex(); // create new vertex vtx from item v
  vtx->item = v;
  vtx->next = head; // link this new vertex to the (old) head vertex
  if(head==NULL){
    head = vtx; // the new vertex becomes the new head
    tail = vtx;
  }else{
    head->prev = vtx;
    head = vtx;
  }
}

// O(N)
void LL::insert(int i, int v){ 
  if(head==NULL){
    insertHead(v);
  }else{
    Vertex* pre = Get(i-1);
    Vertex* aft = pre->next; // aft cannot be null, think about it
    Vertex* vtx = new Vertex(); // create new vertex
    vtx->item = v;
    vtx->next = aft; // link this
    vtx->prev = pre;
    pre->next = vtx; // and this
    aft->prev = vtx;
  }
}

// O(1)
void LL::insertBack(int v){
  Vertex* vtx = new Vertex();
  vtx->item = v; // create new vertex vtx from item v
  tail->next = vtx; // just link this, as tail is the i = (N-1)-th item
  if(head==NULL){
    tail = vtx; // now update the tail pointer
    head = vtx;
  }else{
    vtx->prev = tail;
    tail = vtx;
  }
}

// O(1)
void LL::removeHead(){
  if(head==NULL){
    return; // avoid crashing when DLL is empty
  }else{
    Vertex* temp = head; // so we can delete it later
    head = head->next; // book keeping, update the head pointer
    head->prev = NULL;
    delete temp; // which is the old head
  }
}

// O(N)
void LL::remove(int i){
  if(head==NULL){
    return;
  }else{
    Vertex* pre = Get(i-1); // traverse to (i-1)-th vertex, O(N)
    Vertex* temp = pre->next;
    Vertex* aft = temp->next;
    pre->next = aft; // bypass temp
    aft->prev = pre;
    delete temp;
  }
}

// O(1)
void LL::removeBack(){
  if(head==NULL){
   return;
  }else{
    Vertex* temp = tail; // remember tail item
    tail = tail->prev; // the key step to achieve O(1) performance :O
    tail->next = NULL; // remove this dangling reference
    delete temp; // temp = (old) tail
  }
}
