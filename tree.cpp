#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <math.h>

using namespace std;

struct tn{
	int data;
	tn* left;
	tn* right;
	tn* parent;
	tn(int d):data(d), left(0), right(0), parent(0){}
};

tn* root;

void clearTree(tn* node)
{
	if(node)
	{
		clearTree(node->left);
		clearTree(node->right);
//		printf("\nDeleting %d",node->data);
		delete node;
	}
}

void inorder(tn* node)
{
	if(node)
	{
		inorder(node->left);
		printf("%d ",node->data);
		inorder(node->right);
	}
}

void preorder(tn* node)
{
	if(node)
	{
		printf("%d ",node->data);
		preorder(node->left);
		preorder(node->right);
	}
}

void postorder(tn* node)
{
	if(node)
	{
		postorder(node->left);
		postorder(node->right);
		printf("%d ",node->data);
	}
}

int max(const int& a, const int& b)
{
	return (a>b)?a:b;
}

int height(tn* node)
{
	if(NULL == node)
		return 0;

	return max(height(node->left), height(node->right)) + 1; 
}

int diameter(tn* node)
{
	if(NULL == node)
		return 0;

	int l = height(node->left);
	int h = height(node->right);

	int dl = diameter(node->left);
	int dr = diameter(node->right);

	return max(l + h + 1, max(dl, dr));
}

void samelevel(tn* node)
{
	list<tn*> Q;
	if(NULL == node)
		return;

	Q.push_back(node);

	while(false == Q.empty())
	{
		tn* t = Q.front();
		Q.pop_front();
		printf("%d ",t->data);
		if(t->left)
			Q.push_back(t->left);

		if(t->right)
			Q.push_back(t->right);
	}
}

int checkHt(tn* node)
{
	if(NULL == node)
		return 0;

	int l = checkHt(node->left);
	if(-1 == l)
		return l;

	int r = checkHt(node->right);
	if(-1 == r)
		return r;

	int diff = l - r;
	if(abs(diff) > 1)
		return -1;
	else 
		return max(l,r) + 1;
}

bool isBalanced(tn* node)
{
	if(-1 == checkHt(node))
		return false;
	else
		return true;
}

void printlevel(tn* node, int level)
{
	if(NULL == node)
		return;
	
	if(1 == level)
		printf("%d ",node->data);
	else
	{
		printlevel(node->left, level -1);
		printlevel(node->right, level-1);
	}
}

tn* createMinSpTree(int* arr, int l, int r)
{
	if( r > l)
		return NULL;

	int m = (l+ r)/2;

	tn* node = new tn(m);

	node->left = createMinSpTree(arr, l, m-1);
	node->right= createMinSpTree(arr, m+1, r);

	return node;

}

tn* leftmost(tn* node)
{
	if(NULL == node)
		return NULL;

	while(node->left)
	{
		node = node->left;
	}
	return node;
}

tn* inorderSucc(tn* node)
{
	if(NULL == node)
		return NULL;

	if(node->right)
		return leftmost(node->right);

	tn* p = node->parent;
	tn* c = node;

	while(NULL != p && c != p->left)
	{
		c = p;
		p = c->parent;
	}

	return p;
}

bool isMatch(tn* t1, tn* t2)
{
	if(NULL == t1 && NULL == t2)
		return true;

	if(NULL == t1 || NULL == t2)
		return false;

	if(t1->data != t2->data)
		return false;

	return isMatch(t1->left, t2->left) && isMatch(t1->right, t2->right);
}

bool isSubTree(tn* t1, tn* t2)
{
	if(NULL == t1)
		return false;

	if(t1->data == t2->data)
		if( isMatch(t1, t2))
			return true;


	return isSubTree(t1->left, t2) || isSubTree(t1->right, t2);
}

bool containsTree(tn* t1, tn* t2)
{
	if(NULL == t2)
		return true;

	return isSubTree(t1, t2);
}

int main(int argc, char* argv[])
{
	printf("Hello World\n");

	root = new tn(10);
	root->left = new tn(5);
	root->left->left = new tn(3);
	root->left->right = new tn(7);
	root->right = new tn(15);
	root->right->left = new tn(13);
	root->right->right= new tn(18);
	
	printf("Inorder\n");
	inorder(root);

	printf("\nPreorder\n");
	preorder(root);

	printf("\nPostorder\n");
	postorder(root);
	
	printf("\nSame level\n");
	samelevel(root);

	printf("\nHeight of tree : %d\n",height(root));

	printf("\nDiameter of tree: %d\n", diameter(root));
	clearTree(root);	
	printf("\n");
	return 0;
}
