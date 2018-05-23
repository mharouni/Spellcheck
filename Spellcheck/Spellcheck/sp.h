//
//  sp.h
//  Spellcheck
//
//  Created by Mohamed Harouni on 5/21/18.
//  Copyright © 2018 Mohamed Harouni. All rights reserved.
//

#ifndef sp_h
#define sp_h

#include <stdio.h>

typedef struct
{
	char * word;
	struct Node * left, *right;
} Node;
typedef struct {
	Node * root;
} BST;
Node * newnode(char []);
Node * Search(Node *root,char word[]);
void initializeBST(BST *);
Node * GetParent(Node * root, char word[]);
Node * insert(Node *,  char word []);




#endif /* sp_h */
