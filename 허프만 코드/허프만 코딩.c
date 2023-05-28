#define _CRT_SECURE_NO_WARNINGS
/*
*�Է�: �Է� ������ n���� ���ڿ� ���� ������ �󵵼�
* ���: ������ Ʈ��
* 1. �� ���ڿ� ���� ��带 �����, �� ������ �󵵼��� ��忡 �����Ѵ�.
* 2. n���� ������ �󵵼��� ���� �켱���� ť Q�� �����.
* 3. while(Q�� �մ� ��� �� >= 2{
* 4 .�󵵼��� ���� ���� 2���� ��� (A�� B)�� Q���� �����Ѵ�.
* 5. �� ��� N�� �����, A�� B�� N�� �ڽ� ���� �����.
* 6. N�� �󵵼� <- A�� �󵵼� + B�� �󵵼�
* 7. ��� N�� Q�� �����Ѵ�.
* }
* 8. return Q // ������ Ʈ���� ��Ʈ�� �����ϴ� ���̴�.
*/

//������������
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 100
#define EMPTY_STRING ""
#define MAX_CHAR 128

// Ʈ�� ���
struct Node
{
    char ch;
    int freq;
    struct Node* left, * right;
};

// �󵵼� ��踦 �����ϱ� ���� ����ü
typedef struct {
    char character;
    int frequency;
} FrequencyStat;

void countCharacterFrequency(const char* inputFileName, const char* outputFileName) {
    FILE* inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("Failed to open input file.\n");
        return;
    }


    // �󵵼� ��踦 ������ �迭
    FrequencyStat frequencyStats[MAX_CHAR];
    memset(frequencyStats, 0, sizeof(frequencyStats));

    // ���Ͽ��� ���ڸ� �ϳ��� �о� �󵵼� ���
    int c;
    while ((c = fgetc(inputFile)) != EOF) {
        if (c >= 0 && c < MAX_CHAR) {
            frequencyStats[c].character = c;
            frequencyStats[c].frequency = 0; // �󵵼� �ʱ�ȭ
        }
    }

    // ���Ͽ��� ���ڸ� �ٽ� �о� �󵵼� ����
    rewind(inputFile);
    while ((c = fgetc(inputFile)) != EOF) {
        if (c >= 0 && c < MAX_CHAR) {
            frequencyStats[c].frequency++;
        }
    }

    fclose(inputFile);

    FILE* outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("Failed to open output file.\n");
        return;
    }

    // �󵵼� ��踦 ���Ͽ� ����
    for (int i = 0; i < MAX_CHAR; i++) {
        if (frequencyStats[i].frequency > 0) {
            fprintf(outputFile, "%c\t%d\n", frequencyStats[i].character, frequencyStats[i].frequency);
        }
    }

    fclose(outputFile);

    printf("Character frequency statistics saved to %s.\n", outputFileName);
}

// ���ο� Ʈ�� ��带 �Ҵ��ϴ� �Լ�
struct Node* getNode(char ch, int freq, struct Node* left, struct Node* right)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}

// Huffman Ʈ���� Ž���ϰ� ������ Huffman �ڵ带 �����մϴ�.
void encode(struct Node* root, char* str, char* huffmanCode[])
{
    if (root == NULL)
        return;

    // ���� ��带 ã�ҽ��ϴ�.
    if (root->left == NULL && root->right == NULL)
    {
        int index = root->ch - 'A';
        strcpy(huffmanCode[index], str != EMPTY_STRING ? str : "1");
    }

    int len = strlen(str);
    char* leftStr = (char*)malloc(sizeof(char) * (len + 2));
    char* rightStr = (char*)malloc(sizeof(char) * (len + 2));

    strcpy(leftStr, str);
    strcpy(rightStr, str);

    leftStr[len] = '0';
    leftStr[len + 1] = '\0';

    rightStr[len] = '1';
    rightStr[len + 1] = '\0';

    encode(root->left, leftStr, huffmanCode);
    encode(root->right, rightStr, huffmanCode);

    free(leftStr);
    free(rightStr);
}

//decod �Լ� �߰�
void decode(struct Node* root, int* index, char* encodedStr)
{
    if (root == NULL)
        return;

    // ���� ��带 ã�ҽ��ϴ�.
    if (root->left == NULL && root->right == NULL)
    {
        printf("%c", root->ch);
        return;
    }

    (*index)++;

    if (encodedStr[*index] == '0')
        decode(root->left, index, encodedStr);
    else
        decode(root->right, index, encodedStr);
}


