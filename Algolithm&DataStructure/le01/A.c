#include <stdio.h>
#define N 100

int main(){
  int i, j, k, length, key, print_count, A[N];
  
  scanf("%d",&length);
  print_count = length;
  for(i = 0; i < length; i++) scanf("%d",&A[i]);

  for(k = 0; k < length; k++){
      printf("%d",A[k]);
      if( k == length-1 ) printf("\n");
      else printf(" ");
    }
  print_count--;

  for(j = 1; j < length; j++){
    key = A[j];
    i = j-1;
    while( i >= 0 && A[i] > key ){
      A[i+1] = A[i];
      i--;
    }
    A[i+1] = key;
    for(k = 0; k < length; k++){
      printf("%d",A[k]);
      if( k == length-1 ) printf("\n");
      else printf(" ");
    }
    print_count--;
  }

  for(i = 1; i <= print_count; i++){
    for(k = 0; k < length; k++){
      printf("%d",A[k]);
      if( k == length-1 ) printf("\n");
      else printf(" ");
    }
  }
  
  return 0;
}
