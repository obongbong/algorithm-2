#pragma once

//typedef struct _Node Node;

typedef struct _Node
{
	int value;
	struct Node* left;
	struct Node* right;
}Node;
Node* root;


extern Node* makeTree();
extern void printTree(Node* root);
Node* createNode(int val);

Node* insertLeftNode(Node* where, Node* new_node);
Node* insertRightNode(Node* where, Node* new_node);

