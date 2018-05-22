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
	
}
