#include <stdio.h>
#define H_MAX 500000

int parent(int i){
  return (int)i/2;
}

int left(int i){
  return i*2;
}

int right(int i){
  return i*2+1;
}

void maxHeapify(int *H, int i, int heap_size){
  int l, r, largest, x;
  l = left(i);
  r = right(i);
  
  // Select node whose value is max among left, itself and right node.
  if( l <= heap_size && H[l] > H[i] ) largest = l;
  else largest = i;
  if( r <= heap_size && H[r] > H[largest] ) largest = r;

  if( largest != i ){
    x = H[i];
    H[i] = H[largest];
    H[largest] = x;
    maxHeapify( H, largest, heap_size);
  }
}

void buildMaxHeap(int *H, int heap_size){
  int i;
  for(i = heap_size; i >= 1; i--){
    maxHeapify( H, i, heap_size);
  }
}

int main(){
  int H[H_MAX], heap_size, i;

  scanf("%d",&heap_size);
  for(i = 1; i < heap_size+1; i++){
    scanf("%d",&H[i]);
  }
  buildMaxHeap( H, heap_size);

  for(i = 1; i < heap_size+1; i++){
    printf(" %d",H[i]);
  }
  printf("\n");
  return 0;
}
