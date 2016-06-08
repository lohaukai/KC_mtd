/*
 * mtd.c
 *
 *  Created on: Jan 30, 2016
 *      Author: Kevin Lo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include "mtd.h"

#define PRINT_CONTENT(x, y) \
	printf("Content Size: %d\n" \
			"Content Data: \n" \
			"%s", x, y)

static int mtdFd;

int OpenMtdFd(char* filename)
{
	mtdFd = open(filename, O_RDWR);
	if (mtdFd < 0)
	{
		perror("open mtdblock failed");
		exit(1);
	}
	return mtdFd;
}

void CloseMtdFd()
{
	if (mtdFd < 0)
		return;
	close(mtdFd);
}

MtdData mtdData_new(int offset, int length)
{
	MtdData mtdData;

	mtdData.offset = offset;
	mtdData.length = length;
	mtdData.data = malloc(length);
	if (mtdData.data == NULL)
	{
		if (mtdData.length != 0)
			fprintf(stderr, "%s\n", strerror(errno));
		else
			printf("Content Size: %d\n"
					"Content Data: NULL\n", mtdData.length);
		CloseMtdFd();
		exit(1);
	}
	mtdData_clean(mtdData);

	return mtdData;
}

void mtdData_clean(MtdData mtdData)
{
	memset(mtdData.data, 0, mtdData.length);
}

void mtdData_delete(MtdData mtdData)
{
	mtdData.offset = 0;
	mtdData.length = 0;
	free(mtdData.data);
}

int ReadMtd(MtdData mtdData, bool printing)
{
	if (mtdFd < 0)
		return -1;

	lseek(mtdFd, mtdData.offset, SEEK_SET);
	read(mtdFd, mtdData.data, mtdData.length);

	if(printing)
		PRINT_CONTENT(mtdData.length, mtdData.data);

	return 0;
}

int WriteMtd(MtdData mtdData)
{
	if (mtdFd < 0)
		return -1;

	lseek(mtdFd, mtdData.offset, SEEK_SET);
	write(mtdFd, mtdData.data, mtdData.length);

	return 0;
}
