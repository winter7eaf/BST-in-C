#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

typedef struct _Node{
       int data;
       Node * leftNode;
       Node * rightNode;
} Node;

//function to create a new node
Node * createNewNode(int value){
              Node* newLeafNode = (Node*)malloc(sizeof (Node));
              newLeafNode->data = value;
              newLeafNode->leftNode = NULL;
              newLeafNode->rightNode = NULL;
              return newLeafNode;
}

Node * addNode(Node * root, int value){
       Node* currentNode = root; 
       Node* parentNode; 
       Node * newNode = createNewNode(value);
       
       //case 1: the tree is empty and case 5: tree reaches NULL
       if (root == NULL){
              //when the tree is empty
              return newNode;
       }
       while (currentNode != NULL){
              parentNode = currentNode;
              if (value == currentNode->data){
                     //case 2: duplicate node, not add anything and return NULL
                     free(newNode);
                     return NULL;
              }else if(value < currentNode->data){
                     //case 3: value is smaller than the root node
                     currentNode = currentNode->rightNode;
              }else{
                     //case 4: the value is bigger than the root node
                     currentNode = currentNode->leftNode;
              }
              
       }
       //assign the pointer from parent
       if (value < parentNode->data){
              parentNode->rightNode = newNode;
       }else{
              parentNode->leftNode = newNode;
       }

       return newNode;
};

//function to find the min node
int findMinNode(Node * root){

       while (root->leftNode != NULL){
              root = root->leftNode;
       }

       return root->data;
}

Node * removeNode(Node * root, int value){
       //case 1: empty tree, nothing to remove
       if (root == NULL){
              return root;
       }
       //case 2: the given value is bigger than the root node, so it is in the right
       else if (root->data > value){
              root->rightNode = removeNode(root->rightNode, value);
       }
       //case 3: the value is smaller than the root, so it is in the left
       else if (root->data < value){
              root->leftNode = removeNode(root->leftNode, value);
       }
       //case 4: value same as root, delete the root node
       else if (root->data == value){
              //case 1: leaf node
              if (root->leftNode == NULL && root->rightNode == NULL){
                     free(root);
                     return NULL;
              }
              /*case 2: root with left children, 
              replace root and delete the old root*/
              else if (root->rightNode == NULL){
                     Node* newRoot = root->leftNode;
                     free(root);
                     return newRoot;
              }
              /*case 3: root with right children
              replace root and delete the old root*/
              else if (root->leftNode == NULL){
                     Node* newRoot = root->rightNode;
                     free(root);
                     return newRoot;
              }
              /*case 4: root with left and right children
              *find min value in right subtree, replace, 
              *call the fuction with min node to remove node*/
              else{
                     int minNode = findMinNode(root->rightNode);
                     root->data = minNode;
                     root->rightNode = removeNode(root->rightNode, minNode);
              }
       }
       return root;
};

void displaySubtree(Node * N){
       if(N == NULL){
              return;
       }
       //prints values of the right subtree 
       displaySubtree(N->rightNode);
       //prints value of the node
       printf("%d\n",N->data);
       //prints values of the left subtree
       displaySubtree(N->leftNode);
};

int numberLeaves(Node * N){
       //case 1: if empty tree or not in presented in tree
       if (N == NULL){
              return 0;
       }
       //case 2: if it is a leaf
       if (N->leftNode == NULL && N->rightNode == NULL){
              return 1;
       }
       //case 3: when it is a root node
       else{
              return numberLeaves(N->leftNode) + numberLeaves(N->rightNode);
       }
};

Node * removeSubtree(Node * root, int value){
       if (root == NULL){
              return root;
       }
       Node* nodeToDel = NULL;
       /*case 1: found the root wanted to delete, 
       remove the left subtree and the right subtree then the root*/
       if(value == root->data){
              if (root->leftNode != NULL){
                     removeSubtree(root->leftNode, root->leftNode->data);
              }
              if (root->rightNode != NULL){
                     removeSubtree(root->rightNode, root->rightNode->data);
              }
              free(root);
       }else{
              //case 1: the value is smaller than the root given, go into the right subtree
              if(value < root->data){
                     nodeToDel = removeSubtree(root->rightNode, value);
              }
              //case 2: the value is bigger than the root, go into the left subtree
              else if(value > root->data){
                     nodeToDel = removeSubtree(root->leftNode, value);
              }

              //empty the pointer of parent node
              if(root->leftNode == nodeToDel){
                     root->leftNode = NULL;
              }else if(root->rightNode == nodeToDel){
                     root->rightNode = NULL;
              }
       }
       return root;
};

int nodeDepth (Node * R, Node * N){
       //case 1: empty tree, or null node
       if(R == NULL || N == NULL){
              return -1;
       }
       //case 2: the root is the node
       if(N->data == R->data){
              return 0;
       }
       int depth = -1;
       /*case 3:
       *a) the node is in the left subtree
       *b) the node is in the right subtree
       */  
       if((depth = nodeDepth(R->leftNode, N)) >= 0
       || (depth = nodeDepth(R->rightNode, N)) >= 0){
              return depth + 1;
       }
       //case 4: when the node does not belong to the root
       return depth;
}; 

