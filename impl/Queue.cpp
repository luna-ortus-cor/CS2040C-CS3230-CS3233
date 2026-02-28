// protected singly linked list, only removal at head and insertion after tail allowed

// Linked List
struct Vertex { // we can use either C struct or C++/Python/Java class
  int item; // the data is stored here, an integer in this example
  Vertex* next; // this pointer tells us where is the next vertex
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
  Vertex* Get();
  void insertBack(int v);
  void removeHead();
}

// O(1)
Vertex* LL::Get() { // returns the vertex
  Vertex* ptr = head; // we have to start from head
  return ptr;
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
    tail = vtx;
  }
}

// O(1)
void LL::removeHead(){
  if(head==NULL){
    return; // avoid crashing when SLL is empty
  }else{
    Vertex* temp = head; // so we can delete it later
    head = head->next; // book keeping, update the head pointer
    delete temp; // which is the old head
  }
}
