#include <stdio.h>
#include <string.h>
#define LEN 100000

typedef struct pp{
  char name[100];
  int t;
}P;

void enqueue(P x);
P dequeue();

P Q[LEN];
int head=0, tail=0;

int main(){
  int elaps = 0;
  int i, q, n;
  P now_process;
  scanf("%d %d", &n, &q);

  for ( i = 0; i < n; i++){
    scanf("%s", Q[i].name);
    scanf("%d", &Q[i].t);
    tail++;
  }

  while( head != tail ){
    now_process = dequeue();
    if( now_process.t <= q ){
      elaps += now_process.t;
      printf("%s %d\n",now_process.name, elaps);
    }
    else{
      elaps += q;
      now_process.t -= q;
      enqueue( now_process );
    }
  }
  
  return 0;
}

void enqueue(P x){
  int next = (tail+1)%LEN;
  
  strcpy( Q[tail].name, x.name );
  Q[tail].t = x.t;
  tail = next;
}

P dequeue(){
  P now_process;

  strcpy( now_process.name, Q[head].name);
  now_process.t = Q[head].t;
  head = (head+1)%LEN;
  return now_process;
}
