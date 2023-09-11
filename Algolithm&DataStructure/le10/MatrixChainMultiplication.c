#include <stdio.h>
#define INF 100000
#define MAT_MAX 100

typedef struct {
  int r;
  int c;
} Matrix;

int min(int x, int y){
  return x > y ? y : x;
}

void matrixChainOrder(int m[MAT_MAX+1][MAT_MAX+1], int *p, int n){
  int i, j, k, l, q;
  for(i = 1; i <= n; i++) m[i][i] = 0;
  for(l = 2; l <= n; l++){
    for(i = 1; i <= n-l+1; i++){
      j = i+l-1;
      m[i][j] = INF;
      for(k = i; k <= j-1; k++){
	q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
	m[i][j] = min(m[i][j], q);
      }
    }
  }
  printf("%d\n",m[i-1][j]);
}

int main(){
  int i, j, n, m[MAT_MAX+1][MAT_MAX+1], p[MAT_MAX+1];
  Matrix M[MAT_MAX+1];

  scanf("%d",&n);
  for(i = 1; i <= n; i++){
    scanf("%d %d",&M[i].r, &M[i].c);
    p[i] = M[i].c;
    if( i == 1 ) p[0] = M[i].r;
  }
  matrixChainOrder(m, p, n);
  return 0;
}
