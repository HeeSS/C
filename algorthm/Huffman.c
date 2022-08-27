//1492018 서희선 허프만 알고리즘
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
HuffmanCode *codearr;	//허프만 코드가 저장된 배열

int fixed_bit_counter(int n);	//고정비트를 구하는 함수
int SearchData(char temp, Data *data, int size);	//문자가 이미 노드에 있는지 검색
void destroy_tree(TreeNode *root);		//트리 동적할당 해제
void en_decoding(int n, int fixbit, element e, char *huffsentence);		//인코딩 후 다시 디코딩하여 출력
void free_codearr(int n);		//허프만코드가 저장된 codearr을 동적할당해제
void HeapNodeInorder(HeapType *h, int i);		//최소 히프의 배열을 중위순회
void init(HeapType *h);		//히프 초기화
void inorder(TreeNode *root);		//트리 중위순회
void insert_min_heap(HeapType *h, element item);		//최소 히프의 노드삽입
void make_code(TreeNode *root, char str[], char str2[], int fixbit);	//허프만 코드 생성
void print_huff_code(int n, int Fsum, int Hsum, int fixbit);	//가변비트와 고정비트 저장공간 계산&출력
element delete_min_heap(HeapType *h);		//최소 히프의 노드 삭제
element huffman_tree(Data freq[], int n, int fixbit);	//허프만 트리 생성
TreeNode *make_tree(TreeNode *left, TreeNode *right, int fixbit);		//트리 생성

