/*
 ============================================================================
 Name        : KC_mtd
 Author      : 
 Version     : Jan 30, 2016
 Copyright   : KCodes
 Description : Read data from mtdblock
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <strings.h>

#include "common.h"
#include "cert.h"
#include "key.h"
#include "backupkey.h"

#include "config.h"

enum ContentType
{
	Self = 0, Import, Csr
};

enum Backup
{
	All = 0, Key1, Key2, Key3, Key4, Key5
};

static Key keys[] =
{
{ .offesetSize = OffsetSelfKeySize, .offesetContent = OffsetSelfKey, },
{ .offesetSize = OffsetImportKeySize, .offesetContent = OffsetImportKey, },
{ .offesetSize = OffsetCsrKeySize, .offesetContent = OffsetCsrKey, } };

static Cert certs[] =
{
{ .offesetSize = OffsetSelfCertSize, .offesetContent = OffsetSelfCert, },
{ .offesetSize = OffsetImportCertSize, .offesetContent = OffsetImportCert, },
{ .offesetSize = OffsetCsrCertSize, .offesetContent = OffsetCsrCert, } };

static BackUpKey BackUpKeys[] =
{
{ .offesetContent = OffsetBackUpKey1, },
{ .offesetContent = OffsetBackUpKey2, },
{ .offesetContent = OffsetBackUpKey3, },
{ .offesetContent = OffsetBackUpKey4, },
{ .offesetContent = OffsetBackUpKey5, }, };

static BackUpKeyStack backUpKeyStack =
{ .offesetSize = OffsetNumOfBackUpKeys, .backUpKeys = BackUpKeys, };

void Read(char *ContentType)
{
	OpenMtdFd(mtdblock);

	// Key
	if (strcasecmp(ContentType, "SelfKey") == 0
			|| atoi(ContentType) == OffsetSelfKey)
		ReadKey(&keys[Self]);
	else if (strcasecmp(ContentType, "ImportKey") == 0
			|| atoi(ContentType) == OffsetImportKey)
		ReadKey(&keys[Import]);
	else if (strcasecmp(ContentType, "CsrKey") == 0
			|| atoi(ContentType) == OffsetCsrKey)
		ReadKey(&keys[Csr]);
	// Cert
	else if (strcasecmp(ContentType, "SelfCert") == 0
			|| atoi(ContentType) == OffsetSelfCert)
		ReadCert(&certs[Self]);
	else if (strcasecmp(ContentType, "ImportCert") == 0
			|| atoi(ContentType) == OffsetImportCert)
		ReadCert(&certs[Import]);
	else if (strcasecmp(ContentType, "CsrCert") == 0
			|| atoi(ContentType) == OffsetCsrCert)
		ReadCert(&certs[Csr]);
	// Size
	else if (strcasecmp(ContentType, "SelfKeySize") == 0
			|| atoi(ContentType) == OffsetSelfKeySize)
		printf("Key Size: %d\n", ReadKeySize(&keys[Self]));
	else if (strcasecmp(ContentType, "ImportKeySize") == 0
			|| atoi(ContentType) == OffsetImportKeySize)
		printf("Key Size: %d\n", ReadKeySize(&keys[Import]));
	else if (strcasecmp(ContentType, "CsrKeySize") == 0
			|| atoi(ContentType) == OffsetCsrKeySize)
		printf("Key Size: %d\n", ReadKeySize(&keys[Csr]));
	// problem
	else if (strcasecmp(ContentType, "SelfCertSize") == 0)
//			|| atoi(ContentType) == OffsetSelfCertSize)
		printf("Cert Size: %d\n", ReadCertSize(&certs[Self]));
	else if (strcasecmp(ContentType, "ImportCertSize") == 0
			|| atoi(ContentType) == OffsetImportCertSize)
		printf("Cert Size: %d\n", ReadCertSize(&certs[Import]));
	else if (strcasecmp(ContentType, "CsrCertSize") == 0
			|| atoi(ContentType) == OffsetCsrCertSize)
		printf("Cert Size: %d\n", ReadCertSize(&certs[Csr]));
	// top
	else if (strcasecmp(ContentType, "NumOfBackUpKeys") == 0
			|| atoi(ContentType) == OffsetNumOfBackUpKeys)
		ReadNumOfBackUPKeys(&backUpKeyStack, true);
	// back up keys
	else if (strcasecmp(ContentType, "BackupKeyAll") == 0)
		ReadBackUpKeyStack(&backUpKeyStack, All);
	else if (strcasecmp(ContentType, "BackupKey1") == 0
			|| atoi(ContentType) == OffsetBackUpKey1)
		ReadBackUpKeyStack(&backUpKeyStack, Key1);
	else if (strcasecmp(ContentType, "BackupKey2") == 0
			|| atoi(ContentType) == OffsetBackUpKey2)
		ReadBackUpKeyStack(&backUpKeyStack, Key2);
	else if (strcasecmp(ContentType, "BackupKey3") == 0
			|| atoi(ContentType) == OffsetBackUpKey3)
		ReadBackUpKeyStack(&backUpKeyStack, Key3);
	else if (strcasecmp(ContentType, "BackupKey4") == 0
			|| atoi(ContentType) == OffsetBackUpKey4)
		ReadBackUpKeyStack(&backUpKeyStack, Key4);
	else if (strcasecmp(ContentType, "BackupKey5") == 0
			|| atoi(ContentType) == OffsetBackUpKey5)
		ReadBackUpKeyStack(&backUpKeyStack, Key5);
	else if (strcasecmp(ContentType, "BackupKey") == 0)
		fprintf(stderr, "Need to be BackupKeyN (N = 1 ~ 5) or BackupKeyAll\n");
	else
		fprintf(stderr, "Content Type not supported\n");

	CloseMtdFd();

}

void Delete(char *ContentType)
{
	OpenMtdFd(mtdblock);

	if (strcasecmp(ContentType, "SelfKey") == 0
			|| atoi(ContentType) == OffsetSelfKey)
		DeleteKey(&keys[Self]);
	else if (strcasecmp(ContentType, "ImportKey") == 0
			|| atoi(ContentType) == OffsetImportKey)
		DeleteKey(&keys[Import]);
	else if (strcasecmp(ContentType, "CsrKey") == 0
			|| atoi(ContentType) == OffsetCsrKey)
		DeleteKey(&keys[Csr]);

	else if (strcasecmp(ContentType, "SelfCert") == 0
			|| atoi(ContentType) == OffsetSelfCert)
		DeletCert(&certs[Self]);
	else if (strcasecmp(ContentType, "ImportCert") == 0
			|| atoi(ContentType) == OffsetImportCert)
		DeletCert(&certs[Import]);
	else if (strcasecmp(ContentType, "CsrCert") == 0
			|| atoi(ContentType) == OffsetCsrCert)
		DeletCert(&certs[Csr]);

	else if (strcasecmp(ContentType, "BackupKeyAll") == 0)
		DestroyBackUpKeyStack(&backUpKeyStack);
	else if (strcasecmp(ContentType, "BackupKey") == 0)
		DeletBackUpKeyStack(&backUpKeyStack);
	else if (strcasecmp(ContentType, "BackupKey1") == 0
			|| strcasecmp(ContentType, "BackupKey2") == 0
			|| strcasecmp(ContentType, "BackupKey3") == 0
			|| strcasecmp(ContentType, "BackupKey4") == 0
			|| strcasecmp(ContentType, "BackupKey5") == 0)
		fprintf(stderr, "Can only be BackupKey or BackupKeyAll\n");

	else
		fprintf(stderr, "Content Type not supported\n");

	CloseMtdFd();

}

void Write(char *ContentType, char *filename)
{
	OpenMtdFd(mtdblock);

	if (strcasecmp(ContentType, "SelfKey") == 0
			|| atoi(ContentType) == OffsetSelfKey)
		WriteKey(&keys[Self], filename);
	else if (strcasecmp(ContentType, "ImportKey") == 0
			|| atoi(ContentType) == OffsetImportKey)
		WriteKey(&keys[Import], filename);
	else if (strcasecmp(ContentType, "CsrKey") == 0
			|| atoi(ContentType) == OffsetCsrKey)
		WriteKey(&keys[Csr], filename);

	else if (strcasecmp(ContentType, "SelfCert") == 0
			|| atoi(ContentType) == OffsetSelfCert)
		WriteCert(&certs[Self], filename);
	else if (strcasecmp(ContentType, "ImportCert") == 0
			|| atoi(ContentType) == OffsetImportCert)
		WriteCert(&certs[Import], filename);
	else if (strcasecmp(ContentType, "CsrCert") == 0
			|| atoi(ContentType) == OffsetCsrCert)
		WriteCert(&certs[Csr], filename);

	else if (strcasecmp(ContentType, "BackupKey") == 0)
		WriteBackUpKeyStack(&backUpKeyStack, filename);
	else if (strcasecmp(ContentType, "BackupKey1") == 0
			|| strcasecmp(ContentType, "BackupKey2") == 0
			|| strcasecmp(ContentType, "BackupKey3") == 0
			|| strcasecmp(ContentType, "BackupKey4") == 0
			|| strcasecmp(ContentType, "BackupKey5") == 0
			|| strcasecmp(ContentType, "BackupKeyAll") == 0)
		fprintf(stderr, "Can only be BackupKey\n");

	else
		fprintf(stderr, "[ContentType] not supported\n");

	CloseMtdFd();

}

int main(int argc, char* argv[])
{
	int cmd_opt = 0;

	while (1)
	{
		cmd_opt = getopt(argc, argv, "hsr:d:w:f:");

		/* End condition always first */
		if (cmd_opt == -1)
		{
			if (optind == 1)
				usage();
			break;
		}

		/* No args */
		switch (cmd_opt)
		{
		case 'h':
			usage();
			break;
		case 's':
			show();
			break;

			/* Single arg */
		case 'r':
			Read(optarg);
			break;
		case 'd':
			Delete(optarg);
			break;
		case 'w':
			if (argv[optind] == NULL)
			{
				fprintf(stderr, "\tFile is needed for write option\n"
						"\tExample: KC_mtd -w [ContentType] [File]\n");
				break;
			}
			Write(optarg, argv[optind]);
			optind++;
			break;

			/* Error handle: Mainly missing arg or illegal option */
		case '?':
			usage();
			break;
		default:
			fprintf(stderr, "Not supported option\n");
			usage();
			break;
		}
	}

	/* Do we have args? */
	if (argc > optind)
	{
		fprintf(stderr, "Too many arguments\n");
	}

	return EXIT_SUCCESS;
}
