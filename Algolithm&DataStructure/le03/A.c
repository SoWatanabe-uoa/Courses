#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define MAX_DIGIT 7

void push(int);
int pop(void);
int stack[MAX], top = 0;

int main(){
  int  x1, x2;
  char str[MAX_DIGIT];

  while( scanf("%s",str) != EOF ){
    if( str[0] == '+' ){
      x1 = pop();
      x2 = pop();
      push( x1+x2 );
    }
    else if( str[0] == '-' ){
      x1 = pop();
      x2 = pop();
      push( x2-x1 );
    }
    else if( str[0] == '*' ){
      x1 = pop();
      x2 = pop();
      push( x1*x2 );
    }
    else push( atoi(str) );
  }

  printf("%d\n",stack[0]);
  
  return 0;
}

void push(int x){
  stack[top] = x;
  top++;
}

int pop(void){
  top--;
  return stack[top];
}
