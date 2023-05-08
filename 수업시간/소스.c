#define INFN (1000000000000)

#include <stdio.h>

typedef struct _Nodeinfo{
	int id;
	char* name[20];
}Node;

const Node nodeSet[4] = { {2332, "n0"}, {9993, "n1"}, {332, "n2"}, {234, "n3"} }; //Node 집합

typedef struct _Bnode {
	int id;
	Bnode* left;
	Bnode* right;
}Bnode;

//반환: 초기화된 이진 트리의 루트노드
Bnode initTree()
{
	Bnode* b0 = (Bnode*)malloc(sizeof(Bnode));
	Bnode* b1 = (Bnode*)malloc(sizeof(Bnode));
	Bnode* b2 = (Bnode*)malloc(sizeof(Bnode));
	Bnode* b3 = (Bnode*)malloc(sizeof(Bnode));
	Bnode* b4 = (Bnode*)malloc(sizeof(Bnode));

	b0->left = b1;
	b1->right = b2;
	b2->left = b3;
	b2->right = b4;
	
	// ...

}return b0;


int main(void)
{
	//const char* nodeName[4] = { "n0", "n1", "n2", "n3" }; //Node 집합

	//const Node nodeSet[4] = { {2332, "n0"}, {9993, "n1"}, {332, "n2"}, {234, "n3"} }; //Node 집합

	int G[4][4] = {
		{0, 3, INFN, INFN},
		{INFN, 0, 4, INFN},
		{INFN, INFN, 0, 5},
		{INFN, INFN, 2, 0}
	};

	return 0;

}

void initGraph()
{
	Node n1;
	strcpy(n1.name, "n0");
	nodeSet[0] = n1;

}


