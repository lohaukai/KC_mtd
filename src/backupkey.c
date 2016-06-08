/*
 * backupbackupkeys.c
 *
 *  Created on: Feb 1, 2016
 *      Author: Kevin Lo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "backupkey.h"

#define BackUpKeySize 4096
#define MaxNumOfBackUpKeys 5

int ReadBackUpKey(BackUpKey *backUpKey)
{
	backUpKey->content = mtdData_new(backUpKey->offesetContent, BackUpKeySize);
	if (ReadMtd(backUpKey->content, true) < 0)
		return -1;

	return 0;
}

int WriteBackUpKey(BackUpKey *backUpKey, char *filename)
{
	FILE *fp = fopen(filename, "r");
	fseek(fp, 0, SEEK_END);
	int fileLen = ftell(fp);
	rewind(fp);

	printf("write file length: %d\n", fileLen);

	backUpKey->content = mtdData_new(backUpKey->offesetContent, BackUpKeySize);
	fread(backUpKey->content.data, 1, fileLen, fp);

	if (WriteMtd(backUpKey->content) < 0)
		return -1;

	fclose(fp);
	return 0;
}

int DeletBackUpKey(BackUpKey *backUpKey)
{
	backUpKey->content = mtdData_new(backUpKey->offesetContent, BackUpKeySize);
	if (WriteMtd(backUpKey->content) < 0)
		return -1;

	return 0;
}

int ReadNumOfBackUPKeys(BackUpKeyStack *backUpKeyStack, bool printing)
{
	int NumOfBackUPKeys = -1;
	backUpKeyStack->NumOfBackUPKeys = mtdData_new(backUpKeyStack->offesetSize, SizeLength);
	if (ReadMtd(backUpKeyStack->NumOfBackUPKeys, false) < 0)
		return -1;

	NumOfBackUPKeys = bytesToInt(backUpKeyStack->NumOfBackUPKeys.data);
	if(printing)
	{
		if (NumOfBackUPKeys == MaxNumOfBackUpKeys)
			fprintf(stdout, "Backup Key Stack is full\n");
		else if (NumOfBackUPKeys == 0)
			fprintf(stdout, "Backup Key Stack is empty\n");
		else
			fprintf(stdout, "Number of backup keys: %d\n", NumOfBackUPKeys);
	}

	return NumOfBackUPKeys;
}

int WriteNumOfBackUPKeys(BackUpKeyStack *backUpKeyStack, int NumOfBackUPKeys)
{
	backUpKeyStack->NumOfBackUPKeys = mtdData_new(backUpKeyStack->offesetSize, SizeLength);
	intToByte(NumOfBackUPKeys, backUpKeyStack->NumOfBackUPKeys.data);
	if (WriteMtd(backUpKeyStack->NumOfBackUPKeys) < 0)
		return -1;

	return 0;
}

int ReadBackUpKeyStack(BackUpKeyStack *backUpKeyStack, int NumOfBackUPKeys)
{
	if (NumOfBackUPKeys > MaxNumOfBackUpKeys
			|| NumOfBackUPKeys > ReadNumOfBackUPKeys(backUpKeyStack, true))
	{
		printf("Key is out of stack range.\n");
		return -1;
	}
	else if (!NumOfBackUPKeys)
	{
		NumOfBackUPKeys = ReadNumOfBackUPKeys(backUpKeyStack, true);
		for (int i = 0; i < NumOfBackUPKeys; ++i)
			ReadBackUpKey(backUpKeyStack->backUpKeys + i);

	}
	else
		ReadBackUpKey(backUpKeyStack->backUpKeys + NumOfBackUPKeys - 1);

	return 0;
}

int WriteBackUpKeyStack(BackUpKeyStack *backUpKeyStack, char *filename)
{
	int NumOfBackUPKeys = ReadNumOfBackUPKeys(backUpKeyStack, true);

	if (NumOfBackUPKeys < MaxNumOfBackUpKeys)
		WriteBackUpKey(backUpKeyStack->backUpKeys + NumOfBackUPKeys, filename);
	else
		return -1;

	if (WriteNumOfBackUPKeys(backUpKeyStack, NumOfBackUPKeys + 1) < 0)
		return -1;

	return 0;
}

int DeletBackUpKeyStack(BackUpKeyStack *backUpKeyStack)
{
	int NumOfBackUPKeys = ReadNumOfBackUPKeys(backUpKeyStack, true) - 1;

	if (NumOfBackUPKeys >= 0)
		DeletBackUpKey(backUpKeyStack->backUpKeys + NumOfBackUPKeys);
	else
		return -1;

	if (WriteNumOfBackUPKeys(backUpKeyStack, NumOfBackUPKeys) < 0)
		return -1;

	return 0;
}

int DestroyBackUpKeyStack(BackUpKeyStack *backUpKeyStack)
{
	do
	{
		if (DeletBackUpKeyStack(backUpKeyStack) < 0)
			break;
	} while (ReadNumOfBackUPKeys(backUpKeyStack, false) > 0);

	return 0;
}
