#include<stdio.h> 
#include<stdlib.h> 

void main() 
{ 
	int c, i=0, j=0, f=0; 
	FILE *fp, *fp1, *fp2; 

	fp=fopen("rose.bmp", "rb");  

	if(fp==NULL) 
	{ 
		printf("�б⿡��\n");  		
		return ;  
	}  

	printf("��Ʈ������ �б� ����\n"); 

	if((fp1=fopen("rose.txt","w"))==NULL) 
	{ 
		printf("��������\n");  
		fclose(fp); 
		return ;  
	} 

	fp2=fopen("rose2.bmp","w");
	while((c=fgetc(fp))!=EOF) // fgetc�Լ��� �о���Դϴ�. 
	{ 
		if(c=='F')
			fprintf(fp1,"0"); 
		else
		fprintf(fp1,"%d",c); 
	}


	fseek(fp, 0, SEEK_SET); 
	printf("�ؽ�Ʈ���� ���� ����\n"); 
	while((c=fgetc(fp))!=EOF) // fgetc�Լ��� �о���Դϴ�. 
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

	printf("��Ʈ�� ��簪 ��ȯ ����\n");system("pause"); 

	//fp2=fopen("rose2.bmp","w");
	//while((c=fgetc(fp1))!=EOF) // fgetc�Լ��� �о���Դϴ�. 
	//{ 
	//	fprintf(fp2,"%d\n",c); 
	//} 

	fclose(fp); 
	fclose(fp1); 
	fclose(fp2);
}

