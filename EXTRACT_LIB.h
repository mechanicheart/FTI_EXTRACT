#ifndef _EXTRACT_LIB
#define _EXTRACT_LIB

#include "stdafx.h"

#define BASE_CODE 0x1000

extern int GetStringLength(char s[]);
extern int CalcStringInt(char s[]);
extern int WORDBlock_Code(int lo , int hi);
extern int WORDBlock_DecodeLow(int num);
extern int WORDBlock_DecodeHigh(int num);

bool JumptoAddress(FILE *fp , int Address)
{
	if(fseek(fp , Address , SEEK_SET) == 0)
		return 1;
	else return 0;
}

int GetStringLength(char s[])
{
	return strlen(s);
}
int CalcStringInt(char s[])
{
	int i , sum = 0;
	for(i = 3 ; i >= 0 ; i--)
	{
		unsigned char c = s[i];
		sum = int(c) + sum * 256;
	}
	//printf("%d\n",sum);
	return sum;
}

int WORDBlock_Code(int lo , int hi)
{
	return lo * BASE_CODE + hi;
}
int WORDBlock_DecodeLow(int num)
{
	return num / BASE_CODE;
}
int WORDBlock_DecodeHigh(int num)
{
	return num % BASE_CODE;
}

#endif
