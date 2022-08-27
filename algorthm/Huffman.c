//1492018 ���� ������ �˰���
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char ch;
	int count;
	char *code;
}HuffmanCode;
typedef struct data{
	char ch;
	int n;
	int isNew;
	char *code;
}Data;
typedef struct TreeNode{
	Data weight;
	struct TreeNode *left_child;
	struct TreeNode *right_child;
}TreeNode;
typedef struct element{
	TreeNode *ptree;
	int key;
}element;
typedef struct{
	element *heap;
	int heap_size;
}HeapType;

int index=0;
HuffmanCode *codearr;	//������ �ڵ尡 ����� �迭

int fixed_bit_counter(int n);	//������Ʈ�� ���ϴ� �Լ�
int SearchData(char temp, Data *data, int size);	//���ڰ� �̹� ��忡 �ִ��� �˻�
void destroy_tree(TreeNode *root);		//Ʈ�� �����Ҵ� ����
void en_decoding(int n, int fixbit, element e, char *huffsentence);		//���ڵ� �� �ٽ� ���ڵ��Ͽ� ���
void free_codearr(int n);		//�������ڵ尡 ����� codearr�� �����Ҵ�����
void HeapNodeInorder(HeapType *h, int i);		//�ּ� ������ �迭�� ������ȸ
void init(HeapType *h);		//���� �ʱ�ȭ
void inorder(TreeNode *root);		//Ʈ�� ������ȸ
void insert_min_heap(HeapType *h, element item);		//�ּ� ������ ������
void make_code(TreeNode *root, char str[], char str2[], int fixbit);	//������ �ڵ� ����
void print_huff_code(int n, int Fsum, int Hsum, int fixbit);	//������Ʈ�� ������Ʈ ������� ���&���
element delete_min_heap(HeapType *h);		//�ּ� ������ ��� ����
element huffman_tree(Data freq[], int n, int fixbit);	//������ Ʈ�� ����
TreeNode *make_tree(TreeNode *left, TreeNode *right, int fixbit);		//Ʈ�� ����

