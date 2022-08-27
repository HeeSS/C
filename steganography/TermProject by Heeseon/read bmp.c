#include<stdio.h> 
#include<stdlib.h> 

void main() 
{ 
	int c, i=0, j=0, f=0; 
	FILE *fp, *fp1, *fp2; 

	fp=fopen("rose.bmp", "rb");  

	if(fp==NULL) 
	{ 
		printf("읽기에러\n");  		
		return ;  
	}  

	printf("비트맵파일 읽기 성공\n"); 

	if((fp1=fopen("rose.txt","w"))==NULL) 
	{ 
		printf("생성에러\n");  
		fclose(fp); 
		return ;  
	} 

	fp2=fopen("rose2.bmp","w");
	while((c=fgetc(fp))!=EOF) // fgetc함수로 읽어들입니다. 
	{ 
		if(c=='F')
			fprintf(fp1,"0"); 
		else
		fprintf(fp1,"%d",c); 
	}


	fseek(fp, 0, SEEK_SET); 
	printf("텍스트파일 쓰기 성공\n"); 
	while((c=fgetc(fp))!=EOF) // fgetc함수로 읽어들입니다. 
	{ 
		fprintf(fp1,"%02X ",c); 
		i++;
		j++;
		if(j==54){
			fprintf(fp1,"\n\n\n"); 
			for(f=0; f<i; f++){
				fprintf(fp1,"   ");
			}
		}
		if(i==16){
			fprintf(fp1,"\n"); 
			i=0;
		}
	} 

	printf("비트맵 헥사값 변환 성공\n");system("pause"); 

	//fp2=fopen("rose2.bmp","w");
	//while((c=fgetc(fp1))!=EOF) // fgetc함수로 읽어들입니다. 
	//{ 
	//	fprintf(fp2,"%d\n",c); 
	//} 

	fclose(fp); 
	fclose(fp1); 
	fclose(fp2);
}

