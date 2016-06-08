/*
 * cert.c
 *
 *  Created on: Jan 30, 2016
 *      Author: Kevin Lo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "cert.h"

#define MaxCertSize 4096

int ReadCert(Cert *cert)
{
	cert->content = mtdData_new(cert->offesetContent, ReadCertSize(cert));
	if (ReadMtd(cert->content, true) < 0)
		return -1;

	return 0;
}

int ReadCertSize(Cert *cert)
{
	cert->size = mtdData_new(cert->offesetSize, SizeLength);
	if (ReadMtd(cert->size, false) < 0)
		return 0;

	return bytesToInt(cert->size.data);
}

int WriteCert(Cert *cert, char *filename)
{
	FILE *fp = fopen(filename, "r");
	fseek(fp, 0, SEEK_END);
	int fileLen = ftell(fp);
	rewind(fp);

	cert->size = mtdData_new(cert->offesetSize, SizeLength);
	intToByte(fileLen, cert->size.data);

	cert->content = mtdData_new(cert->offesetContent, fileLen);
	fread(cert->content.data, 1, fileLen, fp);

	if (WriteMtd(cert->size) < 0 || WriteMtd(cert->content) < 0)
		return -1;

	fclose(fp);
	return 0;
}

int DeletCert(Cert *cert)
{
	cert->size = mtdData_new(cert->offesetSize, SizeLength);
	if (WriteMtd(cert->size) < 0)
		return -1;

	cert->content = mtdData_new(cert->offesetContent, MaxCertSize);
	if (WriteMtd(cert->content) < 0)
		return -1;

	return 0;
}
