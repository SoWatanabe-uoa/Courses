#include <stdio.h>
#include <stdlib.h>

struct node{
  struct node *left;
  struct node *right;
  struct node *parent;
  int id;
  int depth;
  int height;
  int deg;
};
typedef struct node *NodePointer;

void findDepth(NodePointer, int);
int findHeight(NodePointer);
void findDegree(NodePointer);
void nodeJudge(NodePointer);

int main(){
  int n, id, left_id, right_id, i, j;
  NodePointer T;

  scanf("%d",&n);
  T = (NodePointer)malloc( n * sizeof( struct node ) );
  for(i = 0; i < n; i++){
    T[i].parent = NULL;
    T[i].deg = 0;
  }

  for(i = 0; i < n; i++){
    scanf("%d %d %d",&id, &left_id, &right_id);
    T[id].id = id;
    if( left_id == -1 ) T[id].left = NULL;
    else{
      T[id].left = &T[left_id];
      T[id].left->parent = &T[id];
    }
    if( right_id == -1 ) T[id].right = NULL;
    else{
      T[id].right = &T[right_id];
      T[id].right->parent = &T[id];
    }
  }

  for(i = 0; i < n; i++){
    if( T[i].parent == NULL ){
      findDepth(&T[i], 0);
      break;
    }
  }

  for(i = 0; i < n; i++){
    T[i].height = findHeight(&T[i]);
    findDegree(&T[i]);
  }

  // Output
  for(i = 0; i < n; i++){    
    printf("node %d: ",T[i].id);
    if( T[i].parent == NULL ) printf("parent = -1, ");
    else printf("parent = %d, ",T[i].parent->id);
    printf("sibling = ");
    if( T[i].parent != NULL &&
	(T[i].parent->left != NULL && T[i].parent->right != NULL) ){
      if( T[i].parent->left != &T[i] ) printf("%d, ",T[i].parent->left->id);
      else printf("%d, ",T[i].parent->right->id);
    }
    else printf("-1, ");
    printf("degree = %d, ",T[i].deg);
    printf("depth = %d, ",T[i].depth);
    printf("height = %d, ",T[i].height);
    nodeJudge(&T[i]);
  }

  free(T);
  return 0;
}

void findDepth(NodePointer x, int depth){
  x->depth = depth;
  if( x->left != NULL ) findDepth( x->left, depth+1);
  if( x->right != NULL ) findDepth( x->right, depth+1);
}

int findHeight(NodePointer x){
  int h1=0, h2=0;
  if( x->left != NULL ) h1 = findHeight(x->left)+1;
  if( x->right != NULL ) h2 = findHeight(x->right)+1;
  return h1 > h2 ? h1 : h2;
}

void findDegree(NodePointer x){
  if( x->left != NULL ) x->deg++;
  if( x->right != NULL ) x-> deg++;
}

void nodeJudge(NodePointer x){
  if( x->parent == NULL ) printf("root\n");
  else if( x->left == NULL && x->right == NULL ) printf("leaf\n");
  else printf("internal node\n");
}
