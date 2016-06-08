/*
 * mtd.h
 *
 *  Created on: Jan 30, 2016
 *      Author: Kevin Lo
 */

#ifndef MTD_H_
#define MTD_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
	int offset;
	int length;
	uint8_t *data;

} MtdData;

int OpenMtdFd(char* filename);
void CloseMtdFd();

MtdData mtdData_new(int offset, int length);
void mtdData_clean(MtdData mtdData);
void mtdData_delete(MtdData mtdData);

int ReadMtd(MtdData mtdData, bool printing);
int WriteMtd(MtdData mtdData);

#endif /* MTD_H_ */
