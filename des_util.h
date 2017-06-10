
#include <sys/types.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#define IP_TOTAL_SIZE 64
#define E_TOTAL_SIZE 48
#define P_TOTAL_SIZE 32
#define S_ROW_SIZE 4
#define S_COL_SIZE 16
#define PC1_TOTAL_SIZE 56
#define PC2_TOTAL_SIZE 48
#define PC1_SIZE 64
#define PC2_SIZE 56
#define S_COUNT 4
#define S_BOX_SHIFT 6
#define KEY_SIZE 6
#define S_SIZE  16
#define E_SIZE 48
#define V_SIZE 16
#define V1_COUNT 4
#define V2_COUNT 12
#define BYTE_SIZE 8
#define BUFF_SIZE 1024
#define TEMP_BUFF 25
#define IP_CHECK  0x00000001
#define P_CHECK 0x00000001
#define BYTE_CHECK 0x01
#define DES_ROUNDS 16
#define DES_1 1
#define DES_2 2
#define DES_3 3
#define DES    0

extern int IP[IP_TOTAL_SIZE];
extern int IP_INV[IP_TOTAL_SIZE];
extern int E[E_TOTAL_SIZE];
extern int P[P_TOTAL_SIZE];
extern int S1[S_ROW_SIZE][S_COL_SIZE];
extern int S2[S_ROW_SIZE][S_COL_SIZE];
extern int S3[S_ROW_SIZE][S_COL_SIZE];
extern int S4[S_ROW_SIZE][S_COL_SIZE];
extern int S5[S_ROW_SIZE][S_COL_SIZE];
extern int S6[S_ROW_SIZE][S_COL_SIZE];
extern int S7[S_ROW_SIZE][S_COL_SIZE];
extern int S8[S_ROW_SIZE][S_COL_SIZE];
extern int PC1[PC1_TOTAL_SIZE];
extern int PC2[PC2_TOTAL_SIZE];
extern int V[V_SIZE];
extern char finalKey[DES_ROUNDS][KEY_SIZE];
extern char finalKey3D1[DES_ROUNDS][KEY_SIZE];
extern char finalKey3D2[DES_ROUNDS][KEY_SIZE];
extern char finalKey3D3[DES_ROUNDS][KEY_SIZE];

extern void constructIPInverse();
extern void validateIP(char *buff);
extern void validateE(char *buff);
extern void validateP(char *buff);
extern void validateV(char *buff);
extern void validateS(char *buff, int k);
extern void validatePC1(char *buff);
extern void validatePC2(char *buff);
extern void validateTable(FILE *fp);
extern void computeHex(char *key_str, char *key_byt);
extern void shuffleWithIP(char *inp, char *inp_af_ip);
extern void computeInitialC0D0(char *key, char *cKey, char *dKey);
extern void computeKey(char *cKey, char *dKey, int round, int type);
extern void expandRightXOR(char *right, char *expR, int round, int type);
extern void computeSvalue(char *expR, char *sVal);
extern void permuteP(char *sVal, char *pVal);
extern void printRoundValues(char *left, char *right, int round);
extern void permuteIPInverse(char *final, char *cipher);
extern void desEncrypt(char *inp, int enc_flag, char *cipher, int type, int is_first);
extern void preprocessInput(int argc, char *argv[], int flag);
extern void preprocessTripleInput(int argc, char *argv[], int flag);
