#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define n 20
#define q 200

int solve(int, int);

int A_len, A[n];

int main(){
  int M[q], M_len, i;

  scanf("%d",&A_len);
  for(i = 0; i < A_len; i++) scanf("%d",&A[i]);
  scanf("%d",&M_len);
  for(i = 0; i < M_len; i++) scanf("%d",&M[i]);

  for(i = 0; i < M_len; i++){
    if( solve( M[i], 0 ) ) printf("yes\n");
    else printf("no\n");
  }
  
  return 0;
}

int solve(int m, int i){
  if( m == 0 ) return TRUE;
  if( i == A_len ) return FALSE;
  return solve( m, i+1 ) || solve( m-A[i], i+1 );
}