int main(int argc, char *argv[])
{
	int n, i, Fsum=0, Hsum=0, fixbit;
	char temp=0;
	char *huffsentence = NULL;
	element e;
	Data *data;

	printf("---------Huffman algorithm 1492018 서희선----------\n");
	if(argc==1)
	{
		printf("입력할 문자 개수: ");
		scanf(" %d", &n);
		data = (Data*)malloc(sizeof(Data)*n);
		for(i=0; i<n; i++)
		{
			printf("문자 정보: ");
			scanf(" %c", &temp);
			if(SearchData(temp, data, i))	//없으면 return 1, 있으면 return 0
			{
				data[i].ch = temp;
				printf("빈도수 정보: ");
				scanf(" %d", &data[i].n);
				Fsum+=data[i].n;
				data[i].isNew = 0;	//추가된 노드가 아님
			}
			else
			{
				printf("중복되는 문자가 있습니다.\n");
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
			if(SearchData(temp, data, i))	//없으면 return 1, 있으면 return 0
			{
				data[i].ch = temp;
				fscanf(fp, " %d", &data[i].n);
				Fsum+=data[i].n;
				data[i].isNew = 0;	//추가된 노드가 아님
			}
			else
			{
				printf("중복되는 문자가 있습니다.\n");
				return 0;
			}
		}
		fclose(fp);
	}
	printf("문자 개수: %d, 문자 빈도 수 합: %d\n", n, Fsum);
	codearr = (HuffmanCode*)malloc(sizeof(HuffmanCode)*n);
	fixbit = fixed_bit_counter(n);
	e = huffman_tree(data, n, fixbit);
	print_huff_code(n, Fsum, Hsum, fixbit);
	en_decoding(n, fixbit, e, huffsentence);
	destroy_tree(e.ptree);
	free(data);
	free_codearr(n);
}
int fixed_bit_counter(int n)	//n = 알파벳 종류 n가지
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
			return 0;	//있으면 0
	}
	return 1;	//없으면 1
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
	printf("허프만 코드를 출력하고 싶은 문장을 쓰시오.\n");
	scanf(" %s", sentence);
	slen = strlen(sentence);
	blen = fixbit*slen;
	huffsentence = (char*)malloc(sizeof(char)*(blen+2));
	strcpy(huffsentence, "");
	printf("\n<Huffman code>\n");
	printf("문자열: %s\n", sentence);
	printf("코드열: ");
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
	printf("\n\n<복원>\n");
	printf("코드열: %s\n", huffsentence);
	printf("문자열: ");
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
		if(h->heap[i].ptree->weight.isNew==0)	//기존노드
			printf("%c ", h->heap[i].ptree->weight.ch);
		else	//추가된 노드
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
		if(root->weight.isNew==0)	//기존노드
			printf("%c ", root->weight.ch);
		else	//추가된 노드
			printf("W-%d ", root->weight.isNew);
		inorder(root->right_child);
	}
}
void insert_min_heap(HeapType *h, element item)
{
	int i;
	i = ++(h->heap_size);

	//올라가면서 부모노드와 비교
	while((h->heap_size!=1) && (item.key < h->heap[i/2].key))
	{
		h->heap[i] = h->heap[i/2];
		i/=2;
	}
	h->heap[i] = item;

	printf("(삽입) ");
	printf("\n중위순회: "); 
	HeapNodeInorder(h, 1);
	printf("\n히프배열: ");
	for(i=1; i<=h->heap_size; i++)
	{
		if(h->heap[i].ptree->weight.isNew==0)	//기존노드
			printf("%c ",h->heap[i].ptree->weight.ch);
		else	//추가된 노드
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
	printf("허프만(가변길이)코드\n");
	for(i=0; i<n; i++)
	{
		printf("%c -> %s\n", codearr[i].ch, codearr[i].code);
		Hsum+=strlen(codearr[i].code)*codearr[i].count;
	}
	printf("\nHuffman (가변 Bit) 표현 저장 공간 -> %dBits\n", Hsum);
	printf("고정 Bit 표현 저장 공간 -> %dBits\n", fixbit*Fsum);
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

	item = h->heap[1];	//삭제 노드
	temp = h->heap[(h->heap_size)--];	//마지막노드(맨위로 올려서 내려가며 제자리 찾기)
	parent = 1;
	child = 2;
	//밑으로 내려가면서 작은 자식노드 위로 올리기
	while(child<=h->heap_size)
	{
		if((child<h->heap_size) && (h->heap[child].key > h->heap[child+1].key))	//현재노드의 자식(left, right)중 작은 값으로 선택
			child++;
		if(temp.key <= h->heap[child].key)	//최소히프이므로 <=
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	printf("(삭제)");
	printf("\n중위순회: "); 
	HeapNodeInorder(h, 1);
	printf("\n히프배열: ");
	for(i=1; i<=h->heap_size; i++)
	{
		if(h->heap[i].ptree->weight.isNew==0)	//기존노드
			printf("%c ",h->heap[i].ptree->weight.ch);
		else	//추가된 노드
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
	printf("최소 히프 배열의 중위 순회와 순차적 넘버링 출력\n");
	init(&heap);
	heap.heap = (element*)malloc(sizeof(element)*(2*n-1));
	for(i=0; i<n; i++)
	{
		node = make_tree(NULL, NULL, fixbit);
		e.key = node->weight.n = freq[i].n;	//빈도수
		node->weight.ch = freq[i].ch;	//알파벳
		node->weight.isNew = 0;	//기존 노드임을 나타냄
		e.ptree = node;
		insert_min_heap(&heap, e);
	}
	for(i=1; i<n; i++)
	{
		//최솟값 갖는 두개의 노드 합치기
		e1 = delete_min_heap(&heap);
		e2 = delete_min_heap(&heap);
		x = make_tree(e1.ptree, e2.ptree, fixbit);
		e.key = x->weight.n = e1.key + e2.key;
		x->weight.ch = 'W';
		x->weight.isNew = (++newNodeCnt);	//새로 만든 노드 'W-n' (n은 1부터 1씩 증가)
		e.ptree = x;
		insert_min_heap(&heap, e);
	}
	//최종 허프만 트리 완성
	e = delete_min_heap(&heap);
	free(heap.heap);
	printf("------------------------------------------------\n");
	printf("완성된 허프만트리 중위순회 출력\n");
	inorder(e.ptree);
	printf("\n------------------------------------------------\n");
	printf("허프만 트리\n");
	make_code(e.ptree, str, str2, fixbit);
	return e;
}
TreeNode *make_tree(TreeNode *left, TreeNode *right, int fixbit)
{
	TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
	node->weight.code = (char*)malloc(sizeof(char)*(fixbit*2+5));
	if(node==NULL)
	{
		fprintf(stderr, "메모리 에러\n");
		exit(1);
	}
	node->left_child = left;
	node->right_child = right;
	return node;
}