int main(int argc, char *argv[])
{
	int n, i, Fsum=0, Hsum=0, fixbit;
	char temp=0;
	char *huffsentence = NULL;
	element e;
	Data *data;

	printf("---------Huffman algorithm 1492018 ����----------\n");
	if(argc==1)
	{
		printf("�Է��� ���� ����: ");
		scanf(" %d", &n);
		data = (Data*)malloc(sizeof(Data)*n);
		for(i=0; i<n; i++)
		{
			printf("���� ����: ");
			scanf(" %c", &temp);
			if(SearchData(temp, data, i))	//������ return 1, ������ return 0
			{
				data[i].ch = temp;
				printf("�󵵼� ����: ");
				scanf(" %d", &data[i].n);
				Fsum+=data[i].n;
				data[i].isNew = 0;	//�߰��� ��尡 �ƴ�
			}
			else
			{
				printf("�ߺ��Ǵ� ���ڰ� �ֽ��ϴ�.\n");
				return 0;
			}
		}
	}
	else if(argc==2)
	{
		FILE *fp;
		fp = fopen(argv[1], "r");
		if(fp == NULL)
		{
			printf("File Open ERROR for reading\n");
			return 0;
		}
		fscanf(fp, " %d", &n);
		data = (Data*)malloc(sizeof(Data)*n);
		for(i=0; i<n; i++)
		{
			fscanf(fp, " %c", &temp);
			if(SearchData(temp, data, i))	//������ return 1, ������ return 0
			{
				data[i].ch = temp;
				fscanf(fp, " %d", &data[i].n);
				Fsum+=data[i].n;
				data[i].isNew = 0;	//�߰��� ��尡 �ƴ�
			}
			else
			{
				printf("�ߺ��Ǵ� ���ڰ� �ֽ��ϴ�.\n");
				return 0;
			}
		}
		fclose(fp);
	}
	printf("���� ����: %d, ���� �� �� ��: %d\n", n, Fsum);
	codearr = (HuffmanCode*)malloc(sizeof(HuffmanCode)*n);
	fixbit = fixed_bit_counter(n);
	e = huffman_tree(data, n, fixbit);
	print_huff_code(n, Fsum, Hsum, fixbit);
	en_decoding(n, fixbit, e, huffsentence);
	destroy_tree(e.ptree);
	free(data);
	free_codearr(n);
}
int fixed_bit_counter(int n)	//n = ���ĺ� ���� n����
{
	int bit=0, x=1;
	while(n!=1 && n>x)
	{
		bit++;
		x*=2;
	}
	if(bit==0)
		return 1;
	else
		return bit;
}
int SearchData(char temp, Data *data, int size)
{
	int i;
	for(i=0; i<size; i++)
	{
		if(data[i].ch==temp)
			return 0;	//������ 0
	}
	return 1;	//������ 1
}
void destroy_tree(TreeNode *root)
{
	if(root == NULL)
		return;
	destroy_tree(root->left_child);
	destroy_tree(root->right_child);
	free(root->weight.code);
	free(root);
}
void en_decoding(int n, int fixbit, element e, char *huffsentence)
{
	int slen, blen, i, j;
	char sentence[100];
	char *huffp;
	TreeNode *treep;
	printf("������ �ڵ带 ����ϰ� ���� ������ ���ÿ�.\n");
	scanf(" %s", sentence);
	slen = strlen(sentence);
	blen = fixbit*slen;
	huffsentence = (char*)malloc(sizeof(char)*(blen+2));
	strcpy(huffsentence, "");
	printf("\n<Huffman code>\n");
	printf("���ڿ�: %s\n", sentence);
	printf("�ڵ忭: ");
	for(i=0; i<slen; i++)
	{
		for(j=0; j<n; j++)
		{
			if(sentence[i]==codearr[j].ch)
			{
				printf("%s", codearr[j].code);
				strcat(huffsentence, codearr[j].code);
			}
		}
	}
	huffp = huffsentence;
	treep = e.ptree;
	printf("\n\n<����>\n");
	printf("�ڵ忭: %s\n", huffsentence);
	printf("���ڿ�: ");
	strcat(huffsentence, "BE");
	while(*huffp!='E')
	{
		if(treep->weight.isNew==0)
		{
			printf("%c", treep->weight.ch);
			treep = e.ptree;
			continue;
		}
		if(*huffp=='1')
			treep = treep->left_child;
		else if(*huffp=='0')
			treep = treep->right_child;
		huffp++;
	}
	printf("\n");
	free(huffsentence);
}
void free_codearr(int n)
{
	int i;
	for(i=0; i<n; i++)
		free(codearr[i].code);
	free(codearr);
}
void HeapNodeInorder(HeapType *h, int i)
{
	if(i<=h->heap_size)
	{
		HeapNodeInorder(h, i*2);
		if(h->heap[i].ptree->weight.isNew==0)	//�������
			printf("%c ", h->heap[i].ptree->weight.ch);
		else	//�߰��� ���
			printf("W-%d ", h->heap[i].ptree->weight.isNew);
		HeapNodeInorder(h, i*2+1);
	}
}
void init(HeapType *h)
{
	h->heap_size = 0;	
}
void inorder(TreeNode *root)
{
	if(root)
	{
		inorder(root->left_child);
		if(root->weight.isNew==0)	//�������
			printf("%c ", root->weight.ch);
		else	//�߰��� ���
			printf("W-%d ", root->weight.isNew);
		inorder(root->right_child);
	}
}
void insert_min_heap(HeapType *h, element item)
{
	int i;
	i = ++(h->heap_size);

	//�ö󰡸鼭 �θ���� ��
	while((h->heap_size!=1) && (item.key < h->heap[i/2].key))
	{
		h->heap[i] = h->heap[i/2];
		i/=2;
	}
	h->heap[i] = item;

	printf("(����) ");
	printf("\n������ȸ: "); 
	HeapNodeInorder(h, 1);
	printf("\n�����迭: ");
	for(i=1; i<=h->heap_size; i++)
	{
		if(h->heap[i].ptree->weight.isNew==0)	//�������
			printf("%c ",h->heap[i].ptree->weight.ch);
		else	//�߰��� ���
			printf("W-%d ", h->heap[i].ptree->weight.isNew);
	}
	printf("\n");
}
void make_code(TreeNode *root, char str[], char str2[], int fixbit)
{
	if(root)
	{
		strcpy(root->weight.code, str);
		strcat(root->weight.code, str2);
		if(root->weight.isNew==0)
			printf("\ndata -> %c", root->weight.ch);
		else
			printf("\ndata -> W-%d", root->weight.isNew);
		printf("	count -> %d", root->weight.n);
		printf("	newcode -> ");
		if(root->weight.isNew==0)
		{
			codearr[index].ch = root->weight.ch;
			codearr[index].count = root->weight.n;
			codearr[index].code = (char*)malloc(sizeof(char)*(fixbit*2+5));
			strcpy(codearr[index].code, root->weight.code);
			printf("%s", codearr[index].code);
			index++;
		}
		printf("\n");
		make_code(root->left_child, root->weight.code, "1", fixbit);
		make_code(root->right_child, root->weight.code, "0", fixbit);
	}
}
void print_huff_code(int n, int Fsum, int Hsum, int fixbit)
{
	int i;
	printf("\n------------------------------------------------\n");
	printf("������(��������)�ڵ�\n");
	for(i=0; i<n; i++)
	{
		printf("%c -> %s\n", codearr[i].ch, codearr[i].code);
		Hsum+=strlen(codearr[i].code)*codearr[i].count;
	}
	printf("\nHuffman (���� Bit) ǥ�� ���� ���� -> %dBits\n", Hsum);
	printf("���� Bit ǥ�� ���� ���� -> %dBits\n", fixbit*Fsum);
	printf("------------------------------------------------\n");
}
element delete_min_heap(HeapType *h)
{
	int i;
	int parent, child;
	element item, temp;

	if(h->heap_size==0)
	{
		item.key = 0;
		item.ptree = NULL;
		return item;	
	}

	item = h->heap[1];	//���� ���
	temp = h->heap[(h->heap_size)--];	//���������(������ �÷��� �������� ���ڸ� ã��)
	parent = 1;
	child = 2;
	//������ �������鼭 ���� �ڽĳ�� ���� �ø���
	while(child<=h->heap_size)
	{
		if((child<h->heap_size) && (h->heap[child].key > h->heap[child+1].key))	//�������� �ڽ�(left, right)�� ���� ������ ����
			child++;
		if(temp.key <= h->heap[child].key)	//�ּ������̹Ƿ� <=
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	printf("(����)");
	printf("\n������ȸ: "); 
	HeapNodeInorder(h, 1);
	printf("\n�����迭: ");
	for(i=1; i<=h->heap_size; i++)
	{
		if(h->heap[i].ptree->weight.isNew==0)	//�������
			printf("%c ",h->heap[i].ptree->weight.ch);
		else	//�߰��� ���
			printf("W-%d ", h->heap[i].ptree->weight.isNew);
	}
	printf("\n");
	return item;
}
element huffman_tree(Data freq[], int n, int fixbit)
{
	int i;
	TreeNode *node, *x;
	HeapType heap;
	element e, e1, e2;
	int newNodeCnt = 0;
	char str[100] = "";
	char str2[100] = "";

	printf("------------------------------------------------\n");
	printf("�ּ� ���� �迭�� ���� ��ȸ�� ������ �ѹ��� ���\n");
	init(&heap);
	heap.heap = (element*)malloc(sizeof(element)*(2*n-1));
	for(i=0; i<n; i++)
	{
		node = make_tree(NULL, NULL, fixbit);
		e.key = node->weight.n = freq[i].n;	//�󵵼�
		node->weight.ch = freq[i].ch;	//���ĺ�
		node->weight.isNew = 0;	//���� ������� ��Ÿ��
		e.ptree = node;
		insert_min_heap(&heap, e);
	}
	for(i=1; i<n; i++)
	{
		//�ּڰ� ���� �ΰ��� ��� ��ġ��
		e1 = delete_min_heap(&heap);
		e2 = delete_min_heap(&heap);
		x = make_tree(e1.ptree, e2.ptree, fixbit);
		e.key = x->weight.n = e1.key + e2.key;
		x->weight.ch = 'W';
		x->weight.isNew = (++newNodeCnt);	//���� ���� ��� 'W-n' (n�� 1���� 1�� ����)
		e.ptree = x;
		insert_min_heap(&heap, e);
	}
	//���� ������ Ʈ�� �ϼ�
	e = delete_min_heap(&heap);
	free(heap.heap);
	printf("------------------------------------------------\n");
	printf("�ϼ��� ������Ʈ�� ������ȸ ���\n");
	inorder(e.ptree);
	printf("\n------------------------------------------------\n");
	printf("������ Ʈ��\n");
	make_code(e.ptree, str, str2, fixbit);
	return e;
}
TreeNode *make_tree(TreeNode *left, TreeNode *right, int fixbit)
{
	TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
	node->weight.code = (char*)malloc(sizeof(char)*(fixbit*2+5));
	if(node==NULL)
	{
		fprintf(stderr, "�޸� ����\n");
		exit(1);
	}
	node->left_child = left;
	node->right_child = right;
	return node;
}
