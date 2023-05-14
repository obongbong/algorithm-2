#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int value;
	struct Node* left;	//���� ���
	struct Node* right;	//������ ���
}Node;

Node* root;


Node* createNode(int val)
{
	//1. sizeof(Node)malloc
	Node* pNode = (Node*)malloc(sizeof(Node));

	//2. �ʱ�ȭ: n->value = val, left, right (NULL)
	pNode->value = val;
	pNode->left = NULL;
	pNode->right = NULL;

	//3. ��ȯ Node ��ü(����) ������ ��ȯ
	return pNode;
}

static Node* connectChild(Node* parent, Node* left, Node* right)
{
	if (parent == NULL) return NULL;

	parent->left = left;
	parent->right = right;
	return parent;
}


Node* makeTree()
{
	Node* pRoot = NULL;
	Node* tLeft = NULL;
	Node* tRight = NULL;




	pRoot = createNode(100);
	tLeft = createNode(200);
	tRight = createNode(300);

	connectChild(pRoot, tLeft, tRight); // pRoot�� tLeft tRight

	connectChild(tRight, createNode(400), createNode(500)); //tRight�� 400 500

	return pRoot;
}

// in order, pre order, post order �Լ� �ۼ�
void preorder(Node* root)
{
	if (root != NULL)
	{
		printf("[%d] ", root->value);
		preorder(root->left);
		preorder(root->right);
	}
}

void inorder(Node* root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf("[%d] ", root->value);
		inorder(root->right);
	}
}

void postorder(Node* root)
{
	if (root != NULL)
	{
		postorder(root->left);
		postorder(root->right);
		printf("[%d] ", root->value);
	}
}



void printTree(Node* root)
{
	if (root == NULL) return NULL;

	printf("Node: %d\n", root->value);

	//pre order, in order, post order �ۼ�
	if (root != NULL)
	{
		printf("pre order : ");preorder(root);

		printf("\nin order : ");inorder(root);

		printf("\npost order : ");postorder(root);

	}


}

//finNode �Լ� �߰� �ۼ�
Node* findNode(Node* root, int value)
{
	if (root == NULL) {
		printf("�ش� ���� Ʈ���� �������� �ʽ��ϴ�.\n");
		return NULL;
	}
	else if (root->value == value) {
		printf("ã�� ����� ��: %d\n", value);
		return root;
	}
	else if (root->value > value) {
		return findNode(root->left, value);
	}
	else {
		return findNode(root->right, value);
	}
}



//Ʈ���� ��带 �����ϴ� �Լ�
//where = ������ ��ġ�� ���
//new_node = ������ ���ο� ��� ��
Node* insertLeftNode(Node* where, Node* new_node) 
{
	if (where == NULL) { //where�� NULL�̸� NULL ��ȯ
		return NULL;
	}

	Node* left = where->left; //where ����� ���� �ڽ� ��带 left �����Ϳ� ����
	where->left = new_node; // where ����� ���� �ڽ� ��带 new_node�� ��ü
	new_node->left = left; //new_node ����� ���� �ڽ� ��带 left�� �ٲ�

	return where;
}

Node* insertRightNode(Node* where, Node* new_node)
{
	if (where == NULL) {
		return NULL;
	}

	Node* right = where->right;
	where->right = new_node;
	new_node->right = right;

	return where;
}