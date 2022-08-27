#include <zlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    char *filename = NULL;

    gzFile *zfp;
    char buf[1024];

    if (argc != 2)
    {
        printf("Usage : jcat [file name]\n");
        exit(0);
    }
    filename = argv[1];

    if ((zfp = gzopen(filename, "rb")) == NULL)
    {
        exit(0);
    }

    while(gzgets(zfp, buf, 1023) != NULL)
    {
        printf("%s", buf);
    }

    gzclose(zfp);
}