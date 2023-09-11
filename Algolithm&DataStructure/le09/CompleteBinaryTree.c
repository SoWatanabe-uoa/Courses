#include <stdio.h>
#define H_MAX 250

int parent(int i){
  return (int)i/2;
}

int left(int i){
  return i*2;
}

int right(int i){
  return i*2+1;
}

int main(){
  int H[H_MAX], heap_size, i;

  scanf("%d",&heap_size);
  for(i = 1; i < heap_size+1; i++){
    scanf("%d",&H[i]);
  }

  for(i = 1; i < heap_size+1; i++){
    printf("node %d: key = %d, ",i,H[i]);
    if( i != 1 ) printf("parent key = %d, ",H[parent(i)] );
    if( left(i) <= heap_size ) printf("left key = %d, ",H[left(i)] );
    if( right(i) <= heap_size ) printf("right key = %d, ",H[right(i)] );
    printf("\n");
  }
  return 0;
}
