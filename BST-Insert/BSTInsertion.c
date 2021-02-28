/*
 ============================================================================
 Name        : BST-15.c
 Author      : CodeSTACK
 Version     : v0.1
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

// WAP a BST using C program

#include <stdio.h>
#include <stdlib.h>

struct node
{
    /* data */
    int key;
    struct node *left, *right;
};
// Create a new BST node

struct node* newNode(int item)
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp -> key = item;
    temp -> left = temp -> right =NULL;
    return temp;
};
// Travelsal in BST

void inorder(struct node* root){
    if (root != NULL){
        inorder(root -> left);
        printf("%d \n", root -> key);
        inorder(root -> right);
    }

}
// Insert a new node with given key in BST

struct node* insert(struct node* node, int key){
    // If tree is empty, return a new node
    if (node == NULL)
        return newNode(key);
    // Otherwise recur down the tree
    if (key < node -> key)
        node -> left = insert(node -> left, key);
    else if (key > node -> key)
        node -> right = insert(node -> right, key);
    // Return the (unchanged) node pointer
    return node;
}
// Main() function

int main(){
    struct node* root = NULL;
    int val[8],i;
    for( i = 0; i < 8; i++){
    	printf("\nEnter value to be entered:");
    	scanf("%d",&val[i]);

    	root = insert(root,val[i]);
    }
    //Print inoder traversal of the BST
    inorder(root);
    return 0;
}
