#include <stdio.h>
#define n 10000
#define q 500

int *linearSearch(int, int *, int);

int main(){
  int S[n], T[q], C=0, S_len, T_len, i, j=0, found_flag=0;

  scanf("%d",&S_len);
  for(i = 0; i < S_len; i++) scanf("%d",&S[i]);
  scanf("%d",&T_len);
  for(i = 0; i < T_len; i++) scanf("%d",&T[i]);

  for(i = 0; i < T_len; i++){
    if( linearSearch(S_len,S,T[i]) ){
      C++;
      found_flag = 1;
    }
  }

  if( found_flag == 0 ) printf("0\n");
  else printf("%d\n",C);
  
  return 0;
}

int *linearSearch(int len, int *X, int key){
  int i;

  for(i = 0; i < len; i++){
    if( X[i] == key ) return &X[i];
  }
  return NULL;
}
