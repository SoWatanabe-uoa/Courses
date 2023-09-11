#include <stdio.h>
#include <stdlib.h>

struct node{
  struct node *parent;
  struct node **children;
  int id;
  int depth;
  int k;
};
typedef struct node *NodePointer;

struct node make_1node(int, int, NodePointer);
void findDepth(NodePointer, int);
void nodeJudge(NodePointer);

int main(){
  int n, id, k, c_id, i, j;
  NodePointer T;
  
  scanf("%d",&n);
  T = (NodePointer)malloc( n * sizeof( struct node ) );

  for(i = 0; i < n; i++) T[i].parent = NULL;
  
  for(i = 0; i < n; i++){
    scanf("%d %d",&id, &k);
    T[id] = make_1node(id, k, T[id].parent);
    for(j = 0; j < k; j++){
      scanf("%d",&c_id);
      T[id].children[j] = &(T[c_id]);
      T[c_id].parent = &(T[id]);
    }
  }

  for(i = 0; i < n; i++){
    if( T[i].parent == NULL ){
      findDepth(&(T[i]), 0);
      break;
    }
  }
  
  for(i = 0; i < n; i++){    
    printf("node %d: ",T[i].id);
    if( T[i].parent == NULL ) printf("parent = -1, ");
    else printf("parent = %d, ",T[i].parent->id);
    printf("depth = %d, ",T[i].depth);
    nodeJudge(&T[i]);
    for(j = 0;; j++){
      if( T[i].children == NULL ) break;
      printf("%d",T[i].children[j]->id);
      if( j == T[i].k - 1 ) break;
      printf(", ");
    }
    printf("]\n");
  }
  free(T);
  return 0;
}

struct node make_1node(int id, int k, NodePointer parent){
  struct node temp;
  temp.id = id;
  temp.k = k;
  if( k == 0 ) temp.children = NULL;
  else temp.children = (NodePointer *)malloc( sizeof( NodePointer ) * k );
  temp.parent = parent;
  return temp;
}
  
void findDepth(NodePointer x, int depth){
  int i;
  x->depth = depth;
  if( x->children != NULL ){
    for(i = 0; i < x->k ; i++) findDepth( x->children[i], depth+1);
  }
}

void nodeJudge(NodePointer x){
  if( x->parent == NULL ) printf("root, [");
  else if( x->children == NULL ) printf("leaf, [");
  else printf("internal node, [");
}
