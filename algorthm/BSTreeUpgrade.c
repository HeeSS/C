//�˰��� - ����Ž��Ʈ��
//1492018 ����
//Ʈ�����ȿ� *parent�߰�
//Ž����� ǥ�� �߰� //void search(TreeNode *root)
//A: ����Ž�� ��� �߰� //void LRP(TreeNode *root)
//B: ���� ��� ������ �Ÿ� ���ϱ� �߰� //void distance(TreeNode *root)

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 100

//����� ����
typedef struct TreeNode {
	char data[MAX];
	struct TreeNode *left, *right, *parent;
}TreeNode;

typedef struct Array {
	char data[MAX];
}Array;

void print_menu();
void insert_node(TreeNode **root);
void delete_node(TreeNode **root);
void preorder(TreeNode *root);
void inorder(TreeNode *root);
void postorder(TreeNode *root);
void search(TreeNode *root);
void LRP(TreeNode *root);
int mymax(int a, int b);
int get_height(TreeNode *node);
void distance(TreeNode *root);
void TreeHeight(TreeNode *root);
int get_node_count(TreeNode *node);
void num_of_node(TreeNode *root);
void get_min_node(TreeNode *root);
void get_max_node(TreeNode *root);

void print_menu(){
	printf("\n************************\n");
	printf("1: �Է�\n2: ����\n3: ������ȸ\n4: ������ȸ\n5: ������ȸ\n6: ����� Ž��\n7: Ʈ���� ����\n8: ����� ����\n9: ����\na: �ּ� Ű\nb: �ִ� Ű\nA: ���� Ž��\nB: ���� ��� ������ �Ÿ�\n");
	printf("*** Which select ? : ");
}

void insert_node(TreeNode **root){
	TreeNode *p, *t, *n; //p=�θ���, t=������, n=���ο���
	char key[MAX];

	t = *root;
	p = NULL;

	printf("Ű��: ");
	fflush(stdin);
	scanf("%s", key);

	//Ž���� ���� ����
	while(t != NULL){
		if(strcmp(key,t->data)==0) return;
		p = t;
		if(strcmp(key,p->data)==-1) t = p->left;
		else t = p->right;
	}
	//key�� Ʈ���ȿ� �����Ƿ� ���԰���
	//Ʈ����屸��
	n = (TreeNode *)malloc(sizeof(TreeNode));
	if(n == NULL) return;
	//������ ����
	strcpy(n->data,key);
	n->left = n->right = NULL;
	n->parent = p;		
	//�θ���� ����
	if(p != NULL)
		if(strcmp(key,p->data)==-1)
			p->left = n;
		else p->right = n;
	else *root = n;
}

void delete_node(TreeNode **root){
	TreeNode *p, *child, *succ, *succ_p, *t;
	char key[MAX];

	//key�� ���� ���t�� Ž��, p�� t�Ǻθ���
	p = NULL;
	t = *root;

	printf("Ű��: ");
	fflush(stdin);
	scanf("%s", key);

	//key�� ���� ��� t�� Ž���Ѵ�
	while(t != NULL && strcmp(t->data, key)!=0){
		p = t;
		t = (strcmp(key,p->data)==-1) ? p->left : p->right;		
	}
	//Ž���� ����� ������ t�� NULL�̸� Ʈ���ȿ� key�� ����
	if( t == NULL){
		printf("key is not in the tree");
		return;
	}
	//1. �ܸ������ ���
	if((t->left == NULL) && (t->right == NULL)){
		if(p!=NULL){
			if(p->left == t)
				p->left = NULL;
			else	p->right = NULL;
		}
		else //���� �θ� ��尡 NULL�̸� �����Ǵ� ��尡 ��Ʈ
			*root = NULL;
	}
	//2. �ϳ��� �ڽĸ� ������ ���
	else if((t->left==NULL) || (t->right == NULL)){
		child = (t->left != NULL) ? t->left : t->right;
		if(p!=NULL){
			if(p->left == t)
				p->left = child;
			else	p->right = child;
		}
		else	//���� �θ��尡 NULL�̸� �����Ǵ� ��尡 ��Ʈ
			*root = child;
	}
	//3. �� ���� �ڽ��� ������ ���
	else{
		//������ ����Ʈ������ �İ��ڸ� ã�´�.
		succ_p = t;
		succ = t->right;
		//�İ��ڸ� ã�Ƽ� ��� �������� �̵��Ѵ�.
		while(succ->left != NULL){
			succ_p = succ;
			succ = succ->left;
		}
		//�ļ����� �θ�� �ڽ��� ����
		if(succ_p->left == succ)
			succ_p->left = succ->right;
		else
			succ_p->right = succ->right;
		//�ļ��ڰ� ���� Ű ���� ���� ��忡 ����
		strcpy(t->data, succ->data);
		//������ �ļ��� ����
		t = succ;
	}
	free(t);
}

