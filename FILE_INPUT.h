#ifndef _FILE_INPUT
#define _FILE_INPUT

#include "stdafx.h"
#include "EXTRACT_LIB.h"

FILE *fp;

extern int Read_INTBlock(FILE *fp);
extern int Read_INTBlock(FILE *fp , int Address);

int Read_CHARBlock(FILE *fp)
{
	char s[1];
	fread(s , 1 , 1 , fp);
	return int(s[0]);
}
int Read_CHARBlock(FILE *fp , int Address)
{
	if(JumptoAddress(fp , Address))
		return Read_CHARBlock(fp);
	else return -1;
}
int Read_WORDBlock(FILE *fp)
{
	int lo = Read_CHARBlock(fp);
	int hi = Read_CHARBlock(fp);
	return WORDBlock_Code(lo , hi);
}
int Read_WORDBlock(FILE *fp , int Address)
{
	if(JumptoAddress(fp , Address))
		return Read_WORDBlock(fp);
	else return -1;
}
int Read_INTBlock(FILE *fp)
{
	char s[4];
	fread(s , 1 , 4 , fp);
	return CalcStringInt(s);
}
int Read_INTBlock(FILE *fp , int Address)
{
	if(JumptoAddress(fp , Address))
		return Read_INTBlock(fp);
	else return -1;
}
void Read_STRINGBlock(FILE *fp , char s[] , int Count)
{
	fread(s , 1 , Count , fp);
}
void Read_STRINGBlock(FILE *fp , char s[] , int Count , int Address)
{
	if(JumptoAddress(fp , Address))
		Read_STRINGBlock(fp , s , Count);
}

#endif