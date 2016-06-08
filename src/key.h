/*
 * key.h
 *
 *  Created on: Jan 30, 2016
 *      Author: Kevin Lo
 */

#ifndef KEY_H_
#define KEY_H_

#include "common.h"

typedef struct
{
	OffesetSize offesetSize;
	MtdData size;
	OffesetContent offesetContent;
	MtdData content;

} Key;

int ReadKey(Key *key);
int ReadKeySize(Key *key);
int WriteKey(Key *key, char *filename);
int DeleteKey(Key *key);

#endif /* KEY_H_ */
