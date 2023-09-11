#include <stdio.h>
#define n 100000
#define q 50000

int *binarySearch(int, int *, int);

int main(){
  int S[n], T[q], C=0, S_len, T_len, i, j=0, found_flag=0;

  scanf("%d",&S_len);
  for(i = 0; i < S_len; i++) scanf("%d",&S[i]);
  scanf("%d",&T_len);
  for(i = 0; i < T_len; i++) scanf("%d",&T[i]);

  for(i = 0; i < T_len; i++){
    if( binarySearch(S_len,S,T[i]) ){
      C++;
      found_flag = 1;
    }
  }

  if( found_flag == 0 ) printf("0\n");
  else printf("%d\n",C);
  
  return 0;
}

int *binarySearch(int len, int *X, int key){
  int i, left=0, right=len, mid;

  while( left < right ){
    mid = (int)(left + right)/2;
    if( key == X[mid] ) return &X[mid];
    if( key > X[mid] ) left = mid+1;
    else if( key < X[mid] ) right = mid;
  }
  
  return NULL;
}
