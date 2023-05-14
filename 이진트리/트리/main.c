#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#include "tree.h"


int main(int argc, char* argv[])
{
	printf("Hello World\n");

	Node* root = makeTree();
	printTree(root);

	//findNode ���
	printf("\n");
	findNode(root, 100);
	printf("\n");


	// Root�� Left ��忡 ������ ���ο� ��� ����
	Node* new_node = createNode(150);

	// Root�� Left ��忡 ���ο� ��� ����
	insertLeftNode(root, new_node);

	// Root�� Right ��忡 ������ ���ο� ��� ����
	new_node = createNode(350);

	// Root�� Right ��忡 ���ο� ��� ����
	insertRightNode(root, new_node);

	// ����� Tree ���
	printf("\nƮ���� ��带 �߰��� ��\n");
	printTree(root);

	_getch();
	return 0;
}