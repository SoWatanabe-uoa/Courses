#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int main(){
  int G[MAX+1][MAX+1], n, vertex, degree, adj, i, j;
  for(i = 1; i <= MAX; i++){
    for(j = 1; j <= MAX; j++){
      G[i][j] = 0;
    }
  }

  scanf("%d",&n);
  for(i = 1; i <= n; i++){
    scanf("%d %d",&vertex,&degree);
    for(j = 1; j <= degree; j++){
      scanf("%d",&adj);
      G[vertex][adj] = 1;
    }
  }

  for(i = 1; i <= n; i++){
    for(j = 1; j <= n; j++){
      printf("%d",G[i][j]);
      if( j != n ) printf(" ");
    }
    printf("\n");
  }
  
  return 0;
}
