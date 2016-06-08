/*
 * key.c
 *
 *  Created on: Jan 30, 2016
 *      Author: Kevin Lo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "key.h"

#define MaxKeySize 4096

int ReadKey(Key *key)
{
	key->content = mtdData_new(key->offesetContent, ReadKeySize(key));
	if (ReadMtd(key->content, true) < 0)
		return -1;

	return 0;
}

int ReadKeySize(Key *key)
{
	key->size = mtdData_new(key->offesetSize, SizeLength);
	if (ReadMtd(key->size, false) < 0)
		return 0;

	return bytesToInt(key->size.data);
}

int WriteKey(Key *key, char *filename)
{
	FILE *fp = fopen(filename, "r");
	fseek(fp, 0, SEEK_END);
	int fileLen = ftell(fp);
	rewind(fp);

	key->size = mtdData_new(key->offesetSize, SizeLength);
	intToByte(fileLen, key->size.data);

	key->content = mtdData_new(key->offesetContent, fileLen);
	fread(key->content.data, 1, fileLen, fp);

	if (WriteMtd(key->size) < 0 || WriteMtd(key->content) < 0)
		return -1;

	fclose(fp);
	return 0;
}

int DeleteKey(Key *key)
{
	key->size = mtdData_new(key->offesetSize, SizeLength);
	if (WriteMtd(key->size) < 0)
		return -1;

	key->content = mtdData_new(key->offesetContent, MaxKeySize);
	if (WriteMtd(key->content) < 0)
		return -1;

	return 0;
}