// Huffman Tree�� �����ϰ� �־��� �Է� �ؽ�Ʈ�� ���ڵ��մϴ�.
void buildHuffmanTree(char* text)
{
    if (strlen(text) == 0)
        return;

    // �� ������ ���� �󵵸� ����մϴ�.
    int freq[26] = { 0 };
    int i;
    for (i = 0; i < strlen(text); i++)
    {
        char ch = text[i];
        if (ch >= 'A' && ch <= 'Z')
            freq[ch - 'A']++;
        else if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }

    // Huffman Tree�� ���� ��带 ������ �迭�� �����մϴ�.
    struct Node* leaves[26];
    for (i = 0; i < 26; i++)
        leaves[i] = NULL;

    // �� ���ڿ� ���� ���� ��带 �����ϰ� �迭�� �����մϴ�.
    for (i = 0; i < 26; i++)
    {
        if (freq[i] > 0)
            leaves[i] = getNode('A' + i, freq[i], NULL, NULL);
    }

    // Huffman Tree�� ���� ��带 ������ ť�� �����մϴ�.
    struct Node** queue = (struct Node**)malloc(sizeof(struct Node*) * MAX_TREE_HT);
    int queueSize = 0;

    // ���� ��带 ť�� �߰��մϴ�.
    for (i = 0; i < 26; i++)
    {
        if (leaves[i] != NULL)
            queue[queueSize++] = leaves[i];
    }

    // Huffman Tree�� �����մϴ�.
    struct Node* root = NULL;
    while (queueSize > 1)
    {
        // ���� ���� �󵵸� ���� �� ���� ��带 �����մϴ�.
        struct Node* min1 = queue[0];
        struct Node* min2 = queue[1];

        // ���õ� �� ��带 ť���� �����մϴ�.
        for (i = 0; i < queueSize - 2; i++)
            queue[i] = queue[i + 2];
        queueSize -= 2;

        // ���ο� ���� ��带 �����ϰ� ���õ� �� ��带 �ڽ����� �����մϴ�.
        struct Node* internalNode = getNode('\0', min1->freq + min2->freq, min1, min2);

        // ���ο� ���� ��带 ť�� �߰��մϴ�.
        int j = queueSize - 1;
        while (j >= 0 && internalNode->freq < queue[j]->freq)
        {
            queue[j + 1] = queue[j];
            j--;
        }
        queue[j + 1] = internalNode;
        queueSize++;
    }

    // Huffman �ڵ带 ������ �迭�� �����մϴ�.
    char* huffmanCode[26];
    for (i = 0; i < 26; i++)
        huffmanCode[i] = (char*)malloc(sizeof(char) * MAX_TREE_HT);

    // Huffman Tree�� Ž���ϰ� Huffman �ڵ带 �����մϴ�.
    encode(queue[0], EMPTY_STRING, huffmanCode);

    printf("Huffman Codes are:\n");
    for (i = 0; i < 26; i++)
    {
        if (leaves[i] != NULL)
            printf("%c %s\n", leaves[i]->ch, huffmanCode[i]);
    }

    printf("\nThe original string is:\n%s\n", text);

    // ���ڵ��� ���ڿ��� �����մϴ�.
    int len = strlen(text);
    char* encodedStr = (char*)malloc(sizeof(char) * (len * MAX_TREE_HT));
    encodedStr[0] = '\0';

    for (i = 0; i < len; i++)
    {
        char ch = text[i];
        if (ch >= 'A' && ch <= 'Z')
            strcat(encodedStr, huffmanCode[ch - 'A']);
        else if (ch >= 'a' && ch <= 'z')
            strcat(encodedStr, huffmanCode[ch - 'a']);
    }

    printf("\nThe encoded string is:\n%s\n", encodedStr);

    printf("\nThe decoded string is:\n");
    if (queue[0] == NULL)
    {
        printf("Huffman Tree is empty.\n");
        return;
    }

    int index = -1;
    while (index < len - 1)
        decode(queue[0], &index, encodedStr);

    printf("\n");

    // �޸� ����
    for (i = 0; i < 26; i++)
        free(huffmanCode[i]);
    
    FILE* outputFile = fopen("output.huf", "w");
    if (outputFile == NULL) {
        printf("Failed to open output file.\n");
        return;
    }

    // ����� �����͸� ���Ͽ� ����
    fputs(encodedStr, outputFile);

    fclose(outputFile);


    free(encodedStr);
    free(queue);
}

//��������
void decodebuildHuffmanTree(const char* statsFileName, const char* compressedFileName, const char* outputFileName) {
    // stats.txt ������ �о�ͼ� Huffman Tree�� �籸���մϴ�.

    // ����� �����͸� �о�� ������ ���ϴ�.
    FILE* compressedFile = fopen(compressedFileName, "r");
    if (compressedFile == NULL) {
        printf("Failed to open compressed file.\n");
        return;
    }

    // output.txt ������ ����
    FILE* outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("Failed to open output file.\n");
        fclose(compressedFile); // ������ �ݽ��ϴ�.
        return;
    }

    fclose(compressedFile); // ���� �ݱ�
    fclose(outputFile); // ���� �ݱ�
}




int main()
{
    const char* inputFileName = "input.txt";
    const char* outputFileName = "output.huf";
    const char* statsFileName = "stats.txt";

    FILE* inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("Failed to open input file.\n");
        return 1;
    }

    // �Է� ������ ������ �о�ɴϴ�.
    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    rewind(inputFile);

    char* fileContent = (char*)malloc(sizeof(char) * (fileSize + 1));
    fread(fileContent, sizeof(char), fileSize, inputFile);
    fileContent[fileSize] = '\0';

    fclose(inputFile);

    // Huffman Tree�� �����ϰ� ������ �����մϴ�.
    buildHuffmanTree(fileContent);

    // ����� ����� ���Ͽ� �����մϴ�.
    FILE* outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("Failed to open output file.\n");
        return 1;
    }


    fwrite(fileContent, sizeof(char), strlen(fileContent), outputFile);

    fclose(outputFile);

    printf("File compressed and saved to %s.\n", outputFileName);

    countCharacterFrequency(inputFileName, statsFileName);

    free(fileContent);

    decodebuildHuffmanTree("stats.txt", "output.huf", "output.txt");


    return 0;
}


