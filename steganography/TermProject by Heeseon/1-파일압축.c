/*
* 파일명 : jzip.c 
* 사용법 : # jzip [filename]
* 압축하고자 하는 filename를 입력하면 filename.gz이라는 압축파일이 
* 생성된다.  
*/

// zlib 헤더파일  
#include <zlib.h>
#include <zconf.h>

//#pragma comment(lib,"zlibstat.lib")



// 표준 C헤더파일
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

int main(int argc, char **argv)
{
	char    *filename   = NULL;
	char    *gzfilename = NULL;

	gzFile  *zfp;
	int     fd;
	int     n;
	char    buf[256];
	int     lerrno;

	if(argc !=2)
	{
		printf("Usage : jzip [file name]\n"); 
		exit(0);
	}
	filename = argv[1];
	// 압축파일의 이름은 filename.gz 으로 한다. 
	gzfilename = (char *)malloc(strlen(filename)*sizeof(char));
	sprintf(gzfilename, "%s.gz", filename);

	// 압축원본 파일이 존재하는지 확인한다. 
	if (access(filename, F_OK) != 0) 
	{
		printf("존재하지 않는 파일입니다\n");
		exit(0);
	}

	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		printf("file open error\n");
		exit(0);    
	}

	// 압축파일을 연다. 
	if ((zfp = gzopen(gzfilename, "wb")) == NULL)
	{
		exit(0);
	}

	// 원본파일을 에서 데이타를 읽어들이고 
	// gzwrite함수를 이용해서 데이터를 압축하고 파일에 쓴다.   
	while((n = read(fd, buf, 255)) > 0)
	{
		if (gzwrite(zfp, buf, n) < 0)
		{
			printf("%s\n",gzerror(zfp, &lerrno));
			exit(0);
		}
	}
	gzclose(zfp);
	printf("압축 성공 : %s => %s\n", filename, gzfilename);
}