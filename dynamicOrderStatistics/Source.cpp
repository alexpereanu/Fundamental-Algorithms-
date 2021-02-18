#include <stdlib.h>
#include <stdio.h>
#include "Profiler.h"
#define COUNT 6

Profiler profiler("StatisticiDinamiceDeOrdine");

typedef struct node {

	int data;
	struct node* left;
	struct node* right;
	int size;
};

struct node* newNode(int data) {

	struct node* node = (struct node*)malloc(sizeof(struct node));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	node->size = 0;

	return node;
}

int maxim(int a, int b){
	return (a > b) ? a : b;
}

struct node* buildBST(int arr[], int left, int right) {

	if (left > right)
		return NULL;
	int mid = (left + right) / 2;
	struct node* root = newNode(arr[mid]);
	root->left = buildBST(arr, left, mid - 1);
	root->right = buildBST(arr, mid + 1, right);
	return root;
}

void preOrder(struct node* node) {
	
	
	if (node != NULL)
	{
		printf("%d ", node->data);
		preOrder(node->left);
		preOrder(node->right);
	}
	
}

void prettyPrint(node* root, int space) {

	if (root == NULL)
		return;
	space += COUNT;
	prettyPrint(root->right, space);
	printf_s("\n");
	for (int i = COUNT; i < space; i++)
		printf_s(" ");
	printf("%d\n", root->data);

	prettyPrint(root->left, space);

	
}
int height(struct node *N);

int getBalance(struct node *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

int height(struct node *N)
{
	if (N == NULL)
		return 0;
	return N->size;
}

struct node *leftRotate(struct node *x)
{
	struct node *y = x->right;
	struct node *T2 = y->left;

	y->left = x;
	x->right = T2;

	x->size = maxim(height(x->left), height(x->right)) + 1;
	y->size = maxim(height(y->left), height(y->right)) + 1;

	return y;
}

struct node *rightRotate(struct node *y)
{
	struct node *x = y->left;
	struct node *T2 = x->right;

	x->right = y;
	y->left = T2;

	y->size = maxim(height(y->left), height(y->right)) + 1;
	x->size = maxim(height(x->left), height(x->right)) + 1;

	return x;
}

struct node* Insert(struct node* node, int key)
{
	if (node == NULL)
		return (newNode(key));

	if (key < node->data)
		node->left = Insert(node->left, key);
	else if (key > node->data)
		node->right = Insert(node->right, key);
	else 
		return node;

	node->size = 1 + maxim(height(node->left),
		height(node->right));

	int balance = getBalance(node);

	if (balance > 1 && key < node->left->data)
		return rightRotate(node);

	if (balance < -1 && key > node->right->data)
		return leftRotate(node);

	if (balance > 1 && key > node->left->data)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	if (balance < -1 && key < node->right->data)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	return node;
}

struct node* insert(struct node* node, int key) {

	if (node == NULL) 
		return newNode(key);
	if (key < node->data)
		node->left = insert(node->left, key);
	else if (key > node->data)
		node->right = insert(node->right, key);

	return node;
}

void inorder(struct node* root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}

}

int osSELECT(struct node* root, int k, int n) {

	int ret = -1;
	profiler.countOperation("OS-SELECT", n);
	if (root)
	{
		struct node* aux = root;
		profiler.countOperation("OS-SELECT", n);
		while (aux)
		{
			if ((aux->size + 1) == k)
			{
				ret = aux->data;
				profiler.countOperation("OS-SELECT", n,2);
				break;
			}
			else if (k > aux->size )
			{
				k = k - (aux->size + 1);
				aux = aux->right;
				profiler.countOperation("OS-SELECT", n,3);
			}
			else
				aux = aux->left;
			profiler.countOperation("OS-SELECT", n);
		}
	}

	return ret;
}
struct node * minValue(struct node* node,int n)
{
	struct node* current = node;

	profiler.countOperation("OS-DELETE", n);

	while (current->left != NULL)
	{
		current = current->left;
		profiler.countOperation("OS-DELETE", n);
	}

	return current;
}

struct node* osDELETE(struct node* root, int key,int n)
{
	
	if (root == NULL)
	{
		return root;
		profiler.countOperation("OS-DELETE", n);
	}

	if (key < root->data) {

		root->left = osDELETE(root->left, key,n);

		profiler.countOperation("OS-DELETE", n,2);
	}
	else if (key > root->data) {

		root->right = osDELETE(root->right, key, n);
		profiler.countOperation("OS-DELETE", n,2);
	}
	else
	{
		if (root->left == NULL && root->right == NULL)
		{	
			profiler.countOperation("OS-DELETE", n,4);
			delete(root);
			root = NULL;
		}
		if (root->left == NULL)
		{
			profiler.countOperation("OS-DELETE", n,5);
			struct node *temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL)
		{
			profiler.countOperation("OS-DELETE", n,5);
			struct node *temp = root->left;
			free(root);
			return temp;
		}

		struct node* temp = minValue(root->right,n);
		root->data = temp->data;
		root->right = osDELETE(root->right, temp->data,n);
		profiler.countOperation("OS-DELETE", n,4);
	}
	//root->size--;
	return root;
}

void countChild(struct node* node, struct node* node2)
{
	if (node2 == NULL)
		return;
	if (node == NULL)
		return;
	if (node2->left != NULL)
		node->size++;
	if (node2->right != NULL)
		node->size++;
	countChild(node, node2->left);
	countChild(node, node2->right);
	return;
}

void addChild(struct node* node)
{
	if (node == NULL)
		return;
	node->size = 0;
	countChild(node, node);
	addChild(node->left);
	addChild(node->right);
}
int main() {

	/*int arr[] = { 2,3,8,9,-1};
	int n = sizeof(arr) / sizeof(int);
	struct node* root = buildBST(arr, 0, n - 1);
	printf_s("Preordine: ");
	preOrder(root);
	root = insert(root, 123);
	printf_s("\nINORDER:\n");
	inorder(root);
	int x = osSELECT(root, 2);
	printf_s("Elementul al 2 lea cel mai mic, %d\n",x);
	root = osDELETE(root, 8);
	printf_s("\nPretty print: ");
	prettyPrint(root, COUNT);
	getchar();*/

	int n, i, j;
	int arr[10001];
	for (n = 100; n < 10000; n += 100) {
		for (i = 0; i < 5; i++) {
			FillRandomArray(arr,n,-20000, 20000, true, 1);
			struct node* root = buildBST(arr, 0, n - 1);
			addChild(root);
			for (j = 0; j < 50; j++)
			{
				osSELECT(root, j, n);
				int nr = rand() % n;
				osDELETE(root, nr, n);
			}

		}
	
	}
	profiler.divideValues("OS-SELECT", 5);
	profiler.divideValues("OS-DELETE", 5);
	profiler.createGroup("StatisticiDinamiceDeOrdine", "OS-SELECT", "OS-DELETE");
	profiler.showReport();
	getchar();


}