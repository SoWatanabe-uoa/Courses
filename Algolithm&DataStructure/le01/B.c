#include <stdio.h>

int main(){
  int a, b, x; // a >= b
  /* There are "x" in this program
     in order to store the value of "a". */
  
  scanf("%d %d",&a,&b);
  if( a <= b ){
    x = a;
    a = b;
    b = x;
  }
  while( a%b ){
    x = a;
    a = b;
    b = x%b;
  }
  printf("%d\n",b);
  
  return 0;
}
