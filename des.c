#include <sys/types.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include "des_util.h"

int main(int argc, char *argv[])
{
	int flag = 0;
	memset(IP, 0, IP_TOTAL_SIZE * sizeof(int));
	memset(IP_INV, 0, IP_TOTAL_SIZE * sizeof(int));
	memset(E, 0, E_TOTAL_SIZE * sizeof(int));
	memset(P, 0, P_TOTAL_SIZE * sizeof(int));
	memset(V, 0, V_SIZE * sizeof(int));
	memset(S1, 0, S_ROW_SIZE * S_COL_SIZE * sizeof(int));
	memset(S2, 0, S_ROW_SIZE * S_COL_SIZE * sizeof(int));
	memset(S3, 0, S_ROW_SIZE * S_COL_SIZE * sizeof(int));
	memset(S4, 0, S_ROW_SIZE * S_COL_SIZE * sizeof(int));
	memset(S5, 0, S_ROW_SIZE * S_COL_SIZE * sizeof(int));
	memset(S6, 0, S_ROW_SIZE * S_COL_SIZE * sizeof(int));
	memset(S7, 0, S_ROW_SIZE * S_COL_SIZE * sizeof(int));
	memset(S8, 0, S_ROW_SIZE * S_COL_SIZE * sizeof(int));
	memset(PC1, 0, PC1_TOTAL_SIZE * sizeof(int));
	memset(PC2, 0, PC2_TOTAL_SIZE * sizeof(int));
	memset(finalKey, 0, DES_ROUNDS * KEY_SIZE);
	memset(finalKey3D1, 0, DES_ROUNDS * KEY_SIZE);
	memset(finalKey3D2, 0, DES_ROUNDS * KEY_SIZE);
	memset(finalKey3D3, 0, DES_ROUNDS * KEY_SIZE);

	if(argc < 2 || argc > 5)
	{
		fprintf(stderr, "\r\nerror: malformed command\r\nusage: hw4 tablecheck -t=tablefile\r\n");
		fprintf(stderr, "       hw4 encrypt -k=key -t=tablefile [file]\r\n");
		fprintf(stderr, "       hw4 decrypt -k=key -t=tablefile [file]\r\n");
		fprintf(stderr, "       hw4 encrypt3 -k=key3 -t=tablefile [file]\r\n");
		fprintf(stderr, "       hw4 decrypt3 -k=key3 -t=tablefile [file]\r\n");
                exit(-1);
	}

 	if(!strcmp(argv[1], "tablecheck"))
        {
		char *token = NULL;
	        char *save  = NULL;
        	FILE *fp    = NULL;
		token = strtok_r(argv[2], "=", &save);
	        if(!strlen(save))
        	{
                	fprintf(stderr, "\r\nerror: malformed command\r\nusage: hw4 tablecheck -t=tablefile\r\n");
                	exit(-1);
        	}
        	if(strcmp(token, "-t"))
        	{
                	fprintf(stderr, "\r\nerror: malformed command\r\nusage: hw3 hw4 tablecheck -t=tablefile\r\n");
                	exit(-1);
        	}
        	fp = fopen(save, "r");
        	if(!fp)
        	{
                	fprintf(stderr, "\r\nerror: %s %s\n", save, strerror(errno));
                	exit(-1);
        	}
        	if(errno)
        	{
                	fprintf(stderr, "\r\nerror: %s %s\n", save, strerror(errno));
                	exit(-1);
        	}
                validateTable(fp);
        }
	else if(!strcmp(argv[1], "encrypt"))
	{
		flag = 1;
		preprocessInput(argc, argv, flag);
	}
	else if(!strcmp(argv[1], "decrypt"))
	{
		flag = 0;
		preprocessInput(argc, argv, flag);
	}
	else if(!strcmp(argv[1], "encrypt3"))
	{
		flag = 1;
		preprocessTripleInput(argc, argv, flag);
	}
	else if(!strcmp(argv[1], "decrypt3"))
	{
		flag = 0;
		preprocessTripleInput(argc, argv, flag);
	}
	else
	{
		fprintf(stderr, "\r\nerror: malformed command\r\nusage: hw4 tablecheck -t=tablefile\r\n");
                fprintf(stderr, "       hw4 encrypt -k=key -t=tablefile [file]\r\n");
                fprintf(stderr, "       hw4 decrypt -k=key -t=tablefile [file]\r\n");
                fprintf(stderr, "       hw4 encrypt3 -k=key3 -t=tablefile [file]\r\n");
                fprintf(stderr, "       hw4 decrypt3 -k=key3 -t=tablefile [file]\r\n");
                exit(-1);

	}
		
	return 0;
}
