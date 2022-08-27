#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//main
void extract (void);	//그림에서 숨은파일 꺼내기
void embed (void);	//그림에 파일 숨기기

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
		printf("\n무엇을 하고 싶으신가요?\n\n");
		printf("1) 그림에서 숨은파일 꺼내기\n");
		printf("2) 그림에 파일 숨기기\n");
		printf("0) 종료\n\n");
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

//Extract : bmp --> file (그림에서 숨은파일 꺼내기)
void extract()
{
	FILE *image_in;

	unsigned char header[14];
	unsigned char info[40];
	unsigned char *image;
	int imageSize;
	int embeddedLength;
	char embeddedName[80];

	image_in = askAndOpen("스테가노이미지 파일의 이름 입력: ", 'r');

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

//크기 반납
int searchForFile(unsigned char image[], char filename[])
{
    unsigned char leader[86];
    int i;
    int j;
    char *p_leader = leader;
    char *p_image  = image;
 
    for (i=0; i<86; i++, p_leader++)                                                      
        for (j=0; j<8; j++, p_image++)
           *p_leader = ( *p_leader << 1 ) | ( *p_image & 1 ) ;	//★★★★
 
	//첫 두글자가 KS이면 embedded 파일 
    if ( (leader[0] == 'K') && (leader[1] == 'S') )                                       
    {                                                                                     
        for (i=0; i<79; i++)
            filename[i] = (leader[i+2] == '*') ? 0 : leader[i+2] ;       //★★★★                 
        return (leader[82] + 256*( leader[83] + 256*(leader[84] + 256 * leader[85])));    //길이리턴
    }
    else                                                                                  
        return (0);                                                                      //숨겨진파일이없으면 0리턴
 
}

void saveFile(unsigned char image[], char filename[], int filelength)	//★★★★
{
 
}

//Embed : file -> bmp (그림에 파일 숨기기)
void embed (void)
{
    FILE *originalBMP  ; //사용할 이미지 파일
    FILE *embeddedFile ; //숨길파일
    FILE *alteredBMP   ;
    unsigned char header[14];  //bmp의 헤더 정보 저장                                                          
    unsigned char info  [40];  //bmp의 info section저장                                                         
    unsigned char *image;      //image를 가리키는 포인터                                                           
    int imageSize;             //image의 data part size                                              
 
 
    unsigned char *embeddedData;     //embedded파일 data를 가리킬 포인터                                                    
    int embeddedLength;      //embedded파일의 길이                                                
    char embeddedName[80];   //embedded파일의 이름                                               
 
 

    originalBMP = askAndOpen("사용할 이미지 파일의 이름 입력: ",'r');          //사용할 이미지 파일 열기
    imageSize = BMPheaders( originalBMP, header, info );         //사용할 이미지 파일의 사이즈                     
    if ( NULL == (image = (unsigned char*)malloc(imageSize))             ) exit(5);      //사용할 이미지의 image section을 저장할 메모리 할당
    if ( imageSize != fread(image, sizeof(char), imageSize, originalBMP) ) exit(6);      //사용할 이미지의 image section 읽기
    fclose( originalBMP  );                                                               
 
 
  
    do                                                                                    
    {
      printf("=================================================================\n");
      printf("숨길 파일의 이름입력: ");
      fgets(embeddedName,80,stdin);                                                      
  /*    if (embeddedName[0]=='*') exit (0);      */                                           
      embeddedName[strlen(embeddedName)-1] = 0;          //개행문자 지움                               
    }
    while (NULL == (embeddedFile  = fopen(embeddedName,"rb")));
 
 
    if ( NULL == (embeddedData = (unsigned char*)malloc(imageSize/8))    ) exit(7);      //embedded파일을 저장할 메모리 할당
    embeddedLength = fread(embeddedData, sizeof(unsigned char), (imageSize/8), embeddedFile);	//embedded파일 읽기
    fclose(embeddedFile);                                                               
 
    if (embeddedLength >(imageSize/8 - 56) )
    {
        printf("File too large to embed ");
        exit (8);
    }
 
 
	//embedded data를 이미지에 넣기		//★★★★★
    EmbedFile (image, embeddedName, embeddedData, embeddedLength);
    free (embeddedData);
 

	//결과물에 데이터쓰기
    alteredBMP = askAndOpen("Please enter name of output bmp         : ",'w');         
    fwrite(header, sizeof(unsigned char), 14,        alteredBMP);     //header쓰기                    
    fwrite(info, sizeof(unsigned char), 40,        alteredBMP);       //info쓰기                  
    fwrite(image, sizeof(unsigned char), imageSize, alteredBMP);      //image쓰기                  
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