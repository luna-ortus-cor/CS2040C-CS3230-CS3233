// taken from https://www.comp.nus.edu.sg/~stevenha/cs2040c/demos/BinaryHeapDemo.cpp
// FOR REFERENCE PURPOSES

#include <bits/stdc++.h>
using namespace std;

template <typename T>
class binary_heap {
private:
  vector<T> A; // the underlying data structure, we will ignore index 0
  int heap_size; // heap_size is not always the same as (int)A.size()

  // three helper navigation function, written in bit manipulation format to improve runtime speed, all three are fast O(1) functions
  int parent(int i) { return i>>1; } // i>>1 is the same as i/2
  int left(int i) { return i<<1; } // i<<1 is the same as i*2
  int right(int i) { return (i<<1)+1; } // (i<<1)+1 is the same as i*2+1

  void shift_up(int i) { // O(log n)
    if (i == 1) return; // at root, do nothing
    if (A[i] > A[parent(i)]) { // violate property with parent
      swap(A[i], A[parent(i)]); // swap upwards
      shift_up(parent(i)); // recurse, at most O(log n) steps back to the root
    }
  }

  void shift_down(int i) { // O(log n)
    if (i > heap_size) return; // beyond last element, do nothing
    int swap_id = i;
    if ((left(i) <= heap_size) && (A[i] < A[left(i)])) // compare with left child, if exists
      swap_id = left(i);
    if ((right(i) <= heap_size) && (A[swap_id] < A[right(i)])) // compare with right child, if exists
      swap_id = right(i);
    if (swap_id != i) { // need to swap with the larger of the two children
      swap(A[i], A[swap_id]); // swap downwards with the larger of the two children
      shift_down(swap_id); // recurse, at most O(log n) steps to one of the bottom-most leaf
    }
  }

public:
  binary_heap() { // O(1)
    A.push_back(T()); // remember to set index 0 to be 'dummy'
    heap_size = 0; // an empty Binary Heap
  }

  ~binary_heap() { // O(n)
    A.clear();
  }

  void push(T x) { // O(log n)
    if (heap_size+1 >= (int)A.size()) // O(1)
      A.push_back(T()); // enlarge the vector by one (internally, vector doubles its size) if needed, to avoid potential RTE below, O(1)
    A[++heap_size] = x; // the only possible insertion point, O(1)
    shift_up(heap_size); // shift upwards, O(log n) at worst
  }

  void pop() { // O(log n)
    if (empty()) return; // safeguard
    swap(A[1], A[heap_size--]); // swap with the last existing leaf, O(1)
    shift_down(1); // fix heap property downwards, O(log n) at worst
  }

  T top() { // O(1)
    return A[1]; // this is the root
  }

  bool empty() { // O(1)
    return heap_size == 0; // the condition for an empty A
  }

  int size() { // O(1)
    assert(heap_size <= (int)A.size()); // should be true at all times
    return heap_size;
  }
};

int main() {
  cout << "Our own Binary Heap\n";
  binary_heap<int> pq; // this shows that binary (max) heap can be used as an efficient ADT Priority Queue
  cout << pq.empty() << '\n'; // should be 1/true as pq content is {}

  pq.push(5);
  cout << pq.empty() << '\n'; // should be 0/false as pq content is {5 (max)}

  pq.push(2);
  pq.push(7);
  pq.push(3);
  cout << pq.top() << '\n'; pq.pop(); // should be 7 as pq content is {7 (max),5,3,2} -> {5 (max),3,2}

  pq.push(1);
  cout << pq.top() << '\n'; // should be 5 as pq content is {5 (max),3,2,1}
  cout << pq.top() << '\n'; pq.pop(); // should still be 5 as pq content is {5 (max),3,2,1} -> {3 (max),2,1}

  pq.push(8);
  pq.push(8); // duplicates is ok
  while (!pq.empty()) { // will print 8, 8, 3, 2, 1, in that order
    cout << pq.top() << '\n'; pq.pop();
  }


  cout << '\n';
  cout << "C++ STL version\n";
  priority_queue<int> pq_stl;
  cout << pq_stl.empty() << '\n'; // should be 1/true as pq_stl content is {}

  pq_stl.push(5);
  cout << pq_stl.empty() << '\n'; // should be 0/false as pq_stl content is {5 (max)}

  pq_stl.push(2);
  pq_stl.push(7);
  pq_stl.push(3);
  cout << pq_stl.top() << '\n'; pq_stl.pop(); // should be 7 as pq_stl content is {7 (max),5,3,2} -> {5 (max),3,2}

  pq_stl.push(1);
  cout << pq_stl.top() << '\n'; // should be 5 as pq_stl content is {5 (max),3,2,1}
  cout << pq_stl.top() << '\n'; pq_stl.pop(); // should still be 5 as pq_stl content is {5 (max),3,2,1} -> {3 (max),2,1}

  pq_stl.push(8);
  pq_stl.push(8); // duplicates is ok
  while (!pq_stl.empty()) { // will print 8, 8, 3, 2, 1, in that order
    cout << pq_stl.top() << '\n'; pq_stl.pop();
  }


  cout << '\n';
  cout << "Equivalency testing on a very large test case\n";

  // large random test
  clock_t begin = clock();

  srand(time(NULL));
  binary_heap<int> ours;
  priority_queue<int> theirs;
  assert(ours.empty() and theirs.empty()); // both empty at the start
  int N = 1000000; // usually just a few seconds
  for (int i = 0; i < N; ++i) { // insert N random integers to both data structures
    int value = rand();
    ours.push(value), theirs.push(value); // yes you can use comma like this... or just split this into two lines
  }
  assert(!ours.empty() and !theirs.empty()); // both not empty (has N entries) by now
  assert(ours.size() == (int)theirs.size()); // heap size should match, note that ours.size() returns int, theirs.size() returns size_t (depends on implementation, may not be really int)
  while (!ours.empty()) {
    assert(ours.top() == theirs.top()); // max value should match
    ours.pop(), theirs.pop();
    assert(ours.size() == (int)theirs.size()); // heap size should match
  }
  assert(ours.empty() and theirs.empty()); // both empty at the end

  cout << "Test time = " << fixed << setprecision(2) << (double)(clock()-begin)/CLOCKS_PER_SEC << "s\n";
  cout << "If there is no assertion (Run Time Error), then all is good\n";

  return 0;
}
