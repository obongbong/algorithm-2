#define INFN (1000000000000)

#include <stdio.h>

typedef struct _Nodeinfo{
	int id;
	char* name[20];
}Node;

int main(void)
{
	//const char* nodeName[4] = { "n0", "n1", "n2", "n3" }; //Node 집합

	const Node nodeSet[4] = { {2332, "n0"}, {9993, "n1"}, {332, "n2"}, {234, "n3"} }; //Node 집합

	int G[4][4] = {
		{0, 3, INFN, INFN},
		{INFN, 0, 4, INFN},
		{INFN, INFN, 0, 5},
		{INFN, INFN, 2, 0}
	};

	return 0;

}




