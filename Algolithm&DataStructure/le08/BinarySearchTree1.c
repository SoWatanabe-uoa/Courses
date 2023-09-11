#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
  struct node *right;
  struct node *left;
  struct node *parent;
  int key;
};
typedef struct node *NodePointer;

NodePointer root = NULL;

NodePointer make_1node(int, NodePointer);
void insert(int);
void inorder(NodePointer);
void preorder(NodePointer);

int main(){
  int command_num, key, i;
  char command[10];

  scanf("%d",&command_num);
  for(i = 1; i <= command_num; i++){
    scanf("%s",command);
    if( strcmp(command,"print") == 0 ){
      inorder(root);
      printf("\n");
      preorder(root);
      printf("\n");
    }
    else if( strcmp(command,"insert") == 0 ){
      scanf("%d",&key);
      insert(key);
    }
  }
  
  return 0;
}

void insert(int key){
  NodePointer x=root, y=NULL;

  while( x != NULL ){
    y = x;
    if( key < x->key ) x = x->left;
    else x = x->right;
  }
  if( y == NULL ) root = make_1node(key, NULL); //Tree is empty
  else if( key < y->key ) y->left = make_1node(key, y);
  else y->right = make_1node(key, y);
}

NodePointer make_1node(int key, NodePointer parent){
  NodePointer newnode;
  newnode = (NodePointer)malloc( sizeof(struct node) );
  newnode->parent = parent;
  newnode->right = NULL;
  newnode->left = NULL;
  newnode->key = key;
  return newnode;
}

void inorder(NodePointer x){
  if( x != NULL ){
    inorder(x->left);
    printf(" %d",x->key);
    inorder(x->right);
  }
}

void preorder(NodePointer x){
  if( x != NULL ){
    printf(" %d",x->key);
    preorder(x->left);
    preorder(x->right);
  }
}
