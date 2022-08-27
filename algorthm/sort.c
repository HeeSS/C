//1492018 서희선 정렬 알고리즘
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int *heap;
	int heap_size;
} HeapType;
typedef struct QueueNode{
	int item;
	struct QueueNode *link;
} QueueNode;
typedef struct{
	QueueNode *front, *rear;
} QueueType;

void error(char *message) //error처리
void enqueue(QueueType *q, int item) //큐 삽입
int dequeue(QueueType *q) //큐 삭제
void print_list(int list[], int n) //정렬 결과 출력
void selection_sort(int list[], int n, int order) //선택정렬
void insertion_sort(int list[], int n, int order) //삽입정렬
void bubble_sort(int list[], int n, int order) //버블정렬
void merge(int list[], int sorted[], int left, int mid, int right, int order, int n) //합병
void merge_sort(int list[],int sorted[], int left, int right, int order, int n) //합병정렬
void insert_min_heap(HeapType *h, int item) //최소 히프 삽입
void insert_max_heap(HeapType *h, int item) //최대 히프 삽입
int delete_min_heap(HeapType *h) //최소 히프 삭제
int delete_max_heap(HeapType *h) //최대 히프 삭제
void heap_sort(int list[], int n, int order) //히프 정렬
int return_digits(int list[], int n) //자리수 반환
void radix_sort(int list[], int n, int order) //기수 정렬
int partition(int list[], int left, int right, int order, int n) //pivot위치 반환, 퀵 정렬
void quick_sort(int list[], int left, int right, int order, int n) //퀵 정렬
void inc_insertion_sort(int list[], int first, int last, int gap, int order) //gap(부분리스트) 정렬
void shell_sort(int list[], int n, int order)// 셸 정렬

