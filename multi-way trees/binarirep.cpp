#include<stdio.h>
#include<stdlib.h>
#define COUNT 10


struct Node {
	int data;
	struct Node* next;
	struct Node* child;
};

//Crearea unui nod nou
Node* newNode(int data) {
	Node *newNode = new Node;
	newNode->next = newNode->child = NULL;
	newNode->data = data;
	return newNode;
}

Node *addSibling(Node *n, int data)
{
	if (n == NULL)
		return NULL;
	while (n->next)
		n = n->next;
	return (n->next = newNode(data));
}

Node *addChild(Node * n, int data)
{
	if (n == NULL)
		return NULL;
	if (n->child)
		return addSibling(n->child, data);
	else
		return (n->child = newNode(data));
}

void traverseTree(Node * root)
{
	if (root == NULL)
		return;

	while (root)
	{
		printf_s("%d ",root->data);
		if (root->child)
			traverseTree(root->child);
		root = root->next;
	}
}

void print2DUtil(Node *root, int space)
{
	if (root == NULL)
		return;
	space += COUNT;
	print2DUtil(root->next, space);

	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	printf("%d\n", root->data);
	print2DUtil(root->child, space);
}

void createNode(int parent[], int i, Node *created[], Node **root)
{

	if (created[i] != NULL)
		return;
	created[i] = newNode(i);
	if (parent[i] == -1)
	{
		*root = created[i];
		return;
	}

	if (created[parent[i]] == NULL)
		createNode(parent, parent[i], created, root);


	Node *p = created[parent[i]];

	if (p->next == NULL)
		p->next = created[i];
	else 
		p->child = created[i];
}

Node *createTree(int parent[], int n)
{
	
	Node *created[9];
	for (int i = 0; i < n; i++)
		created[i] = NULL;

	Node *root = NULL;
	for (int i = 0; i < n; i++)
		createNode(parent, i, created, &root);

	return root;
}

int main() {

	Node* root = newNode(7);
	Node* n1 = addChild(root, 2);
	Node* n2 = addChild(root, 5);
	Node* n3 = addChild(root, 6);
	Node* n4 = addChild(n1,1);
	Node* n5 = addChild(n1,4);
	Node* n6 = addChild(n1,9);
	Node* n7 = addChild(n2,3);
	Node* n8 = addChild(n2,8);
	/*int v[] = { 2, 7, 5, 2, 7, 7,-1,5,2 };
	int n = 9;
	Node* root = createTree(v, n);*/

	print2DUtil(root,5);
	getchar();




}