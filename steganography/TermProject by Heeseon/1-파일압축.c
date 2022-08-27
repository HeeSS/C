/*
* ���ϸ� : jzip.c 
* ���� : # jzip [filename]
* �����ϰ��� �ϴ� filename�� �Է��ϸ� filename.gz�̶�� ���������� 
* �����ȴ�.  
*/

// zlib �������  
#include <zlib.h>
#include <zconf.h>

//#pragma comment(lib,"zlibstat.lib")



// ǥ�� C�������
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
	// ���������� �̸��� filename.gz ���� �Ѵ�. 
	gzfilename = (char *)malloc(strlen(filename)*sizeof(char));
	sprintf(gzfilename, "%s.gz", filename);

	// ������� ������ �����ϴ��� Ȯ���Ѵ�. 
	if (access(filename, F_OK) != 0) 
	{
		printf("�������� �ʴ� �����Դϴ�\n");
		exit(0);
	}

	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		printf("file open error\n");
		exit(0);    
	}

	// ���������� ����. 
	if ((zfp = gzopen(gzfilename, "wb")) == NULL)
	{
		exit(0);
	}

	// ���������� ���� ����Ÿ�� �о���̰� 
	// gzwrite�Լ��� �̿��ؼ� �����͸� �����ϰ� ���Ͽ� ����.   
	while((n = read(fd, buf, 255)) > 0)
	{
		if (gzwrite(zfp, buf, n) < 0)
		{
			printf("%s\n",gzerror(zfp, &lerrno));
			exit(0);
		}
	}
	gzclose(zfp);
	printf("���� ���� : %s => %s\n", filename, gzfilename);
}