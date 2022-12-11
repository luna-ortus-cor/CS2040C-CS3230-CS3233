// protected singly linked list, only operations allowed at head

// Linked List
struct Vertex { // we can use either C struct or C++/Python/Java class
  int item; // the data is stored here, an integer in this example
  Vertex* next; // this pointer tells us where is the next vertex
};

// consider immplementation where keep track of N, number of items in LL
class LL:public Vertex{
private:
  Vertex *head;
public:
  LL(){
    head=NULL;
  }
  Vertex* Get();
  void insertHead(int v);
  void removeHead();
}

// O(1)
Vertex* LL::Get() { // returns only the head vertex
  Vertex* ptr = head; // we have to start from head
  return ptr;
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
    head = vtx;
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
