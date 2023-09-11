#include <stdio.h>
#define n 20

int Partition(int *, int, int);

int main(){
  int A[n], A_len, q, i;

  scanf("%d",&A_len);
  for(i = 0; i < A_len; i++) scanf("%d",&A[i]);

  q = Partition( A, 0, A_len-1);
  for(i = 0; i < q; i++) printf("%d ",A[i]);
  printf("[%d] ",A[q]);
  for(i = q+1; i < A_len-1; i++) printf("%d ",A[i]);
  printf("%d\n",A[A_len-1]);
  
  return 0;
}

int Partition(int *A, int p, int r){
  int i, j, x;

  i = p-1;
  for(j = p; j < r; j++){
    if( A[j] <= A[r] ){
      i++;
      x = A[i];
      A[i] = A[j];
      A[j] = x;
    }
  }
  x = A[i+1];
  A[i+1] = A[r];
  A[r] = x;
  
  return i+1;
}
