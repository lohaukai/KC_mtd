/*
 * backupkey.h
 *
 *  Created on: Feb 1, 2016
 *      Author: Kevin Lo
 */

#include "common.h"

#ifndef BACKUPKEY_H_
#define BACKUPKEY_H_

typedef struct
{
	OffesetContent offesetContent;
	MtdData content;

} BackUpKey;

typedef struct
{
	OffesetSize offesetSize;
	MtdData NumOfBackUPKeys;
	BackUpKey *backUpKeys;

} BackUpKeyStack;

//int ReadBackUpKey(BackUpKey *backUpKey);
//int WriteBackUpKey(BackUpKey *backUpKey);
//int DeletBackUpKey(BackUpKey *backUpKey);

int ReadNumOfBackUPKeys(BackUpKeyStack *backUpKeyStack, bool printing);
//int WriteNumOfBackUPKeys(BackUpKeyStack *backUpKeyStack, int NumOfBackUPKeys);

int ReadBackUpKeyStack(BackUpKeyStack *backUpKeyStack, int NumOfBackUPKeys);
int WriteBackUpKeyStack(BackUpKeyStack *backUpKeyStack, char *filename);
int DeletBackUpKeyStack(BackUpKeyStack *backUpKeyStack);
int DestroyBackUpKeyStack(BackUpKeyStack *backUpKeyStack);

#endif /* BACKUPKEY_H_ */
