#include <bits/stdc++.h>
using namespace std;

// O(n^2)
void bubbleSort(int a[], int N) { // the standard version
  for (; N > 0; --N){ // N iterations
    for (int i = 0; i < N-1; ++i) { // except the last, O(N)
      if (a[i] > a[i+1]) { // not in non-decreasing order
        swap(a[i], a[i+1]); // swap in O(1)
      }
    }
  }
}

// O(n^2)
void selectionSort(int a[], int N) {
  for (int L = 0; L < N-1; ++L) { // O(N)
    int X = min_element(a+L, a+N) - a; // O(N)
    swap(a[X], a[L]); // O(1), X may be equal to L (no actual swap)
  }
}

// O(n^2)
void insertionSort(int a[], int N) {
  for (int i = 1; i < N; ++i) { // O(N)
    int X = a[i]; // X is the item to be inserted
    int j = i-1;
    for (; j >= 0 && a[j] > X; --j) { // can be fast or slow
      a[j+1] = a[j]; // make a place for X
    }
    a[j+1] = X; // index j+1 is the insertion point
  }
}

void merge(int a[], int low, int mid, int high) {
  // subarray1 = a[low..mid], subarray2 = a[mid+1..high], both sorted
  int N = high-low+1;
  int b[N]; // discuss: why do we need a temporary array b?
  int left = low, right = mid+1, bIdx = 0;
  while (left <= mid && right <= high) { // the merging
    b[bIdx++] = (a[left] <= a[right]) ? a[left++] : a[right++];
  }
  while (left <= mid) {
    b[bIdx++] = a[left++]; // leftover, if any
  }
  while (right <= high) {
    b[bIdx++] = a[right++]; // leftover, if any
  }
  for (int k = 0; k < N; ++k) {
    a[low+k] = b[k]; // copy back
  }
}

// O(NlogN)
void mergeSort(int a[], int low, int high) {
  // the array to be sorted is a[low..high]
  if (low < high) { // base case: low >= high (0 or 1 item)
    int mid = (low+high) / 2;	
    mergeSort(a, low  , mid ); // divide into two halves
    mergeSort(a, mid+1, high); // then recursively sort them
    merge(a, low, mid, high); // conquer: the merge subroutine
  }
}

int partition(int a[], int i, int j) {
  int p = a[i]; // p is the pivot
  int m = i; // S1 and S2 are initially empty
  for (int k = i+1; k <= j; ++k) { // explore the unknown region
    if ((a[k] < p) || ((a[k] == p) && (rand()%2 == 0)))  { // case 2+3
      ++m;
      swap(a[k], a[m]); // C++ STL algorithm std::swap
    } // notice that we do nothing in case 1: a[k] > p
  }
  swap(a[i], a[m]); // final step, swap pivot with a[m]
  return m; // return the index of pivot
}

// O(N^2)
void quickSort(int a[], int low, int high) {
  if (low < high) {
    int m = partition(a, low, high); // O(N)
    // a[low..high] ~> a[low..m–1], pivot, a[m+1..high]
    quickSort(a, low, m-1); // recursively sort left subarray
    // a[m] = pivot is already sorted after partition
    quickSort(a, m+1, high); // then sort right subarray
  }
}

int partition(int a[], int i, int j) {
  int rng=i+rand()%(j-i+1);
  int p = a[rng]; // p is the pivot
  swap(a[rng],a[i]);
  int m = i; // S1 and S2 are initially empty
  for (int k = i+1; k <= j; ++k) { // explore the unknown region
    if ((a[k] < p) || ((a[k] == p) && (rand()%2 == 0)))  { // case 2+3
      ++m;
      swap(a[k], a[m]); // C++ STL algorithm std::swap
    } // notice that we do nothing in case 1: a[k] > p
  }
  swap(a[i], a[m]); // final step, swap pivot with a[m]
  return m; // return the index of pivot
}

// O(NlogN)
void quickSort(int a[], int low, int high) {
  if (low < high) {
    int m = partition(a, low, high); // O(N)
    // a[low..high] ~> a[low..m–1], pivot, a[m+1..high]
    quickSort(a, low, m-1); // recursively sort left subarray
    // a[m] = pivot is already sorted after partition
    quickSort(a, m+1, high); // then sort right subarray
  }
}

// O(N) for small range of integer
void countingSort(vector<int> (&a)){
  int maximum=*max_element(a.begin(),a.end());
  int minimum=*min_element(a.begin(),a.end());
  int freq[maximum-minimum+1]={0};
  for(int i:a){
    freq[i-minimum]++;
  }
  int idx=0;
  for(int i=0;i<maximum-minimum+1;i++){
    int f=freq[i];
    if(f>0){
      for(int j=0;j<f;j++){
        a[idx]=i+minimum;
        idx++;
      }
    }
  }
}

// O(N) for large range but few digits
int getMax(int arr[], int size) { 
    int max = arr[0]; 
    for (int i = 1; i < size; i++) 
        if (arr[i] > max) 
            max = arr[i]; 
    return max; 
} 
  
void CountingSort(int arr[], int size, int div) { 
    int output[size]; 
    int count[10] = {0}; 
    for (int i = 0; i < size; i++) {
        count[ (arr[i]/div)%10 ]++; 
    }
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1]; 
    }
    for (int i = size - 1; i >= 0; i--) { 
        output[count[ (arr[i]/div)%10 ] - 1] = arr[i]; 
        count[ (arr[i]/div)%10 ]--; 
    }
    for (int i = 0; i < size; i++) {
        arr[i] = output[i]; 
    }
} 
  
void RadixSort(int arr[], int size) { 
    int m = getMax(arr, size); 
    for (int div = 1; m/div > 0; div *= 10) 
        CountingSort(arr, size, div); 
}

