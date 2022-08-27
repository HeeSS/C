#include <stdio.h>
#include <stdlib.h>
#define ROWS 3
#define COLS 3
#define MAX_TERMS 10 

typedef struct { 
    int row; 
    int col; 
    int value; 
} element; 

typedef struct SparseMatrix {
	element data[MAX_TERMS];
	int rows;	// 행의 개수
	int cols;	// 열의 개수
	int terms; 	// 0이 아닌 항의 개수
} SparseMatrix;

void print_matrix(SparseMatrix m){
	int i;
	for(i=0;i<m.terms;i++){
		if(m.data[i].value!=0)
				printf("%d | %d %d %d\n", i, m.data[i].row, m.data[i].col, m.data[i].value);
	}
	printf("\n");
}

//// 희소 행렬 덧셈 함수
//void sparse_matrix_add(int A[ROWS][COLS], int B[ROWS][COLS], int C[ROWS][COLS]){	
//	int r,c;
//	for(r=0;r<ROWS;r++)
//		for(c=0;c<COLS;c++)
//			C[r][c] = A[r][c] + B[r][c];
//}
// 희소 행렬 덧셈 함수
SparseMatrix sparse_matrix_add2(SparseMatrix a, SparseMatrix b){
	SparseMatrix c;
	int ca=0, cb=0, cc=0;
	// 크기가 같은지를 확인
	if( a.rows != b.rows || a.cols != b.cols ){
		fprintf(stderr,"희소행렬 크기에러\n");
		exit(1);
	}
	c.rows = a.rows;
	c.cols = a.cols;
	c.terms = 0;

	while( ca < a.terms && cb < b.terms ){
		int inda = a.data[ca].row * a.cols + a.data[ca].col;
		int indb = b.data[cb].row * b.cols + b.data[cb].col;
		if( inda < indb) {
			// b 항목이 더 나중에 와야 함
			c.data[cc++] = a.data[ca++];
		}
		else if( inda == indb ){
			// a와 b가 같은 위치
			c.data[cc].row = a.data[ca].row;
			c.data[cc].col = a.data[ca].col;
			c.data[cc++].value = a.data[ca++].value +
					      b.data[cb++].value;
		}
		else 
			c.data[cc++] = b.data[cb++];
		
	}
	// 나머지항들을 옮긴다.
	for(; ca < a.terms; ca++)
		c.data[cc++] = a.data[ca++];
	for(; cb < b.terms; cb++)
		c.data[cc++] = b.data[cb++];
	c.terms = cc;
	return c;
}
// 주함수
main(){
	SparseMatrix m1 = {	{{ 0,0,2 },{ 1,2,3 },{ 2,2,1 }}, 3,3,3 };
	SparseMatrix m2 = {	{{ 0,1,4 },{ 1,2,5 }, { 2,0,3 }, { 2,2,2 }}, 3,3,4 };
	SparseMatrix m3;

	m3 = sparse_matrix_add2(m1, m2);

	print_matrix(m1);

	print_matrix(m2);

	print_matrix(m3);
}

//#if 0
//// 주함수
//main()
//{
//	int array1[ROWS][COLS] = {	{ 2,3,0 },
//					{ 8,9,1 },
//					{ 7,0,5 } };
//	int array2[ROWS][COLS] = {	{ 1,0,0 },
//					{ 1,0,0 },
//					{ 1,0,0 } };
//	int array3[ROWS][COLS];
//	sparse_matrix_add(array1,array2,array3);
//}
//#endif