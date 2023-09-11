#include <stdio.h>
#include <stdlib.h>
#define n 500000
#define INFTY 1000000000

void merge(int *, int, int, int);
void mergeSort(int *, int, int);

int compare_count=0;

int main(){
  int A[n], A_len, i;

  scanf("%d",&A_len);
  for(i = 0; i < A_len; i++) scanf("%d",&A[i]);

  mergeSort( A, 0, A_len);
  for(i = 0; i < A_len-1; i++) printf("%d ",A[i]);
  printf("%d\n%d\n", A[A_len-1], compare_count);
  
  return 0;
}

void merge(int *A, int left, int mid, int right){
  int n1, n2, *L, *R, i, j, k;

  n1 = mid - left;
  n2 = right - mid;
  L = (int *)malloc( (n1+1) * sizeof(int) );
  R = (int *)malloc( (n2+1) * sizeof(int) );
  for(i = 0; i < n1; i++) L[i] = A[left+i];
  for(i = 0; i < n2; i++) R[i] = A[mid+i];
  L[n1] = INFTY;
  R[n2] = INFTY;
  i = 0;
  j = 0;
  for(k = left; k < right; k++){
    if( L[i] <= R[j] ){
      A[k] = L[i];
      i++;
    }
    else{
      A[k] = R[j];
      j++;
    }
    compare_count++;
  }
}

void mergeSort(int *A, int left, int right){
  if( left+1 < right ){
    int mid;
    mid = (left + right)/2;
    mergeSort(A, left, mid);
    mergeSort(A, mid, right);
    merge(A, left, mid, right);
  }
}
