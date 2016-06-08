/*
 * cert.h
 *
 *  Created on: Jan 30, 2016
 *      Author: Kevin Lo
 */

#ifndef CERT_H_
#define CERT_H_

#include "common.h"

typedef struct
{
	OffesetSize offesetSize;
	MtdData size;
	OffesetContent offesetContent;
	MtdData content;

} Cert;

int ReadCert(Cert *cert);
int ReadCertSize(Cert *cert);
int WriteCert(Cert *cert, char *filename);
int DeletCert(Cert *cert);

#endif /* CERT_H_ */
