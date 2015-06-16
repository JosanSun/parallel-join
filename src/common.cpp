#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "common.h"

/*
 * index代表第几个数据文件文件，key[]存放主键,keyLen表示数组key的长度
 */
void loaddata(int index, unsigned int* key,int *keyLen)
{
	FILE *fpin ;
    char filename[NAMEMAX] = "./DataSet/";
    strcat(filename, filenames[index]);
	fpin = fopen(filename, "rb" );
	if ( fpin == NULL )
	{
		printf( "fopen for fpin error\n" );
		exit( 1 );
	}

	printf("loading file %s\n", filename);
    *keyLen = fread(key, sizeof(unsigned int), data_len[index], fpin);
	if ( *keyLen != data_len[index] )
	{
        if (feof(fpin)) {
           printf("Error reading %s: unexpected end of file\n", filename);
        }
        else if (ferror(fpin)) {
            fprintf(stderr, "Error reading %s: %s\n", filename, strerror(errno));
        }
        exit(1);
	}
	fclose( fpin );
}

