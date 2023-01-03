// Binary (Max) Heap (there is also a binary min heap)
// complete binary tree i.e. all levels except possibly the last are fully filled, and all vertices in the last level are as far left as possible
// max heap property i.e. parent of each vertex except root is larger than that vertex
// used to implement priority queue (PQ)
// PQ is similar to queue, but with following 2 operations
// Enqueue(x): put a new element x into the PQ (in some order)
// Dequeue(): return an existing element that has the highest priority in the PQ
// if tied, can choose to return any, or return in order that was enqueued (FIFO)
// we can implement PQ using (circular) array or linked list, but this is slow O(N) enqueue and dequeue operation
// max height of binary heap is log N for N elements
// store elements in compact array, starting with root at index 1, and subsequent levels from left to right in increasing indices
// then tree traversal can be simplified to following operations
// parent(i) = i>>1 (index i divided by 2, integer division)
// left(i) = i<<1 (index i multiplied by 2)
// right(i) = (i<<1)+1 (index i multiplied by 2 add 1)
// similar to BST, 
// insert(v) is O(logN)
// delete(i) is O(logN)
// update(i,v) is O(logN)
// we can naively create a binary heap in O(NlogN) by doing N insert(v)
// alternatively, we notice that by taking the array of numbers as the initial binary heap, 
// we only need to correct half of the elements (leaves are considered to satisfy the heap property initially, so no change required)
// this is O(N) instead of O(NlogN), take note that the cost of correcting an element is not O(logN) but O(h) where h is the height of the subtree
// we can also use this for heap sort i.e. call extract N times to sort in descending order (will be ascending for a min heap), O(NlogN)
// similarly we can use this for partial sort i.e. call extract K times to get the K largest elements (will be K smallest for a min heap), O(KlogN)
// two ways to convert from max heap to min heap, both O(N)
// starting from the original max heap, call heapify (i.e. make swaps to maintain heap property) on all the non-leaves (basically the second part of the fastCreate)
// see https://www.techiedelight.com/convert-max-heap-min-heap-linear-time/
// recreate a min heap in O(N) by negating all the values in the max heap, then fastCreate again, then re-negate

class Heap{
private:
  vector<int> A;
public:
  Heap(){
    A.push_back(0);
  }
  void slowCreate(vector<int> vi);
  void fastCreate(vector<int> vi);
  int parent(int i);
  int left(int i);
  int right(int i);
  void insert(int v);
  void remove(int i);
  void update(int i, int newv);
  int extract();
}

void Heap::slowCreate(vector<int> vi){
  for(int v:vi){
    insert(vi);
  }
}

void Heap::fastCreate(vector<int> vi){
  for(int i=1;i<1+vi.length;i++){
    A[i]=vi[i-1];
  }
  for(int j=(A.length-1)/2;j>=1;j--){
    int i=j;
    while(i<A.length){
      if(A[left(i)]>A[right(i)]){
        if(A[i]<A[left(i)]){
          swap(A[i],A[left(i)]);
          i=left(i);
        }
      }else if(A[left(i)]<A[right(i)]){
        if(A[i]<A[right(i)]){
          swap(A[i],A[right(i)]);
          i=right(i);
        }
      }else{
        break;
      }
    }
  }
}

int Heap::parent(int i){
  return i>>1;
}

int Heap::left(int i){
  return i<<1;
}

int Heap::right(int i){
  return (i<<1)+1;
}

void Heap::insert(int v){
  A[A.length] = v;
  i = A.length-1;
  while((i>1)&&(A[i]>A[parent(i)])){
    swap(A[i],A[parent(i)]);
    i=parent(i);
  }
}

void Heap::remove(int i){
  A[i]=A[1]+1;
  while((i>1)&&(A[i]>A[parent(i)])){
    swap(A[i],A[parent(i)]);
    i=parent(i);
  }
  extract();
}

void Heap::update(int i, int newv){
  int oldv = A[i];
  A[i] = newv;
  if(newv>oldv){
    while((i>1)&&(A[i]>A[parent(i)])){
      swap(A[i],A[parent(i)]);
      i=parent(i);
    }
  }else if(oldv>newv){
    
  }else{
    //do nothing
  }

int Heap::extract(){ //returns max element for binary max heap, we can easily write similar code to return min element for binary min heap
  int ret = A[1];
  A[1]=A[A.length-1];
  int i=1;
  A.length--;
  while(i<A.length){
    if(A[left(i)]>A[right(i)]){
      if(A[i]<A[left(i)]){
        swap(A[i],A[left(i)]);
        i=left(i);
      }
    }else if(A[left(i)]<A[right(i)]){
      if(A[i]<A[right(i)]){
        swap(A[i],A[right(i)]);
        i=right(i);
      }
    }else{
      break;
    }
  }
  return ret;
}
