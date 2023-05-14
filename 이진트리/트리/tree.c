#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int value;
	struct Node* left;	//왼쪽 노드
	struct Node* right;	//오른쪽 노드
}Node;

Node* root;


Node* createNode(int val)
{
	//1. sizeof(Node)malloc
	Node* pNode = (Node*)malloc(sizeof(Node));

	//2. 초기화: n->value = val, left, right (NULL)
	pNode->value = val;
	pNode->left = NULL;
	pNode->right = NULL;

	//3. 반환 Node 객체(변수) 포인터 반환
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

	connectChild(pRoot, tLeft, tRight); // pRoot에 tLeft tRight

	connectChild(tRight, createNode(400), createNode(500)); //tRight에 400 500

	return pRoot;
}

// in order, pre order, post order 함수 작성
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

	//pre order, in order, post order 작성
	if (root != NULL)
	{
		printf("pre order : ");preorder(root);

		printf("\nin order : ");inorder(root);

		printf("\npost order : ");postorder(root);

	}


}

//finNode 함수 추가 작성
Node* findNode(Node* root, int value)
{
	if (root == NULL) {
		printf("해당 값이 트리에 존재하지 않습니다.\n");
		return NULL;
	}
	else if (root->value == value) {
		printf("찾은 노드의 값: %d\n", value);
		return root;
	}
	else if (root->value > value) {
		return findNode(root->left, value);
	}
	else {
		return findNode(root->right, value);
	}
}



//트리에 노드를 삽입하는 함수
//where = 삽입할 위치의 노드
//new_node = 삽입할 새로운 노드 값
Node* insertLeftNode(Node* where, Node* new_node) 
{
	if (where == NULL) { //where이 NULL이면 NULL 반환
		return NULL;
	}

	Node* left = where->left; //where 노드의 왼쪽 자식 노드를 left 포인터에 저장
	where->left = new_node; // where 노드의 왼쪽 자식 노드를 new_node로 대체
	new_node->left = left; //new_node 노드의 왼쪽 자식 노드를 left로 바꿈

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