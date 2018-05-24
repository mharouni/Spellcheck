//
//  sp.c
//  Spellcheck
//
//  Created by Mohamed Harouni on 5/21/18.
//  Copyright © 2018 Mohamed Harouni. All rights reserved.
//

#include "sp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Node * newnode(char word [])
{
	Node *n;
	n=(Node*)malloc(sizeof(Node));
	n->word = word;
	n->left = NULL;
	n->right= NULL;
	n->height = 1;
	return n;
}
void initialiseBST(BST * b)
{
	b->root=NULL;
}
Node * search (Node * root, char word[])
{
	Node * n;
	n=root;
	if (n==NULL)
	{
		printf("Not Found \n");
		return NULL;
	}
	else if(strcmp(n->word, word)==0)
	{
		printf("Found!!\n");
		return n;
	}
	else if(strcmp(n->word, word) == -1)
	{
		printf("Moved Right\n");
		n = (n->right);
		search(n, word);
	}
	else if(strcmp(n->word, word) == 1)
	{
		
		n = (n->left);
		search(n, word);
	}else {
		
		printf("Error: In Search BST");
		return NULL;
	}
	return NULL;
}
int height( Node *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}
int getBalance(Node *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}
int max(int x, int y)
{
	return (x > y)? x : y;
}
Node *rightRotate(Node *y)
{
	
	Node *x = y->left;
	Node *T = x->right;
	
	x->right = y;
	y->left = T;
	
	
	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;
	return x;
}

Node *leftRotate(Node *x)
{
	
	Node *y = x->right;
	Node *T = y->left;
	
	y->left = x;
	x->right = T;

	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	
	return y;
}
Node * insert (Node * root, char word [])
{
	Node *n =root;
	if(n == NULL)
	{
		return newnode(word);
	}
	else if (strcmp(n->word,word) == 1)
				n->left = insert(n->left,word);
	else if (strcmp(n->word, word ) == -1)
				n->right = insert(n->right, word);
	else if (strcmp(word, n->word) == 0)
	return n ;
	n->height = 1 + max(height(n->left),
						   height(n->right));
	
	int balance = getBalance(n);
	// If this node becomes unbalanced, then
	// there are 4 cases
	// Left Left Case
	
	
	if (balance > 1 && strcmp(word, n ->left->word ) == -1)// key<left
	{
		 printf("LR:");
		return rightRotate(n);
	}
	// Right Right Case
	if (balance < -1 && strcmp(word, n ->right->word ) == 1)// key >right
	{
		printf("RR:");
		return leftRotate(n);
	}
	// Left Right Case
	if (balance > 1 && strcmp(word, n ->left->word ) == 1)
	{
		 printf("LR:");
		n->left =  leftRotate(n->left);
		return rightRotate(n);
	}
	// Right Left Case
	if (balance < -1 && strcmp(word, n ->right->word ) == -1)
	{
		 printf("RL:");
		n->right = rightRotate(n->right);
		return leftRotate(n);
	}
	/* return the (unchanged) node pointer */
	return n;
}
	
	

