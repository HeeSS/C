#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//main
void extract (void);	//�׸����� �������� ������
void embed (void);	//�׸��� ���� �����

//extract
FILE *askAndOpen (char message[], char mode);
int BMPheaders (FILE *image_in, unsigned char header[], unsigned char info[]);
int searchForFile (unsigned char image[], char filename[]);
void saveFile (unsigned char image[], char filename[], int im_size);

//embed
FILE* askAndOpen   (char          message[], char          mode                              );
int   BMPheaders   ( FILE*        image_in,  unsigned char header[],   unsigned char info[]  );
void  EmbedFile    (unsigned char image[],   char filename[],          unsigned char data[], int filelength );

int main()
{
	char choice;

	do
	{
		printf("\n������ �ϰ� �����Ű���?\n\n");
		printf("1) �׸����� �������� ������\n");
		printf("2) �׸��� ���� �����\n");
		printf("0) ����\n\n");
		printf(" >> ");

		choice = getchar();
		getchar();

	} while ((choice != '0') && (choice !='1') && (choice !='2'));

	if (choice =='1')
		extract();
	else if (choice == '2')
		embed();
	else if (choice == '0')
		return 0;
}

//Extract : bmp --> file (�׸����� �������� ������)
void extract()
{
	FILE *image_in;

	unsigned char header[14];
	unsigned char info[40];
	unsigned char *image;
	int imageSize;
	int embeddedLength;
	char embeddedName[80];

	image_in = askAndOpen("���װ����̹��� ������ �̸� �Է�: ", 'r');

	imageSize = BMPheaders(image_in, header, info);

	if ((image = (unsigned char*) malloc (imageSize)) == NULL)
	{
		printf("image = (unsigned char*) malloc (imageSize)) == NULL !!!\n");
		exit(1);
	}

	if (imageSize != fread(image, sizeof(char), imageSize, image_in))
	{
		printf("imageSize != fread(image, sizeof(char), imageSize, image_in) !!!\n");
		exit(1);
	}

	embeddedLength = searchForFile(image, embeddedName);

	if (embeddedLength)
		saveFile (image, embeddedName, embeddedLength);

	free (image);
	fclose (image_in);

}

//ũ�� �ݳ�
int searchForFile(unsigned char image[], char filename[])
{
    unsigned char leader[86];
    int i;
    int j;
    char *p_leader = leader;
    char *p_image  = image;
 
    for (i=0; i<86; i++, p_leader++)                                                      
        for (j=0; j<8; j++, p_image++)
           *p_leader = ( *p_leader << 1 ) | ( *p_image & 1 ) ;	//�ڡڡڡ�
 
	//ù �α��ڰ� KS�̸� embedded ���� 
    if ( (leader[0] == 'K') && (leader[1] == 'S') )                                       
    {                                                                                     
        for (i=0; i<79; i++)
            filename[i] = (leader[i+2] == '*') ? 0 : leader[i+2] ;       //�ڡڡڡ�                 
        return (leader[82] + 256*( leader[83] + 256*(leader[84] + 256 * leader[85])));    //���̸���
    }
    else                                                                                  
        return (0);                                                                      //�����������̾����� 0����
 
}

void saveFile(unsigned char image[], char filename[], int filelength)	//�ڡڡڡ�
{
 
}

//Embed : file -> bmp (�׸��� ���� �����)
void embed (void)
{
    FILE *originalBMP  ; //����� �̹��� ����
    FILE *embeddedFile ; //��������
    FILE *alteredBMP   ;
    unsigned char header[14];  //bmp�� ��� ���� ����                                                          
    unsigned char info  [40];  //bmp�� info section����                                                         
    unsigned char *image;      //image�� ����Ű�� ������                                                           
    int imageSize;             //image�� data part size                                              
 
 
    unsigned char *embeddedData;     //embedded���� data�� ����ų ������                                                    
    int embeddedLength;      //embedded������ ����                                                
    char embeddedName[80];   //embedded������ �̸�                                               
 
 

    originalBMP = askAndOpen("����� �̹��� ������ �̸� �Է�: ",'r');          //����� �̹��� ���� ����
    imageSize = BMPheaders( originalBMP, header, info );         //����� �̹��� ������ ������                     
    if ( NULL == (image = (unsigned char*)malloc(imageSize))             ) exit(5);      //����� �̹����� image section�� ������ �޸� �Ҵ�
    if ( imageSize != fread(image, sizeof(char), imageSize, originalBMP) ) exit(6);      //����� �̹����� image section �б�
    fclose( originalBMP  );                                                               
 
 
  
    do                                                                                    
    {
      printf("=================================================================\n");
      printf("���� ������ �̸��Է�: ");
      fgets(embeddedName,80,stdin);                                                      
  /*    if (embeddedName[0]=='*') exit (0);      */                                           
      embeddedName[strlen(embeddedName)-1] = 0;          //���๮�� ����                               
    }
    while (NULL == (embeddedFile  = fopen(embeddedName,"rb")));
 
 
    if ( NULL == (embeddedData = (unsigned char*)malloc(imageSize/8))    ) exit(7);      //embedded������ ������ �޸� �Ҵ�
    embeddedLength = fread(embeddedData, sizeof(unsigned char), (imageSize/8), embeddedFile);	//embedded���� �б�
    fclose(embeddedFile);                                                               
 
    if (embeddedLength >(imageSize/8 - 56) )
    {
        printf("File too large to embed ");
        exit (8);
    }
 
 
	//embedded data�� �̹����� �ֱ�		//�ڡڡڡڡ�
    EmbedFile (image, embeddedName, embeddedData, embeddedLength);
    free (embeddedData);
 

	//������� �����;���
    alteredBMP = askAndOpen("Please enter name of output bmp         : ",'w');         
    fwrite(header, sizeof(unsigned char), 14,        alteredBMP);     //header����                    
    fwrite(info, sizeof(unsigned char), 40,        alteredBMP);       //info����                  
    fwrite(image, sizeof(unsigned char), imageSize, alteredBMP);      //image����                  
    fclose( alteredBMP   );
 
 
    free (image);
 
}

void  EmbedFile (unsigned char image[], char filename[], unsigned char data[], int filelength )
{
}

FILE* askAndOpen(char message[], char mode)
{ 
    char filename[80];
    char modestring[3] = {'x','b',0};
    FILE* filef;
 
    modestring[0] = mode;
 
    do
    {
      printf("=================================================================\n");
      printf("%s",message);
      fgets(filename,80,stdin);                                                          
      if (filename[0]=='*') exit (0);                                                   
      filename[strlen(filename)-1] = 0;                                                
    }
    while (NULL == (filef  = fopen(filename,modestring)));
 
    return (filef);
}

int BMPheaders( FILE* image_in, unsigned char header[], unsigned char info[] )
{
    if ( 14 != fread( header, sizeof(char), 14, image_in)) exit (1);                      
    if ( 40 != fread( info,   sizeof(char), 40, image_in)) exit (2);                      
    if ( (header[0] != 'B')   ||   (header[1] != 'M')    ) exit (3);                     
    if ( 24 != info[14]                                  ) exit (4);                     
 
    return ( info[20] + (info[21]  + (info[22]  + info[23]  * 256 ) * 256 ) * 256);
}