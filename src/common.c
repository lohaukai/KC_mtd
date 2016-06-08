/*
 * common.c
 *
 *  Created on: Feb 2, 2016
 *      Author: root
 */

#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bytesToInt(uint8_t* bytes)
{
	int addr = bytes[0] & 0xFF;
	addr |= ((bytes[1] << 8) & 0xFF00);
	addr |= ((bytes[2] << 16) & 0xFF0000);
	addr |= ((bytes[3] << 24) & 0xFF000000);
	return addr;
}

void intToByte(int i, uint8_t *bytes)
{
	memset(bytes, 0, sizeof(uint8_t) * 4);
	bytes[0] = (uint8_t) (0xff & i);
	bytes[1] = (uint8_t) ((0xff00 & i) >> 8);
	bytes[2] = (uint8_t) ((0xff0000 & i) >> 16);
	bytes[3] = (uint8_t) ((0xff000000 & i) >> 24);
	return;
}

void usage()
{
	fprintf(stderr, "\nUsage: KC_mtd [Option] [ContentType] [File]\n"
			"KCodes program for modifying mtdblock5\n"
			"[Option]\n"
			" -s\tShow composition of mtdblock5\n"
			" -r\tRead data\n"
			" -d\tDelete data\n"
			" -w\tWrite file into mtdblock\n"
			"[ContentType]\n"
			" \tSelfKey, SelfCert, ImportKey, ImportCert, CsrKey, CsrCert,\n"
			" \tSelfKeySize, SelfCertSize, ImportKeySize, ImportCertSize, CsrKeySize, CsrCertSize,\n"
			" \tBackupKey, BackupKeyN (N = 1 ~ 5), BackupKeyAll, NumOfBackUpKeys\n"
			"[File]\n"
			" \tFile to be written into mtdblock\n\n");
}

void show()
{
	fprintf(stderr, "\t  0------4------8------12------\n"
			"\t  | self | self |import|import|\n"
			"\t  | cert | key  | cert | key  |\n"
			"\t  | size | size | size | size |\n"
			"\t 16----------------------------\n"
			"\t  |                           |\n"
			"\t  |        self cert          |\n"
			"\t  |                           |\n"
			"\t4112--------------------------|\n"
			"\t  |                           |\n"
			"\t  |        self key           |\n"
			"\t  |                           |\n"
			"\t8208--------------------------|\n"
			"\t  |                           |\n"
			"\t  |       import key          |\n"
			"\t  |                           |\n"
			"\t12304-------------------------|\n"
			"\t  |                           |\n"
			"\t  |       import cert         |\n"
			"\t  |                           |\n"
			"\t16400---------16404-----------|\n"
			"\t  |     csr     |             |\n"
			"\t  |     key     |     csr     |\n"
			"\t  |     size    |     size    |\n"
			"\t16408-------------------------|\n"
			"\t  |                           |\n"
			"\t  |          csr key          |\n"
			"\t  |                           |\n"
			"\t20504-------------------------|\n"
			"\t  |                           |\n"
			"\t  |         csr cert          |\n"
			"\t  |                           |\n"
			"\t24600-------------------------|\n"
			"\t  |     num of backup keys    |\n"
			"\t24604-------------------------|\n"
			"\t  |                           |\n"
			"\t  |       backup key 1        |\n"
			"\t  |                           |\n"
			"\t28700-------------------------|\n"
			"\t  |                           |\n"
			"\t  |       backup key 2        |\n"
			"\t  |                           |\n"
			"\t32796-------------------------|\n"
			"\t  |                           |\n"
			"\t  |       backup key 3        |\n"
			"\t  |                           |\n"
			"\t36892-------------------------|\n"
			"\t  |                           |\n"
			"\t  |       backup key 4        |\n"
			"\t  |                           |\n"
			"\t40988-------------------------|\n"
			"\t  |                           |\n"
			"\t  |       backup key 5        |\n"
			"\t  |                           |\n"
			"\t  ------------------------45084\n");
	return;

}
