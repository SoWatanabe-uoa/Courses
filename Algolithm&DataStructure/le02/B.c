#include <stdio.h>
#define N 100

int main(){
  int i, j, mini, length, x, A[N], swap_count=0;
  //There is x in this program for storing the value of the element of A.

  scanf("%d",&length);
  for(i = 0; i < length; i++) scanf("%d",&A[i]);

  for(i = 0; i < length; i++){
    mini = i;
    for(j = i; j < length; j++){
      if( A[j] < A[mini] ) mini = j;
    }
    if( i != mini ){
      x = A[i];
      A[i] = A[mini];
      A[mini] = x;
      swap_count++;
    }
  }
  
  for(i = 0; i < length; i++){
    if( i == length-1 ) printf("%d\n",A[i]);
    else printf("%d ",A[i]);
  }
  printf("%d\n",swap_count);
  
  return 0;
}
