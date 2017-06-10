#include "des_util.h"

int IP[IP_TOTAL_SIZE];
int IP_INV[IP_TOTAL_SIZE];
int E[E_TOTAL_SIZE];
int P[P_TOTAL_SIZE];
int S1[S_ROW_SIZE][S_COL_SIZE];
int S2[S_ROW_SIZE][S_COL_SIZE];
int S3[S_ROW_SIZE][S_COL_SIZE];
int S4[S_ROW_SIZE][S_COL_SIZE];
int S5[S_ROW_SIZE][S_COL_SIZE];
int S6[S_ROW_SIZE][S_COL_SIZE];
int S7[S_ROW_SIZE][S_COL_SIZE];
int S8[S_ROW_SIZE][S_COL_SIZE];
int PC1[PC1_TOTAL_SIZE];
int PC2[PC2_TOTAL_SIZE];
int V[V_SIZE];
char finalKey[DES_ROUNDS][KEY_SIZE];
char finalKey3D1[DES_ROUNDS][KEY_SIZE];
char finalKey3D2[DES_ROUNDS][KEY_SIZE];
char finalKey3D3[DES_ROUNDS][KEY_SIZE];

void constructIPInverse()
{
	int i = 0;
	for(i = 0; i < IP_TOTAL_SIZE; i++)
	{
		IP_INV[IP[i] - 1] = i + 1;
	}
	
	/*for(i = 0; i < IP_TOTAL_SIZE; i++)
	{
		printf("%d  ", IP_INV[i]);
	}
	exit(-1);*/
}
void validateIP(char *buff)
{
	char *token  = NULL;
        char *save   = NULL;
	int i        = 0;
	int count    = 0;
	int ip_chk_1 = 0;
	int ip_chk_2 = 0;

	token  = strtok_r(buff, "=", &save);

	if(save && !strlen(save))
        {
                fprintf(stderr, "\r\nerror: malformed input table file\r\n");
                exit(-1);
        }
        if(strcmp(token, "IP"))
        {
                fprintf(stderr, "\r\nerror: malformed input table file\r\n");
                exit(-1);
        }
	token = strtok(save, ",");
	while(token != NULL)
	{
		IP[i] = atoi(token);
		
		if(IP[i] <= 32)
		{
			if(((ip_chk_1 >> (IP[i] - 1)) & (IP_CHECK)) == 1)
			{
				fprintf(stderr, "\r\nerror: malformed input table file - element %d appearing twice in IP\r\n", IP[i]);
		                exit(-1);
			}
			ip_chk_1 = (ip_chk_1 | (1 << (IP[i] - 1)));
		}
		else
		{
			if(((ip_chk_2 >> (IP[i] - 33)) & (IP_CHECK)) == 1)
                        {
                                fprintf(stderr, "\r\nerror: malformed input table file - element %d appearing twice in IP\r\n", IP[i]);
                                exit(-1);
                        }
                        ip_chk_2 = (ip_chk_2 | (1 << (IP[i] - 33)));

		}
		i++;
		token = strtok(NULL, ",");
	}
	for(i = 0; i < 32; i++)
	{
		if(((ip_chk_1 >> i) & IP_CHECK) == 0)
		{
			fprintf(stderr, "\r\nerror: malformed input table file - element %d does not appear in IP\r\n", i + 1);
                        exit(-1);
		}
		if(((ip_chk_2 >> i) & IP_CHECK) == 0)
                {
                        fprintf(stderr, "\r\nerror: malformed input table file - element %d does not appear in IP\r\n", i + 33);
                        exit(-1);
                }
	}
	
	/*for(i = 0; i < IP_TOTAL_SIZE; i++)
	{
		printf("%d  ", IP[i]);
	}*/
	constructIPInverse();

}
void validateE(char *buff)
{
	char *token  = NULL;
        char *save   = NULL;
        int i        = 0;
        int j        = 0;
        int count    = 0;
        int ep_chk[E_SIZE];

	memset(ep_chk, 0, E_SIZE * sizeof(int));

        token  = strtok_r(buff, "=", &save);
        if(!strlen(save))
        {
                fprintf(stderr, "\r\nerror: malformed input table file\r\n");
                exit(-1);
        }
        if(strcmp(token, "E"))
        {
                fprintf(stderr, "\r\nerror: malformed input table file\r\n");
                exit(-1);
        }
        token = strtok(save, ",");
	while(token != NULL)
        {
		E[i] = atoi(token);
		if(!(E[i] >= 1 && E[i] <= 32))
		{
			fprintf(stderr, "\r\nerror: malformed input table file - E values must be between 1 and 32\r\n");
	                exit(-1);
		}
		if(ep_chk[E[i]] == 2)
		{
                	fprintf(stderr, "\r\nerror: malformed input table file - E value %d repeats more than twice\r\n", E[i]);
                	exit(-1);
		}
		else
		{
			ep_chk[E[i]]++;
		}
                i++;
		token = strtok(NULL, ",");
	}
	/*for(i = 0; i < E_TOTAL_SIZE; i++)
	{
		printf("%d  ", E[i]);
	}
	exit(-1);*/

}
void validateP(char *buff)
{
	char *token  = NULL;
        char *save   = NULL;
        int i        = 0;
        int j        = 0;
        int count    = 0;
	int p_chk    = 0;


        token  = strtok_r(buff, "=", &save);
        if(!strlen(save))
        {
                fprintf(stderr, "\r\nerror: malformed input table file\r\n");
                exit(-1);
        }
        if(strcmp(token, "P"))
        {
                fprintf(stderr, "\r\nerror: malformed input table file\r\n");
                exit(-1);
        }
        token = strtok(save, ",");
	while(token != NULL)
        {
		count++;
		if(count > 32)
		{
			fprintf(stderr, "\r\nerror: malformed input table file - more than 32 values read in P\r\n");
                        exit(-1);

		}
                P[i] = atoi(token);
		if(((p_chk >> (P[i] - 1)) & (P_CHECK)) == 1)
                {
                	fprintf(stderr, "\r\nerror: malformed input table file - element %d appearing twice in P\r\n", P[i]);
                        exit(-1);
               	}
                p_chk = (p_chk | (1 << (P[i] - 1)));

                i++;
                token = strtok(NULL, ",");
        }
	for(i = 0; i < 32; i++)
        {
                if(((p_chk >> i) & P_CHECK) == 0)
                {
                        fprintf(stderr, "\r\nerror: malformed input table file - element %d does not appear in P\r\n", i + 1);
                        exit(-1);
                }

	}
	/*
	for(i = 0; i < P_TOTAL_SIZE; i++)
	{
		printf("%d  ", P[i]);
	}
	*/
}
void validateV(char *buff)
{
	char *token  = NULL;
        char *save   = NULL;
        int i        = 0;
        int count_1  = V1_COUNT;
	int count_2  = V2_COUNT;

        token  = strtok_r(buff, "=", &save);
        if(!strlen(save))
        {
                fprintf(stderr, "\r\nerror: malformed input table file\r\n");
                exit(-1);
        }
        if(strcmp(token, "V"))
        {
                fprintf(stderr, "\r\nerror: malformed input table file\r\n");
                exit(-1);
        }
        token = strtok(save, ",");
        while(token != NULL)
        {
		V[i] = atoi(token);
		if(V[i] == 1)
		{
			count_1--;
		}
		else if(V[i] == 2)
		{
			count_2--;
		}
		else
		{
			fprintf(stderr, "\r\nerror: malformed input table file - only values 1 and 2 permitted in V\r\n");
                        exit(-1);
		}	
		i++;
		token = strtok(NULL, ",");
        }
	if(count_1 != 0)
	{
		fprintf(stderr, "\r\nerror: malformed input table file - V table must have 4 1's\r\n");
                exit(-1);
        }
	if(count_2 != 0)
        {
                fprintf(stderr, "\r\nerror: malformed input table file - V table must have 12 2's\r\n");
                exit(-1);
        }
	
}
void validateS(char *buff, int k)
{
	char *token  = NULL;
        char *save   = NULL;
        int i        = 0;
        int j        = 0;
	int local    = 0;
        int count    = 0;
        int s_chk[S_SIZE];
	char temp[TEMP_BUFF];

        memset(s_chk, 0, S_SIZE * sizeof(int));
	memset(temp, 0, TEMP_BUFF);

	sprintf(temp, "S%d", k);

        token  = strtok_r(buff, "=", &save);
        if(!strlen(save))
        {
                fprintf(stderr, "\r\nerror: malformed input table file\r\n");
                exit(-1);
        }
        if(strcmp(token, temp))
        {
                fprintf(stderr, "\r\nerror: malformed input table file\r\n");
                exit(-1);
        }
        token = strtok(save, ",");
	
        while(token != NULL)
        {
		count++;
		local = atoi(token);
		if(!(local >= 0 && local <= 15))
                {
                        fprintf(stderr, "\r\nerror: malformed input table file - S%d values must be between 0 and 15\r\n", k);
                        exit(-1);
                }
                if(s_chk[local] == 4)
                {
                        fprintf(stderr, "\r\nerror: malformed input table file- in S%d table value %d appears more than 4 times\r\n", k, local);
                        exit(-1);
                }
                else
                {
                        s_chk[local]++;
                }
		if(k == 1)
		{
                	S1[i][j] = atoi(token);
		}
		if(k == 2)
                {
                        S2[i][j] = atoi(token);
                }
		if(k == 3)
                {
                        S3[i][j] = atoi(token);
                }
		if(k == 4)
                {
                        S4[i][j] = atoi(token);
                }
		if(k == 5)
                {
                        S5[i][j] = atoi(token);
                }
		if(k == 6)
                {
                        S6[i][j] = atoi(token);
                }
		if(k == 7)
                {
                        S7[i][j] = atoi(token);
                }
		if(k == 8)
                {
                        S8[i][j] = atoi(token);
                }
		j++;
                if(j == S_COL_SIZE)
                {
                        j = 0;
                        i++;
                }
                token = strtok(NULL, ",");
	}
	if(count != (S_ROW_SIZE * S_COL_SIZE))
	{
		fprintf(stderr, "\r\nerror: malformed input table file - S%d table must contain 64 values\r\n", k);
                exit(-1);	
	}
	for(i = 0; i < S_SIZE; i++)
	{
		if(s_chk[i] != S_COUNT)
		{
			fprintf(stderr, "\r\nerror: malformed input table file - value %d in S%d table does not appear 4 times\r\n", i, k);
                	exit(-1);
		}
	}
		 
}
void validatePC1(char *buff)
{
	char *token  = NULL;
        char *save   = NULL;
        int i        = 0;
        int count    = 0;
	int local    = 0;
	int pc1_chk[PC1_SIZE];

	memset(pc1_chk, 0, PC1_SIZE * sizeof(int));

        token  = strtok_r(buff, "=", &save);
        if(!strlen(save))
        {
                fprintf(stderr, "\r\nerror: malformed input table file\r\n");
                exit(-1);
        }
        if(strcmp(token, "PC1"))
        {
                fprintf(stderr, "\r\nerror: malformed input table file\r\n");
                exit(-1);
        }
        token = strtok(save, ",");
	while(token != NULL)
        {
                count++;
		local = atoi(token);
                if(!(local >= 1 && local <= 64))
                {
                        fprintf(stderr, "\r\nerror: malformed input table file - PC1 table values must be between 1 and 64\r\n");
                        exit(-1);
                }
		if(local % 8 == 0)
		{
			fprintf(stderr, "\r\nerror: malformed input table file - PC1 table contains multiples of 8\r\n");
                        exit(-1);
		}
		pc1_chk[local - 1]++;
		PC1[i] = local;
                i++;
		token = strtok(NULL, ",");
        }
	if(count != (PC1_TOTAL_SIZE))
        {
                fprintf(stderr, "\r\nerror: malformed input table file - PC1 table must contain 56 values\r\n");
                exit(-1);
        }
	for(i = 0; i < PC1_SIZE; i++)
	{
		if((i + 1) % 8 == 0)
		{
			continue;
		}
		if(!pc1_chk[i])
		{
			fprintf(stderr, "\r\nerror: malformed input table file - value %d did not occur in PC1 table\r\n", i + 1);
	                exit(-1);
		}

	}
	/*for(i = 0; i < PC1_TOTAL_SIZE; i++)
	{
		printf("%d  ", PC1[i]);
	}
	exit(-1);*/

}
void validatePC2(char *buff)
{
	char *token  = NULL;
        char *save   = NULL;
        int i        = 0;
        int count    = 0;
	int local    = 0;
	int pc2_chk[PC2_SIZE];

	memset(pc2_chk, 0, PC2_SIZE * sizeof(int));

        token  = strtok_r(buff, "=", &save);
        if(!strlen(save))
        {
                fprintf(stderr, "\r\nerror: malformed input table file\r\n");
                exit(-1);
        }
        if(strcmp(token, "PC2"))
        {
                fprintf(stderr, "\r\nerror: malformed input table file\r\n");
                exit(-1);
        }
        token = strtok(save, ",");
        while(token != NULL)
        {
                count++;
		local = atoi(token);
                if(!(local >= 1 && local <= 56))
                {
                        fprintf(stderr, "\r\nerror: malformed input table file - PC2 table values must be between 1 and 56\r\n");
                        exit(-1);
                }
		if(pc2_chk[local - 1] != 0)
		{
			fprintf(stderr, "\r\nerror: malformed input table file - value %d occurs too many times in PC2 table\r\n", local);
                        exit(-1);
		}
		pc2_chk[local - 1]++;

		PC2[i] = local;
                i++;
                token = strtok(NULL, ",");
        }
	if(count != (PC2_TOTAL_SIZE))
        {
                fprintf(stderr, "\r\nerror: malformed input table file - PC2 table must contain 48 values\r\n");
                exit(-1);
        }

	/*for(i = 0; i < PC2_TOTAL_SIZE; i++)
	{
		printf("%d  ", PC2[i]);
	}*/

}
void validateTable(FILE *fp)
{
	int i       = 0;
	char buff[BUFF_SIZE];

	memset(buff, 0, BUFF_SIZE);

	while(fgets(buff, BUFF_SIZE, fp))
	{
		buff[strlen(buff) - 1] = '\0';
		if(i == 0)
		{
			validateIP(buff);
		}
		if(i == 1)
		{
			validateE(buff);	
		}
		if(i == 2)
		{
			validateP(buff);
		}
		if(i >= 3 && i <= 10)
		{
			validateS(buff, i - 2);
		}
		if(i == 11)
		{
			validateV(buff);
		}
		if(i == 12)
		{
			validatePC1(buff);
		}
		if(i == 13)
		{
			validatePC2(buff);	
		}
		i++;
	}

	
	/*int j;
	for(i = 0; i < 4; i++)
        {
                for(j = 0; j < 16; j++)
                {
                        printf("%d  ", S8[i][j]);
                }
        }
	exit(-1);*/
	
}
void computeHex(char *key_str, char *key_byt)
{
	int i   = 0;
	int j   = 0;
	int len = strlen(key_str);
	char temp[TEMP_BUFF];

	memset(temp, 0, TEMP_BUFF);

	while(i < len)
	{
		strncpy(temp, &key_str[i], 2);
		key_byt[j] = (char)strtol(temp, NULL, 16);
		j++;
		i += 2;
		memset(temp, 0, TEMP_BUFF);	
	}
}
void shuffleWithIP(char *inp, char *inp_af_ip)
{
	int i    = 0;
	int j    = 0;
	int calc = 0;
	int rem  = 0;
	int k    = BYTE_SIZE - 1;
	char byt = 0;
	for(i = 0; i < IP_TOTAL_SIZE; i++)
	{
		calc = IP[i] / 8;
		rem  = IP[i] % 8;
		if(rem % 8 != 0)
		{
			calc++;
		}
		calc--;
		if(rem != 0)
		{
			byt  = (inp[calc] >>  (BYTE_SIZE - rem)) & (BYTE_CHECK);
		}
		else
		{
			byt  = (inp[calc]) & (BYTE_CHECK);
		}
		inp_af_ip[j] = (inp_af_ip[j] | (byt << k));
		k--;
		if((i + 1) % 8 == 0)
		{
			j++;
			k = BYTE_SIZE - 1;
		}
		calc = 0;
		rem  = 0;
		byt  = 0;
	}
	/*fprintf(stderr, "(L0,R0)=");	
	for(i = 0; i < BYTE_SIZE; i++)
	{
		fprintf(stderr, "%x", (inp_af_ip[i] & 0xff));
	}*/
}
void computeInitialC0D0(char *key, char *cKey, char *dKey)
{
	int i    = 0;
        int j    = 0;
	int k    = 3;
        int calc = 0;
        int rem  = 0;
	char byt = 0;
	for(i = 0; i < PC1_TOTAL_SIZE; i++)
        {
		calc = PC1[i] / 8;
                rem  = PC1[i] % 8;
                if(rem % 8 != 0)
                {
                        calc++;
                }
                calc--;
		if(rem != 0)
                {
                	byt  = (key[calc] >>  (BYTE_SIZE - rem)) & (BYTE_CHECK);
              	}
                else
                {
                        byt  = (key[calc]) & (BYTE_CHECK);
                }
		if(i < (PC1_TOTAL_SIZE / 2))
		{
			cKey[j] = (cKey[j] | (byt << k));	
		}
		else
		{
			dKey[j] = (dKey[j] | (byt << k));
		}
		if(i == 27)
		{
			k = 3;
			j = 0;
			calc = 0;
                	rem  = 0;
                	byt  = 0;
			continue;
		}
                k--;
                if(k == -1)
                {
                        j++;
                        k = BYTE_SIZE - 1;
                }
                calc = 0;
                rem  = 0;
                byt  = 0;
	}

	//printing values to stderr	
	fprintf(stderr, "(C0,D0)=");
	for(i = 0; i < 4; i++)
	{
		if(i == 0)
		{
			fprintf(stderr, "%x", cKey[i] & 0xff);
			
		}
		else
		{
			fprintf(stderr, "%02x", cKey[i] & 0xff);
		}
	}
	for(i = 0; i < 4; i++)
        {
		if(i ==0)
		{
                	fprintf(stderr, "%x", dKey[i] & 0xff);
		}
		else
		{
			fprintf(stderr, "%02x", dKey[i] & 0xff);
		}
        }
	fprintf(stderr, "\n");
	//exit(-1);
		
}
void computeKey(char *cKey, char *dKey, int round, int type)
{
	char cKey_r[BYTE_SIZE / 2];
        char dKey_r[BYTE_SIZE / 2];
	int  curr = V[round];
	int  i    = 0;
	int j     = 0;
        int k     = BYTE_SIZE - 1;
        int calc  = 0;
        int rem   = 0;
        char byt  = 0;

	memset(cKey_r, 0, BYTE_SIZE / 2);
        memset(dKey_r, 0, BYTE_SIZE / 2);

	//running loop 4 times for 4 bytes
	for(i = 0; i < (BYTE_SIZE / 2); i++)
	{
		if(curr == 1)
		{
			cKey_r[i] = ((cKey[i] << curr) & 0xfe);
			dKey_r[i] = ((dKey[i] << curr) & 0xfe);
			
		}
		else
		{
			cKey_r[i] = ((cKey[i] << curr) & 0xfc);
                        dKey_r[i] = ((dKey[i] << curr) & 0xfc);
		}
	}

	//nullifying the first four bits
	cKey_r[0] = cKey_r[0] & 0x0f;
	dKey_r[0] = dKey_r[0] & 0x0f;

	//implementing circular shift
	if(curr == 1)
	{
		for(i = 0; i < 3; i++)
		{
			cKey_r[i] = (cKey_r[i] | ((cKey[i + 1] & 0x80) >> (BYTE_SIZE - 1)));
			dKey_r[i] = (dKey_r[i] | ((dKey[i + 1] & 0x80) >> (BYTE_SIZE - 1)));
		}
		cKey_r[3] = (cKey_r[3] | (((cKey[0] << curr) & 0x10) >> (BYTE_SIZE / 2)));
		dKey_r[3] = (dKey_r[3] | (((dKey[0] << curr) & 0x10) >> (BYTE_SIZE / 2)));
	}
	else
	{
		for(i = 0; i < 3; i++)
                {
                        cKey_r[i] = (cKey_r[i] | ((cKey[i + 1] & 0xc0) >> (BYTE_SIZE - 2)));
                        dKey_r[i] = (dKey_r[i] | ((dKey[i + 1] & 0xc0) >> (BYTE_SIZE - 2)));
                }
		cKey_r[3] = (cKey_r[3] | (((cKey[0] << curr) & 0x30) >> (BYTE_SIZE / 2)));
                dKey_r[3] = (dKey_r[3] | (((dKey[0] << curr) & 0x30) >> (BYTE_SIZE / 2)));

	}

	//permuting to 48 using PC2
	for(i = 0; i < PC2_TOTAL_SIZE; i++)
	{
		//pick from C or D
		if(PC2[i] <= (PC1_TOTAL_SIZE / 2))
		{
			if(PC2[i] >= 1 && PC2[i] <= 4)
			{
				calc = 1;
				rem  = PC2[i] % 4;
			}
			else
			{
				calc = (PC2[i] + 4) / 8; //to compensate for the dummy four bits
		                rem  = (PC2[i] + 4) % 8;
        			if(rem % 8 != 0)
                		{	
                        		calc++;
                		}
			}
                	calc--;
			if(rem != 0)
	                {
				if(calc == 0)
				{
        	                	byt  = (cKey_r[calc] >>  (4 - rem)) & (BYTE_CHECK);
				}
                		else
				{
					byt  = (cKey_r[calc] >>  (BYTE_SIZE - rem)) & (BYTE_CHECK);
				}
			}
                	else
                	{
                        	byt  = (cKey_r[calc]) & (BYTE_CHECK);
                	}

		}
		else
		{
			if(PC2[i] >= 29 && PC2[i] <= 32)
                        {
                                calc = 1;
                                rem  = (PC2[i] - 28) % 4;
                        }
			else
			{
				calc = (PC2[i] + 8) / 8; //to compensate for the dummy four bits
                        	rem  = (PC2[i] + 8) % 8;
                        	if(rem % 8 != 0)
                        	{
                                	calc++;
                        	}
				calc = calc - 4;
			}
                        calc--;
                        if(rem != 0)
                        {
                                if(calc == 0)
                                {
                                        byt  = (dKey_r[calc] >>  (4 - rem)) & (BYTE_CHECK);
                                }
                                else
                                {
                                        byt  = (dKey_r[calc] >>  (BYTE_SIZE - rem)) & (BYTE_CHECK);
                                }
                        }
                        else
                        {
                                byt  = (dKey_r[calc]) & (BYTE_CHECK);
                        }
	
		}
		if(type == DES)
		{
			finalKey[round][j] = (finalKey[round][j] | (byt << k));
		}
		else if(type == DES_1)
		{
			finalKey3D1[round][j] = (finalKey3D1[round][j] | (byt << k));
		}
		else if(type == DES_2)
		{
			finalKey3D2[round][j] = (finalKey3D2[round][j] | (byt << k));
		}
		else
		{
			finalKey3D3[round][j] = (finalKey3D3[round][j] | (byt << k));
		}
		k--;
                if(k == -1)
                {
                        j++;
                        k = BYTE_SIZE - 1;
                }
                calc = 0;
                rem  = 0;
                byt  = 0;
	}
	
	for(i = 0; i < 4; i++)
	{
		dKey[i] = dKey_r[i];
		cKey[i] = cKey_r[i];
	}

	fprintf(stderr, "(C%d,D%d)=", round + 1, round + 1);
        for(i = 0; i < 4; i++)
        {
                if(i == 0)
                {
                        fprintf(stderr, "%x", cKey[i] & 0xff);

                }
                else
                {
                        fprintf(stderr, "%02x", cKey[i] & 0xff);
                }
        }
        for(i = 0; i < 4; i++)
        {
                if(i ==0)
                {
                        fprintf(stderr, "%x", dKey[i] & 0xff);
                }
                else
                {
                        fprintf(stderr, "%02x", dKey[i] & 0xff);
                }
        }
        fprintf(stderr, "\nk%d=", round + 1);

	for(i = 0; i < KEY_SIZE; i++)
	{
		if(type == DES)
                {
			fprintf(stderr, "%02x", finalKey[round][i] & 0xff);
                }
                else if(type == DES_1)
                {
			fprintf(stderr, "%02x", finalKey3D1[round][i] & 0xff);
                }
                else if(type == DES_2)
                {
			fprintf(stderr, "%02x", finalKey3D2[round][i] & 0xff);
                }
                else
                {
			fprintf(stderr, "%02x", finalKey3D3[round][i] & 0xff);
                }

	}

	fprintf(stderr, "\n");
}
void expandRightXOR(char *right, char *expR, int round, int type)
{
	int i    = 0;
        int j    = 0;
        int calc = 0;
        int rem  = 0;
        int k    = BYTE_SIZE - 1;
        char byt = 0;
	for(i = 0; i < E_TOTAL_SIZE; i++)
        {
		calc = E[i] / 8;
                rem  = E[i] % 8;
                if(rem % 8 != 0)
                {
                        calc++;
                }
                calc--;
		if(rem != 0)
                {
                        byt  = (right[calc] >>  (BYTE_SIZE - rem)) & (BYTE_CHECK);
                }
                else
                {
                        byt  = (right[calc]) & (BYTE_CHECK);
                }
		expR[j] = (expR[j] | (byt << k));
                k--;
                if((i + 1) % 8 == 0)
                {
                        j++;
                        k = BYTE_SIZE - 1;
                }
                calc = 0;
                rem  = 0;
                byt  = 0;
	}
	for(i = 0; i < KEY_SIZE; i++)
	{
	        if(type == DES)
		{	
			expR[i] = (expR[i] ^ finalKey[round][i]);
		}
		else if(type == DES_1)
		{
			expR[i] = (expR[i] ^ finalKey3D1[round][i]);
		}
		else if(type == DES_2)
                {
                        expR[i] = (expR[i] ^ finalKey3D2[round][i]);
                }
		else if(type == DES_3)
                {
                        expR[i] = (expR[i] ^ finalKey3D3[round][i]);
                }

	}
	/*for(i = 0; i < KEY_SIZE; i++)
	{
		printf("%x  ", expR[i] & 0xff);
	}
	exit(-1);*/
	
}
void computeSvalue(char *expR, char *sVal)
{
	char init = 0;
	char row  = 0;
	char col  = 0;
	char val  = 0;

	//S-box 1 value
	row = (((expR[0] >> 2) & 0x01) | ((expR[0] >> 6) & 0x02));
	col = ((expR[0] >> 3) & 0xf);
	val = (S1[row][col] << 4);

	//S-box 2 value
	row = ((expR[0] & 0x02) | ((expR[1] >> 4) & 0x01));
	col = (((expR[1] >> 5) & 0x07) | ((expR[0] << 3) & 0x08));
	sVal[0] = (val | S2[row][col]);
	
	//S-box 3 value
	row = (((expR[1] >> 2) & 0x02) | ((expR[2] >> 6) & 0x01));
	col = (((expR[2] >> 7) & 0x01) | ((expR[1] << 1) & 0x0e));
	val = (S3[row][col] << 4);

	//S-box 4 value
	row = ((expR[2] & 0x01) | ((expR[2] >> 4) & 0x02));
	col = ((expR[2] >> 1) & 0x0f);
	sVal[1] = (val | S4[row][col]);

	//S-box 5 value
        row = (((expR[3] >> 2) & 0x01) | ((expR[3] >> 6) & 0x02));
        col = ((expR[3] >> 3) & 0xf);
        val = (S5[row][col] << 4);

        //S-box 6 value
        row = ((expR[3] & 0x02) | ((expR[4] >> 4) & 0x01));
        col = (((expR[4] >> 5) & 0x07) | ((expR[3] << 3) & 0x08));
        sVal[2] = (val | S6[row][col]);

        //S-box 7 value
        row = (((expR[4] >> 2) & 0x02) | ((expR[5] >> 6) & 0x01));
        col = (((expR[5] >> 7) & 0x01) | ((expR[4] << 1) & 0x0e));
        val = (S7[row][col] << 4);

        //S-box 8 value
        row = ((expR[5] & 0x01) | ((expR[5] >> 4) & 0x02));
        col = ((expR[5] >> 1) & 0x0f);
        sVal[3] = (val | S8[row][col]);

	/*int i;
	for(i = 0; i < 4; i++)
	{
		printf("%x ", sVal[i] & 0xff);
	}
	exit(-1);*/
	
}
void permuteP(char *sVal, char *pVal)
{
	int i    = 0;
        int j    = 0;
        int calc = 0;
        int rem  = 0;
        int k    = BYTE_SIZE - 1;
        char byt = 0;
	for(i = 0; i < P_TOTAL_SIZE; i++)
        {
                calc = P[i] / 8;
                rem  = P[i] % 8;
                if(rem % 8 != 0)
                {
                        calc++;
                }
                calc--;
                if(rem != 0)
                {
                        byt  = (sVal[calc] >>  (BYTE_SIZE - rem)) & (BYTE_CHECK);
                }
                else
                {
                        byt  = (sVal[calc]) & (BYTE_CHECK);
                }
                pVal[j] = (pVal[j] | (byt << k));
                k--;
                if((i + 1) % 8 == 0)
                {
                        j++;
                        k = BYTE_SIZE - 1;
                }
                calc = 0;
                rem  = 0;
                byt  = 0;
        }
	
	/*for(i = 0; i < 4; i++)
	{
		printf("%x ", pVal[i] & 0xff);
	}
	*/
}
void printRoundValues(char *left, char *right, int round)
{
	int i = 0;

        //printing L and R values for particular round
        fprintf(stderr, "(L%d,R%d)=", round, round);

        for(i = 0; i < 4; i++)
        {
                fprintf(stderr, "%02x", left[i] & 0xff);
        }
        for(i = 0; i < 4; i++)
        {
                fprintf(stderr, "%02x", right[i] & 0xff);
        }
	fprintf(stderr, "\n");

}
void permuteIPInverse(char *final, char *cipher)
{
	int i    = 0;
        int j    = 0;
        int calc = 0;
        int rem  = 0;
        int k    = BYTE_SIZE - 1;
        char byt = 0;
	for(i = 0; i < IP_TOTAL_SIZE; i++)
        {
                calc = IP_INV[i] / 8;
                rem  = IP_INV[i] % 8;
                if(rem % 8 != 0)
                {
                        calc++;
                }
                calc--;
                if(rem != 0)
                {
                        byt  = (final[calc] >>  (BYTE_SIZE - rem)) & (BYTE_CHECK);
                }
                else
                {
                        byt  = (final[calc]) & (BYTE_CHECK);
                }
                cipher[j] = (cipher[j] | (byt << k));
                k--;
                if((i + 1) % 8 == 0)
                {
                        j++;
                        k = BYTE_SIZE - 1;
                }
                calc = 0;
                rem  = 0;
                byt  = 0;
        }
	/*for(i = 0; i < 8; i++)
	{
		printf("%02x  ", cipher[i] & 0xff);
	}*/

}
void desEncrypt(char *inp, int enc_flag, char *cipher, int type, int is_first)
{
	int i = 0;
	int j = 0;
	char inp_af_ip[BYTE_SIZE];
	char left[BYTE_SIZE / 2];
	char right[BYTE_SIZE / 2];
	char temp[BYTE_SIZE / 2];
	char expR[KEY_SIZE];
	char sVal[BYTE_SIZE / 2];
	char pVal[BYTE_SIZE / 2];
	char final[BYTE_SIZE];

	memset(inp_af_ip, 0, BYTE_SIZE);
	memset(left, 0, BYTE_SIZE / 2);
	memset(right, 0, BYTE_SIZE / 2);
	memset(expR, 0, KEY_SIZE);
	memset(sVal, 0, BYTE_SIZE / 2);
	memset(pVal, 0, BYTE_SIZE / 2);
	memset(temp, 0, BYTE_SIZE / 2);
	memset(final, 0, BYTE_SIZE);
	memset(cipher, 0, BYTE_SIZE);

	//initial permutation with IP
	shuffleWithIP(inp, inp_af_ip);

	//splitting input into L0 and R0
	for(i = 0; i < 4; i++)
	{
		left[i]  = inp_af_ip[i];
		right[i] = inp_af_ip[i + 4]; 
		temp[i]  = inp_af_ip[i + 4];
	}

	//repeating for fifteen rounds of DES
	for(j = 0; j <= DES_ROUNDS; j++)
	{
		if(is_first)
		{
			printRoundValues(left, right, j);
		}
		if(j == DES_ROUNDS)
		{
			break;
		}
		for(i = 0; i < 4; i++)
        	{
			temp[i] = right[i];
		}
		//expanding R0 to 48 bits - last parameter round to pick the key
		//TO DO: write it common for all rounds
		if(enc_flag == 1)
		{
			expandRightXOR(right, expR, j, type);
		}
		else
		{
			expandRightXOR(right, expR, (DES_ROUNDS - 1- j), type);
		}

		//compute S value from 48-bit to 32 bit
		computeSvalue(expR, sVal);

		permuteP(sVal, pVal);	

		//assigning the first left and right values
		for(i = 0; i < 4; i++)
		{
			right[i] = (pVal[i] ^ left[i]);
			left[i]  = temp[i];
	
		}
		memset(expR, 0, KEY_SIZE);
        	memset(sVal, 0, BYTE_SIZE / 2);
        	memset(pVal, 0, BYTE_SIZE / 2);
		
	}

	//clubbing the irregular swap into final
	for(i = 0; i < 4; i++)
	{
		final[i]     = right[i];
		final[i + 4] = left[i];
	}

	//permute final according to IP inverse
	permuteIPInverse(final, cipher);
	
	//printing final cipher value	
	/*for(i = 0; i < 8; i++)
        {
		if(enc_flag == 1)
		{
                	fprintf(stderr, "%02x", cipher[i] & 0xff);
		}
		else
		{
			fprintf(stderr, "%c", cipher[i]);
		}
		
        }*/
	if((type == DES) || ((enc_flag == 1) && (type == DES_3)) || ((enc_flag == 0) && (type == DES_1)))
	{
		fwrite(cipher, 1, BYTE_SIZE, stdout);
	}
}
void preprocessInput(int argc, char *argv[], int flag)
{
	
	char *token   = NULL;
        char *save    = NULL;
	char *key_str = NULL;
	char *inp_str = NULL;
	FILE *fp_t    = NULL;
	FILE *fp_i    = NULL;
	int n         = 0;
	int i         = 0;
	int is_first  = 1;
	int enc_flag  = flag;
	char cKey[BYTE_SIZE / 2];
        char dKey[BYTE_SIZE / 2];
	char cipher[BYTE_SIZE];
	char key_byt[BYTE_SIZE];
	
	memset(key_byt, 0, BYTE_SIZE);
	memset(cKey, 0, BYTE_SIZE / 2);
	memset(dKey, 0, BYTE_SIZE / 2);
	memset(cipher, 0, BYTE_SIZE);

	if(argc < 4)
	{
		fprintf(stderr, "\r\nerror: malformed command - usage: hw4 encrypt -k=key -t=tablefile [file]\r\n");
                fprintf(stderr, "                                  hw4 decrypt -k=key -t=tablefile [file]\r\n");
                exit(-1);
	}
	//parsing -k=key part
	token  = strtok_r(argv[2], "=", &save);
        if(!strlen(save))
        {
                fprintf(stderr, "\r\nerror: malformed command - usage: hw4 encrypt -k=key -t=tablefile [file]\r\n");
		fprintf(stderr, "                                  hw4 decrypt -k=key -t=tablefile [file]\r\n");
                exit(-1);
        }
        if(strcmp(token, "-k"))
        {
                fprintf(stderr, "\r\nerror: malformed command - usage: hw4 encrypt -k=key -t=tablefile [file]\r\n");
		fprintf(stderr, "                                  hw4 decrypt -k=key -t=tablefile [file]\r\n");
                exit(-1);
        }
	
	//converting key from string to hex and populate key_byt
	key_str = (char *)malloc(strlen(save) + 1);
	memset(key_str, 0, strlen(save) + 1);
	strcpy(key_str, save);

	if(strlen(key_str) != 16)
	{
		fprintf(stderr, "\r\nerror: malformed key - key must be 8 bytes in length\r\n");
		exit(-1);
	}
	for(i = 0; i < strlen(key_str); i++)
	{
		if(!((key_str[i] >= 97 && key_str[i] <= 122) || (key_str[i] >= 48 && key_str[i] <= 57)))
		{
			fprintf(stderr, "\r\nerror: malformed key - must contain only hexadecimal characters\r\n");
                	exit(-1);
		}
        }

	computeHex(key_str, key_byt);
	

	//parse -t=tablefile part
	token = NULL;
	save  = NULL;
	
	token  = strtok_r(argv[3], "=", &save);
        if(!strlen(save))
        {
                fprintf(stderr, "\r\nerror: malformed command - usage: hw4 encrypt -k=key -t=tablefile [file]\r\n");
		fprintf(stderr, "\r\n                                  hw4 decrypt -k=key -t=tablefile [file]\r\n");
                exit(-1);
        }
        if(strcmp(token, "-t"))
        {
                fprintf(stderr, "\r\nerror: malformed command - usage: hw4 encrypt -k=key -t=tablefile [file]\r\n");
		fprintf(stderr, "\r\n                                  hw4 decrypt -k=key -t=tablefile [file]\r\n");
                exit(-1);
        }
	fp_t = fopen(save, "r");
        if(!fp_t)
        {
                fprintf(stderr, "\r\nerror: %s %s\n", save, strerror(errno));
                exit(-1);
        }
        if(errno)
        {
                fprintf(stderr, "\r\nerror: %s %s\n", save, strerror(errno));
                exit(-1);
        }
	if(argc > 4)
	{
		fp_i = fopen(argv[4], "r");
	}
	else
	{
		fp_i = stdin;
	}
        if(!fp_i)
        {
                fprintf(stderr, "\r\nerror: %s %s\n", argv[4], strerror(errno));
                exit(-1);
        }
        if(errno)
        {
                fprintf(stderr, "\r\nerror: %s %s\n", argv[4], strerror(errno));
                exit(-1);
        }

	
	//get plain text from input file
	inp_str = (char *)malloc(BYTE_SIZE);
        memset(inp_str, 0, BYTE_SIZE);

	//validating the input des table
        validateTable(fp_t);

	//computing initial C0 and D0
        computeInitialC0D0(key_byt, cKey, dKey);

        //computing all 16 keys and storing in finalKey
        for(i = 0; i < DES_ROUNDS; i++)
        {
                computeKey(cKey, dKey, i, DES);
        }

	while(1)
        {
                n = 0;
                n = fread(inp_str, 1, BYTE_SIZE, fp_i);
		
                if(n == 0)
                {
			break;
                }
		//calling actual encrypt function for the first 8bytes
		desEncrypt(inp_str, enc_flag, cipher, DES, is_first);
		is_first = 0;
		memset(inp_str, 0, BYTE_SIZE);
	}
	
}
void preprocessTripleInput(int argc, char *argv[], int flag)
{
	char *token   = NULL;
        char *save    = NULL;
        char *key_str = NULL;
        char *inp_str = NULL;
        FILE *fp_t    = NULL;
        FILE *fp_i    = NULL;
        int n         = 0;
        int i         = 0;
	int k         = 0;
	int type      = 0;
        int enc_flag  = flag;
	int is_first  = 1;
        char cKey[BYTE_SIZE / 2];
        char dKey[BYTE_SIZE / 2];
	char cipher[BYTE_SIZE];
        char key_byt[BYTE_SIZE];

        memset(key_byt, 0, BYTE_SIZE);
        memset(cKey, 0, BYTE_SIZE / 2);
        memset(dKey, 0, BYTE_SIZE / 2);
	memset(cipher, 0, BYTE_SIZE);

	//converting key from string to hex and populate key_byt
        key_str = (char *)malloc(BYTE_SIZE * 2);
        memset(key_str, 0, BYTE_SIZE * 2);

	//parse -t=tablefile part
        token = NULL;
        save  = NULL;

        token  = strtok_r(argv[3], "=", &save);
        if(!strlen(save))
        {
                fprintf(stderr, "\r\nerror: malformed command - usage: hw4 encrypt3 -k=key -t=tablefile [file]\r\n");
		fprintf(stderr, "\r\n                                  hw4 decrypt3 -k=key -t=tablefile [file]\r\n");
                exit(-1);
        }
        if(strcmp(token, "-t"))
        {
                fprintf(stderr, "\r\nerror: malformed command - usage: hw4 encrypt3 -k=key -t=tablefile [file]\r\n");
		fprintf(stderr, "\r\n                                  hw4 decrypt3 -k=key -t=tablefile [file]\r\n");
                exit(-1);
        }
        fp_t = fopen(save, "r");
        if(!fp_t)
        {
                fprintf(stderr, "\r\nerror: %s %s\n", save, strerror(errno));
                exit(-1);
        }
        if(errno)
        {
                fprintf(stderr, "\r\nerror: %s %s\n", save, strerror(errno));
                exit(-1);
        }
        if(argc > 4)
        {
                fp_i = fopen(argv[4], "r");
        }
        else
        {
                fp_i = stdin;
        }
        if(!fp_i)
        {
                fprintf(stderr, "\r\nerror: %s %s\n", argv[4], strerror(errno));
                exit(-1);
	}
        if(errno)
        {
                fprintf(stderr, "\r\nerror: %s %s\n", argv[4], strerror(errno));
                exit(-1);
        }
	
	//parsing -k=key part
        token  = strtok_r(argv[2], "=", &save);
        if(!strlen(save))
        {
                fprintf(stderr, "\r\nerror: malformed command - usage: hw4 encrypt3 -k=key -t=tablefile [file]\r\n");
		fprintf(stderr, "\r\n                                  hw4 decrypt3 -k=key -t=tablefile [file]\r\n");
                exit(-1);
        }
        if(strcmp(token, "-k"))
        {
                fprintf(stderr, "\r\nerror: malformed command - usage: hw4 encrypt3 -k=key -t=tablefile [file]\r\n");
		fprintf(stderr, "\r\n                                  hw4 decrypt3 -k=key -t=tablefile [file]\r\n");
                exit(-1);
        }

	//validating the input des table
        validateTable(fp_t);

	if(strlen(save) != 48)
	{
		fprintf(stderr, "\r\nerror: malformed key - key must be 24 bytes in length\r\n");
                exit(-1);
	}
	while(k < 3)
	{
		strncpy(key_str, save, 16);
		for(i = 0; i < strlen(key_str); i++)
	        {
        	        if(!((key_str[i] >= 97 && key_str[i] <= 122) || (key_str[i] >= 48 && key_str[i] <= 57)))
                	{
                        	fprintf(stderr, "\r\nerror: malformed key - must contain only hexadecimal characters\r\n");
                        	exit(-1);
                	}
        	}
		computeHex(key_str, key_byt);
		if( k == 0)
		{
			type = DES_1;
		}
		else if(k == 1)
		{
			type = DES_2;
		}
		else
		{
			type = DES_3;
		}
		computeInitialC0D0(key_byt, cKey, dKey);

	        //computing all 16 keys and storing in finalKey
       		for(i = 0; i < DES_ROUNDS; i++)
        	{
                	computeKey(cKey, dKey, i, type);
        	}
		memset(key_str, 0, BYTE_SIZE * 2);
		memset(key_byt, 0, BYTE_SIZE);
		memset(cKey, 0, BYTE_SIZE / 2);
		memset(dKey, 0, BYTE_SIZE / 2);
		save = save + (BYTE_SIZE * 2);
		k++;
	}	
	//get plain text from input file
        inp_str = (char *)malloc(BYTE_SIZE);
        memset(inp_str, 0, BYTE_SIZE);
	while(1)
        {
                n = 0;
                n = fread(inp_str, 1, BYTE_SIZE, fp_i);
                if(n == 0)
                {
                        break;
                }
                //calling appropriate rounds depending encrypt3/decrypt3 flags
		if(enc_flag == 1)
		{
		
			//performing encryption with key 1 if encrypt3 is set
                	desEncrypt(inp_str, enc_flag, cipher, DES_1, is_first);
			memset(inp_str, 0, BYTE_SIZE);
			for(i = 0; i < BYTE_SIZE; i++)
			{
				inp_str[i] = cipher[i];
			}

			//performing decryption with key 2 if encrypt3 is set
			desEncrypt(inp_str, !enc_flag, cipher, DES_2, is_first);
                	memset(inp_str, 0, BYTE_SIZE);
                	for(i = 0; i < BYTE_SIZE; i++)
                	{
                        	inp_str[i] = cipher[i];
                	}
			
			//performing encryption with key 3 if encrypt3 is set
			desEncrypt(inp_str, enc_flag, cipher, DES_3, is_first);
		}
		else
		{
			//performing decryption with key 3 if decrypt3 is set
                        desEncrypt(inp_str, enc_flag, cipher, DES_3, is_first);
                        memset(inp_str, 0, BYTE_SIZE);
                        for(i = 0; i < BYTE_SIZE; i++)
                        {
                                inp_str[i] = cipher[i];
                        }

                        //performing encryption with key 2 if decrypt3 is set
                        desEncrypt(inp_str, !enc_flag, cipher, DES_2, is_first);
                        memset(inp_str, 0, BYTE_SIZE);
                        for(i = 0; i < BYTE_SIZE; i++)
                        {
                                inp_str[i] = cipher[i];
                        }

                        //performing decryption with key 1 if decrypt3 is set
                        desEncrypt(inp_str, enc_flag, cipher, DES_1, is_first);
		}
		is_first = 0;
                memset(inp_str, 0, BYTE_SIZE);
        }

}
