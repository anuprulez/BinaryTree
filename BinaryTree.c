#include<stdlib.h>
#include<stdio.h>

struct tree_el {
   int val;
   struct tree_el * right, * left;
};

typedef struct tree_el node;
int Size = 0;

//Inserts node to the binary tree
void insertNode(node ** tree, node * item)
{
    if((!*tree)){
       *tree = item;
       return;
    }
    if(item->val < (*tree)->val){
        insertNode(&(*tree)->left, item);
    }
    else if(item->val > (*tree)->val){
        insertNode(&(*tree)->right, item);
    }
}

//finds the size of the binary tree
int findSize(node * tree)
{
    int leftcounter, rightcounter;
    //printf("Inside findSize");
    if(tree->left){
        Size++;
        findSize(tree->left);
    }
    if(tree->right){
        Size++;
        findSize(tree->right);
    }
    return Size;
}

// InOrder Traversal
void InOrder(node * tree) {
   if(tree->left) InOrder(tree->left);
   printf("%d\n",tree->val);
   if(tree->right) InOrder(tree->right);
}

// PreOrder traversal
void PreOrder(node * tree) {
   printf("%d\n",tree->val);
   if(tree->left) PreOrder(tree->left);
   if(tree->right) PreOrder(tree->right);
}

// PostOrder traversal
void PostOrder(node * tree) {
   if(tree->left) PostOrder(tree->left);
   if(tree->right) PostOrder(tree->right);
   printf("%d\n",tree->val);
}

// Searches the node 
void Search(node * tree, int value)
{
    if(tree->val == value)
    {
        printf("Match found \n");
    }
    else if(tree->val < value)
    {
        if(tree->right)
        {
            Search(tree->right, value);
        }
        else
        {
            printf("Match not found \n");
        }
    }
    else if(tree->val > value)
    {
        if(tree->left)
        {
            Search(tree->left, value);
        }
        else
        {
            printf("Match not found \n");
        }
    }

}

int MaxDepth(node * tree)
{
    if(tree == NULL)
    {
        return 0;
    }
    else
    {
        int leftDepth = MaxDepth(tree->left);
        int rightDepth = MaxDepth(tree->right);
        
        if(leftDepth > rightDepth)
        {
            return (leftDepth+1);
        }
        else
        {
            return rightDepth+1;
        }
    }
}

//gets all the paths from root to leaf
void printPathsRecur(node * tree, int path[], int pathLen) { 
  if (tree==NULL) return;

  // append this node to the path array 
  path[pathLen] = tree->val; 
  pathLen++;

  // it's a leaf, so print the path that led to here 
  if (tree->left==NULL && tree->right==NULL) { 
    printArray(path, pathLen); 
  } 
  else { 
  // otherwise try both subtrees 
    printPathsRecur(tree->left, path, pathLen); 
    printPathsRecur(tree->right, path, pathLen); 
  } 
}

// Gets ancestors
void getNodeAncestors(node * tree, int ancestorPath[], int pathLength)
{
    if (tree==NULL) return;
    
    ancestorPath[pathLength] = tree->val;
    pathLength++;
    if(pathLength > 1)
    {
        printf("Ancestors:\n");
        printAncestors(ancestorPath, pathLength);
    }
    getNodeAncestors(tree->left, ancestorPath, pathLength);
    getNodeAncestors(tree->right, ancestorPath, pathLength);
}


// Utility that prints node's Ancestors 
void printAncestors(int ancestorArray[], int length) { 
  int i; 
  for (i=length-1; i>=0; i--) { 
    printf("%d ", ancestorArray[i]); 
  } 
  printf("\n"); 
} 

// Utility that prints out a path on a line. 
void printArray(int ints[], int len) { 
  int i; 
  for (i=0; i<len; i++) { 
    printf("%d ", ints[i]); 
  } 
  printf("\n"); 
} 
 

void main() {
   node * curr, * root;
   int i, number, max, counter;
   counter = 0;
   root = NULL;
   int path[1000];
   int ancestorPath[1000];

   for(i=1;i<=10;i++) {
      curr = (node *)malloc(sizeof(node));
      curr->left = curr->right = NULL;
      curr->val = rand()/10000000;
      insertNode(&root, curr);
   }
   printf("The binary tree is \n");
   InOrder(root); 
   
   printf("Preorder traversal \n");
   PreOrder(root);
   
   printf("Postorder traversal \n");
   PostOrder(root);
   
   int size = findSize(root) + 1;
   printf("The size binary tree is \n");
   printf("%d \n", size);
   
   printf("\nSearching for the node \nSearch Result: \n");
   Search(root, 118);
   
   printf("Maximum depth of the tree \n");
   int maxDepth = MaxDepth(root);
   printf("%d \n", maxDepth);
   
   printf("The paths are as follows: \n");
   printPathsRecur(root, path, 0); 
   
   
   printf("The Ancestors are as follows\n");
   getNodeAncestors(root, ancestorPath, 0);
} 
