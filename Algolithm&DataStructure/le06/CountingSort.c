#include <stdio.h>
#define N 2000

void CountingSort(int *, int *, int, int);

int main(){
  int A[N], B[N], A_len,k=0, i;

  scanf("%d",&A_len);
  for(i = 1; i <= A_len; i++){
    scanf("%d",&A[i]);
    if( A[i] > k ) k = A[i];
  }

  CountingSort( A, B, A_len, k);
  for(i = 1; i < A_len; i++) printf("%d ",B[i]);
  printf("%d\n",B[A_len]);
  
  return 0;
}

void CountingSort(int *A, int *B, int A_len, int k){
  int i, j, C[k+1];

  for(i = 0; i <= k; i++) C[i] = 0;
  for(j = 1; j <= A_len; j++) C[A[j]]++;
  for(i = 1; i <= k; i++) C[i] += C[i-1];
  for(j = A_len; j >= 1; j--){
    B[C[A[j]]] = A[j];
    C[A[j]]--;
  }
}
