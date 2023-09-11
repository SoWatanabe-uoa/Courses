#include <stdio.h>
#define DISCONNECT 0
#define CONNECT 1000
#define WHITE 2000
#define GRAY 3000
#define BLACK 4000
#define MAX 100
void push(int);
int pop(void);
void dfs();
void visit(int);
int next(int);
int n, G[MAX+1][MAX+1], stack[MAX+1], top = 1,
  d[MAX+1], f[MAX+1], color[MAX+1], time=0;

int main(){
  int vertex, degree, adj, i, j;
  for(i = 1; i <= MAX; i++){
    for(j = 1; j <= MAX; j++){
      G[i][j] = DISCONNECT;
    }
  }

  scanf("%d",&n);
  for(i = 1; i <= n; i++){
    scanf("%d %d",&vertex,&degree);
    color[vertex] = DISCONNECT;
    color[vertex] = WHITE;
    for(j = 1; j <= degree; j++){
      scanf("%d",&adj);
      G[vertex][adj] = CONNECT;
    }
  }
  dfs();

  for(i = 1; i <= n; i++) printf("%d %d %d\n",i,d[i],f[i]);
  
  return 0;
}

void dfs(){
  int i;
  for(i = 1; i <= n; i++){
    if( color[i] == WHITE ) visit(i);
  }
}

void visit(int r){
  int i;
  int u, v;
  
  push(r);
  color[r] = GRAY;
  d[r] = ++time;
  while( top != 1 ){ //Stack is not empty
    u = stack[top-1];
    v = next(u);
    if( v != DISCONNECT ){
      if( color[v] == WHITE ){
	push(v);
	color[v] = GRAY;
	d[v] = ++time;
      }
    }
    else{
      pop();
      color[u] = BLACK;
      f[u] = ++time;
    }
  } 
}

int next(int x){
  int i;
  for(i = 1; i <= n; i++){
    if( G[x][i] == CONNECT && color[i] == WHITE ) return i;
  }
  return DISCONNECT;
}

void push(int x){
  stack[top] = x;
  top++;
}

int pop(void){
  top--;
  return stack[top];
}
