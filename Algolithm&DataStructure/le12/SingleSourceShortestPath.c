#include <stdio.h>
#define MAX 100
#define INF 1000000
#define DISCONNECT -1
#define BLACK -2
void initializeSingleSource(int);
void dijkstra(int G[MAX][MAX], int);

int d[MAX], pi[MAX];

int main(){
  int G[MAX][MAX], n, u, v, k, i, j;

  for(i = 0; i < MAX; i++){
    for(j = 0; j < MAX; j++) G[i][j] = DISCONNECT;
  }
  scanf("%d",&n);
  for(i = 0; i < n; i++){
    scanf("%d %d",&u,&k);
    for(j = 0; j < k; j++){
      scanf("%d",&v);
      scanf("%d",&G[u][v]);
    }
  }
  dijkstra( G, n );

  for(i = 0; i < n; i++) printf("%d %d\n",i,d[i]);
  return 0;
}

void initializeSingleSource(int n){
  int i;
  for(i = 0; i < n; i++){
    d[i] = INF;
    pi[i] = DISCONNECT;
  }
  d[0] = 0;
}

void dijkstra(int G[MAX][MAX], int n){
  int mincost, color[MAX], u, v, i, j;
  initializeSingleSource(n);
  while( 1 ){
    mincost = INF;
    for(i = 0; i < n; i++){
      if( color[i] != BLACK && d[i] < mincost ){
	mincost = d[i];
	u = i;
      }
    }
    if( mincost == INF ) break;
    color[u] = BLACK;
    for(j = 0; j < n; j++){
      if( G[u][j] != DISCONNECT ){
	v = j;
	if( color[v] != BLACK && d[u] + G[u][v] < d[v] ){
	  pi[v] = u;
	  d[v] = d[u] + G[u][v];
	}
      }
    }
  }
}