int main(int argc, char *argv[])
{
	while(1)
	{
		char menu;
		int order, n=0, *data, i, *sorted = NULL;

		printf("=======================\n");
		printf("a) 선택 정렬\n");
		printf("b) 삽입 정렬\n");
		printf("c) 버블 정렬\n");
		printf("d) 합병 정렬\n");
		printf("e) 히프 정렬\n");
		printf("f) 기수 정렬\n");
		printf("g) 퀵 정렬\n");
		printf("h) 쉘 정렬\n");
		printf("x) 프로그램 종료\n");
		printf("=======================\n");
		printf("원하는 정렬을 선택하시오 : ");
		scanf(" %c", &menu);
		if(menu=='x')
			return 0;
		printf("=======================\n");
		printf("1) 오름차순\n");
		printf("0) 내림차순\n");
		printf("=======================\n");
		printf("차순을 선택하시오 : ");
		scanf(" %d", &order);

		if(argc==1)
		{
			char ch[100];

			data = (int*)malloc(sizeof(int)*50);

			for(i=0; i<50; i++)
			{
				printf("숫자 입력(50개이내) : ");
				scanf(" %s", &ch);
				if(strcmp(ch, "=")==0)	break;
				data[i] = atoi(ch);
				n++;
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
			data = (int*)malloc(sizeof(int)*n);
			for(i=0; i<n; i++)
			{
				fscanf(fp, " %d", &data[i]);
			}
			fclose(fp);
		}
		else
		{
			printf("input error!\n");	return 0;
		}

		printf("=======================\n");
		printf("\n정렬 전: ");	print_list(data, n);	printf("\n");

		switch(menu)
		{
		case 'a': selection_sort(data, n, order); break;
		case 'b': insertion_sort(data, n, order); break;
		case 'c': bubble_sort(data, n, order); break;
		case 'd': 
			sorted = (int*)malloc(sizeof(int)*n); 
			merge_sort(data, sorted, 0, n-1, order, n); 
			free(sorted); 
			break;
		case 'e': heap_sort(data, n, order); break;
		case 'f': radix_sort(data, n, order); break;
		case 'g': quick_sort(data, 0, n-1, order, n); break;
		case 'h': shell_sort(data, n, order); break;
		}

		printf("\n정렬 후: ");	print_list(data, n);	printf("\n");
		free(data);
	}
}
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
void enqueue(QueueType *q, int item)
{
	QueueNode *temp = (QueueNode*)malloc(sizeof(QueueNode));
	if(temp == NULL)
		error("Queue memory alloc error!");
	else
	{
		temp->item = item;
		temp->link = NULL;
		if(q->front==NULL)
		{
			q->front = temp;
			q->rear = temp;
		}
		else
		{
			q->rear->link = temp;
			q->rear = temp;
		}
	}
}
int dequeue(QueueType *q)
{
	QueueNode *temp = q->front;
	int item;
	if(q->front==NULL)
		error("Queue is empty!");
	else
	{
		item = temp->item;
		q->front = q->front->link;
		if(q->front==NULL)
			q->rear = NULL;
		free(temp);
		return item;
	}
}
void print_list(int list[], int n)
{
	int i;
	for(i=0; i<n; i++)
		printf("%d ", list[i]);
	printf("\n");
}
void selection_sort(int list[], int n, int order) 
{
	int i, j, least, temp;

	if(order)
		for(i=0; i<n-1; i++)
		{
			least = i;
			for(j=i+1; j<n; j++)
				if(list[j]<list[least])	least = j;

			//SWAP
			temp = list[i];
			list[i] = list[least];
			list[least] = temp;

			print_list(list, n);
		}
	else
		for(i=0; i<n-1; i++)
		{
			least = i;
			for(j=i+1; j<n; j++)
				if(list[j]>list[least])	least = j;

			//SWAP
			temp = list[i];
			list[i] = list[least];
			list[least] = temp;

			print_list(list, n);
		}
}
void insertion_sort(int list[], int n, int order) 
{
	int i, j, key;
	if(order)
		for(i=1; i<n; i++)
		{
			key = list[i];
			for(j=i-1; j>=0 && list[j]>key; j--)
				list[j+1] = list[j];
			list[j+1] = key;
			print_list(list, n);
		}
	else
		for(i=1; i<n; i++)
		{
			key = list[i];
			for(j=i-1; j>=0 && list[j]<key; j--)
				list[j+1] = list[j];
			list[j+1] = key;
			print_list(list, n);
		}
}
void bubble_sort(int list[], int n, int order) 
{
	int i, j, temp;
	if(order)
		for(i=n-1; i>0; i--)
		{
			for(j=0; j<i; j++)
			{
				if(list[j]>list[j+1])
				{
					//SWAP
					temp = list[j];
					list[j] = list[j+1];
					list[j+1] = temp;
				}
			}
			print_list(list, n);
		}
	else
		for(i=n-1; i>0; i--)
		{
			for(j=0; j<i; j++)
			{
				if(list[j]<list[j+1])
				{
					//SWAP
					temp = list[j];
					list[j] = list[j+1];
					list[j+1] = temp;
				}
			}
			print_list(list, n);
		}
}
void merge(int list[], int sorted[], int left, int mid, int right, int order, int n)
{
	int i, j, k, l;
	i = left; j = mid+1; k = left;
	if(order){
		while(i<=mid && j<=right)
		{
			if(list[i]<=list[j])
				sorted[k++] = list[i++];
			else
				sorted[k++] = list[j++];
		}}
	else{
		while(i<=mid && j<=right)
		{
			if(list[i]>=list[j])
				sorted[k++] = list[i++];
			else
				sorted[k++] = list[j++];
		}}
	if(i>mid)
		for(l=j; l<=right; l++)
			sorted[k++] = list[l];
	else
		for(l=i; l<=mid; l++)
			sorted[k++] = list[l];
	for(l=left; l<=right; l++)
		list[l] = sorted[l];

	print_list(list, n);
}
void merge_sort(int list[],int sorted[], int left, int right, int order, int n)
{
	int mid;
	if(left<right)
	{
		mid = (left+right)/2;
		merge_sort(list, sorted, left, mid, order, n);
		merge_sort(list, sorted, mid+1, right, order, n);
		merge(list, sorted, left, mid, right, order, n);
	}
}
void insert_min_heap(HeapType *h, int item)
{
	int i;
	i = ++(h->heap_size);

	while((i!=1) && (item < h->heap[i/2]))
	{
		h->heap[i] = h->heap[i/2];
		i /=2;
	}
	h->heap[i] = item;
}
void insert_max_heap(HeapType *h, int item)
{
	int i;
	i = ++(h->heap_size);

	while((i!=1) && (item > h->heap[i/2]))
	{
		h->heap[i] = h->heap[i/2];
		i /=2;
	}
	h->heap[i] = item;
}
int delete_min_heap(HeapType *h)
{
	int parent, child;
	int item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while(child <= h->heap_size)
	{
		if((child < h->heap_size) && (h->heap[child] > h->heap[child+1]))
			child++;
		if(temp <= h->heap[child]) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *=2;
	}
	h->heap[parent] = temp;
	return item;
}
int delete_max_heap(HeapType *h)
{
	int parent, child;
	int item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while(child <= h->heap_size)
	{
		if((child < h->heap_size) && (h->heap[child]) < h->heap[child+1])
			child++;
		if(temp >= h->heap[child]) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *=2;
	}
	h->heap[parent] = temp;
	return item;
}
void heap_sort(int list[], int n, int order)
{
	int i, j;
	HeapType h;
	h.heap = (int*)malloc(sizeof(int)*n);
	h.heap_size = 0;

	if(order)
	{
		printf("(Insert Heap)\n");
		for(i=0; i<n; i++)
		{
			insert_min_heap(&h, list[i]);
			for(j=1; j<=h.heap_size; j++)
				printf("%d ", h.heap[j]);
			printf("\n");
		}
		printf("\n(Delete Heap)\n");
		for(i=0; i<n; i++)
		{
			list[i] = delete_min_heap(&h);
			printf("delete %d", list[i]);
			printf(" / ");
			for(j=1; j<=h.heap_size; j++)
				printf("%d ", h.heap[j]);
			printf("\n");
		}
	}
	else
	{
		printf("(Insert Heap)\n");
		for(i=0; i<n; i++)
		{
			insert_max_heap(&h, list[i]);
			for(j=1; j<=h.heap_size; j++)
				printf("%d ", h.heap[j]);
			printf("\n");
		}
		printf("\n(Delete Heap)\n");
		for(i=0; i<n; i++)
		{
			list[i] = delete_max_heap(&h);
			printf("delete %d", list[i]);
			printf(" / ");
			for(j=1; j<=h.heap_size; j++)
				printf("%d ", h.heap[j]);
			printf("\n");
		}
	}
}
int return_digits(int list[], int n)
{
	int i, max, digit=1;
	max = list[0];
	for(i=1; i<n; i++)
	{
		if(max<list[i])
			max = list[i];
	}
	while(max>=10)
	{
		max/=10;
		digit++;
	}
	return digit;
}
void radix_sort(int list[], int n, int order)
{
	int i, b, d, BUCKETS=10, DIGITS, factor=1;
	QueueType queues[10];
	DIGITS = return_digits(list, n);

	for(b=0; b<BUCKETS; b++)
		queues[b].front = queues[b].rear = NULL;

	if(order)
		for(d=DIGITS-1; d>=0; d--)
		{
			for(i=0; i<n; i++)
				enqueue(&queues[(list[i]/factor)%10], list[i]);
			for(b=i=0; b<BUCKETS; b++)
				while(queues[b].front!=NULL)
					list[i++] = dequeue(&queues[b]);
			print_list(list, n);
			factor*=10;
		}
	else
		for(d=DIGITS-1; d>=0; d--)
		{
			for(i=0; i<n; i++)
				enqueue(&queues[(list[i]/factor)%10], list[i]);
			i=0;
			for(b=BUCKETS-1; b>=0; b--)
				while(queues[b].front!=NULL)
					list[i++] = dequeue(&queues[b]);
			print_list(list, n);
			factor*=10;
		}
}
int partition(int list[], int left, int right, int order, int n)
{
	int pivot, temp;
	int low, high;
	low = left;
	high = right+1;
	pivot = list[left];
	printf("(pivot: %d)\n", pivot);
	if(order){
		do{
			do{
				low++;
			}while(low <= right && list[low] < pivot);
			do{
				high--;
			}while(high >= left && list[high] > pivot);
			if(low<high)
			{
				temp = list[low];
				list[low] = list[high];
				list[high] = temp;
				print_list(list, n);
			}
		}while(low<high);
	}
	else{
		do{
			do{
				low++;
			}while(low <= right && list[low] > pivot);
			do{
				high--;
			}while(high >= left && list[high] < pivot);
			if(low<high)
			{
				temp = list[low];
				list[low] = list[high];
				list[high] = temp;
				print_list(list, n);
			}
		}while(low<high);
	}
	temp = list[left];
	list[left] = list[high];
	list[high] = temp;
	print_list(list, n);
	return high;
}
void quick_sort(int list[], int left, int right, int order, int n)
{
	if(left<right)
	{
		int q = partition(list, left, right, order, n);
		quick_sort(list, left, q-1, order, n);
		quick_sort(list, q+1, right, order, n);
	}
}
void inc_insertion_sort(int list[], int first, int last, int gap, int order)
{
	int i, j, key;
	if(order)
		for(i=first+gap; i<=last; i=i+gap)
		{
			key = list[i];
			for(j=i-gap; j>=first && key<list[j]; j=j-gap)
				list[j+gap] = list[j];
			list[j+gap] = key;
		}
	else
		for(i=first+gap; i<=last; i=i+gap)
		{
			key = list[i];
			for(j=i-gap; j>=first && key>list[j]; j=j-gap)
				list[j+gap] = list[j];
			list[j+gap] = key;
		}
}
void shell_sort(int list[], int n, int order)
{
	int i, gap;
	for(gap=n/2; gap>0; gap=gap/2)
	{
		if((gap%2)==0)	gap++;
		printf("(gap: %d)\n", gap);
		for(i=0; i<gap; i++)
		{
			inc_insertion_sort(list, i, n-1, gap, order);
			print_list(list, n);
		}
	}
}
