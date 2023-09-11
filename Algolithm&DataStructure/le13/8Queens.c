#include <stdio.h>
#define NOT_FREE -1
#define FREE -2
#define EXIST -3
#define NOT_EXIST -4
#define N 8
void putQueen(int);
void printBoard();
int col[N], row[N], dpos[2*N-1], dneg[2*N-1], Board[N][N];

int main(){
  int k, r, c, i, j;
  for(i = 0; i < N; i++){
      col[i] = FREE;
      row[i] = FREE;
  }
  for(i = 0; i < 2*N-1; i++){
      dpos[i] = FREE;
      dneg[i] = FREE;
  }
  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++) Board[i][j] = NOT_EXIST;
  }

  scanf("%d",&k);
  for(i = 0; i < k; i++){
    scanf("%d %d",&r, &c);
    Board[r][c] = EXIST;
  }
  putQueen(0);
  return 0;
}

void putQueen(int i){
  int j;
  if( i == N ){
    printBoard();
    return;
  }
  for(j = 0; j < N; j++){
    if( col[j] == NOT_FREE || dpos[i+j] == NOT_FREE ||
	dneg[i-j+N-1] == NOT_FREE ) continue;
    //put a queen at (i,j)
    row[i] = j;
    col[j] = dpos[i+j] = dneg[i-j+N-1] = NOT_FREE;
    //try the next row
    putQueen(i+1);
    //remove the queen at (i,j) for backtracking
    col[j] = dpos[i+j] = dneg[i-j+N-1] = FREE;
  }
}

void printBoard(){
  int i, j;
  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      if( Board[i][j] == EXIST && row[i] != j ) return;
    }
  }
  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      if( row[i] == j ) printf("Q");
      else printf(".");
    }
    printf("\n");
  }
}
