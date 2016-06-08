/*
 * common.h
 *
 *  Created on: Jan 30, 2016
 *      Author: Kevin Lo
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "mtd.h"

#define SizeLength 4

int bytesToInt(uint8_t* bytes);
void intToByte(int i, uint8_t *bytes);
void show();
void usage();

typedef enum
{
	OffsetSelfCertSize = 0,
	OffsetSelfKeySize = 4,
	OffsetImportCertSize = 8,
	OffsetImportKeySize = 12,
	OffsetCsrKeySize = 16400,
	OffsetCsrCertSize = 16404,
	OffsetNumOfBackUpKeys = 24600,
} OffesetSize;

typedef enum
{
	OffsetSelfCert = 16,
	OffsetSelfKey = 4112,
	OffsetImportKey = 8208,
	OffsetImportCert = 12304,
	OffsetCsrKey = 16408,
	OffsetCsrCert = 20504,
	OffsetBackUpKey1 = 24604,
	OffsetBackUpKey2 = 28700,
	OffsetBackUpKey3 = 32796,
	OffsetBackUpKey4 = 36892,
	OffsetBackUpKey5 = 40988,
} OffesetContent;

#endif /* COMMON_H_ */
