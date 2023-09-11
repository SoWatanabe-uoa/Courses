#include <stdio.h>
#define MAX 100
#define WHITE 3000
#define BLACK 3001
#define INF 3002
#define NIL -1

int prim(int);
int d[MAX+1], G[MAX+1][MAX+1];

int main(){
  int n, i, j;

  scanf("%d",&n);
  for(i = 1; i <= n; i++){
    for(j = 1; j <= n; j++){
      scanf("%d",&G[i][j]);
    }
  }
  printf("%d\n",prim(n) );
  return 0;
}

int prim(int n){
  int parent[n+1], color[n+1], mincost, weight_sum=0, u, v, i=0, j;
  
  for(i = 1; i <= n; i++){
      d[i] = INF;
      parent[i] = NIL;
      color[i] = WHITE;
  }
  d[1] = 0;

  while( 1 ){
    mincost = INF;
    for(i = 1; i <= n; i++){
      if( color[i] != BLACK && d[i] < mincost ){
	mincost = d[i];
	u = i;
      }
    }
    if( mincost == INF ) break;
    color[u] = BLACK;
    for(j = 1; j <= n; j++){
      if( G[u][j] != NIL ){
	v = j;
	if( color[v] != BLACK && G[u][v] < d[v] ){
	  parent[v] = u;
	  d[v] = G[u][v];
	}
      }
    }
  }
  for(i = 1; i <= n; i++) weight_sum += d[i];
  return weight_sum;
}


