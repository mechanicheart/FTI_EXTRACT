#ifndef _FILE_OUTPUT
#define _FILE_OUTPUT

#include "stdafx.h"
#include "EXTRACT_LIB.h"

FILE *wp;

void Write_CHARBlock(FILE *fp , char c)
{
	char s[Max_Length];
	s[0] = c;
	fwrite(s , sizeof(char) , 1 , fp);
}
void Write_CHARBlock(FILE *fp , char c , int Address)
{
	if(JumptoAddress(fp , Address))
		Write_CHARBlock(fp , c);
}
void Write_INTBlock(FILE *fp , char s[])
{
	fwrite(s , sizeof(int) , 1 , fp);
}
void Write_INTBlock(FILE *fp , char s[] , int Address)
{
	if(JumptoAddress(fp , Address))
		Write_INTBlock(fp , s);
}
void Write_STRINGBlock(FILE *fp , char s[] , int Count)
{
	fwrite(s , 1 , Count , fp);
}
void Write_STRINGBlock(FILE *fp , char s[] , int Count , int Address)
{
	if(JumptoAddress(fp , Address))
		Write_STRINGBlock(fp , s , Count);
}

char *Output_NameGen(char *s)
{
	const char *FTI_AFFIX = ".fti";
	char p[Max_Length];
	strcpy(p , s);
	return strcat(p , FTI_AFFIX);
}

#endif