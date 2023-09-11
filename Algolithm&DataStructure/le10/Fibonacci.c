#include <stdio.h>
#define FIBO_MAX 1000

int fibonacci(int *F, int n){
  if( n == 0 || n == 1 ) return F[n] = 1;
  if( F[n] != 0 ) return F[n];
  return F[n] = fibonacci(F, n-2) + fibonacci(F, n-1);
}

int main(){
  int n, i, F[FIBO_MAX];
  
  scanf("%d",&n);
  printf("%d\n",fibonacci(F, n) );
  return 0;
}
