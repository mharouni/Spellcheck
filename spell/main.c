#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node  Node;
struct Node
{
	char * word;
	struct Node * left, *right;
	int height;
};
Node * newnode(char []);// creates a new node that contains the string given as argument
Node * Search(Node *root,char word[]);//takes the root node of the tree and traverses through the tree searching for the node that contains the word given as argument utilizing the BST properties that the right node is greater and the left node is smaller
Node * insert(Node *,  char word []);//takes the root node of the tree as an argument inserts a node that contains the word given as argument to the tree and self-balance the tree using AVL algorithm and then return the new root node
int height( Node *N);//returns the height if the given node from the leaf with the leaves height is 1
Node *leftRotate(Node *x);//performs left rotation to neutralize the right bias
Node *rightRotate(Node *y);//performs the right rotation to neutralize the left bias
int getBalance(Node *N); //returns the difference between the heights of the branches the tree (subtree) with root N given as argument
//void readf(Node * N, Node * root);
void split(Node * N);//function that examines a sentence entered by the user against a balanced tree with the node of the tree given as an argument
//void preOrder(struct Node *root);
Node * maxValueNode(Node *node);//functions that returns the node with the max value according to (strcmp) in a tree or a subtree with the argument considered the root node
Node * minValueNode(Node *node);//functions that returns the node with the least value according to (strcmp) in a tree or a subtree with the argument considered the root node
Node * Predecessor(Node * root, Node * x);//function that returns the inorder predecessor of a given node x
Node * Successor(Node *root, Node *x);//function that returns the inorder successor of a given node x
int main(int argc, const char * argv[]) {
	
		FILE *f;
	char x[10000][27];//array of strings
	int i=0;//counter that keeps track of the words in the file
	if((f = fopen("test.txt","r"))){// checks the validity of the file
		printf("Reading\n");
		while(!feof(f)){
			fgets(x[i],27,f);
			
			i++;
		}
		Node * root = NULL;//root node declared as the root of the AVL tree
		int y;
		for( y=0;y<i;y++)
		{
		
			if(y<i-1)
			{
				x[y][strlen(x[y])-2]='\0';//handles the new line in the file
			}
			
			root = insert(root, x[y]);
		}
		printf("Insertion Completed\nAVL Tree\n");
		printf("the height of the tree is %d \n",height(root));
		printf("Root Node contains (%s)\n",root->word);
		split(root);
		
		
		//preOrder(root);
	}
	


//		root = insert(root, "zurich");
//		root = insert(root, "fade");
//	root = insert(root, "amer");
//	root = insert(root, "asf");
//
//	root = insert(root, "sdf");
//	root = insert(root, "fgh");
//	root = insert(root, "dfg");
//	root = insert(root, "ghj");
//
//
//	printf("%s\n",root->left->word);
//	printf("%s\n",root->word);
//
//		printf("%s\n",root->right->word);
//
//
//	printf("Hello, World!\n");
//	Node *s;
//	s = Search(root, "hik");
//	preOrder(root);
	fclose(f);

	return 0;
}
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
Node * Search (Node *n, char word[])
{
	
	if ( strcmp(n->word, word) == 0)
	{
		
		printf("The word is correct \n Optional ");
		
		return n;
	}
	
	
		//printf("Found!!\n");
		
	
	if(strcmp(n->word, word) < 0)
	{
	//printf("Moved Right\n");
		if(height(n->right) == 0)
		{
			printf("Word is not in the Tree\n");
			return  n;
		}
		else {
		n = n->right;
		return Search(n, word);
		}
	}
		//printf("Moved left\n");
		if(height(n->left) == 0)
		{
			printf("Not Found\n");
			return  n;
		}
	
			n = n->left;
			return Search(n, word);
	
	
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
	Node *T2 = x->right;
	x->right = y;
	y->left = T2;
	y->height = max(height(y->left), height(y->right))+1; x->height = max(height(x->left), height(x->right))+1; // Return new root
	return x;
}
Node *leftRotate(Node *x)
{
	Node *y = x->right;
	Node *T2 = y->left;
	y->left = x;
	x->right = T2;
	x->height = max(height(x->left), height(x->right))+1; y->height = max(height(y->left), height(y->right))+1;
	return y; }
Node * insert (Node * n, char word [])
{
	if(n == NULL)
	{
		//printf("Inserted\n");
		return newnode(word);
	}
	else if (strcmp(n->word,word) >0)
		{
			//printf("Moved lft\n");
			n->left = insert(n->left,word);
		}
	else if (strcmp(n->word, word ) <0)
	{
	//	printf("Moved right\n");
		n->right = insert(n->right, word);
	}
	else if (strcmp(word, n->word) == 0){
		//printf("duplicate\n");
		return n ;
	}
	else{
		//printf("Error: detected\n");
	}
	n->height = 1 + max(height(n->left), height(n->right));
	int balance = getBalance(n);
	if (balance > 1 && strcmp(word, n ->left->word )  <0)
	{
		//printf("LL\n");
		return rightRotate(n);
	}
	if (balance < -1 && strcmp(word, n ->right->word ) > 0)
	{
		//printf("rr\n");
		return leftRotate(n);
	}
	if (balance > 1 && strcmp(word, n ->left->word ) > 0)
	{
		//printf("lr\n");
		n->left =  leftRotate(n->left);
		return rightRotate(n);
	}
	if (balance < -1 && strcmp(word, n ->right->word ) <0)
	{
		//printf("rl\n");
		n->right = rightRotate(n->right);
		return leftRotate(n);
	}
	return n;
}
void  split(Node * N){
	char str[1000],*part[100];
	int i=0;
	
	printf("Enter Sentence to check ");
	scanf("%[^\n]s",str);
	
	char *token = strtok(str, " ");
	
	
	while (token != NULL)
	{
		
		part[i] = token;
		if(part[i][1]!='\0')
		{
			Node *s;
		s=Search (N, part[i]);
		printf("Suggestions: (%s) \t (%s)\n",Predecessor(N,s)->word, Successor(N, s)->word );
		i++;
		token = strtok(NULL, " ");
		}
	}
}
void preOrder(struct Node *root)
{
	if(root != NULL)
	{
		printf("%s ", root->word);
		preOrder(root->left);
		preOrder(root->right);
	}
}

Node * minValueNode(Node* node)
{
	if (!node)
		return NULL;
	Node* current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}
Node * maxValueNode(Node *node)
{
	if (!node)
		return NULL;
	Node* current = node;
	while (current->right != NULL)
		current = current->right;
	return current;
}
Node * Predecessor(Node * root, Node * x)
{
	if (!x)
		return NULL;
		if(x->left)
			return maxValueNode(x->left);
	Node *p = NULL;
	while (root != NULL) {
		if (strcmp(x->word, root->word) >0)
		{
			p=root;
			root=root->right;
		}
		else if (strcmp(x->word, root->word) < 0)
		{
			root = root->left;
		}
		else break;
		
	}
	return p;
}
Node * Successor(Node *root, Node *x)
{
	if (x->right != NULL)
		return minValueNode(x->right);
	Node *s = NULL;
	while (root!= NULL)
	{
		if(strcmp(x->word,root->word) < 0)
		{
			s = root;
			root = root->left;
		}
		else if (strcmp(x->word,root->word) > 0)
			root=root->right;
		else break;
			
	}
	return s;
}