void preorder(TreeNode *root){
	if(root){
		printf("%s ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void inorder(TreeNode *root){
	if(root){
		inorder(root->left);
		printf("%s ", root->data);
		inorder(root->right);
	}
}

void postorder(TreeNode *root){
	if(root){
		postorder(root->left);
		postorder(root->right);
		printf("%s ", root->data);
	}
}

void search(TreeNode *root){
	char key[MAX];
	TreeNode *node = root;

	printf("Ű��: ");
	fflush(stdin);
	scanf("%s", key);

	printf("Ž�� ���: ");
	while(node != NULL){
		if(node==root)
			printf("(root) ");
		printf("%s ", node->data);
		if(strcmp(key, node->data)==0){
			printf("\n%s Ž�� ������ Ű: %s\n", key, node->data);
			return;
		}
		else if(strcmp(key, node->data)==-1)
		{
			node = node->left;
			printf("(left) ");
		}
		else
		{
			node = node->right;
			printf("(right) ");
		}
	}
	//Ž������
	printf("%s Ž�� Error!!!\n", key);
	return;
}

void LRP(TreeNode *root){
	char ch=NULL;
	TreeNode *node = root;

	while(ch!='Q')
	{
		if(node==NULL)
		{
			printf("\n	(parent) NULL\n");
			break;
		}
		else
		{
			if(node==root)
				printf("\n	(root) %s\n", node->data);
			else
				printf("\n	(parent) %s\n", node->data);

			if(node->left==NULL)
				printf("(left) NULL");
			else
				printf("(left) %s(%d)", node->left->data, get_height(node->left));
			if(node->right==NULL)
				printf("	(right) NULL\n");
			else
				printf("	(right) %s(%d)\n", node->right->data, get_height(node->right));


			printf("�Է�(L,R,P,Q): ");		
			fflush(stdin);
			scanf("%c", &ch);

			if(ch!='L' && ch!='R' && ch!='P' && ch!='Q')		
				printf("Please reenter!\n");
			else
			{
				if(ch=='L')
					node = node->left;
				else if(ch=='R')
					node = node->right;
				else if(ch=='P')
				{
					if(node!=root)
						node = node->parent;		
					else
						printf("There was no parent!\n");		
				}
			}
		}

	}
}

int mymax(int a, int b){
	int c;
	c= (a>b) ? a : b;
	return c;
}

int get_height(TreeNode *node){
	int height = 0;

	if(node != NULL)
		height = 1 + mymax(get_height(node->left), get_height(node->right));
	return height;
}

void distance(TreeNode *root){
	TreeNode *node = root;
	char key1[MAX], key2[MAX];
	Array *arr1, *arr2;
	Array *p1, *p2;
	int arrsize, size1=0, size2=0;
	int distance=0;
	int is_in1=0, is_in2=0;
	int cntp1=0, cntp2=0;

	arrsize = get_height(root);

	arr1 = (Array*)malloc(sizeof(Array)*arrsize);
	arr2 = (Array*)malloc(sizeof(Array)*arrsize);

	p1 = arr1;
	p2 = arr2;

	printf("Ű��1: ");
	fflush(stdin);
	scanf("%s", key1);

	printf("Ű��2: ");
	fflush(stdin);
	scanf("%s", key2);

	if(strcmp(key1, key2)==0)
	{
		printf("(key1�� key2 ������ �Ÿ�) = 0\n");
		return;
	}

	//arr1 ���ϱ�
	while(node != NULL){
		strcpy(p1->data, node->data);
		p1++;
		size1++;

		if(strcmp(key1, node->data)==0){
			is_in1=1;
			break;
		}
		else if(strcmp(key1, node->data)==-1)
			node = node->left;
		else
			node = node->right;
	}

	//Ž������
	if(is_in1==0)
	{
		printf("key1�� �����ϴ�.\n");
		return;
	}

	node = root;

	//arr2 ���ϱ�
	while(node != NULL){
		strcpy(p2->data, node->data);
		p2++;
		size2++;

		if(strcmp(key2, node->data)==0){
			is_in2=1;
			break;
		}
		else if(strcmp(key2, node->data)==-1)
			node = node->left;
		else
			node = node->right;
	}

	//Ž������
	if(is_in2==0)
	{
		printf("key2�� �����ϴ�.\n");
		return;
	}

	p1 = arr1;
	p2 = arr2;

	while(1)
	{
		if(strcmp(p1->data, p2->data)==0)
		{
			p1++; p2++;
			cntp1++; cntp2++;
			if(cntp1==size1)
			{
				while(cntp2!=size2)
				{
					distance++;
					p2++;
					cntp2++;
				}
				break;
			}
			else if(cntp2==size2)
			{
				while(cntp1!=size1)
				{
					distance++;
					p1++;
					cntp1++;
				}
				break;
			}
		}
		else
		{
			distance+=2;
			p1++; p2++;
			cntp1++; cntp2++;
			if(cntp1==size1)
			{
				while(cntp2!=size2)
				{
					distance++;
					p2++;
					cntp2++;
				}
				break;
			}
			else if(cntp2==size2)
			{
				while(cntp1!=size1)
				{
					distance++;
					p1++;
					cntp1++;
				}
				break;
			}
		}
	}

	p1=arr1;
	p2=arr2;
	cntp1=0; cntp2=0;

	/*printf("key1 Ž�����: ");
	while(cntp1!=size1)
	{
		printf("%s ", p1->data);
		p1++;
		cntp1++;
	}
	printf("\n");

	printf("key2 Ž�����: ");
	while(cntp2!=size2)
	{
		printf("%s ", p2->data);
		p2++;
		cntp2++;
	}
	printf("\n");*/

	free(arr1);
	free(arr2);

	printf("(key1�� key2 ������ �Ÿ�) = %d\n", distance);
}

void TreeHeight(TreeNode *root){
	printf("Ʈ���� ����: %d\n", get_height(root));
}

int get_node_count(TreeNode *node){
	int count = 0;
	if(node != NULL)
		count = 1 + get_node_count(node->left) + get_node_count(node->right);
	return count;
}

void num_of_node(TreeNode *root){
	printf("����� ����: %d\n", get_node_count(root));
}

void get_min_node(TreeNode *root){
	char min[MAX];
	while(root){
		strcpy(min, root->data);
		root = root->left;
	}
	printf("�ּ� Ű: %s\n", min);
}

void get_max_node(TreeNode *root){
	char max[MAX];
	while(root){
		strcpy(max, root->data);
		root = root->right;
	}
	printf("�ִ� Ű: %s\n", max);
}

void main(){
	char menu;
	TreeNode *root = NULL;

	while(1){
		print_menu();
		fflush(stdin);
		scanf("%c", &menu);
		switch(menu){
		case '1': insert_node(&root); break;
		case '2': delete_node(&root); break;
		case '3': preorder(root); break;
		case '4': inorder(root); break;
		case '5': postorder(root); break;
		case '6': search(root); break;
		case '7': TreeHeight(root); break;
		case '8': num_of_node(root); break;
		case '9': return;
		case 'a': get_min_node(root); break;
		case 'b': get_max_node(root); break;
		case 'A': LRP(root); break;
		case 'B': distance(root); break;
		default: printf("select error!!!\n"); break;
		}
	}
}